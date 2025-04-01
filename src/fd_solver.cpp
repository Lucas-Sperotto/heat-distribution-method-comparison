#include "fd_solver.hpp"
#include <cmath>
#include <iostream>

void resolverDifFinita(Grid &grid, double tol, int maxIter, int ordem)
{
    switch (ordem)
    {
    case 2:
        resolverOrdem_2(grid, tol, maxIter);
        break;

    case 4:
        resolverOrdem_4(grid, tol, maxIter);
        break;

    case 6:
        resolverOrdem_6(grid, tol, maxIter);
        break;
        
    default:
        std::cerr << "Ordem de esquema nao suportada: " << ordem << std::endl;
        return;
    }
}

void resolverOrdem_2(Grid &grid, double tol, int maxIter)
{
    int nx = grid.nx, ny = grid.ny;
    double erro;

    for (int it = 0; it < maxIter; ++it)
    {
        erro = 0.0;

        for (int j = 1; j < ny - 1; ++j)
        {
            for (int i = 1; i < nx - 1; ++i)
            {
                double T_old = grid.T[j][i];
                grid.T[j][i] = 0.25 * (grid.T[j + 1][i] + grid.T[j - 1][i] +
                                       grid.T[j][i + 1] + grid.T[j][i - 1]);
                erro = std::max(erro, std::abs(grid.T[j][i] - T_old));
            }
        }

        if (erro < tol)
        {
            std::cout << "Convergência em " << it << " iterações.\n";
            break;
        }
    }
}

void resolverOrdem_4(Grid &grid, double tol, int maxIter)
{
    int nx = grid.nx, ny = grid.ny;
    double erro;

    for (int it = 0; it < maxIter; ++it)
    {
        erro = 0.0;

        for (int j = 1; j < ny - 1; ++j)
        {
            for (int i = 1; i < nx - 1; ++i)
            {
                double T_old = grid.T[j][i];

                grid.T[j][i] = (1.0 / 20.0) * (4.0 * (grid.T[j + 1][i] + grid.T[j - 1][i] +
                                                      grid.T[j][i + 1] + grid.T[j][i - 1]) +
                                               (grid.T[j + 1][i + 1] + grid.T[j + 1][i - 1] +
                                                grid.T[j - 1][i + 1] + grid.T[j - 1][i - 1]));
                erro = std::max(erro, std::abs(grid.T[j][i] - T_old));
            }
        }

        if (erro < tol)
        {
            std::cout << "Convergência em " << it << " iterações.\n";
            break;
        }
    }
}

void resolverOrdem_6(Grid &grid, double tol, int maxIter)
{
    int nx = grid.nx, ny = grid.ny;
    double erro;

    for (int it = 0; it < maxIter; ++it)
    {
        erro = 0.0;

        for (int j = 1; j < ny - 1; ++j)
        {
            for (int i = 1; i < nx - 1; ++i)
            {
                double T_old = grid.T[j][i];

                if (i == 1 || j == 1 || i == (nx - 2) || j == (ny - 2))
                {
                    // std::cout << "Borda [" << j << "]["<< i << std::endl;
                    grid.T[j][i] = (1.0 / 20.0) * (4.0 * (grid.T[j + 1][i] + grid.T[j - 1][i] +
                                                          grid.T[j][i + 1] + grid.T[j][i - 1]) +
                                                   (grid.T[j + 1][i + 1] + grid.T[j + 1][i - 1] +
                                                    grid.T[j - 1][i + 1] + grid.T[j - 1][i - 1]));
                }
                else
                {
                    grid.T[j][i] = (1.0 / 60.0) * (-(grid.T[j - 2][i] + grid.T[j + 2][i] + grid.T[j][i - 2] + grid.T[j][i + 2]) +
                                                   16.0 * (grid.T[j + 1][i] + grid.T[j - 1][i] + grid.T[j][i + 1] + grid.T[j][i - 1]));
                }

                erro = std::max(erro, std::abs(grid.T[j][i] - T_old));
            }
        }

        if (erro < tol)
        {
            std::cout << "Convergência em " << it << " iterações.\n";
            break;
        }
    }
}