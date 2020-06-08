# 인공지능기초수학
# 소프트웨어학과 2018125084 임예랑
# 20200601 11주차 실습

import numpy as np


#Array는 8, 16, 8 의 shape 을 가진다 1 에서 1024 까지의 수를 가진 1d array 를 만들고
# np.reshape 을 사용하여 [8, 16, 8] 의 shape 을 가진 array 로 변환하시오
# 1.1. 노란색 에 해당하는 부분 출력
# 1.2. 초록색 에 해당하는 부분 출력
# 1.3. 회색 에 해당하는 부분 출력

array = np.arange(1024)
newshape = (8, 16, 8)
array = np.reshape(array, newshape)

# 1-1
print("1-1: ",end='')
print(array[1, ::2, 0])

# 1-2
print("1-2: ",end='')
print(array[3, 15, ::2])

# 1-3
print("1-3: ",end='')
print(array[6:, :5, 0])
print("\n")

# 2.1. Normal distribution 에서 sampling 한 수들을 element 로 하고 shape 이 [20,20] 인 array
# a를 생성하고 출력 하시오

# 2.2. Array a 에서 짝수 행 열에 해당하는 원소 를 array b 라고 한다 Array b 첫번째 행의 원
# 소를 10 으로 바꾸고 array a, b 를 출력했을 때 array a 의 값이 바뀌지 않도록 array b 를
# 선언하고 b 모든 원소의 값 을 10 으로 바꾼 후 a, b 를 출력 하시오

# 2- 1
a = np.random.randn(400)
newshape = (20, 20)
a = np.reshape(a, newshape)
print("2-1: ",end='')
print(a)

# 2- 2
b = a[::2, ::2].copy()
b[::, ::] = 10
print("2-2: ",end='')
print(a)
print(b)
print("\n")


# 3.1. Normal distribution에서 sampling 한 수들을 element 로 하고 shape 이 [10 , 10] 인 array
# a를 생성하 고 element 값이 0.5 보다 크면 1, 0.5 미만이면 0 의 값을 가지도록 mask 를
# 사용해서 만들고 출력 하시오
# 3.2. 1 부터 25 의 값 을 가지는 1d array 를 만들고 np.reshape 을 사용해서 [5,5] 의 shape 을
# 가지도록 array 를 생성하고 아래 그림에 파란색으로 표시된 부분을 출력하시오
# 3.3. 위 그림에서 빨간색으로 표시된 부분을 출력하시오

# 3- 1
a = np.random.randn(100)
newshape = (10, 10)
a = np.reshape(a, newshape)
mask1 = (a > 0.5)
mask2 = (a < 0.5)
a[mask1] = 1
a[mask2] = 0

print("3-1: ",end='')
print(a)


# 3- 2
a = np.arange(1,26)
newshape = (5, 5)
a = np.reshape(a, newshape)
print("3-2: ",end='')
print(a[(0,1,2,3,4), (0,1,2,3,4)])

# 3- 3
print("3-2: ",end='')
print(a[3, (0,2,4)])