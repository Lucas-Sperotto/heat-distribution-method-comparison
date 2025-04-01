#include "grid.hpp"

// Inicializa malha e temperatura com zero
Grid::Grid(int nx_, int ny_, double a_, double b_)
    : nx(nx_), ny(ny_), a(a_), b(b_)
{
    dx = a / (nx - 1);
    dy = b / (ny - 1);
    T = std::vector<std::vector<double>>(ny, std::vector<double>(nx, 0.0));
}

// Exemplo de condição de contorno
void Grid::aplicarCondicoesDeContorno() {
    // Bordas horizontais
    for (int i = 0; i < nx; i++) {
        T[0][i] = 100.0;           // y = 0
        //T[1][i] = 100.0; 
        T[ny - 1][i] = 0.0;        // y = b
        //T[ny - 2][i] = 0.0; 
    }

    // Bordas verticais
    for (int j = 0; j < ny; j++) {
        T[j][0] = 75.0;            // x = 0
        //T[j][1] = 75.0;
        T[j][nx - 1] = 50.0;       // x = a
        //T[j][nx - 2] = 50.0;
    }
}
