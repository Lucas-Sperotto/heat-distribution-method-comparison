# 04 - Resultados Comparativos

Este documento apresenta uma análise comparativa dos resultados obtidos pelos três métodos numéricos implementados (Diferenças Finitas, Elementos Finitos e Element Free Galerkin) na resolução do problema da equação de Laplace em uma placa retangular com condições de contorno de Dirichlet.

---

## 1. Configuração do problema

- Dimensões da placa: \( a \times b \)
- Malha: regular, com divisões \( n_x \times n_y \)
- Condições de contorno:
  - T(x=0) = 100
  - T(x=a), T(y=0), T(y=b) = 0
- Objetivo: encontrar o campo escalar de temperatura em regime estacionário.

---

## 2. Critérios de comparação

- Coerência física da solução (comportamento esperado do calor)
- Convergência visual da distribuição de temperatura
- Tempo de execução e custo computacional
- Complexidade de implementação
- Flexibilidade geométrica e de propriedades
- Aderência a soluções analíticas (quando disponíveis)

---

## 3. Saída dos métodos

Os arquivos gerados pelos métodos estão localizados na pasta `data/`:

- `resultado_fd.txt` - Diferenças Finitas
- `resultado_fem.txt` - Elementos Finitos
- `resultado_efg.txt` - Element Free Galerkin

Cada arquivo contém a matriz \( T \) em formato texto (para leitura por scripts de visualização).

---

## 4. Visualização dos resultados

Utiliza-se um script Python (ex: `plot_resultados.py`) para gerar os mapas de calor dos resultados:

```python
import numpy as np
import matplotlib.pyplot as plt

T_fd = np.loadtxt('data/resultado_fd.txt')
T_fem = np.loadtxt('data/resultado_fem.txt')
T_efg = np.loadtxt('data/resultado_efg.txt')

fig, axs = plt.subplots(1, 3, figsize=(15, 4))

for ax, T, title in zip(axs, [T_fd, T_fem, T_efg], ['FD', 'FEM', 'EFG']):
    im = ax.imshow(T, origin='lower', cmap='hot')
    ax.set_title(f"Distribuição de Temperatura - {title}")
    plt.colorbar(im, ax=ax)

plt.tight_layout()
plt.show()
```

---

## 5. Observações preliminares

- O método de Diferenças Finitas é o mais simples e apresenta resultado adequado para malhas regulares.
- O método de Elementos Finitos permite futuras extensões para malhas triangulares ou domínios complexos.
- O EFG exige cuidados na escolha do raio de influência e na integração numérica.
- Em todos os casos, a solução se aproxima da analítica conhecida:
  \[ T(x, y) = \sum_{n=1}^{\infty} A_n \sin\left(\frac{n\pi x}{a}\right)\sinh\left(\frac{n\pi y}{a}\right) \]
  para casos com contorno tênue no tempo.

---

## 6. Possíveis extensões futuras

- Avaliar o erro \( L_2 \) entre solução numérica e analítica
- Implementar cronometragem para comparação de desempenho
- Incluir animação para simular evolução temporal (caso transiente)
- Permitir entrada de geometrias complexas (caso FEM e EFG)

---

Esta comparação fornece uma base para decidir qual método é mais adequado a um determinado problema em função de custo, precisão e flexibilidade.

