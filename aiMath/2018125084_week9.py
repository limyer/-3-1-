import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def visualize(f):
	# TODO: python lambda의 개념을 이해, matplotlib를 사용해 3d graph를 plot.
	
	# Argument
	#	f: visualize 하려는 함수 

	x = np.linspace(-2, 2, 500)
	y = np.linspace(-2, 2, 500)
	x, y = np.meshgrid(x, y)
	z = f(np.array([x,y]))

	fig = plt.figure(figsize=(12, 6))
	ax = plt.axes(projection='3d')

	ax.plot_surface(x, y, z, cmap=plt.cm.rainbow)
	plt.savefig('case2.svg')
	plt.title("y = f(x, y)")
	plt.xlabel('x')
	plt.ylabel('y')
	plt.show()

	return

def gradient_descent_f(s0, df, f, alpha=0.1):
	# TODO: 	while 문 사용해서 gradient descent 진행
	# 			while문 조건은 gradient vector 크기가 0.01보다 큰 경우
	
	# Argument:
	#	s0: gradient descent 시작 지점
	#	df: gradient descent 진행하는 함수의 도함수. lambda function의 형태
	#	 f: gradient descent 진행할 함수. lambda function의 형태
	#	alpha: update 계수. 이 실습에서는 바꿀 필요 없음.

	# return: 	수렴한 s의 함숫값 return

	sn = s0
	while(np.linalg.norm(df(sn)) > 0.01):
		sn = sn - np.dot(alpha, df(sn))
	return f(sn)

def main():
	####################### 실습: Visualize ###############################
	# TODO: python lambda function을 사용해서 원하는 함수를 Visualize
	z1 = lambda x:x[0]*np.exp(-x[0]**2-x[1]**2)
	visualize(z1)
	z2 = lambda x:np.sin(x[0])*np.cos(x[1])
	visualize(z2)

	############################ Case 1 ###################################
	f1 = lambda x:x[0]*np.exp(-x[0]**2-x[1]**2)
	df1 = lambda x:((1-2*(x[0]**2))*np.exp(-((x[0]**2)+(x[1]**2))), -2*x[1]*x[0]*np.exp(-x[0]**2-x[1]**2))

	s0_1 = np.array([-1.5, -1])
	s0_2 = np.array([-0.5, 0.5])
	s0_3 = np.array([1.5, 0])

	res1 = gradient_descent_f(s0_1, df1, f1)
	res2 = gradient_descent_f(s0_2, df1, f1)
	res3 = gradient_descent_f(s0_3, df1, f1)

	print(res1)
	print(res2)
	print(res3)

	########################### Case 2 ###################################
	f2 = lambda x:np.sin(x[0])*np.cos(x[1])
	df2 = lambda x:(np.cos(x[0])*np.cos(x[1]), -np.sin(x[0])*np.sin(x[1]))

	s0_1 = np.array([-1.5, -1])
	s0_2 = np.array([1, 1])
	s0_3 = np.array([0, 0])

	res1_1 = gradient_descent_f(s0_1, df2, f2)
	res2_1 = gradient_descent_f(s0_2, df2, f2)
	res3_1 = gradient_descent_f(s0_3, df2, f2)

	print(res1_1)
	print(res2_1)
	print(res3_1)

if __name__ == '__main__':
	main()