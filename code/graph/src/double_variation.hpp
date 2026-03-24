#pragma once
#include "graph.hpp"
#include "graphs_algorithm.hpp"
#include <filesystem>
#include <fstream>
#include <functional>
#include <random>
#include <string>
#include <vector>
#include <iostream>
#include "variation_utils.hpp"
class RandomVariation {
    const int n_verices;
    const int n_graphs;
    const double epsilon;
    const std::string filename;
    std::vector<double> lattice;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> uniform;
    std::vector<std::vector<double>> sizes;
    std::function<double(const Graph &)> func;
    double start;
    double end;
    void variation();

  public:
    RandomVariation(int n, double eps, int m, int k, std::string f,
                    std::function<double(const Graph &)> function);
    void experiment();
    void save_results();
};
RandomVariation::RandomVariation(int n, double eps, int m, int k, std::string f,
                                 std::function<double(const Graph &)> function)
    : n_verices(n), epsilon(eps), n_graphs(m), filename(f), gen(rd()),
      uniform(0, 1), func{function}, start{(1 - eps) / n}, end{(1 + eps) / n} {

          lattice = utils::gen_lattice(n,k,start,end);
}

void RandomVariation::variation() {
    std::vector<double> result;
    std::vector<double> probs;
    int N = (n_verices * (n_verices - 1)) / 2;
    for (int i = 0; i < N; i++) {
        probs.push_back(uniform(gen));
    }
    for (double p : lattice) {
        Graph g = utils::random_graph(p, probs,n_verices);
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
        out << n_verices << " " << epsilon << std::endl;
        for (double p : lattice) {
            out << p << " ";
        }
        out << std::endl;
    }
    for (std::vector<double> sizes : sizes) {
        for (double i : sizes) {
            out << i << " ";
        }
        out << std::endl;
    }
    out.close();
}
