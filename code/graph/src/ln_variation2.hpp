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
    const std::string filename1;
    const std::string filename2;
    std::vector<double> lattice;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> uniform;
    std::vector<std::vector<double>> cluster_k2;
    std::vector<std::vector<double>> cluster_k1;
    double start;
    double end;
    void variation();

  public:
    RandomVariation(int n, double c1, double c2, int m, int k, std::string f,
                    std::string f2);
    void experiment();
    void save_results();
};
RandomVariation::RandomVariation(int n, double num1, double num2, int m, int k,
                                 std::string f1, std::string f2)
    : n_verices(n), n_graphs(m), filename1(f1), filename2(f2), gen(rd()),
      uniform(0, 1), c1{num1}, c2{num2},  start{(num1 * std::log(n) / n)},
      end{(num2 * std::log(n) / n)} {

    lattice = utils::gen_lattice(n, k, start, end, std::log(n) / n);
}

void RandomVariation::variation() {
    std::vector<double> result1;
    std::vector<double> result2;
    std::vector<double> probs;
    int N = (n_verices * (n_verices - 1)) / 2;
    for (int i = 0; i < N; i++) {
        probs.push_back(uniform(gen));
    }
    for (double p : lattice) {
        Graph g = utils::random_graph(p, probs, n_verices);
        result1.push_back(clustering_coeff_naive(g));
        std::vector<double> cluster_vec;
        for (int i =0 ; i < 10;i++) {
            cluster_vec.push_back(clustering_coeff_doulion(g,0.2));
        }
        result2.push_back(std::accumulate(cluster_vec.begin(),cluster_vec.end(),0.0)/10);
    }
    cluster_k1.push_back(result1);
    cluster_k2.push_back(result2);
}

void RandomVariation::experiment() {
    for (int i = 0; i < n_graphs; i++) {
        variation();
    }
}
void RandomVariation::save_results() {
    std::ofstream out(filename1, std::ios::app);
    if (std::filesystem::is_empty(filename1)) {
        out << n_verices << " " << c1 << " " << c2 << std::endl;
        for (double p : lattice) {
            out << p << " ";
        }
        out << std::endl;
    }
    for (std::vector<double> cluster_k : cluster_k1) {
        for (double i : cluster_k) {
            out << i << " ";
        }
        out << std::endl;
    }
    out.close();
    std::ofstream out2(filename2, std::ios::app);
    if (std::filesystem::is_empty(filename2)) {
        out2 << n_verices << " " << c1 << " " << c2 << std::endl;
        for (double p : lattice) {
            out2 << p << " ";
        }
        out2 << std::endl;
    }
    for (std::vector<double> cluster_k : cluster_k2) {
        for (double i : cluster_k) {
            out2 << i << " ";
        }
        out2 << std::endl;
    }
    out2.close();
}
