#include "linear_solvers.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <iostream>

void gaussSolve(std::vector<std::vector<double>>& A,
                std::vector<double>& b,
                std::vector<double>& x)
{
    int n = A.size();
    x.resize(n);

    for (int i = 0; i < n; ++i) {
        // Pivotamento parcial
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Checagem para divisão por zero
        if (std::abs(A[i][i]) < 1e-12)
            throw std::runtime_error("Matriz singular ou mal condicionada.");

        // Eliminação
        for (int k = i + 1; k < n; ++k) {
            double f = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= A[i][j] * f;
            }
            b[k] -= b[i] * f;
        }
    }

    // Substituição regressiva
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void resolverSistemaLinear(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b,
    std::vector<double>& x,
    const std::string& metodo)
{
    std::vector<std::vector<double>> A_copy = A;
    std::vector<double> b_copy = b;

    if (metodo == "gauss") {
        gaussSolve(A_copy, b_copy, x);
    } else {
        throw std::invalid_argument("Método de resolução desconhecido: " + metodo);
    }
}
