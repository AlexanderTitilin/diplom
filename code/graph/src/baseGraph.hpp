#pragma once
#include <vector>

class BaseGraph {
    protected:
        const int n;
    public:
        virtual bool has_edge(int v, int u) const = 0;
        virtual void add_edge(int v, int u) = 0;
        virtual int deg(int v) const  = 0;
        virtual std::vector<int> get_neighbours(int v) const = 0;
        BaseGraph(int n_verticies) : n(n_verticies) {
            
        };
        int get_n() const {
            return n;
        }
};
