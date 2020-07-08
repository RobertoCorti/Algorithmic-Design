import pandas as pd
import matplotlib.pyplot as plt

table = pd.read_table("../data/test.txt")

#plt.figure(figsize=(12, 9))

plt.plot(table['size'], table['Array'], label='Array', marker='o', color='red')
plt.plot(table['size'], table['Heap'], label='Heap', marker='o', color='green')
plt.xlabel("n")
plt.ylabel("time")
plt.title("Dijkstra Algorith: Array queue vs Heap queue")
plt.legend()
plt.savefig('plot.png')
plt.show()