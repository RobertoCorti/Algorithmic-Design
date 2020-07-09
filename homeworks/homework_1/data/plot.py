import pandas as pd
import matplotlib.pyplot as plt

table = pd.read_table("out.txt")



plt.figure(figsize=(10, 8))

plt.plot(table['n'], table['Strassen Alg.'], label='strassen', marker='o', color='red')
plt.plot(table['n'], table['Opt.Strassen Alg.'], label='opt. strassen', marker='o', color='green')
plt.xlabel("n", fontsize=15)
plt.ylabel("time", fontsize=15)
plt.title("Strassen's Algorithm vs Strassen's Algorithm Optimized", fontsize=20)
plt.legend()
plt.savefig('plot.png')
plt.show()