#include <iostream>

#include "Graph.h"
#include "Graphviz.h"

using namespace GraphLib;

int main(int argc, char* argv[])
{
    Graph<> g(7, "MyGraph");
    
    /*    0
         /  \
        1    2
       / \  / \
      3  4  5  6 */

    g.addEdge(Edge(0, 1, 1));
    g.addEdge(Edge(0, 2, 2));
    g.addEdge(Edge(1, 3, 3));
    g.addEdge(Edge(1, 4, 4));
    g.addEdge(Edge(2, 5, 5));
    g.addEdge(Edge(2, 6, 6));

    g.printToDot(std::cout, 0);
    
    return 0;
}

