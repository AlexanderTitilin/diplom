#pragma once
#include "graph.hpp"
#include <random>

Graph random_gnp(const int n, const double p) {
    std ::random_device rd;
    std ::mt19937 gen(rd());
    std::bernoulli_distribution bern(p);
    Graph result = Graph(n);
    for (int v = 0 ; v < n; v++) {
        for (int u = v + 1; u < n; u++) {
            if (bern(gen)) {
                result.add_edge(v,u);
            }
        }
    }
    return result;
}
