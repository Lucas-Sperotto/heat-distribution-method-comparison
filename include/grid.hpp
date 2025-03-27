// include/grid.hpp
#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

class Grid {
public:
    int nx, ny;       // número de pontos em x e y
    double a, b;      // dimensões da placa
    double dx, dy;    // espaçamentos

    std::vector<std::vector<double>> T;  // temperatura

    Grid(int nx, int ny, double a, double b);
    void aplicarCondicoesDeContorno();
};

#endif
