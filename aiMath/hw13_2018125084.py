# 인공지능기초수학
# 소프트웨어학과 2018125084 임예랑
# 20200616 13주차 실습

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def n1():
	plt.figure(figsize=(16, 6), dpi=80)
	# TODO
	plt.subplot(1,2,1)
	X = np.linspace(0, 2*np.pi, 256)
	C, S = np.cos(X), np.sin(X)
	plt.plot(X,C, color="blue")
	plt.xlim(0,2*np.pi)
	plt.xticks(np.linspace(0,2*np.pi, 10))
	plt.ylim(-1,1)
	plt.yticks(np.linspace(-1,1,5))

	plt.subplot(1,2,2)
	plt.plot(X,S, color="red")
	plt.xlim(0,2*np.pi)
	plt.xticks(np.linspace(0,2*np.pi, 10))
	plt.ylim(-1,1)
	plt.yticks(np.linspace(-1,1,5))

	plt.show()

def n2():
	fig = plt.figure(figsize=(50,10))

	# TODO
	plt.axes([.1, .55, .8, .35])
	X = np.linspace(0, 2, 256)
	f1 = np.exp((X**2)+1)
	plt.plot(X,f1, color="blue")
	plt.xlim(0,2)
	plt.xticks(np.linspace(0, 2, 10))
	plt.ylim(0,100)
	plt.yticks(np.linspace(0,100,5))

	plt.axes([.1, .1, .35, .35])
	X = np.linspace(0, 10, 256)
	f2 = np.log((X**2)+1)
	plt.plot(X,f2, color="red")
	plt.xlim(0,10)
	plt.xticks(np.linspace(0, 10, 5))
	plt.ylim(-1,5)
	plt.yticks(np.linspace(-1,5, 6))

	plt.axes([.55, .1, .35, .35])
	X = np.linspace(-10, 10, 256)
	f3 = np.ones(256)
	plt.plot(X, f3, color="green")
	plt.xlim(-10,10)
	plt.xticks(np.linspace(-10, 10, 5))
	plt.ylim(0,1.5)
	plt.yticks(np.linspace(0, 1.5, 6))

	plt.show()

	

def n3():
	fig = plt.figure()
	
	# TODO
	ax = Axes3D(fig)
	X = np.arange(-np.pi, np.pi, 0.25)
	Y = np.arange(-np.pi, np.pi, 0.25)
	X, Y = np.meshgrid(X, Y)
	R = X + X * Y
	Z = np.sin(R)
	ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.rainbow)
	ax.set_zlim(-1, 1)

	plt.show()


def main():
	n1()
	n2()
	n3()

if __name__ == '__main__':
	main()