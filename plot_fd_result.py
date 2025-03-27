import numpy as np
import matplotlib.pyplot as plt

# Carrega os dados
T = np.loadtxt("data/resultado_fd.txt")

plt.imshow(T, origin='lower', cmap='hot', interpolation='bilinear')
plt.colorbar(label='Temperatura (°C)')
plt.title("Distribuição de Temperatura - FD")
plt.xlabel("x")
plt.ylabel("y")
plt.tight_layout()
plt.savefig("plots/fd_plot.png")
#plt.show()
