import csv
import numpy as np
import pickle
import random as rd
import tensorflow as tf
from data import Data
from NNmaml import MAML
from tensorflow import flags
import pandas as pd
from scipy.special import gamma
from math import e

FLAGS = flags.FLAGS

# Dataset/method options  # 数据集/方法 选项设置
flags.DEFINE_string('datasource', 'sinusoid', 'sinusoid or omniglot or miniimagenet')
# 感觉这一项在回归模型中用不到
flags.DEFINE_integer('num_classes', 5, 'number of classes used in classification (e.g. 5-way classification).')
# oracle means task id is input (only suitable for sinusoid)  # oracle 表示任务id是输入（仅适用于sinusoid数据集）
flags.DEFINE_string('baseline', 'None', 'oracle, or None')

# Training options # 训练选项设置
# 预训练迭代次数设置
flags.DEFINE_integer('pretrain_iterations', 0, 'number of pre-training iterations.')
# 元训练迭代次数设置，15k for omniglot, 50k for sinusoid
flags.DEFINE_integer('metatrain_iterations', 70000, 'number of metatraining iterations.')
# 每次元更新采样的任务数设置
flags.DEFINE_integer('meta_batch_size', 5, 'number of tasks sampled per meta-update')
# 生成器的基本学习率设置
flags.DEFINE_float('meta_lr', 0.001, 'the base learning rate of the generator')
# 用于内部梯度更新的示例数(K表示K-shot学习)设置
flags.DEFINE_integer('update_batch_size', 7, 'number of examples used for inner gradient update (K for K-shot learning).')
# 步长alpha设置，用于内部梯度更新. 0.1 for omniglot
flags.DEFINE_float('update_lr', 0.001, 'step size alpha for inner gradient update.')
# 训练期间内部梯度更新的数量设置
flags.DEFINE_integer('num_updates', 1, 'number of inner gradient updates during training.')

# Model options # 模型选项设置
flags.DEFINE_string('norm', 'None', 'batch_norm, layer_norm, or None')
# conv网的过滤器数量设置？
flags.DEFINE_integer('num_filters', 64, 'number of filters for conv nets -- 32 for miniimagenet, 64 for omiglot.')
# 是否使用卷积网络，仅适用于某些情况？
flags.DEFINE_bool('conv', False, 'whether or not to use a convolutional network, only applicable in some cases')
# 是否使用最大池，而不是跨步卷积？
flags.DEFINE_bool('max_pool', False, 'Whether or not to use max pooling rather than strided convolutions')
# 如果为True，不要在元优化中使用二阶导数(为了速度)
flags.DEFINE_bool('stop_grad', False, 'if True, do not use second derivatives in meta-optimization (for speed)')

# Logging, saving, and testing options # 记录、保存和测试选项
# 如果为False，不记录摘要，用于调试代码
flags.DEFINE_bool('log', True, 'if false, do not log summaries, for debugging code.')
# 目录的摘要和检查点设置？
flags.DEFINE_string('logdir', 'logs/sine/', 'directory for summaries and checkpoints.')
# 若有可用的训练模型，恢复训练？
flags.DEFINE_bool('resume', False, 'resume training if there is a model available')
# True为训练，False为测试?
flags.DEFINE_bool('train', False, 'True to train, False to test.')
# 迭代加载模型(-1表示最新模型)?
flags.DEFINE_integer('test_iter', -1, 'iteration to load model (-1 for latest model)')
# True为在测试集上进行测试，False为在验证集上测试?
flags.DEFINE_bool('test_set', False, 'Set to true to test on the the test set, False for the validation set.')
# 在训练期间用于梯度更新的示例数量(如果您想使用不同的数量进行测试，请使用)?
flags.DEFINE_integer('train_update_batch_size', -1, 'number of examples used for gradient update during training (use if you want to test with a different number).')
# 训练时的内梯度阶跃值。(如果您想测试不同的值，请使用） # 0.1 for omniglot
flags.DEFINE_float('train_update_lr', -1, 'value of inner gradient step step during training. (use if you want to test with a different value)')


def train(model, saver, sess, exp_string, data_read, resume_itr=0):
    SUMMARY_INTERVAL = 100
    SAVE_INTERVAL = 1000
    if FLAGS.datasource == 'sinusoid':
        PRINT_INTERVAL = 1000
        TEST_PRINT_INTERVAL = PRINT_INTERVAL*5

    if FLAGS.log:
        train_writer = tf.summary.FileWriter(FLAGS.logdir + '/' + exp_string, sess.graph)
    print('Done initializing, starting training.')
    prelosses, postlosses = [], []

    for itr in range(resume_itr, FLAGS.pretrain_iterations + FLAGS.metatrain_iterations):
        batch_x, batch_y = data_read.read()

        inputa = batch_x[:, :FLAGS.update_batch_size, :]
        labela = batch_y[:, :FLAGS.update_batch_size, :]
        inputb = batch_x[:, FLAGS.update_batch_size:, :]  # b 用于测试，因此在读入数据时K *2
        labelb = batch_y[:, FLAGS.update_batch_size:, :]
        feed_dict = {model.inputa: inputa, model.inputb: inputb,  model.labela: labela, model.labelb: labelb}

        if itr < FLAGS.pretrain_iterations:
            input_tensors = [model.pretrain_op]
        else:
            input_tensors = [model.metatrain_op]

        if (itr % SUMMARY_INTERVAL == 0 or itr % PRINT_INTERVAL == 0):
            input_tensors.extend([model.summ_op, model.total_loss1, model.total_losses2[FLAGS.num_updates-1]])

        result = sess.run(input_tensors, feed_dict)

        if itr % SUMMARY_INTERVAL == 0:
            prelosses.append(result[-2])
            if FLAGS.log:
                train_writer.add_summary(result[1], itr)
            postlosses.append(result[-1])

        if (itr != 0) and itr % PRINT_INTERVAL == 0:
            if itr < FLAGS.pretrain_iterations:
                print_str = 'Pretrain Iteration ' + str(itr)
            else:
                print_str = 'Iteration ' + str(itr - FLAGS.pretrain_iterations)
            print_str += ': ' + str(np.mean(prelosses)) + ', ' + str(np.mean(postlosses))
            print(print_str)
            prelosses, postlosses = [], []

        if (itr != 0) and itr % SAVE_INTERVAL == 0:
            saver.save(sess, FLAGS.logdir + '/' + exp_string + '/model' + str(itr))

    saver.save(sess, FLAGS.logdir + '/' + exp_string +  '/model' + str(itr))


# calculated for omniglot #计算omniglot
NUM_TEST_POINTS = 1


def test(model, saver, sess, exp_string, data_read, test_num_updates=None):
    def pareto(food_new, paretoset, pareto_no, n, minormax):
        if len(paretoset) >= pareto_no:
            paretoset_cal = np.copy(paretoset)
            paretoset_cal = np.vstack((paretoset_cal, food_new))
            paretoset_value = np.copy(paretoset_cal[:, -n:])
            for i in range(n):
                if minormax[i] == 1:
                    paretoset_value[:, i] = paretoset_value[:, i] * -1  # 根据优化目标求min or max来给优化值取相反数，变为求min
            for j in range(n):
                min = np.min(paretoset_value[:, j])
                max = np.max(paretoset_value[:, j])
                for i in range(pareto_no + 1):
                    paretoset_value[i, j] = (paretoset_value[i, j] - min) / ((max - min) + 0.0000000000000000001)

            score = np.sum(paretoset_value, axis=1)
            s_min = np.min(score)
            s_max = np.max(score)
            s_min_index = list(score).index(s_min)  # 这里可能要进一步考虑有多个最优或最差个体的情况
            s_max_index = list(score).index(s_max)

            # food = paretoset[s_min_index, :]
            # enemy = paretoset_value[s_max_index, :]

            paretoset = np.delete(paretoset_cal, s_max_index, axis=0)  # 删除最差pareto解

        else:
            paretoset = np.vstack((paretoset, food_new))  # 将本轮最优个体存入帕累托解集
        food = np.copy(paretoset[rd.randint(0, len(paretoset) - 1)])
        food_cal = food.reshape(1, 7)
        return paretoset, food_cal


    np.random.seed(1)
    rd.seed(1)

    test_data = np.array(pd.read_csv('test.csv'))
    test_input = np.array([])
    test_label = np.array([])

    # 打乱
    np.random.shuffle(test_data)
    # 取前k行，相当于随机去k个样本了
    data_k = test_data[0: FLAGS.update_batch_size + 1]
    # 拆分为输入与标签
    input_k = data_k[:, :-2]
    label_k = data_k[:, -2:].reshape(FLAGS.update_batch_size + 1, 2)
    # 按任务存入数组
    test_input = np.append(test_input, input_k)
    test_label = np.append(test_label, label_k)
    test_input = test_input.reshape(1, FLAGS.update_batch_size + 1, 5)  # dim_input
    test_label = test_label.reshape(1, FLAGS.update_batch_size + 1, 2)  # dim_output

    inputa = test_input[:, :FLAGS.update_batch_size, :]
    labela = test_label[:, :FLAGS.update_batch_size, :]
    inputb = test_input[:, FLAGS.update_batch_size:, :]  # b 用于测试，因此在读入数据时K *2
    labelb = test_label[:, FLAGS.update_batch_size:, :]

    # 待优化问题
    def target(list):
        for _ in range(NUM_TEST_POINTS):
            for i in range(len(list)):
                inputb[0, 0, i] = list[i]

            feed_dict = {model.inputa: inputa, model.inputb: inputb, model.labela: labela, model.meta_lr: 0.0}

            tt = [model.outputbs]
            result_loss = sess.run(tt, feed_dict)
            outputb = []
            outputb.append(result_loss)

        y1 = outputb[0][0][0][0][0][0]
        y2 = outputb[0][0][0][0][0][1]

        '''单目标优化就return一个'''
        return y2

    # 初始化种群
    def initialization(size, ub, lb, n, dim, target=target):
        position = np.zeros((size, (dim + n)))
        for i in range(size):
            for j in range(dim):
                position[i, j] = rd.uniform(lb[j], ub[j])  # 初始化位置
            for k in range(1, n + 1):
                '''单目标时去掉[-k]'''
                position[i, -k] = target(position[i, :-n])  # 计算适应度值
        return position

    def rank(X, n, minormax):
        V = np.copy(X[:, -n:])
        for i in range(n):
            if minormax[i] == 1:
                V[:, i] = V[:, i] * -1  # 根据优化目标求min or max来给优化值取相反数，变为求min

        for j in range(n):
            min = np.min(V[:, j])
            max = np.max(V[:, j])
            for i in range(size):
                V[i, j] = (V[i, j] - min) / ((max - min) + 0.0000000000000000001)

        score = np.sum(V, axis=1)
        s_min = np.min(score)
        s_max = np.max(score)
        s_min_index = list(score).index(s_min)  # 这里可能要进一步考虑有多个最优或最差个体的情况
        s_max_index = list(score).index(s_max)

        food = X[s_min_index, :]
        enemy = X[s_max_index, :]

        return food

    def pareto(food_new, paretoset, pareto_no, n, minormax):
        if len(paretoset) >= pareto_no:
            paretoset_cal = np.copy(paretoset)
            paretoset_cal = np.vstack((paretoset_cal, food_new))
            paretoset_value = np.copy(paretoset_cal[:, -n:])
            for i in range(n):
                if minormax[i] == 1:
                    paretoset_value[:, i] = paretoset_value[:, i] * -1  # 根据优化目标求min or max来给优化值取相反数，变为求min
            for j in range(n):
                min = np.min(paretoset_value[:, j])
                max = np.max(paretoset_value[:, j])
                for i in range(pareto_no + 1):
                    paretoset_value[i, j] = (paretoset_value[i, j] - min) / ((max - min) + 0.0000000000000000001)

            score = np.sum(paretoset_value, axis=1)
            s_min = np.min(score)
            s_max = np.max(score)
            s_min_index = list(score).index(s_min)  # 这里可能要进一步考虑有多个最优或最差个体的情况
            s_max_index = list(score).index(s_max)

            # food = paretoset[s_min_index, :]
            # enemy = paretoset_value[s_max_index, :]

            paretoset = np.delete(paretoset_cal, s_max_index, axis=0)  # 删除最差pareto解

        else:
            paretoset = np.vstack((paretoset, food_new))  # 将本轮最优个体存入帕累托解集
        food = paretoset[rd.randint(0, len(paretoset) - 1), :]
        food_cal = food[:-n]
        return paretoset, food_cal

    def SOA(size, dim, ub, lb, generations, n, minormax, pareto_no):
        paretoset = np.zeros((0, (dim + n)))
        X = initialization(size, ub, lb, n, dim)
        food = rank(X, n, minormax)

        fc = 2
        Cs = np.zeros((size, dim))
        Ms = np.zeros((size, dim))
        Ds = np.zeros((size, dim))
        X_cal = np.copy(X[:, :-n])
        food_cal = np.copy(food[:-n])

        for t in range(generations):
            print('第', t + 1, '次迭代')
            for i in range(size):
                A = fc - (t * (fc / generations))
                Cs[i, :] = X_cal[i, :] * A

                rd = np.random.rand(1, dim)
                B = 2 * A ** 2 * rd
                Ms[i, :] = np.multiply(B, (food_cal - X_cal[i, :]))

                Ds[i, :] = np.abs(Cs[i, :] + Ms[i, :])

                u = 1
                v = 1
                theta = np.random.rand(1, dim)
                r = u * e ** (theta * v)
                x = r * np.cos(theta * 2 * np.pi)
                y = r * np.sin(theta * 2 * np.pi)
                z = r * theta

                X_new = x * y * z * Ds[i, :] + X_cal

            for i in range(size):  # 边界控制
                for j in range(dim):
                    if (X_new[i, j]) > ub[j]:
                        X_new[i, j] = ub[j]
                    if (X_new[i, j]) < lb[j]:
                        X_new[i, j] = lb[j]
            fitness = np.zeros((size, n))
            for i in range(size):
                fitness[i, :] = target(X_new[i, :])
            X_new = np.hstack((X_new, fitness))
            food_new = rank(X_new, n, minormax)
            print(food_new)
            paretoset, food_cal = pareto(food_new, paretoset, pareto_no, n, minormax)
        print(paretoset)
        return paretoset


    size = 40  # 种群数
    dim = 5  # 特征维数
    ub = [0.094, 1, 1, 1, 1]  # 搜索空间上界
    lb = [0.094, 0, 0, 0, 0]  # 搜索空间下界
    generations = 500  # 迭代次数
    n = 1  # 优化目标数
    '''单目标优化下行也要调整，0:min, 1:max'''
    minormax = [1]
    pareto_no = 30
    r = SOA(size, dim, ub, lb, generations, n, minormax, pareto_no)
    r = np.max(np.array(r)[:, -1:])
    print(r)
    '''r = np.array(r)
    data0 = np.array(pd.read_csv('data.csv'))
    max = []
    min = []
    for i in range(data0.shape[1]):
        max.append(np.max(data0[:, i]))
        min.append(np.min(data0[:, i]))
    max = np.array(max)
    min = np.array(min)
    delta = max - min
    r = r * delta + min
    print("--------------------------------------------------------------------------------------------")
    print(r)
    r = np.mean(r, axis=0)
    print(r)'''





def main():
    # 判断数据集类型，应该只需要保留sinusoid部分
    if FLAGS.datasource == 'sinusoid':
        if FLAGS.train:
            test_num_updates = 5
        else:
            test_num_updates = 1

    if FLAGS.train == False:
        orig_meta_batch_size = FLAGS.meta_batch_size
        # always use meta batch size of 1 when testing.
        FLAGS.meta_batch_size = 1

    if FLAGS.datasource == 'sinusoid':
        data_read = Data(num_task=FLAGS.meta_batch_size, k=FLAGS.update_batch_size + 1, dim_input=5, dim_output=2)


    dim_output = data_read.dim_output
    if FLAGS.baseline == 'oracle':
        assert FLAGS.datasource == 'sinusoid'
        dim_input = 3
        FLAGS.pretrain_iterations += FLAGS.metatrain_iterations
        FLAGS.metatrain_iterations = 0
    else:
        dim_input = data_read.dim_input


    tf_data_load = False
    input_tensors = None

    model = MAML(dim_input, dim_output, test_num_updates=test_num_updates)
    if FLAGS.train or not tf_data_load:
        model.construct_model(input_tensors=input_tensors, prefix='metatrain_')
    model.summ_op = tf.summary.merge_all()

    saver = loader = tf.train.Saver(tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES), max_to_keep=10)

    sess = tf.InteractiveSession()

    if FLAGS.train == False:
        # change to original meta batch size when loading model.
        FLAGS.meta_batch_size = orig_meta_batch_size

    if FLAGS.train_update_batch_size == -1:
        FLAGS.train_update_batch_size = FLAGS.update_batch_size
    if FLAGS.train_update_lr == -1:
        FLAGS.train_update_lr = FLAGS.update_lr

    exp_string = 'cls_'+str(FLAGS.num_classes)+'.mbs_'+str(FLAGS.meta_batch_size) + '.ubs_' + str(FLAGS.train_update_batch_size) + '.numstep' + str(FLAGS.num_updates) + '.updatelr' + str(FLAGS.train_update_lr)

    if FLAGS.num_filters != 64:
        exp_string += 'hidden' + str(FLAGS.num_filters)
    if FLAGS.max_pool:
        exp_string += 'maxpool'
    if FLAGS.stop_grad:
        exp_string += 'stopgrad'
    if FLAGS.baseline:
        exp_string += FLAGS.baseline
    if FLAGS.norm == 'batch_norm':
        exp_string += 'batchnorm'
    elif FLAGS.norm == 'layer_norm':
        exp_string += 'layernorm'
    elif FLAGS.norm == 'None':
        exp_string += 'nonorm'
    else:
        print('Norm setting not recognized.')

    resume_itr = 0
    model_file = None

    tf.global_variables_initializer().run()
    tf.train.start_queue_runners()

    if FLAGS.resume or not FLAGS.train:
        model_file = tf.train.latest_checkpoint(FLAGS.logdir + '/' + exp_string)
        if FLAGS.test_iter > 0:
            model_file = model_file[:model_file.index('model')] + 'model' + str(FLAGS.test_iter)
        if model_file:
            ind1 = model_file.index('model')
            resume_itr = int(model_file[ind1+5:])
            print("Restoring model weights from " + model_file)
            saver.restore(sess, model_file)

    if FLAGS.train:
        train(model, saver, sess, exp_string, data_read, resume_itr)
    else:
        test(model, saver, sess, exp_string, data_read, test_num_updates)


if __name__ == "__main__":
    main()
