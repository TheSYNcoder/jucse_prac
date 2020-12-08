import numpy as np

a = np.random.randint( 0 ,20 , 15 )

print('The vector : '  , *a )
print('Most frequent element : ' , np.argmax(np.bincount(a)))
binc = np.bincount(a)

## masking to prevent counting non-present items
binc[binc == 0] = 1e9
# print(binc)
print('Least frequent element : ', np.argmin(binc))

'''
The vector :  17 11 11 13 7 17 16 17 3 12 19 6 7 2 4
Most frequent element :  17
Least frequent element :  2
'''
