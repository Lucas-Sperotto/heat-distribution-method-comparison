import numpy as np
import matplotlib.pyplot as plt

# Carrega os dados do método EFG
T = np.loadtxt("data/resultado_efg.txt")

plt.imshow(T, origin='lower', cmap='hot', interpolation='bilinear')
plt.colorbar(label='Temperatura (°C)')
plt.title("Distribuição de Temperatura - EFG")
plt.xlabel("x")
plt.ylabel("y")
plt.tight_layout()
plt.savefig("plots/efg_plot.png")
#plt.show()
