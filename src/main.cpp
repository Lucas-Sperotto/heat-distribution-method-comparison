#include "grid.hpp"
#include "fd_solver.hpp"
#include "fem_solver.hpp"
#include "efg_solver.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>  // para std::setprecision

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
    int nx = 41, ny = 41;
    double a = 1.0, b = 1.0;

    Grid placa(nx, ny, a, b);
    placa.aplicarCondicoesDeContorno();

    double tol = 1e-6;
    int maxIter = 10000;
    

    std::chrono::steady_clock::time_point start, end;
    double time_fd, time_fem, time_efg;

    // --- Método de Diferenças Finitas ---
    start = std::chrono::steady_clock::now();
    resolverDifFinita(placa, tol, maxIter);
    salvarResultado(placa, "data/resultado_fd.txt");
    std::cout << "Resultado salvo em data/resultado_fd.txt\n";
    end = std::chrono::steady_clock::now();
    time_fd = std::chrono::duration<double>(end - start).count();


    // --- Método dos Elementos Finitos ---
    start = std::chrono::steady_clock::now();
    resolverFEM(placa);
    salvarResultado(placa, "data/resultado_fem.txt");
    std::cout << "Resultado salvo em data/resultado_fem.txt\n";
    end = std::chrono::steady_clock::now();
    time_fem = std::chrono::duration<double>(end - start).count();




    // --- Método Element Free Galerkin ---
    start = std::chrono::steady_clock::now();
    resolverEFG(placa);
    salvarResultado(placa, "data/resultado_efg.txt");
    std::cout << "Resultado salvo em data/resultado_efg.txt\n";
    end = std::chrono::steady_clock::now();
    time_efg = std::chrono::duration<double>(end - start).count();

    // --- Imprimir os tempos na tela ---
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Tempo de execucao (s):\n";
    std::cout << "Diferenças Finitas:     " << time_fd  << " s\n";
    std::cout << "Elementos Finitos:      " << time_fem << " s\n";
    std::cout << "Element Free Galerkin:  " << time_efg << " s\n";

    // --- Salvar os tempos em CSV ---
    std::ofstream file("tempos_execucao.csv");
    file << "Metodo,Tempo(s)\n";
    file << "Diferencas Finitas," << time_fd << "\n";
    file << "Elementos Finitos," << time_fem << "\n";
    file << "Element Free Galerkin," << time_efg << "\n";
    file.close();

    
    return 0;
}
