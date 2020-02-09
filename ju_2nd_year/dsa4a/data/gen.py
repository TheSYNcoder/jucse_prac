import pandas as pd
import matplotlib.pyplot as plt
# plt.rcParams['figure.figsize'] = 8, 7
df = pd.read_csv("sortcmp.csv")
print(df)
plt.plot(df["Heap"], label="HeapSort")
plt.plot(df["Merge"], label="MergeSort")
plt.plot(df["Quick"], label="QuickSort")
# plt.plot(df["Insertion"], label="InsertionSort")
# plt.plot(df["Bubble"], label="BubbleSort")
# plt.plot(df["Selection"], label="SelectionSort")
plt.xticks([])
plt.legend(loc="upper left")
plt.ylabel("Time ( in seconds)")
plt.xlabel("Number  of elements ")
plt.savefig("SortComparison2")
plt.show()
