#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iterator>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <fstream>

class EGraph final
{
public:
    EGraph();
    ~EGraph();
    void add_edge(std::pair<float,float> edge);
    void make_graph();
    const std::vector<float> get_all_vertex() const;
    bool is_contain_ver(const float& vertex) const;
    int get_deg(const float& vertex) const;
    float get_neighbour(const float& vertex) const ;
    void remove_edge(const float& A, const float& B);
    void mark(const float& vertex);
    bool is_mark(const float& vertex) const;
    std::vector<float> get_adj_vertexes(const float& vertex) const;
    friend std::ostream&  operator<<(std::ostream& out, const EGraph& _graph);
private:
    std::vector<std::pair<float,float> > edge_list_;
    std::vector<float> black_vertex;
};

#endif // GRAPH_H
