#include "mgraph.h"

MGraph::MGraph():Mvertex(), black_vertex(){}
MGraph::~MGraph(){}

void MGraph::add_edge(const int& A, const int& B)
{
    unsigned max = std::max(A,B);
    if(max < Mvertex.size()){
        Mvertex[A][B] = 1;
        Mvertex[B][A] = 1;
    }else{
       resize(max,max);
       Mvertex[A][B] = 1;
       Mvertex[B][A] = 1;
   }
}

void MGraph::resize(const int &x, const int &y)
{
   Mvertex.resize(y + 1);
   std::for_each(std::begin(Mvertex), std::end(Mvertex),
                 [=](std::vector<int>& row){row.resize(x + 1);});
}


void MGraph::make_graph()
{
   std::fstream file;
   file.open("graph.txt", std::ios_base::in);
   int vertex1 = 0;
   int vertex2 = 0;
   while(file  >> vertex1 && file >> vertex2 ){
       if(vertex1 < 0 || vertex2 < 0){
           throw std::invalid_argument("Enter vertex > 0");
       }
       add_edge(vertex1, vertex2);
   }
   return;
}

bool MGraph::is_contain_ver(const int &vertex) const
{
   for(unsigned i = 0 ;i < Mvertex.size(); i++){
       for(unsigned j = 0; j < Mvertex.size(); j++){
           if(Mvertex[i][j] && static_cast<int>(i) == vertex){
               return true;
           }
       }
   }
   return false;
}


std::vector<int> MGraph::get_all_vertex() const
{
    std::vector<int> all_vertex;
    for(unsigned i = 0 ; i < Mvertex.size();++ i){
        for(unsigned j = 0; j < Mvertex.size(); ++j){
            if(Mvertex[i][j]){
                std::vector<int>::iterator it;
                it = std::find(std::begin(all_vertex), std::end(all_vertex), i);
                if(it == all_vertex.end()){
                    all_vertex.push_back(i);
                }
            }
        }
    }
    return all_vertex;
}

int MGraph::get_deg(const int &vertex) const
{
    std::vector<int> adj_ver = get_adj_vertexes(vertex);
    return adj_ver.size();
}

int MGraph::get_neighbour(const int &current_vertex) const
{
    for(unsigned i = 0; i < Mvertex.size(); i++){
        if(Mvertex[current_vertex][i]){
            return i;
        }
    }
    return 0;
}

void MGraph::remove_edge(const int &A, const int &B)
{
    Mvertex[A][B] = 0;
    Mvertex[B][A] = 0;
}

std::vector<int> MGraph::get_adj_vertexes(const int &vertex) const
{
    std::vector<int> adj_vertexes;
    for(unsigned i  = 0; i < Mvertex.size(); i++){
        if(Mvertex[vertex][i]){
            adj_vertexes.push_back(i);
        }
    }
    return adj_vertexes;
}

void MGraph::mark(const int &vertex)
{
    black_vertex.push_back(vertex);
}

bool MGraph::is_mark(const int &vertex) const
{
    std::vector<int>::const_iterator it;
    it = std::find(std::begin(black_vertex), std::end(black_vertex), vertex);
    return it != black_vertex.end();
}

std::ostream& operator<<(std::ostream& out, const MGraph& _graph){

    int i = 0;
    std::for_each(std::begin(_graph.Mvertex), std::end(_graph.Mvertex),
                  [&out, &i](const std::vector<int>& temp){
        int j = 0;
        std::for_each(std::begin(temp), std::end(temp), [&j, &out, &i, temp](const int& ver){
            if(ver == 1){
                out << i << " " << j <<std::endl;
            }
        j++;});
    i++;});

   return out;
}
