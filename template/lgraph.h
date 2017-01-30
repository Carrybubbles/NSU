#ifndef LGRAPH_H
#define LGRAPH_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <list>


class LGraph final
{
public:
    typedef std::pair<std::string, std::vector<std::string> > Pvertex;
    LGraph();
    ~LGraph();
    void add_edge(const std::string& A, const std::string& B);
    void make_graph();
    std::vector<std::string> get_all_vertex() const;
    bool is_contain_ver(const std::string& vertex) const;
    int get_deg(const std::string& vertex) const;
    std::string get_neighbour(const std::string& vertex) const;
    void remove_edge(const std::string& A, const std::string& B);
    void mark(const std::string& vertex);
    bool is_mark(const std::string& vertex) const;
    std::vector<std::string> get_adj_vertexes(const std::string& vertex) const ;
    friend std::ostream&  operator<<(std::ostream& out, const LGraph& _graph);
private:
    //typedef std::pair<std::string, std::vector<std::string> >  Pvertex;
    std::list<Pvertex> Gvertex_;
    std::vector<std::string> black_vertex;
};

#endif // LGRAPH_H
