import pandas as pd
import matplotlib.pyplot as plt

table = pd.read_table("out.txt")



plt.figure(figsize=(12, 9))

plt.plot(table['n'], table['Strassen Alg.'], label='strassen', marker='o', color='red')
plt.plot(table['n'], table['Opt.Strassen Alg.'], label='opt. strassen', marker='o', color='green')
plt.xlabel("n")
plt.ylabel("time")
plt.title("Strassen's Algorithm vs Strassen's Algorithm Optimized")
plt.legend()
plt.savefig('plot.png')
plt.show()