#include "fd_solver.hpp"
#include <cmath>
#include <iostream>

void resolverDifFinita(Grid &grid, double tol, int maxIter)
{
    int nx = grid.nx, ny = grid.ny;
    // double dx2 = grid.dx * grid.dx;
    // double dy2 = grid.dy * grid.dy;
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
