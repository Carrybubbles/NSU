#include "lgraph.h"

LGraph::LGraph():Gvertex_(),black_vertex(){}

LGraph::~LGraph(){}

void LGraph::add_edge(const std::string &A, const std::string &B){
    std::list<LGraph::Pvertex>::iterator it;
    it = std::find_if(std::begin(Gvertex_),std::end(Gvertex_),[&](const LGraph::Pvertex& cur_ver){
        return (A == cur_ver.first);
    });
    if(it == Gvertex_.end()){
        Gvertex_.push_back(std::make_pair(A, std::vector<std::string>(1,B)));
    }else{
        it->second.push_back(B);
    }
}


void LGraph::make_graph()
{
    std::fstream file;
    file.open("Sgraph.txt", std::ios_base::in);
    std::string vertex1;
    std::string vertex2;
    while(file >> vertex1 && file >> vertex2){
        add_edge(vertex1, vertex2);
        add_edge(vertex2, vertex1);
    }
    return;
}

std::vector<std::string> LGraph::get_all_vertex() const
{
    std::vector<std::string> all_vertex;
    std::for_each(std::begin(Gvertex_), std::end(Gvertex_),[&](const LGraph::Pvertex& cur_vertex){
        all_vertex.push_back(cur_vertex.first);
    });
    return all_vertex;
}

bool LGraph::is_contain_ver(const std::string& vertex) const
{
    std::list<LGraph::Pvertex>::const_iterator it;
    it = std::find_if(std::begin(Gvertex_), std::end(Gvertex_),[vertex](const LGraph::Pvertex& cur){
        return cur.first == vertex;
    });
    return it != Gvertex_.end();
}

int LGraph::get_deg(const std::string &vertex) const
{
    std::vector<std::string> adj_ver = get_adj_vertexes(vertex);
    return adj_ver.size();
}

std::string LGraph::get_neighbour(const std::string &current_vertex) const
{
    std::list<LGraph::Pvertex>::const_iterator it;
    it = std::find_if(std::begin(Gvertex_), std::end(Gvertex_), [current_vertex](const LGraph::Pvertex& cur_ver){
        return current_vertex == cur_ver.first;
    });
    return it->second[0];

}

void LGraph::remove_edge(const std::string &A, const std::string &B)
{
    std::list<LGraph::Pvertex>::iterator it;
    std::vector<std::string>::iterator it2;
    it = std::find_if(std::begin(Gvertex_), std::end(Gvertex_), [=](const LGraph::Pvertex& ver_number){
        return ver_number.first == A;
    });
    it2 = std::find_if(std::begin(it->second), std::end(it->second), [=](const std::string& adj_ver ){
        return adj_ver == B;
    });
    it->second.erase(it2);

    it = std::find_if(std::begin(Gvertex_), std::end(Gvertex_), [=](const LGraph::Pvertex& ver_number){
        return ver_number.first == B;
    });
    it2 = std::find_if(std::begin(it->second), std::end(it->second), [=](const std::string& adj_ver ){
        return adj_ver == A;
    });
    it->second.erase(it2);
}

std::vector<std::string> LGraph::get_adj_vertexes(const std::string &cur_vertex) const
{
    std::list<LGraph::Pvertex>::const_iterator it;
    it = std::find_if(std::begin(Gvertex_),std::end(Gvertex_),[=](const LGraph::Pvertex& cur_ver){
        return (cur_vertex == cur_ver.first);
    });
    if(it != Gvertex_.end()){
        return it->second;
    }
}

std::ostream& operator<<(std::ostream& out, const LGraph& _graph)
{
    std::for_each(std::begin(_graph.Gvertex_), std::end(_graph.Gvertex_),
                  [&](const LGraph::Pvertex& vertexes){
        out << vertexes.first << " ";
        std::for_each(std::begin(vertexes.second), std::end(vertexes.second),[&](const std::string& cur_ver){
            out << cur_ver << " ";
        });
        out << std::endl;
    });
    return out;
}


void LGraph::mark(const std::string &vertex)
{
    black_vertex.push_back(vertex);
}

bool LGraph::is_mark(const std::string &vertex) const
{
    std::vector<std::string>::const_iterator it;
    it = std::find(std::begin(black_vertex), std::end(black_vertex), vertex);
    return it != black_vertex.end();
}
