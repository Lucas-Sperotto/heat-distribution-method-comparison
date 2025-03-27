# Equacionamento físico do problema de distribuição de temperatura em uma placa 2D

## 1. Introdução

O estudo da distribuição de temperatura em meios contínuos é fundamental em diversas áreas da engenharia e ciências aplicadas. No caso específico de uma placa retangular com condutividade térmica constante e sob regime estacionário, o modelo físico é descrito pela equação de Laplace, um caso particular da equação do calor sem fonte interna e em regime permanente.

## 2. Modelo físico

Considera-se uma placa retangular de dimensões \( a \times b \), homogênea, isotrópica, com espessura desprezível, sujeita a condições de contorno do tipo Dirichlet (valores de temperatura especificados ao longo das bordas). O meio está em equilíbrio térmico, e portanto, não há variação temporal da temperatura.

A equação que rege esse fenômeno é:

\[
\frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} = 0
\]

onde:
- \( T(x, y) \) representa a temperatura em um ponto da placa,
- \( (x, y) \in \Omega \), com \( \Omega = (0, a) \times (0, b) \).

## 3. Condições de contorno

As condições de contorno do tipo Dirichlet são definidas como:

\[
T(x, 0) = f_1(x), \quad T(x, b) = f_2(x), \quad T(0, y) = g_1(y), \quad T(a, y) = g_2(y)
\]

Essas condições determinam completamente a solução do problema, uma vez que a equação de Laplace é bem-posta com esse tipo de contorno.

## 4. Objetivo

O objetivo é resolver numericamente a equação de Laplace com as condições de Dirichlet especificadas, utilizando três métodos distintos — Diferenças Finitas, Elementos Finitos e Element Free Galerkin — e, sempre que possível, comparar os resultados com a solução analítica conhecida para o problema.

---
