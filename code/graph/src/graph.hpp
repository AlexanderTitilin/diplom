#pragma once
#include "baseGraph.hpp"
#include <vector>
#include <algorithm>
class Graph : public BaseGraph{
    // const int n;
    std ::vector<std::vector<int>> adjacency_list;

  public:
    Graph(int n_vertecies);
    void add_edge(int v, int u) override;
    bool has_edge(int v, int u) const override;
    int deg(int v) const override;
    std::vector<int> get_neighbours(int v) const override;
};

Graph::Graph(int n_vertecies) 
    :BaseGraph(n_vertecies), adjacency_list(n_vertecies) {}

bool Graph::has_edge(int v , int u) const {
    const auto &curr_list = adjacency_list[v];
    return std::find(curr_list.begin(),curr_list.end(),u) != curr_list.end();
}
void Graph::add_edge(int v, int u) {
    if ( !has_edge(v,u) ) {
        adjacency_list[v].push_back(u);
        adjacency_list[u].push_back(v);
    }
}
std::vector<int> Graph::get_neighbours(int v) const {
    return adjacency_list[v];
}

int Graph::deg(int v) const {
    return adjacency_list[v].size();
}
