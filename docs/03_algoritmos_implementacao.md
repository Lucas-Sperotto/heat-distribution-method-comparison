# 03 - Algoritmos e Estrutura de Implementação

Este documento descreve a estrutura computacional dos algoritmos desenvolvidos para resolver numericamente o problema da distribuição de temperatura em uma placa retangular com condições de contorno de Dirichlet, utilizando três abordagens numéricas distintas: Diferenças Finitas (FD), Elementos Finitos (FEM) e Element Free Galerkin (EFG).

---

## 1. Estrutura geral do projeto

O projeto é estruturado em C++, com separação modular entre:
- Estrutura de dados da malha (arquivo `grid.hpp/cpp`)
- Implementações dos métodos numéricos (`fd_solver.cpp`, `fem_solver.cpp`, `efg_solver.cpp`)
- Solvers de sistemas lineares (`linear_solvers.cpp`), com possibilidade de extensão
- Scripts de visualização em Python para análise dos resultados

Cada método numérico implementa uma função do tipo `void resolverMETODO(Grid&)`, que atualiza a matriz de temperatura `T` na estrutura `Grid`.

---

## 2. Diferenças Finitas (FD)

### Etapas principais:
1. Geração da malha regular.
2. Inicialização da temperatura com condições de contorno.
3. Laço iterativo de Gauss-Seidel:
   - Aplica a fórmula de atualização no interior:
     \[ T_{i,j} \leftarrow \frac{T_{i+1,j} + T_{i-1,j}}{\Delta x^2} + \frac{T_{i,j+1} + T_{i,j-1}}{\Delta y^2} \Bigg/ \left(\frac{2}{\Delta x^2} + \frac{2}{\Delta y^2}\right) \]
4. Critério de parada por convergência do erro relativo.

### Observações:
- Método simples, eficiente e fácil de implementar.
- Aplicação direta das condições de contorno.

---

## 3. Elementos Finitos (FEM)

### Etapas principais:
1. Construção da malha regular de elementos quadrilaterais.
2. Montagem da matriz de rigidez global \( K \) e vetor \( F \):
   - Cada elemento contribui com uma matriz local, somada na estrutura global.
   - Para propósitos didáticos, utiliza-se uma matriz local simplificada.
3. Aplicação das condições de contorno de Dirichlet:
   - Linhas e colunas da matriz \( K \) são zeradas e a diagonal principal recebe 1.
   - O vetor \( F \) recebe os valores de contorno.
4. Resolução do sistema \( K T = F \) com eliminação de Gauss (ou outro método).

### Observações:
- Mais flexível que FD para geometria e propriedades variáveis.
- Montagem pode ser aprimorada com integração por pontos de Gauss e formações mais ricas.

---

## 4. Element Free Galerkin (EFG)

### Etapas principais:
1. Geração de nós regulares (sem elementos).
2. Para cada ponto de integração (malha de fundo):
   - Identifica os nós vizinhos dentro de um raio de influência \( r \).
   - Calcula as funções de forma e suas derivadas usando MLS (Moving Least Squares):
     - Base \( [1, x, y] \)
     - Função de ponderação de Schwarz
     - Derivadas via diferenciação da matriz \( A \)
3. Montagem da matriz de rigidez \( K \):
   \[ K_{ij} += (\nabla \phi_i \cdot \nabla \phi_j) \cdot \text{peso} \]
4. Aplicação das condições de Dirichlet da mesma forma que no FEM.
5. Resolução do sistema \( K T = F \).

### Observações:
- Requer integração numérica com malha de fundo.
- Cálculo mais custoso, mas com maior liberdade topológica.
- Sensível à escolha do raio de influência.

---

## 5. Resolução de sistemas lineares

- Os sistemas \( K T = F \) são resolvidos por eliminação de Gauss com pivotamento parcial.
- A função `resolverSistemaLinear(...)` abstrai o método e permite uso futuro de LU, Cholesky, etc.
- Todas as implementações usam `std::vector` para compatibilidade e extensibilidade.

---

## 6. Considerações finais

Cada algoritmo foi implementado de forma independente, permitindo comparar:
- Qualidade da solução
- Custo computacional
- Flexibilidade

Essa documentação serve como referência para o entendimento da lógica de cada método, auxiliando futuros aprimoramentos e extensões do projeto.

