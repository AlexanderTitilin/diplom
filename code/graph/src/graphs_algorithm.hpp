#pragma once
#include "baseGraph.hpp"
#include "graph.hpp"
#include <algorithm>
#include <queue>
#include <random>
#include <stack>
#include <vector>
long count_triplets(const Graph &g) {
    long triplets = 0;
    for (int v = 0; v < g.get_n(); v++) {
        const long d = g.deg(v);
        triplets += d * (d-1) / 2;
    }
    return triplets;
}
double doulion(const Graph &g, const double p) {
    double result = 0;
    const int n = g.get_n();
    Graph g2 = Graph(n);
    std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution coin(p);
    for (int v = 0; v < n; v++) {
        for (int u : g.get_neighbours(v)) {
            if (u > v && coin(rng)) {
                g2.add_edge(v, u);
            }
        }
    }
    for (int v = 0; v < n; v++) {
        const auto &neib = g2.get_neighbours(v);
        for (auto u : neib) {
            for (auto w : neib) {
                if (u < v && v < w && g2.has_edge(u, w)) {
                    result++;
                }
            }
        }
    }
    result = result / (p * p * p);
    return result;
}
long long count_triangles(const Graph &g) {
    const int n = g.get_n();
    long long triangles = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                const bool ij = g.has_edge(i, j);
                const bool ik = g.has_edge(i, k);
                const bool jk = g.has_edge(j, k);
                const int edges = ij + ik + jk;
                if (edges == 3) {
                    triangles++;
                }
            }
        }
    }
    return triangles;
}

double clustering_coeff_doulion(const Graph &g,const double p) {
    const long long triplets = count_triplets(g);
    const double triangles = doulion(g,p);
    if (triplets == 0) {
        return 0.0;
    }
    return 3.0 * triangles / triplets;
}
double clustering_coeff_naive(const Graph &g) {
    const long long triplets = count_triplets(g);
    const long triangles = count_triangles(g);
    if (triplets == 0) {
        return 0.0;
    }
    return 3.0 * triangles / triplets;
}
int first_connected_component_size(const Graph &g) {
    // find first connected component 
    int result = 0;
    const int n = g.get_n();
    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    for (int start = 0; start < n; start++) {
        if (visited[start]) {
            continue;
        }
        const auto &neib = g.get_neighbours(start);
        stack.push(start);
        visited[start] = true;
        while (!stack.empty()) {
            const int v = stack.top();
            stack.pop();
            result++;
            const auto &neib = g.get_neighbours(v);
            for (auto u : neib) {
                if (!visited[u]) {
                    stack.push(u);
                    visited[u] = true;
                }
            }
        }
        return result;
    }
    return 0;
}
bool is_path(const BaseGraph &g, const std::vector<int> vertices) {
    for (int i = 0; i < vertices.size() - 1; i++) {
        int v = vertices[i];
        int u = vertices[i + 1];
        if (!g.has_edge(v, u)) {
            return false;
        }
    }
    return true;
}

enum class State { Unvisited, Stack, Visited };
int max_path(const Graph &g) {
    int result = 0;
    const int n = g.get_n();
    std::vector<State> visited(n, State::Unvisited);
    std::stack<int> stack;
    for (int start = 0; start < n; start++) {
        if (visited[start] != State::Unvisited) {
            continue;
        }
        stack.push(start);
        visited[start] = State::Stack;
        while (!stack.empty()) {
            if (stack.size() > result) {
                result = stack.size();
            }
            const int v = stack.top();
            bool f = true;
            const auto &neib = g.get_neighbours(v);
            for (auto u : neib) {
                if (visited[u] == State::Unvisited) {
                    stack.push(u);
                    visited[u] = State::Stack;
                    f = false;
                    break;
                }
            }
            if (f) {
                visited[v] = State::Visited;
                stack.pop();
            }
        }
    }
    return result;
}
std::vector<int> shortest_paths(const BaseGraph &g, const int source) {
    const int n = g.get_n();
    std::vector<int> dists(n, -1);
    dists[source] = 0;
    std::queue<int> queue;
    queue.push(source);
    while (!queue.empty()) {
        const int v = queue.front();
        queue.pop();
        const auto &neibs = g.get_neighbours(v);
        for (auto u : neibs) {
            if (dists[u] == -1) {
                dists[u] = dists[v] + 1;
                queue.push(u);
            }
        }
    }
    return dists;
}
std::vector<std::vector<int>> connected_components(const BaseGraph &g) {
    const int n = g.get_n();
    std::vector<std::vector<int>> components{};
    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    for (int start = 0; start < n; start++) {
        if (visited[start]) {
            continue;
        }
        std::vector<int> component;
        stack.push(start);
        visited[start] = true;
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            component.push_back(v);
            const auto &neibs = g.get_neighbours(v);
            for (auto u : neibs) {
                if (!visited[u]) {
                    visited[u] = true;
                    stack.push(u);
                }
            }
        }
        components.push_back(component);
    }
    return components;
}

int count_connected_components(const BaseGraph &g) {
    const int n = g.get_n();
    int result = 0;
    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    for (int start = 0; start < n; start++) {
        if (visited[start]) {
            continue;
        }
        visited[start] = true;
        stack.push(start);
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            const auto &neibs = g.get_neighbours(v);
            for (auto u : neibs) {
                if (!visited[u]) {
                    visited[u] = true;
                    stack.push(u);
                }
            }
        }
        result++;
    }
    return result;
}
int connected_components_max_size(const BaseGraph &g) {
    const int n = g.get_n();
    int result = 0;
    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    for (int start = 0; start < n; start++) {
        if (visited[start]) {
            continue;
        }
        visited[start] = true;
        int curr_size = 0;
        stack.push(start);
        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();
            curr_size++;
            const auto &neibs = g.get_neighbours(v);
            for (auto u : neibs) {
                if (!visited[u]) {
                    visited[u] = true;
                    stack.push(u);
                }
            }
        }
        result = std::max(result, curr_size);
    }
    return result;
}
