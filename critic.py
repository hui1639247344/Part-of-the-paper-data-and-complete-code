import pandas as pd
import numpy as np

#导入数据
data=pd.read_excel('critic_input.xlsx')

#数据标准化处理
label_need=data.keys()[1:]
print(label_need)
data1=data[label_need].values
data2=data1.copy()
[m,n]=data2.shape
index_all=np.arange(n)
index=[1] #正向指标位置,注意python是从0开始计数，对应位置也要相应减1
#正向指标
for j in index:
    d_max = max(data1[:, j])
    d_min = min(data1[:, j])
    data2[:, j] = (data1[:, j] - d_min) / (d_max - d_min)
#负向指标
index=np.delete(index_all,index)
for j in index:
    d_max=max(data1[:,j])
    d_min=min(data1[:,j])
    data2[:,j]=(d_max-data1[:,j])/(d_max-d_min)

#对比性
the=np.std(data2,axis=0)
data3=data2.copy()
#矛盾性
data3=list(map(list,zip(*data2))) #矩阵转置
r=np.corrcoef(data3)   #求皮尔逊相关系数
f=np.sum(1-r,axis=1)
#信息承载量
c=the*f

w=c/sum(c)  #计算权重
print(w)