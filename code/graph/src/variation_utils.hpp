#pragma once
#include "graph.hpp"
#include <random>
#include <vector>
namespace utils {
std::vector<double> gen_lattice(int n, int k, double start, double end) {
    std::vector<double> lattice;
    double mid = 1.0 / n;
    double left_step = (mid - start) / k;
    double right_step = (end - mid) / k;
    lattice.reserve(2 * k);
    for (int i = 0; i < k; ++i) {
        lattice.push_back(start + i * left_step);
    }
    for (int i = 0; i <= k; ++i) {
        lattice.push_back(mid + i * right_step);
    }
    return lattice;
}
std::vector<double> gen_lattice(int n, int k, double start, double end,double mid) {
    std::vector<double> lattice;
    double left_step = (mid - start) / k;
    double right_step = (end - mid) / k;
    lattice.reserve(2 * k);
    for (int i = 0; i < k; ++i) {
        lattice.push_back(start + i * left_step);
    }
    for (int i = 0; i <= k; ++i) {
        lattice.push_back(mid + i * right_step);
    }
    return lattice;
}

Graph random_graph(double p, const std::vector<double> &probs, int n_verices) {

    Graph g = Graph(n_verices);
    int n = 0;
    for (int i = 0; i < n_verices; i++) {
        for (int j = i + 1; j < n_verices; j++) {
            if (probs[n] < p) {
                g.add_edge(i, j);
            }
            n++;
        }
    }
    return g;
}

}; // namespace utils
