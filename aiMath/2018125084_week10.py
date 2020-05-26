import numpy as np

import matplotlib.pyplot as plt
import sklearn
import sklearn.datasets
import sklearn.linear_model
from data_utils import decision_boundary, dataloader


def sigmoid(x):
	return 1/(1+np.exp(-x))

class simpleNN:
	def __init__(self, nSamples):
		self.nSamples = nSamples

		# initialize W, b
		self.parameters = {}
		self.parameters['W'] = np.random.randn(1,2)*0.001
		self.parameters['b'] = np.zeros(1)

		# TODO: initialize dW, db
		self.grads = {}
		self.grads['dW'] = np.zeros((1,nSamples))
		self.grads['db'] = np.zeros((1,nSamples))

		self.cache = {}

	def compute_y_hat(self, x):
		# TODO: network 내 y^을 구하는 연산을 진행.
		W, b = list(self.parameters.values())
		z = np.dot(W, x) + b
		y_hat = sigmoid(z)

		self.cache.update(x=x, z=z, y_hat=y_hat)
		
		return y_hat

	def compute_gradients(self, y_hat, y):
		self.cache.update(y=y)
		x, z, _, _ = list(self.cache.values())
		dW, db = list(self.grads.values())
        
		# TODO: compute loss
		diff = y_hat - y
		dz = np.dot(x.transpose(), diff)

		# TODO: compute gradients = dW, db를 구하시오
		dW += dz * x
		db += dz

		self.grads.update(dW=dW, db=db)

	def updates(self, learning_rate=0.1):
		W, b = list(self.parameters.values())
		dW, db = list(self.grads.values())

		# TODO: gradient descent를 사용해 W, b update
		W = W - np.sum(np.dot(learning_rate, dW))
		b = b - np.sum(np.dot(learning_rate, db))
		
		self.parameters.update(W=W, b=b)
		self.grads.update(dW=0, db=0)

	def predict(self, x):
		# TODO: y^을 구하고 0.5 이상은 1, 0.5 미만은 0으로 predict
		y_hat = self.compute_y_hat(x)
		predictions = np.zeros(np.shape(y_hat))
		it = np.nditer(y_hat, flags=['multi_index'], op_flags=['readwrite'])
		while not it.finished:
			idx = it.multi_index
			if y_hat[idx] < 0.5:
				predictions[idx] = 0
			elif y_hat[idx] > 0.5:
				predictions[idx] = 1
			it.iternext()
		return predictions

def main():

	# make dataset & simpleNN
	data = dataloader()
	nSample = data.Input.shape[0]
	neural_net = simpleNN(nSample)
    
	# TODO: 교수님의 pseudo code에 따라서 training code 구현
	# 		for문에서 첫번째 for문은 100 그대로, 두번째 for문에서 m = dataset의 개수로 설정
	for n in range(1,101):
		neural_net.__init__
		for i in range(1,data.Input.shape[1]):
			neural_net.compute_y_hat(np.array(data.Input[1][i],data.Input[0][i]))
			neural_net.compute_gradients(neural_net.cache.get('y_hat'), data.Label[0][i])
		neural_net.updates()

	# training한 network의 boundary, Accuracy 출력
	decision_boundary(lambda x: neural_net.predict(x.T), data.Input, data.Label)
	predictions = neural_net.predict(data.Input)
	print ('Accuracy: %d' % float((np.dot(data.Label,predictions.T) + np.dot(1-data.Label,1-predictions.T))/float(data.Label.size)*100) + '%')


if __name__ == '__main__':
	main()