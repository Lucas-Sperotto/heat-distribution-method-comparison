#include "grid.hpp"
#include "fd_solver.hpp"
#include "fem_solver.hpp"
#include "efg_solver.hpp"
#include <iostream>
#include <fstream>

void salvarResultado(const Grid& grid, const std::string& filename) {
    std::ofstream out(filename);
    for (int j = 0; j < grid.ny; j++) {
        for (int i = 0; i < grid.nx; i++) {
            out << grid.T[j][i] << " ";
        }
        out << "\n";
    }
}

int main() {
    int nx = 401, ny = 401;
    double a = 1.0, b = 1.0;

    Grid placa(nx, ny, a, b);
    placa.aplicarCondicoesDeContorno();

    double tol = 1e-6;
    int maxIter = 10000;
    
   // resolverDifFinita(placa, tol, maxIter);
   // salvarResultado(placa, "data/resultado_fd.txt");
   // std::cout << "Resultado salvo em data/resultado_fd.txt\n";


   // resolverFEM(placa);
   // salvarResultado(placa, "data/resultado_fem.txt");
   // std::cout << "Resultado salvo em data/resultado_fem.txt\n";

    resolverEFG(placa);
    salvarResultado(placa, "data/resultado_efg.txt");
    std::cout << "Resultado salvo em data/resultado_efg.txt\n";


    
    return 0;
}
