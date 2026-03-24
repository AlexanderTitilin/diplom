#pragma once
#include "graph.hpp"
#include "graphs_algorithm.hpp"
#include "variation_utils.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class RandomVariation {
    const int n_verices;
    const int n_graphs;
    const double c1;
    const double c2;
    const std::string filename;
    std::vector<double> lattice;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> uniform;
    std::vector<std::vector<int>> sizes;
    std::function<int(const Graph &)> func;
    double start;
    double end;
    void variation();

  public:
    RandomVariation(int n, double c1, double c2, int m, int k, std::string f,
                    std::function<int(const Graph &)> function);
    void experiment();
    void save_results();
};
RandomVariation::RandomVariation(int n, double num1, double num2
        , int m, int k,
                                 std::string f,
                                 std::function<int(const Graph &)> function)
    : n_verices(n), n_graphs(m), filename(f), gen(rd()), uniform(0, 1), c1{num1},c2{num2},
      func{function}, start{(num1 * std::log(n) / n)},
      end{(num2* std::log(n) / n)} {

    lattice = utils::gen_lattice(n, k, start, end, std::log(n) / n);
}

void RandomVariation::variation() {
    std::vector<int> result;
    std::vector<double> probs;
    int N = (n_verices * (n_verices - 1)) / 2;
    for (int i = 0; i < N; i++) {
        probs.push_back(uniform(gen));
    }
    for (double p : lattice) {
        Graph g = utils::random_graph(p, probs, n_verices);
        result.push_back(func(g));
    }
    sizes.push_back(result);
}

void RandomVariation::experiment() {
    for (int i = 0; i < n_graphs; i++) {
        variation();
    }
}
void RandomVariation::save_results() {
    std::ofstream out(filename, std::ios::app);
    if (std::filesystem::is_empty(filename)) {
        out << n_verices << " " << c1 << " " << c2 << std::endl;
        for (double p : lattice) {
            out << p << " ";
        }
        out << std::endl;
    }
    for (std::vector<int> sizes : sizes) {
        for (int i : sizes) {
            out << i << " ";
        }
        out << std::endl;
    }
    out.close();
}
