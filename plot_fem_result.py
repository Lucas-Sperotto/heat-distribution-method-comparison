import numpy as np
import matplotlib.pyplot as plt

# Carrega os dados do método FEM
T = np.loadtxt("data/resultado_fem.txt")

plt.imshow(T, origin='lower', cmap='hot', interpolation='bilinear')
plt.colorbar(label='Temperatura (°C)')
plt.title("Distribuição de Temperatura - FEM")
plt.xlabel("x")
plt.ylabel("y")
plt.tight_layout()
plt.savefig("plots/fem_plot.png")
#plt.show()
