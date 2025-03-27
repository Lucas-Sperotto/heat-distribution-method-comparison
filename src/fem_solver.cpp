#include "fem_solver.hpp"
#include "linear_solvers.hpp"
#include <vector>
#include <iostream>

// Funções de forma e derivadas no centro do elemento
const double dN_dx[4] = {-0.25, 0.25, 0.25, -0.25};
const double dN_dy[4] = {-0.25, -0.25, 0.25, 0.25};

void resolverFEM(Grid &grid)
{
    int nx = grid.nx;
    int ny = grid.ny;
    int N = nx * ny;

    std::vector<std::vector<double>> K(N, std::vector<double>(N, 0.0));
    std::vector<double> F(N, 0.0);
    std::vector<double> T(N, 0.0);

    double dx = grid.dx;
    double dy = grid.dy;
    double area = dx * dy;

    // Montagem da matriz de rigidez
    for (int j = 0; j < ny - 1; ++j)
    {
        for (int i = 0; i < nx - 1; ++i)
        {
            // índices globais dos 4 nós do elemento
            int nodes[4] = {
                j * nx + i,
                j * nx + (i + 1),
                (j + 1) * nx + (i + 1),
                (j + 1) * nx + i};

            // matriz de rigidez local (simplificada)
            for (int a = 0; a < 4; ++a)
            {
                for (int b = 0; b < 4; ++b)
                {
                    double kab = (dN_dx[a] * dN_dx[b] + dN_dy[a] * dN_dy[b]) * area;
                    K[nodes[a]][nodes[b]] += kab;
                }
            }
        }
    }

    // Aplicar condições de contorno de Dirichlet
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            int id = j * nx + i;
            double valor = grid.T[j][i];

            // Se ponto está na borda
            if (i == 0 || i == nx - 1 || j == 0 || j == ny - 1)
            {
                for (int k = 0; k < N; ++k)
                {
                    K[id][k] = 0.0;
                }
                K[id][id] = 1.0;
                F[id] = valor;
            }
        }
    }

    resolverSistemaLinear(K, F, T, "gauss");

    // Preencher grid com resultados
    for (int j = 0; j < ny; ++j)
        for (int i = 0; i < nx; ++i)
            grid.T[j][i] = T[j * nx + i];
}
