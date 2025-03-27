#include "efg_solver.hpp"
#include "grid.hpp"
#include "linear_solvers.hpp"

#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

// Protótipo
struct MLSResult;
MLSResult calcularMLS(const Grid &grid, double x, double y, double raio);

struct MLSResult
{
    std::vector<int> indices;
    Eigen::VectorXd phi;
    Eigen::VectorXd dphi_dx;
    Eigen::VectorXd dphi_dy;
};

void resolverEFG(Grid &grid)
{
    int nx = grid.nx, ny = grid.ny;
    int N = nx * ny;

    std::vector<std::vector<double>> K(N, std::vector<double>(N, 0.0));
    std::vector<double> F(N, 0.0);
    std::vector<double> T(N, 0.0);

    double raio = 3.0 * std::max(grid.dx, grid.dy);
    double area = grid.dx * grid.dy;

    for (int j = 1; j < ny - 1; ++j)
    {
        for (int i = 1; i < nx - 1; ++i)
        {
            double x = i * grid.dx;
            double y = j * grid.dy;

            MLSResult mls = calcularMLS(grid, x, y, raio);

            int n = mls.indices.size();
            for (int a = 0; a < n; ++a)
            {
                for (int b = 0; b < n; ++b)
                {
                    int ia = mls.indices[a];
                    int ib = mls.indices[b];

                    double dphi_dx_a = mls.dphi_dx(a);
                    double dphi_dy_a = mls.dphi_dy(a);
                    double dphi_dx_b = mls.dphi_dx(b);
                    double dphi_dy_b = mls.dphi_dy(b);

                    double integrando = (dphi_dx_a * dphi_dx_b + dphi_dy_a * dphi_dy_b);

                    K[ia][ib] += mls.phi(a) * mls.phi(b) * area; // K[ia][ib] += integrando * area; // peso da malha de fundo
                }
            }
        }
    }

    // Condições de contorno de Dirichlet
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            int id = j * nx + i;
            if (i == 0 || i == nx - 1 || j == 0 || j == ny - 1)
            {
                for (int k = 0; k < N; ++k)
                    K[id][k] = 0.0;
                K[id][id] = 1.0;
                F[id] = grid.T[j][i];
            }
        }
    }

    resolverSistemaLinear(K, F, T, "gauss");

    for (int j = 0; j < ny; ++j)
        for (int i = 0; i < nx; ++i)
            grid.T[j][i] = T[j * nx + i];
}

std::vector<int> obterNosVizinhos(double x, double y, const Grid &grid, double raio)
{
    std::vector<int> vizinhos;

    for (int j = 0; j < grid.ny; ++j)
    {
        for (int i = 0; i < grid.nx; ++i)
        {
            double xi = i * grid.dx;
            double yj = j * grid.dy;

            double dist = std::sqrt((x - xi) * (x - xi) + (y - yj) * (y - yj));

            if (dist <= raio)
            {
                int id = j * grid.nx + i;
                vizinhos.push_back(id);
            }
        }
    }

    return vizinhos;
}

double peso_schwarz(double distancia, double raio)
{
    double r = distancia / raio;
    if (r >= 1.0)
        return 0.0;
    return 1.0 - 6.0 * r * r + 8.0 * r * r * r - 3.0 * r * r * r * r;
}

Eigen::VectorXd calcularPhiMLS(double x, double y,
                               const std::vector<int> &vizinhos,
                               const Grid &grid,
                               double raio)
{
    // using namespace Eigen;

    int m = 3; // base linear: [1, x, y]
    int n = vizinhos.size();

    Eigen::MatrixXd P(n, m);
    Eigen::VectorXd W(n);
    Eigen::VectorXd p0(m);

    int nx = grid.nx;

    for (int a = 0; a < n; ++a)
    {
        int id = vizinhos[a];
        int j = id / nx;
        int i = id % nx;

        double xi = i * grid.dx;
        double yi = j * grid.dy;
        double dx = x - xi;
        double dy = y - yi;

        double dist = std::sqrt(dx * dx + dy * dy);
        double w = peso_schwarz(dist, raio);

        P(a, 0) = 1.0;
        P(a, 1) = xi;
        P(a, 2) = yi;

        W(a) = w;
    }

    p0 << 1.0, x, y;

    Eigen::MatrixXd A = P.transpose() * W.asDiagonal() * P;
    Eigen::VectorXd coeffs = A.ldlt().solve(P.transpose() * W);

    // phi_i(x,y) = p0^T * A^{-1} * p_i^T * w_i
    Eigen::VectorXd phi(n);
    for (int a = 0; a < n; ++a)
    {
        phi[a] = p0.transpose() * coeffs.col(a);
    }

    return phi;
}
MLSResult calcularMLS(const Grid &grid, double x, double y, double raio)
{
    using namespace Eigen;

    int nx = grid.nx;
    int ny = grid.ny;

    std::vector<int> indices;
    std::vector<Vector2d> coords;

    // Buscar nós dentro do raio
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            double xi = i * grid.dx;
            double yj = j * grid.dy;
            double dx = x - xi;
            double dy = y - yj;
            double dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= raio)
            {
                indices.push_back(j * nx + i);
                coords.emplace_back(xi, yj);
            }
        }
    }

    int n = indices.size();
    const int m = 3; // base linear: [1, x, y]

    MatrixXd P(n, m);
    VectorXd W(n);
    MatrixXd dW_dx = MatrixXd::Zero(n, 1);
    MatrixXd dW_dy = MatrixXd::Zero(n, 1);

    for (int a = 0; a < n; ++a)
    {
        double xi = coords[a][0];
        double yi = coords[a][1];
        double dx = x - xi;
        double dy = y - yi;
        double dist = std::sqrt(dx * dx + dy * dy);
        double r = dist / raio;

        double w = (r >= 1.0) ? 0.0 : (1.0 - 6 * r * r + 8 * r * r * r - 3 * r * r * r * r);
        W(a) = w;

        P(a, 0) = 1.0;
        P(a, 1) = xi;
        P(a, 2) = yi;

        if (dist > 1e-8 && r < 1.0)
        {
            double dwdr = -12.0 * r + 24.0 * r * r - 12.0 * r * r * r;
            double dw = dwdr / raio;
            dW_dx(a, 0) = dw * dx / dist;
            dW_dy(a, 0) = dw * dy / dist;
        }
    }

    Vector3d p0(1.0, x, y);
    MatrixXd Wdiag = W.asDiagonal();

    MatrixXd A = P.transpose() * Wdiag * P;

    // Verificação de condição da matriz
    if (std::abs(A.determinant()) < 1e-10)
    {
        std::cerr << "⚠️ Matriz A mal condicionada em (" << x << ", " << y << "), det = " << A.determinant() << "\n";
    }

    MatrixXd Ainv = A.inverse();
    MatrixXd B = Ainv * P.transpose() * Wdiag;
    VectorXd phi = B.transpose() * p0;

    // Derivadas
    MatrixXd A_x = P.transpose() * dW_dx.asDiagonal() * P;
    MatrixXd A_y = P.transpose() * dW_dy.asDiagonal() * P;

    MatrixXd dAinv_dx = -Ainv * A_x * Ainv;
    MatrixXd dAinv_dy = -Ainv * A_y * Ainv;

    VectorXd dp0_dx(m);
    dp0_dx << 0.0, 1.0, 0.0;
    VectorXd dp0_dy(m);
    dp0_dy << 0.0, 0.0, 1.0;

    MatrixXd dB_dx = dAinv_dx * P.transpose() * Wdiag + Ainv * P.transpose() * dW_dx.asDiagonal();
    MatrixXd dB_dy = dAinv_dy * P.transpose() * Wdiag + Ainv * P.transpose() * dW_dy.asDiagonal();

    VectorXd dphi_dx = dB_dx.transpose() * p0 + B.transpose() * dp0_dx;
    VectorXd dphi_dy = dB_dy.transpose() * p0 + B.transpose() * dp0_dy;

    MLSResult r;
    r.indices = indices;
    r.phi = phi;
    r.dphi_dx = dphi_dx;
    r.dphi_dy = dphi_dy;
    return r;
}
