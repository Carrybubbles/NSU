#include "graph.h"

EGraph::EGraph():edge_list_() {}

EGraph::~EGraph(){}

void EGraph::add_edge(std::pair<float,float> edge)
{
    std::vector<std::pair<float,float> >::iterator it;
    std::pair<float,float> reverse = std::make_pair(edge.second,edge.first);

    it  = std::find(std::begin(edge_list_), std::end(edge_list_), edge);
    if(it == edge_list_.end()){
        edge_list_.push_back(edge);
    }

    it  = std::find(std::begin(edge_list_), std::end(edge_list_), reverse);
    if(it == edge_list_.end()){
        edge_list_.push_back(reverse);
    }
    return;
}

void EGraph::make_graph()
{
    std::fstream file;
    file.open("Dgraph.txt", std::ios_base::in);
    float vertex1 = 0;
    float vertex2 = 0;
    while(file  >> vertex1 && file >> vertex2 ){
        if(vertex1 < 0 || vertex2 < 0){
            throw std::invalid_argument("Enter vertex > 0");
        }
        add_edge(std::make_pair(vertex1,vertex2));
    }
    return;
}

const std::vector<float> EGraph::get_all_vertex() const
{
    std::vector<float> all_vertex;
    std::for_each(std::begin(edge_list_), std::end(edge_list_),[&](const std::pair<float,float>& edge){
        std::vector<float>::const_iterator it;
        it = std::find(std::begin(all_vertex), std::end(all_vertex), edge.first);
        if(it == all_vertex.end()){
            all_vertex.push_back(edge.first);
        }
        it = std::find(std::begin(all_vertex), std::end(all_vertex), edge.second);
        if(it == all_vertex.end()){
            all_vertex.push_back(edge.second);
        }
    });
    return all_vertex;
}

bool EGraph::is_contain_ver(const float& vertex) const
{
    std::vector<std::pair<float,float> >::const_iterator it;
    it = std::find_if(std::begin(edge_list_), std::end(edge_list_), [=](const std::pair<float,float>& ver){
        return ver.first  == vertex;
    });
    return it != edge_list_.end();
}

int EGraph::get_deg(const float &vertex) const
{
    std::vector<float> adj_ver = get_adj_vertexes(vertex);
    return adj_ver.size();
}

float EGraph::get_neighbour(const float &vertex) const
{
    std::vector<std::pair<float,float> >::const_iterator it;
    it = std::find_if(std::begin(edge_list_), std::end(edge_list_), [=](const std::pair<float,float> cur_edge){
        return cur_edge.first == vertex;
    });
    return it->second;
}

void EGraph::remove_edge(const float &A, const float &B)
{
    std::vector<std::pair<float,float> >::iterator it;
    std::pair<float,float> edge = std::make_pair(A,B);
    std::pair<float,float> Redge = std::make_pair(B,A);
    it = std::find_if(std::begin(edge_list_), std::end(edge_list_), [=](const std::pair<float,float>& cur_edge){
       return cur_edge == edge;
    });
    edge_list_.erase(it);
    it = std::find_if(std::begin(edge_list_), std::end(edge_list_), [=](const std::pair<float,float>& cur_edge){
       return cur_edge == Redge;
    });
    edge_list_.erase(it);
    return;
}

std::vector<float> EGraph::get_adj_vertexes(const float& vertex) const
{
    std::vector<float> adj_vertexes;
    std::for_each(std::begin(edge_list_), std::end(edge_list_),
                  [&adj_vertexes, vertex](const std::pair<float,float>& edge ){
        if(edge.first == vertex){
            adj_vertexes.push_back(edge.second);
        }else if(edge.second == vertex){
            adj_vertexes.push_back(edge.first);
        }
    });
    return adj_vertexes;
}

std::ostream& operator<<(std::ostream& out, const EGraph& _graph)
{
    std::for_each(std::begin(_graph.edge_list_), std::end(_graph.edge_list_),
                  [&out](const std::pair<float,float>& edge){out << edge.first << " " << edge.second << std::endl;});
    return out;
}


void EGraph::mark(const float &vertex)
{
    black_vertex.push_back(vertex);
}

bool EGraph::is_mark(const float &vertex) const
{
    std::vector<float>::const_iterator it;
    it = std::find(std::begin(black_vertex), std::end(black_vertex), vertex);
    return it != black_vertex.end();
}
