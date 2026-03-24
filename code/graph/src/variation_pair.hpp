#pragma once
#include "graph.hpp"
#include "graphs_algorithm.hpp"
#include "variation_utils.hpp"
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
    const double epsilon;
    const std::string filename1;
    const std::string filename2;
    std::vector<double> lattice;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> uniform;
    std::vector<std::vector<int>> sizes1;
    std::vector<std::vector<int>> sizes2;
    std::function<int(const Graph &)> func1;
    std::function<int(const Graph &)> func2;
    double start;
    double end;
    void variation();

  public:
    RandomVariation(int n, double eps, int m, int k, std::string f1,
                        std::string f2,
                        std::function<int(const Graph &)> function1,
                        std::function<int(const Graph &)> function2);
    void experiment();
    void save_results();
};
RandomVariation::RandomVariation(
    int n, double eps, int m, int k, std::string f1, std::string f2,
    std::function<int(const Graph &)> function1,
    std::function<int(const Graph &)> function2)
    : n_verices(n), epsilon(eps), n_graphs(m), filename1(f1), filename2(f2),
      gen(rd()), uniform(0, 1), func1{function1}, func2(function2),
      start{(1 - eps) / n}, end{(1 + eps) / n} {

    lattice = utils::gen_lattice(n, k, start, end);
}

void RandomVariation::variation() {
    std::vector<int> result1;
    std::vector<int> result2;
    std::vector<double> probs;
    int N = (n_verices * (n_verices - 1)) / 2;
    for (int i = 0; i < N; i++) {
        probs.push_back(uniform(gen));
    }
    for (double p : lattice) {
        Graph g = utils::random_graph(p, probs, n_verices);
        result1.push_back(func1(g));
        result2.push_back(func2(g));
    }
    sizes1.push_back(result1);
    sizes2.push_back(result2);
}

void RandomVariation::experiment() {
    for (int i = 0; i < n_graphs; i++) {
        variation();
    }
}
void RandomVariation::save_results() {
    std::ofstream out(filename1, std::ios::app);
    if (std::filesystem::is_empty(filename1)) {
        out << n_verices << " " << epsilon << std::endl;
        for (double p : lattice) {
            out << p << " ";
        }
        out << std::endl;
    }
    for (std::vector<int> sizes : sizes1) {
        for (int i : sizes) {
            out << i << " ";
        }
        out << std::endl;
    }
    out.close();
    std::ofstream out2(filename2, std::ios::app);
    if (std::filesystem::is_empty(filename2)) {
        out2 << n_verices << " " << epsilon << std::endl;
        for (double p : lattice) {
            out2 << p << " ";
        }
        out2 << std::endl;
    }
    for (std::vector<int> sizes : sizes2) {
        for (int i : sizes) {
            out2 << i << " ";
        }
        out2 << std::endl;
    }
    out2.close();
}
