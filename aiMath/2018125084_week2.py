# 인공지능기초수학
# 소프트웨어학과 2018125084 임예랑
# 20200324 2주차 실습

import numpy as np


# 1. 이 문제는 numpy array 의 indexing 과 기본 연산에 대한 문제이다
# Matrix A가 아래와 같이 주어졌다 그리고 이 matrix 를 아래와 같이 정의한다 
# 𝐴=[2 5 1       𝐵=[3 5 1
#    8 0 4          0 9 4
#    6 2 9],        12 8 6]
# 이 문제에서는 for 문을 사용하지 말 것
# 1a) Matrix A의 shape 를 출력하시오
# 1b) Matrix A에서 각 row 들 을 합한 결과를 출력하시오
# 1c) Matrix A에서 각 column 들 을 합한 결과를 출력하시오
# 1d) Matrix A의 row vector 들을 출력하시오
# 1e) Matrix A의 column vector 들을 출력하시오
# 1f) Matrix A, B matrix multiplication 결과를 출력하시오
# 1g) Matrix A, B를 element-wise 곱의 결과를 출력하시오

A = np.array(([2,5,1],
[8,0,4],
[6,2,9]))
B = np.array(([3,5,1],
[0,9,4],
[12,8,6]))

# 1-a
print("1-a: ",end='')
print(np.shape(A))

# 1-b
print("1-b: ",end='')
print(np.sum(A, axis=0))

# 1-c
print("1-c: ",end='')
print(np.sum(A, axis=1))

# 1-d
print("1-d: ",end='')
print(A[0], A[1], A[2])

# 1-e
At = np.transpose(A)
print("1-e: ",end='')
print(At[0], At[1], At[2])

# 1-f
print("1-f: ")
print(np.matmul(A,B))

# 1-g
print("1-g: ")
print(A*B)



# 2. 아래와 같이 matrix A 와 vector x 가 주어졌다 (matrix 와 vector 는 모두 NumPy array로 정의
# for 문 사용금지)
# 𝐴=[2 5 1     x=[1
#    8 0 4        2
#    6 2 9],      3]
# 2a) A의 모든 element에 2를 곱한 결과를 아래와 같이 출력하시오
# [4 10 2
#  16 0 8
#  12 4 18]
# 2b) A에서의 column vector 들을 각각 a1, a2, a3 라고 하자 이때 [a1 2*a2 3*a3] 인 matrix 를 아래와 같이 출력하시오
# [2 10 3
#  8  0 12
#  6  4 27]
# 2c) A에서의 row vector 들을 각각 a1, a2, a3 라고 하자 이때 [1∗𝑎1 인 matrix를 아래와 같이 출력하시오
#                                                           2∗𝑎2
#                                                           3∗𝑎3]
#  [2  5 1
#   16 0 8
#   18 6 27]
# 2d) vector x를 가지고 transformation A 를 진행했을 때 vector x를 transform 해주는 함수 trans(A , x)를
# 작성하고 그 값을 출력하시오 단 a, b 가 vector 일 때 a.dot(b) 와 for loop 을 사용 할 것
# 2e) vector x를 가지고 transformation A 를 진행했을 때 vector x 가 어떻게 transform 되는지를 출력하시
# 오 단 for 문 사용 금지

A = np.array(([2,5,1],
[8,0,4],
[6,2,9]))
x = np.array([1, 2, 3])

# 2-a
print("\n\n2-a: ")
print(2*A)

# 2-b
print("2-b: ")
print(A*np.array([1,2,3]))

# 2-c
print("2-c: ")
print(A*np.array(([1],[2],[3])))

# 2-d
print("2-d: ",end='')
def trans(A, x):
    size = np.shape(A)[0]
    result = []
    for i in range(size):
        result.append(A[i].dot(x))
    return result
print(trans(A,x))

# 2-e
print("2-e: ",end='')
print(np.matmul(A,x))




# 3. 아래와 같이 matrix A, B가 주어졌다 두 matrix 는 numpy array 로 정의
# 𝐴=[6 7 3      𝐵=[2 2  1
#    0 1 5         8 3  4
#    6 2 1],       9 12 9]
# 3a) 두 matrix 의 각 element 들에 대한 곱셈을 하고자 한다 아래와 같은 결과를 출력하시오 단 for 문 사용 금지
# 𝐴𝐵=[12 14  3
#      0  3 20
#     54 24  9]
# 3b) transform A 를 하고 난 후 transform B 를 할 때 transform combination matrix 를 출력하는 함수
# trans_comb(A, B) 를 작성하고 그 값을 출력하시오 단 a, b 가 vector 일 때 a.dot(b) 와 for 문 을 사용 할 것
# 3c) transform A 를 하고 난 후 transform B 를 할 때 transform combination matrix 를 출력하시오 단 for 문 사용 금지

A = np.array(([6,7,3],
[0,1,5],
[6,2,1]))
B = np.array(([2,2,1],
[8,3,4],
[9,12,9]))

# 3-a
print("\n\n3-a: ")
print(A*B)

# 3-b
print("3-b: ")
def trans_comb(A, B):
    Bt = np.transpose(B)
    row_size = np.shape(A)[0]
    col_size = np.shape(A)[1]
    result = []
    for i in range(row_size):
        result.append([])
        for j in range(col_size):
            result[i].append(A[i].dot(Bt[j]))
    return np.array(result)
print(trans_comb(A,B))

# 3-c
print("3-c: ")
print(np.matmul(A,B))


# 4. 아래와 같이 Numpy array 로 정의된 matrix 가 주어졌다
# 𝐴=[1   3     B=[1  3
#    4  15],      4 12]
# 4a) matrix A 의 determinant를 구하고 싶다 2x 2 matrix 를 input 으로 받아 determinant 를 출력하는 함수
# determinant(A)을 작성하고 A , B 의 determinant를 출력하시오 numpy det() 함수 사용 금지
# 4b) numpy 의 det() 함수를 사용해서 matrix A , B 의 determinant 를 출력하시오 소수 첫째자리에서 반올림 할 것

A = np.array(([1,3],
[4,15]))
B = np.array(([1,3],
[4,12]))

# 4-a
print("\n\n4-1: ", end='')
def determinant(A):
    result = A[0, 0]*A[1, 1] - A[0, 1] * A[1, 0]
    return result * 1.0
print(determinant(A), determinant(B))

# 4-b
print("4-1: ", end='')
print(round(np.linalg.det(A)), np.linalg.det(B))

# 5. 아래 matrix A 가 주어졌다
# 𝐴=[1 1 3
#    1 2 4
#    1 1 2]
# 5a) numpy 의 inv() 함수를 사용해서 matrix A 의 역행렬을 출력하시오
# 5b) A 와 5-a) 에서 구한 A의 역행렬을 사용 해서 Identity matrix 를 출력하시오

A = np.array(([1,1,3],
[1,2,4],
[1,1,2]))

# 5-a
print("\n\n5-a: ")
invA = np.linalg.inv(A)
print(invA)

# 5-b
print("5-b: ")
print(np.matmul(A,invA))