#include <functional>
#include <string>
#include <vector>

#include "algorithms.h"

#include "graph.h"
#include "mgraph.h"
#include "lgraph.h"

int main(void)
{
    LGraph graph1;
    MGraph graph2;
    EGraph graph3;
    try{
        graph1.make_graph();
        graph2.make_graph();
        graph3.make_graph();
    }catch(const std::exception& error){
        std::cout << error.what() << std::endl;
        return 1;
    }
    try{
        std::vector<float> temp2 =
                ALGO2000::dfs<EGraph,
                              float,
                              std::function<std::vector<float>(EGraph&, float)>,
                              std::function<void(EGraph&, float)>,
                              std::function<bool(EGraph&, float)>>
                              (graph3, 9.1, &EGraph::get_adj_vertexes,
                                            &EGraph::mark,
                                            &EGraph::is_mark);

        std::vector<std::string> temp1 =
                ALGO2000::euler_path<LGraph,
                                     std::string,
                                     std::function<std::vector<std::string>(LGraph&)>,
                                     std::function<void(LGraph&,std::string,std::string)>,
                                     std::function<int(LGraph&,std::string)>,
                                     std::function<std::string(LGraph&,std::string)>>
                                     (graph1,
                                      &LGraph::get_all_vertex,
                                      &LGraph::remove_edge,
                                      &LGraph::get_deg,
                                      &LGraph::get_neighbour);

        for(unsigned i = 0 ; i < temp1.size(); i++){
            std::cout << temp1[i] << " ";
        }
        std::cout << std::endl;
        for(unsigned i = 0 ; i < temp2.size(); i++){
            std::cout << temp2[i] << " ";
        }

    }catch(const std::exception& error){
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}


