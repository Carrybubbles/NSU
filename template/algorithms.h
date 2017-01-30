#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <queue>

namespace ALGO2000{
    template <class Tgraph, class Tvalue, class Tadj_ver, class Tmarker, class Tismark >
    std::vector<Tvalue> dfs(Tgraph& graph, const Tvalue& start_vertex,
                            const Tadj_ver& adj, const Tmarker& mark,
                            const Tismark& is_mark){
        std::stack<Tvalue> stack_of_vertexes;
        std::vector<Tvalue> result;

        stack_of_vertexes.push(start_vertex);
        while(!stack_of_vertexes.empty()){
            Tvalue cur_vertex = stack_of_vertexes.top();
            stack_of_vertexes.pop();

            if(!is_mark(graph, cur_vertex)){
                mark(graph, cur_vertex);
                result.push_back(cur_vertex);

                // get all edges which adj with cur vertex
                auto adj_vertexes = adj(graph,cur_vertex);
                std::for_each(std::begin(adj_vertexes), std::end(adj_vertexes),
                                      [&stack_of_vertexes](const Tvalue& ver){
                        stack_of_vertexes.push(ver);
                });
            }
        }
        return result;
    }

    template<class T, class Tvalue, class Tallvert, class Tdeleter, class Tdeqer, class Tgetbour >
    std::vector<Tvalue> euler_path(T graph, const Tallvert& get_all_vert,
                                   const Tdeleter& deleter, const Tdeqer& get_deq,
                                   const Tgetbour& get_bout){
        std::stack<Tvalue> Vstack1;
        std::vector<Tvalue> result;
        std::vector<Tvalue> all_vertex = get_all_vert(graph);
        std::vector<Tvalue> odd_vertexes;

        Tvalue start_vertex;
        std::for_each(std::begin(all_vertex), std::end(all_vertex), [&odd_vertexes, &graph, get_deq](const Tvalue& cur_ver){
            if(get_deq(graph,cur_ver) % 2)
                odd_vertexes.push_back(cur_ver);
        });
        typename std::vector<Tvalue>::iterator it;
        it = std::find_if(std::begin(all_vertex), std::end(all_vertex),[&graph,get_deq](const Tvalue& cur_ver){
            return get_deq(graph,cur_ver) % 2 != 0;
        });
        if(it == all_vertex.end()){
            start_vertex = all_vertex[0];
        }else if(odd_vertexes.size() == 2){
            start_vertex = odd_vertexes[0];
        }else{
            throw std::invalid_argument("There no euler path");
        }

        Tvalue cur_vertex = start_vertex;
        Vstack1.push(cur_vertex);
        while(!Vstack1.empty()){
            if(!get_deq(graph,cur_vertex)){
                result.push_back(cur_vertex);
                cur_vertex = Vstack1.top();
                Vstack1.pop();
            }else{
                Vstack1.push(cur_vertex);
                const Tvalue neighbour_ver = get_bout(graph,cur_vertex);
                deleter(graph,cur_vertex, neighbour_ver);
                cur_vertex = neighbour_ver;
            }
        }
        std::reverse(std::begin(result), std::end(result));
        return result;
    }
}

























