// include/fd_solver.hpp
#ifndef FD_SOLVER_HPP
#define FD_SOLVER_HPP

#include "grid.hpp"

void resolverDifFinita(Grid& grid, double tol, int maxIter, int ordem);

void resolverOrdem_2(Grid &grid, double tol, int maxIter);
void resolverOrdem_4(Grid &grid, double tol, int maxIter);
void resolverOrdem_6(Grid &grid, double tol, int maxIter);

#endif
