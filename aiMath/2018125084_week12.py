# 인공지능기초수학
# 소프트웨어학과 2018125084 임예랑
# 20200608 12주차 실습

import numpy as np





# 1
array = np.array([2,7,5,1,9])
exp = np.arange(1,6)

print("1: ",end='')
print(array**exp)


# 2
a = np.arange(1,18,2)
a = a.reshape((3,3))
b = np.arange(1,4)
b = b.reshape((3,1))

print("2-1: ")
print(np.dot(a, b))
print("2-2: ")
print(a*b)

# 3
a = np.arange(1,91)
a = a.reshape((5,6,3))
a = a.sum(axis=1)
print("3: ")
print(a)


# 4
a = np.arange(0,31,10)
a = a.reshape((4,1))
b = np.arange(0,3)
print("4-1: ")
print(a+b)

a = np.arange(0,31,10)
a = np.array([a,a,a])
a = a.transpose()
b = np.arange(0,3)
print("4-2: ")
print(a+b)

a = np.arange(0,31,10)
a = np.array([a,a,a])
a = a.transpose()
b = np.arange(0,3)
b = np.array([b,b,b,b])
print("4-3: ")
print(a+b)

# 5
a = np.arange(1,271)
a = a.reshape((10,9,3))
a = a.transpose(2,0,1)
print("5: ")
print(a[0])