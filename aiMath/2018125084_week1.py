# 인공지능기초수학
# 소프트웨어학과 2018125084 임예랑
# 20200317 1주차 실습

import numpy as np


# 1. 5-d data space가 있다. 이때 NumPy를 사용해서 이 space에서의 vector들을 정의하고 싶다. 다음의
# vector들을 생성하시오. (단, np.array(), np.full(), np.zeros(), np.ones(), np.arange() method
# 를 최소 한 번 사용할 것.)
# 1-a) (1, 1, 1, 1, 1)
# 1-b) (0, 0, 0, 0, 0)
# 1-c) (5, 5, ,5 ,5 ,5)
# 1-d) (1, 2, 3, 4, 5)
# 1-e) (1, 3, 5, 7, 9)
# 1-f ) (1, 5, 2, 3, 9)

# 1-a
print("1-a: ",end='')
print(np.ones(5))

# 1-b
print("1-b: ",end='')
print(np.zeros(5))

# 1-c
print("1-c: ",end='')
print(np.full(5,5))

# 1-d
print("1-d: ",end='')
print(np.arange(1,6))

# 1-e
print("1-e: ",end='')
print(np.arange(1,10,2))

# 1-f
print("1-f: ",end='')
print(np.array([1,5,2,3,9]))


# 2. 아래 주어진 vector 연산을 NumPy array를 사용하여 수행하고, 주어진 결과를 출력하도록 하는 code를
# 작성하시오.
# 2-a) (1, 2, 1, 5, 4) + (1, 2, 3, 4, 5)
# 출력: (2, 4, 4, 9, 9)
# 2-b) (1, 2, 3, 4, 5) + (5, 4, 3, 2, 1)
# 출력: (6, 6, 6, 6, 6)
# 2-c) (3, 3, 3, 3, 3, 3, 3, 3, 3) – (1, 1, 1, 1, 1, 1, 1, 1, 1)
# 출력: (2, 2, 2, 2, 2, 2, 2, 2, 2)
# 2-d) (4, 5, 6) – (3, 2, 1)
# 출력: (1, 3, 5)
# 2-e) 2*(1, 1, 1, 1)
# 출력: (2, 2, 2, 2)
# 2-f ) 3*(0, 4, 2, 3)
# 출력: (0, 12, 6, 9)
# 2-g) 1/2*(2, 4, 6, 8, 10)
# 출력: (1, 2, 3, 4, 5)

# 2-a
print("\n\n2-a: ",end='')
print(np.array([1,2,1,5,4]) + np.array([1,2,3,4,5]))

# 2-b
print("2-b: ",end='')
print(np.arange(1,6) + np.arange(5,0,-1))

# 2-c
print("2-c: ",end='')
print(np.full(9,3) - np.ones(9))

# 2-d
print("2-d: ",end='')
print(np.arange(4,7) - np.arange(3,0,-1))

# 2-e
print("2-e: ",end='')
print(2 * np.full(4,1))

# 2-f
print("2-f: ",end='')
print(3 * np.array([0,4,2,3]))

# 2-g
print("2-g: ",end='')
print((1/2) * np.arange(2,11,2))


# 3. 두 vector a = (1, 2, 3), b = (9, 8, 7)가 주어졌다.
# 3-a) NumPy를 사용하지 않고 python list로 vector a, b를 정의하고, 두 vector를 input으로 받아
#  dot product의 결과를 return 해주는 함수 DP를 작성한 후 DP를 사용하여 a, b의 dot product
#  값을 출력하시오.
# 3-b) NumPy array로 vector a, b를 정의한 후 dot product를 수행하는 code를 작성하고 그 결과값
# 을 출력하시오(단, code에 np.sum()을 반드시 사용할 것, for문 사용 금지)

a = [1, 2, 3]
b = [9, 8, 7]

# 3-a
def DP(a, b):
    result = 0
    for i in range(len(a)):
        result += a[i]*b[i]
    return result

print("\n\n3-a: ",end='')
print(DP(a, b))

# 3-b
npA = np.array(a)
npB = np.array(b)
print("3-b: ",end='')
print(np.sum(npA*npB))

# 4. NumPy array로 정의된 vector c = (6, 2, 4)가 있다. 하나의 vector를 input으로 받아 input vector의 size를
# return 해주는 함수 vec_size()를 code로 작성하고, vec_size()의 input으로 c를 넣었을 때의 return
# 값을 출력하시오. (단, for문 사용 금지)

# 4
c = np.array([6, 2, 4])

def vec_size(v):
    return np.sqrt(np.sum(v*v))
    # return np.linalg.norm(v)

print("\n\n4: ",end='')
print(round(vec_size(c),2))


# 5. 아래와 같이 3-d space에서 정의된 coordinate a, b의 basis vector들과 coordinate a에서 (6, 4, 2)의 값을
# 가진 r_a vector가 주어졌다. (모든 vector는 NumPy array로 정의, 결과는 소수점 두번째 자리 까지 출력,
# for문 사용금지)
# # a coordinate
# 𝑎𝑥 = (1, 0, 0)
# 𝑎𝑦 = (0, 1, 0)
# 𝑎𝑧 = (0, 0, 1)
# # b coordinate
# 𝑏𝑥 = (-2, 1, 4)
# 𝑏𝑦 = (1, 2, 0)
# 𝑏𝑧 = (2, -1, 1.25)
# 5-a) ax∙ ay, ax∙ az, ay ∙ az, ax∙ ax 값을 출력하시오.
# 5-b) bx∙ by, bx∙ bz, by ∙ bz, 𝑏𝑥 ∙ bx를 값을 출력하시오.
# 5-c) coordinate a에서의 (6, 4, 2) vector가 coordinate b에서 어떻게 표현되는지 출력하시오.
# 5-d) coordinate a에서의 (1, 0, 0) vector가 coordinate b에서 어떻게 표현되는지 출력하시오.
# 5-e) coordinate a에서의 (2, 2, 2) vector가 coordinate b에서 어떻게 표현되는지 출력하시오.
# 5-f ) coordinate b에서의 (1, 2, 3) vector가 coordinate a에서 어떻게 표현되는지 출력하시오.
# 5-g) coordinate b에서의 (4, 1, 7) vector가 coordinate a에서 어떻게 표현되는지 출력하시오.
# 5-h) coordinate b에서의 (0, -1, 2) vector가 coordinate a에서 어떻게 표현되는지 출력하시오.

ax = np.array([1, 0, 0])
ay = np.array([0, 1, 0])
az = np.array([0, 0, 1])

bx = np.array([-2, 1, 4])
by = np.array([1, 2, 0])
bz = np.array([2, -1, 1.25])

# 5-a
print("\n\n5-a: ", end='')
print(np.sum(ax*ay), end=' ')
print(np.sum(ax*az), end=' ')
print(np.sum(ay*az), end=' ')
print(np.sum(ax*ax))

# 5-b
print("5-b: ", end='')
print(np.sum(bx*by), end=' ')
print(np.sum(bx*bz), end=' ')
print(np.sum(by*bz), end=' ')
print(np.sum(bx*bx))

# 5-c
a_vector = np.array([6, 4, 2])
a_b_vectorx = np.sum(a_vector*bx)/np.linalg.norm(bx)**2
a_b_vectory = np.sum(a_vector*by)/np.linalg.norm(by)**2
a_b_vectorz = np.sum(a_vector*bz)/np.linalg.norm(bz)**2
print("5-c: ", end='')
print(np.array([a_b_vectorx, a_b_vectory, a_b_vectorz]))

# 5-d
a_vector = np.array([1, 0, 0])
a_b_vectorx = np.sum(a_vector*bx)/np.linalg.norm(bx)**2
a_b_vectory = np.sum(a_vector*by)/np.linalg.norm(by)**2
a_b_vectorz = np.sum(a_vector*bz)/np.linalg.norm(bz)**2
print("5-d: ", end='')
print(np.array([round(a_b_vectorx,2), round(a_b_vectory,2), round(a_b_vectorz,2)]))

# 5-e
a_vector = np.array([2, 2, 2])
a_b_vectorx = np.sum(a_vector*bx)/np.linalg.norm(bx)**2
a_b_vectory = np.sum(a_vector*by)/np.linalg.norm(by)**2
a_b_vectorz = np.sum(a_vector*bz)/np.linalg.norm(bz)**2
print("5-e: ", end='')
print(np.array([round(a_b_vectorx,2), round(a_b_vectory,2), round(a_b_vectorz,2)]))

# 5-f
b_vector = np.array([1, 2, 3])
b_a_vectorx = b_vector[0] * bx
b_a_vectory = b_vector[1] * by
b_a_vectorz = b_vector[2] * bz
print("5-f: ", end='')
print(np.array(b_a_vectorx + b_a_vectory + b_a_vectorz))

# 5-g
b_vector = np.array([4, 1, 7])
b_a_vectorx = b_vector[0] * bx
b_a_vectory = b_vector[1] * by
b_a_vectorz = b_vector[2] * bz
print("5-g: ", end='')
print(np.array(b_a_vectorx + b_a_vectory + b_a_vectorz))

# 5-h
b_vector = np.array([0, -1, 2])
b_a_vectorx = b_vector[0] * bx
b_a_vectory = b_vector[1] * by
b_a_vectorz = b_vector[2] * bz
print("5-h: ", end='')
print(np.array(b_a_vectorx + b_a_vectory + b_a_vectorz))