#ifndef MGRAPH_H
#define MGRAPH_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <fstream>

class MGraph final
{
public:
    MGraph();
    ~MGraph();
    void add_edge(const int& A, const int& B);
    void make_graph();
    bool is_contain_ver(const int& vertex) const;
    std::vector<int> get_all_vertex() const ;
    int get_deg(const int& vertex) const;
    int get_neighbour(const int& vertex) const ;
    void remove_edge(const int& A, const int& B);
    std::vector<int> get_adj_vertexes(const int& vertex) const ;
    void mark(const int& vertex);
    bool is_mark(const int& vertex) const;
    friend std::ostream& operator<<(std::ostream& out, const MGraph& _graph);
private:
    void resize(const int& x ,const int& y);
    std::vector<std::vector<int> > Mvertex;
    std::vector<int> black_vertex;
};

#endif // MGRAPH_H
