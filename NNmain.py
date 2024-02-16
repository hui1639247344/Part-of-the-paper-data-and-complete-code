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
flags.DEFINE_bool('train', True, 'True to train, False to test.')
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
NUM_TEST_POINTS = 3

def test(model, saver, sess, exp_string, data_read, test_num_updates=None):

    np.random.seed(1)
    rd.seed(1)

    metaval_accuracies = []

    for _ in range(NUM_TEST_POINTS):
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
        print(labelb)

        feed_dict = {model.inputa: inputa, model.inputb: inputb,  model.labela: labela, model.labelb: labelb, model.meta_lr: 0.0}

        tt = [model.total_loss1, model.total_losses2, model.outputbs]
        result_loss = sess.run(tt, feed_dict)
        ''' result = sess.run([model.total_loss1] +  model.total_losses2, feed_dict)
         metaval_accuracies.append(result)'''
        be_loss = []
        after_loss = []
        outputb = []
        be_loss.append(result_loss[0])
        after_loss.append(result_loss[1])
        outputb.append(result_loss[2])

    '''metaval_accuracies = np.array(metaval_accuracies)
    means = np.mean(metaval_accuracies, 0)
    stds = np.std(metaval_accuracies, 0)
    ci95 = 1.96*stds/np.sqrt(NUM_TEST_POINTS)'''

    print('Mean validation accuracy/loss, stddev, and confidence intervals')
    print(np.mean(be_loss))
    print(np.mean(after_loss))
    print(labelb)
    print(outputb)
    '''print((means, stds, ci95))'''

    '''out_filename = FLAGS.logdir +'/'+ exp_string + '/' + 'test_ubs' + str(FLAGS.update_batch_size) + '_stepsize' + str(FLAGS.update_lr) + '.csv'
    out_pkl = FLAGS.logdir +'/'+ exp_string + '/' + 'test_ubs' + str(FLAGS.update_batch_size) + '_stepsize' + str(FLAGS.update_lr) + '.pkl'
    with open(out_pkl, 'wb') as f:
        pickle.dump({'mses': metaval_accuracies}, f)
    with open(out_filename, 'w') as f:
        writer = csv.writer(f, delimiter=',')
        writer.writerow(['update'+str(i) for i in range(len(means))])
        writer.writerow(means)
        writer.writerow(stds)
        writer.writerow(ci95)'''


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
        data_read = Data(num_task=FLAGS.meta_batch_size, k=FLAGS.update_batch_size + 1, dim_input=5 , dim_output=2)


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
