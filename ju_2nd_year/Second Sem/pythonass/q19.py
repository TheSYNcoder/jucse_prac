from sklearn.metrics import confusion_matrix , accuracy_score
from sklearn.neural_network import MLPClassifier
import matplotlib.pyplot as plt
import numpy as np
import gzip
import random
from sklearn.metrics import roc_auc_score
import time
from sklearn.neighbors import KNeighborsClassifier

f = gzip.open('train-images-idx3-ubyte.gz', 'r')

image_size = 28
num_images = 60000

f.read(16)
buf = f.read(image_size * image_size * num_images)
data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
train_data = data.reshape(num_images, image_size * image_size)


# image = np.asarray(data[random.choice(list(range(num_images)))])
# plt.imshow(image)
# plt.show()

f = gzip.open('train-labels-idx1-ubyte.gz', 'r')

f.read(8)
buf = f.read( num_images )
data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
train_labels = data.reshape( num_images )

# print(train_labels[random.choice(list(range(num_images)))])

f = gzip.open('t10k-labels-idx1-ubyte.gz', 'r')

test_num_images = 10000
f.read(8)
buf = f.read( test_num_images )
data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
test_labels = data.reshape( test_num_images )

# print(train_labels[random.choice(list(range(test_num_images)))])

f = gzip.open('t10k-images-idx3-ubyte.gz', 'r')
f.read(16)
buf = f.read(image_size * image_size * test_num_images)
data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32)
test_data = data.reshape(test_num_images, image_size * image_size)

def train_knn():
    st = time.time()
    classifier = KNeighborsClassifier(n_neighbors=7)
    classifier.fit(train_data, train_labels)
    pred = classifier.predict(test_data)
    en = time.time() - st
    return pred , en

def train_3_layer_nn():
    st = time.time()
    classifier = MLPClassifier( hidden_layer_sizes=(500,300) )
    classifier.fit(train_data , train_labels)
    pred = classifier.predict(test_data)
    en = time.time() - st
    return pred ,en



method ="KNN"
pred, en = train_knn()

# method = "3 Layer Neural Network"
# pred ,en = train_3_layer_nn()


cm = confusion_matrix(test_labels, pred)

print(cm)
# print("7 neighbours")
print("Algorithm :" , method)
print( 'accuracy  : ' ,  accuracy_score( test_labels  , pred) )
# print( 'ROC score' , roc_auc_score( test_labels , pred))
# print( "Time taken : " , en / 60 , " minutes.")

'''
[[ 966    1    3    1    0    1    5    2    1    0]
 [   0 1130    0    2    0    1    1    0    1    0]
 [   0    1 1009    1    2    0    0   11    8    0]
 [   0    1    8  984    0    4    0    2    9    2]
 [   0    1    7    1  923    0    4    3    2   41]
 [   1    1    0   17    1  855    2    3    4    8]
 [   3    2    3    0    5    2  937    0    6    0]
 [   2    5    7    3    3    0    0  995    2   11]
 [   2    1    3    6    0    3    0    2  952    5]
 [   3    3    1    5    1    3    0    2    5  986]]
Algorithm : 3 Layer Neural Network
accuracy  :  0.9737
'''

'''
[[ 974    1    1    0    0    1    2    1    0    0]
 [   0 1133    2    0    0    0    0    0    0    0]
 [  10    9  996    2    0    0    0   13    2    0]
 [   0    2    4  976    1   13    1    7    3    3]
 [   1    6    0    0  950    0    4    2    0   19]
 [   6    1    0   11    2  859    5    1    3    4]
 [   5    3    0    0    3    3  944    0    0    0]
 [   0   21    5    0    1    0    0  991    0   10]
 [   8    2    4   16    8   11    3    4  914    4]
 [   4    5    2    8    9    2    1    8    2  968]]
3 neighbours
Algorithm : KNN
accuracy  :  0.9705
'''

'''
[[ 974    1    1    0    0    1    2    1    0    0]
 [   0 1133    2    0    0    0    0    0    0    0]
 [  11    8  991    2    1    0    1   15    3    0]
 [   0    3    3  976    1   13    1    6    3    4]
 [   3    7    0    0  944    0    4    2    1   21]
 [   5    0    0   12    2  862    4    1    2    4]
 [   5    3    0    0    3    2  945    0    0    0]
 [   0   22    4    0    3    0    0  988    0   11]
 [   8    3    5   13    6   12    5    5  913    4]
 [   5    7    3    9    7    3    1   10    2  962]]
5 neighbours
Algorithm : KNN
accuracy  :  0.9688
'''
'''
[[ 974    1    1    0    0    1    2    1    0    0]
 [   0 1133    2    0    0    0    0    0    0    0]
 [  11    8  988    2    1    0    2   16    4    0]
 [   0    3    2  976    1   12    1    7    4    4]
 [   1    8    0    0  945    0    5    1    1   21]
 [   5    0    0    8    2  866    4    1    2    4]
 [   6    3    0    0    3    2  944    0    0    0]
 [   0   25    3    0    1    0    0  989    0   10]
 [   6    4    6   11    7   12    1    6  916    5]
 [   5    6    3    6    8    4    1   11    2  963]]
Algorithm : KNN
accuracy  :  0.9694
'''



