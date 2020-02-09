# n = 10000
# noise = 6798
# for i in range(1 , 11):
#     nn = n * i 
#     file =str(nn) +'.txt'
#     cn =0
#     with open(file , 'w') as f:
#         for i in range( noise , noise + 2*nn , 2):
#             f.write(str(i))
#             f.write('\n')
#             cn +=1
#     print(cn) 
#     f.close()

# n = 10000
# noise = 6798
# for i in range(1, 11):
#     nn = n * i
#     file = 'r' + str(nn) + '.txt'
#     cn =0
#     with open(file, 'w') as f:
#         for i in range( noise + 2*nn -1, noise-1 , -2):
#             f.write(str(i))
#             f.write('\n')
#             cn+=1
#     print(cn)
#     f.close()
import numpy as np
# a = [i for i in range(noise, noise + n + 1)]
# a = np.array(a)
# np.random.shuffle(a)
# print(a)


# n = 10000
# noise = 6798
# for i in range(1, 11):
#     nn = n * i
#     file = 'ran' + str(nn) + '.txt'
#     a = [i for i in range(noise, noise + 2*nn , 2)]
#     print(len(a))
#     a = np.array(a)
#     np.random.shuffle(a)
#     with open(file, 'w') as f:
#         for i in a:
#             f.write(str(i))
#             f.write('\n')
#     f.close()

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("mergesort.csv" )
print(df)
plt.plot(df["Sorted"] , label="Sorted")
plt.plot(df["Reverse_sorted"] , label="Reverse_sorted")
plt.plot(df["Random_arranged"] , label="Random_arranged")
plt.xticks([])
plt.legend(loc="upper left")
plt.ylabel("Time ( in seconds)")
plt.xlabel("Number  of elements ")
plt.savefig("MergeSort")
plt.show()
