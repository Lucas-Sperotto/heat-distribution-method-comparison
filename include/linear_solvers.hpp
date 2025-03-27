#ifndef LINEAR_SOLVERS_HPP
#define LINEAR_SOLVERS_HPP

#include <vector>
#include <string>

// Interface geral
void resolverSistemaLinear(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b,
    std::vector<double>& x,
    const std::string& metodo = "gauss"
);

// Método de Gauss com pivotamento parcial
void gaussSolve(std::vector<std::vector<double>>& A,
                std::vector<double>& b,
                std::vector<double>& x);

#endif
