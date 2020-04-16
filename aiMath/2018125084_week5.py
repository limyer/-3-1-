from PIL import Image
import numpy as np
import numpy.linalg as la


# Problem 1-a
img1 = Image.open("img1.png")
img2 = Image.open("img2.png")
img3 = Image.open("img3.png")
img4 = Image.open("img4.png")

imgArr1 = np.asarray(img1)
imgArr2 = np.asarray(img2)
imgArr3 = np.asarray(img3)
imgArr4 = np.asarray(img4)

print("1-a")
print("image 1 : ", imgArr1.shape)
print("image 2 : ", imgArr2.shape)
print("image 3 : ", imgArr3.shape)
print("image 4 : ", imgArr4.shape)

# Problem 1-b
imgBatch = np.stack([imgArr1, imgArr2, imgArr3, imgArr4], axis=3)
imgBatch = imgBatch.transpose()
imgBatch = np.swapaxes(imgBatch, 3, 2)

print("1-b: ", end='')
print(imgBatch.shape)

# Problem 1-c
reshapedBatch = imgBatch.reshape(4, 3, 128*256)
print("1-c: ", end='')
print(reshapedBatch.shape)

# Problem 2
gray = np.array([0.3, 0.59, 0.11])
img1red = imgBatch[0][0] * gray[0]
img1green = imgBatch[0][1] * gray[1]
img1blue = imgBatch[0][2] * gray[2]
grayImg1 = img1red + img1green + img1blue

img2red = imgBatch[1][0] * gray[0]
img2green = imgBatch[1][1] * gray[1]
img2blue = imgBatch[1][2] * gray[2]
grayImg2 = img2red + img2green + img2blue

img3red = imgBatch[2][0] * gray[0]
img3green = imgBatch[2][1] * gray[1]
img3blue = imgBatch[2][2] * gray[2]
grayImg3 = img3red + img3green + img3blue

img4red = imgBatch[3][0] * gray[0]
img4green = imgBatch[3][1] * gray[1]
img4blue= imgBatch[3][2] * gray[2]
grayImg4 = img4red + img4green + img4blue

grayImgBatch = np.stack([grayImg1, grayImg2, grayImg3, grayImg4])

print("2: ",end='')
print(grayImgBatch.shape)


# Problem 3-a
T = np.array(([1,2,3], [5,3,4], [7,2,3]))
w1, v1 = la.eig(T)
print("3-a")
print("lambda 1: ", w1[0])
print("eigen vector 1: ", v1.transpose()[0])
print("lambda 2: ", w1[1])
print("eigen vector 2: ", v1.transpose()[1])
print("lambda 3: ", w1[2])
print("eigen vector 3: ", v1.transpose()[2])

# Problem 3-b
print("3-b")
print(np.matmul(T,v1.transpose()[0]))
print(np.matmul(T,v1.transpose()[1]))
print(np.matmul(T,v1.transpose()[2]))

# Problem 3-c
print("3-c")
lambdaX1 = w1[0] * v1.transpose()[0]
lambdaX2 = w1[1] * v1.transpose()[1]
lambdaX3 = w1[2] * v1.transpose()[2]
print(lambdaX1)
print(lambdaX2)
print(lambdaX3)

# Problem 4-a
L = np.array(([0,1/2,0,0], [1/3,0,0,1/2], [1/3,0,0,1/2], [1/3, 1/2, 1, 0]))
print("4-a")
print(L)

# Problem 4-b
Lw, Lv = la.eig(L)
Lv = Lv.transpose()
absV = abs(Lv[0])
sumV = np.sum(absV)
normV = absV/sumV

print("4-b")
print(100 * np.real(normV))

# Problem 4-c
def PageRank(linkMatrix):
    initV = 100 * (1/linkMatrix.shape[0])
    r = np.full(linkMatrix.shape[0], initV)
    newR = np.matmul(linkMatrix, r)
    while (np.abs(la.norm(r) - la.norm(newR)) > 0.01):
        r = newR
        newR = np.matmul(linkMatrix,newR)
    return r

print("4-c")
print(PageRank(L))