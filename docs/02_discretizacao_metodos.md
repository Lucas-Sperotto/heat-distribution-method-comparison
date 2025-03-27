# Discretização numérica da equação de Laplace: FD, FEM e EFG

## 1. Introdução

Para resolver numericamente a equação de Laplace em uma placa retangular com condições de contorno de Dirichlet, utilizaremos três abordagens numéricas: o Método das Diferenças Finitas (FD), o Método dos Elementos Finitos (FEM) e o Método Element Free Galerkin (EFG). Cada técnica possui suas próprias vantagens em termos de simplicidade, generalidade geométrica e flexibilidade de malha.

---

## 2. Método das Diferenças Finitas (FD)

O método das diferenças finitas substitui as derivadas parciais por aproximações em pontos de uma malha regular.

A equação de Laplace:

\[
\frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} = 0
\]

pode ser aproximada em uma malha uniforme por:

\[
\frac{T_{i+1,j} - 2T_{i,j} + T_{i-1,j}}{\Delta x^2} + \frac{T_{i,j+1} - 2T_{i,j} + T_{i,j-1}}{\Delta y^2} = 0
\]

Assumindo \( \Delta x = \Delta y \), temos:

\[
T_{i+1,j} + T_{i-1,j} + T_{i,j+1} + T_{i,j-1} - 4T_{i,j} = 0
\]

Esse sistema gera um conjunto de equações lineares que podem ser resolvidas por métodos iterativos (Gauss-Seidel, SOR, etc.) ou diretos.

---

## 3. Método dos Elementos Finitos (FEM)

O método dos elementos finitos parte da formulação fraca da equação:

\[
\int_\Omega \nabla T \cdot \nabla v \, d\Omega = 0, \quad \forall v \in V_0
\]

A região \( \Omega \) é discretizada em elementos (triangulares ou quadriláteros), e as funções de forma \( \phi_i \) são utilizadas para interpolar a solução dentro de cada elemento:

\[
T(x, y) \approx \sum_{i=1}^N T_i \phi_i(x, y)
\]

Isso gera um sistema do tipo:

\[
\mathbf{K} \mathbf{T} = \mathbf{F}
\]

onde:
- \( \mathbf{K} \) é a matriz de rigidez,
- \( \mathbf{T} \) é o vetor de temperaturas nos nós,
- \( \mathbf{F} \) é o vetor de forças (nulo no caso sem fonte).

---

## 4. Método Element Free Galerkin (EFG)

O método Element Free Galerkin também utiliza a formulação fraca, mas substitui as funções de forma polinomiais por aproximações baseadas em MLS (Moving Least Squares).

A aproximação da solução é:

\[
T(x, y) \approx \sum_{I=1}^n \phi_I(x, y) T_I
\]

onde \( \phi_I(x, y) \) são obtidas via ponderação de funções base centradas em pontos de suporte, não dependendo de elementos conectados.

As integrações são realizadas sobre um domínio de influência com base em técnicas de integração por pontos, frequentemente com auxílio de malhas de background.

O sistema resultante também possui a forma:

\[
\mathbf{K} \mathbf{T} = \mathbf{F}
\]

mas com matriz de rigidez construída a partir das funções de forma obtidas pelo MLS.

---

## 5. Considerações finais

Cada método possui características distintas:
- **FD**: simples e eficiente em malhas regulares.
- **FEM**: generaliza para geometrias complexas e permite maior controle da precisão.
- **EFG**: não requer conectividade de malha, sendo mais flexível, porém mais custoso computacionalmente.

A comparação entre esses métodos será feita tanto em termos de precisão da solução quanto de custo computacional, com referência a uma solução analítica.

---
