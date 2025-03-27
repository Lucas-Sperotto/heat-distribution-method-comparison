CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -I/usr/include/eigen3

SRC = src/main.cpp src/grid.cpp src/fd_solver.cpp src/fem_solver.cpp src/efg_solver.cpp src/linear_solvers.cpp
OUT = heat_solver

all:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
