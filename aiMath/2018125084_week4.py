import numpy as np
import numpy.linalg as la
from bearNecessities import *
import matplotlib.pyplot as plt

'''
	2. Gram-Schmidt process
	이 실습은 Gram-Schmidt process를 이해했는지 확인하는 문제입니다.
	아래 gsBasis3(A)함수는 3x3 matrix를 가지고 Gram Schmidt process를 적용한 matrix를 return해주는 함수입니다.
	함수 안에 적힌 TODO를 차례로 채워넣으면 함수를 완성할 수 있습니다.
	함수를 완성해서 이 파일을 수행했을 때, 실습 안내문에 적힌 결과가 출력하도록 gsBasis3를 완성하시오.

	python에서 @ operator는 dot product연산으로 쓰인다.
	@ 연산을 사용해서 과제를 수행하시오.
'''

def gsBasis3(A):
	# ToDo 1: Make B as a copy of A
	B = np.array(A)
	# TODO 2: compute zeroth column of B
	B[0] = B[0]/la.norm(B[0])
	# TODO 3: compute first column of B & normalize
	U2 = B[1] - (B[1] @ B[0]) * B[0]
	B[1] = U2/la.norm(U2)

	# TODO 4: compute second column of B
	U3 = B[2] - (B[2] @ B[0]) * B[0] - (B[2] @ B[1]) * B[1]
	B[2] = U3/la.norm(U3)
	# return result
	return B.transpose()

'''
	3. Reflecting Bear
	이 실습은 orthornormal하지 않은 basis에서 정의된 한 점을 transformation시킬 때,
	먼저 orthonormal하지 않은 basis를 orthormormal한 basis로 변화시키고, 변화시킨 basis에서 transformation을 시킨 후
	다시 원래의 orthornormal하지 않은 basis로 transform 시키는 문제 입니다
	2번과 같이 TODO를 채워 나가면서 결과를 출력하시오.

'''

def gsBasis2(A):
	# TODO 1: 1번에서 만들었던 gsBasis3와 유사하게, 2x2 matrix의 orthormormal basis를 return해주는 gsBasis2 함수를 정의하시오.
	
	# ToDo 1.1: Make B as a copy of A
	B = np.array(A)

	# TODO 1.2: compute zeroth column of B
	B[0] = B[0]/la.norm(B[0])
	# TODO 1.3: compute first column of B & normalize
	U2 = B[1] - (B[1] @ B[0]) * B[0]
	B[1] = U2/la.norm(U2)

	return B.transpose()

def build_reflectoin_matrix(bearBasis):
	
	# TODO 2: gsBasis2를 사용해서, bearBasis의 orthormormal basis E를 구하시오.
	E = gsBasis2(bearBasis)

	# TODO 3: 기존 vector를 x축 대칭이 하도록 하는 2x2 transform matrix TE를 만드시오.
	TE = np.array(([-1, 0], [0, 1]))

	# TODO 4: TE, E를 사용해서 최종적인 transformation matrix T를 만드시오.
	ETE = np.matmul(E, TE)
	invE = la.inv(E)
	T = np.matmul(ETE, invE)


	return T

def main():

	# 1. matrix indexing
	# TODO: 1번 문제에 대한 답 작성하시오.
	a = np.arange(1,385)
	dimension = (8,12,4)
	a = np.reshape(a,dimension)
	print("1-a: ", end='')
	print(dimension)

	print("1-b")
	print(a[0][0])

	print("1-c")
	As = np.reshape(a[1, :12, :1], (12))
	print(As)

	print("1-d")
	print(a[7])

	# 2. Gram-Schmidt process
	V = np.array([[1, 0, 2],
				 [0, 1, 8],
				 [2, 8, 3],], dtype=np.float_)
	U = gsBasis3(V)
	print('after Gram-Schmidt process for V')
	print(U)

	# 3. Reflecting Bear
	bearBasis = np.array([[1, -1],
						 [1.5, 2]])
	T = build_reflectoin_matrix(bearBasis)

	reflected_bear_white_fur = T @ bear_white_fur
	reflected_bear_black_fur = T @ bear_black_fur
	reflected_bear_face = T @ bear_face

	# This next line runs a code to set up the graphics environment.
	ax = draw_mirror(bearBasis)

	# We'll first plot Bear, his white fur, his black fur, and his face.
	ax.fill(bear_white_fur[0], bear_white_fur[1], color=bear_white, zorder=1)
	ax.fill(bear_black_fur[0], bear_black_fur[1], color=bear_black, zorder=2)
	ax.plot(bear_face[0], bear_face[1], color=bear_white, zorder=3)

	# Next we'll plot Bear's reflection.
	ax.fill(reflected_bear_white_fur[0], reflected_bear_white_fur[1], color=bear_white, zorder=1)
	ax.fill(reflected_bear_black_fur[0], reflected_bear_black_fur[1], color=bear_black, zorder=2)
	ax.plot(reflected_bear_face[0], reflected_bear_face[1], color=bear_white, zorder=3)

if __name__ == '__main__':
	main()