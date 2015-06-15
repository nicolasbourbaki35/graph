#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "OrientedGraph.h"

using namespace std;
using namespace GraphLib;

TEST(GraphTestSuite, TestOrientedGraph) 
{

    OrientedGraph<>::Edges edges;
    edges.push_back(Edge(0, 1, 1)); // 0
    edges.push_back(Edge(1, 0, 1)); // 1
    edges.push_back(Edge(1, 3, 1)); // 2
    edges.push_back(Edge(2, 1, 1)); // 3
    edges.push_back(Edge(2, 4, 1)); // 4
    edges.push_back(Edge(3, 2, 1)); // 5
    edges.push_back(Edge(4, 3, 1)); // 6
    edges.push_back(Edge(4, 8, 1)); // 7
    edges.push_back(Edge(5, 1, 1)); // 8
    edges.push_back(Edge(5, 7, 1)); // 9
    edges.push_back(Edge(6, 5, 1)); // 10
    edges.push_back(Edge(7, 6, 1)); // 11
    edges.push_back(Edge(8, 6, 1)); // 12

    OrientedGraph<>::Vertices vertices(9);

    vertices[0].getPriorityEdges().push(PriorityEdge(1, 1));
    vertices[1].getPriorityEdges().push(PriorityEdge(0, 1));
    vertices[1].getPriorityEdges().push(PriorityEdge(3, 2));
    vertices[1].getPriorityEdges().push(PriorityEdge(8, 2));
    vertices[2].getPriorityEdges().push(PriorityEdge(5, 1));
    vertices[3].getPriorityEdges().push(PriorityEdge(2, 2));
    vertices[3].getPriorityEdges().push(PriorityEdge(6, 1));
    vertices[4].getPriorityEdges().push(PriorityEdge(4, 1));
    vertices[5].getPriorityEdges().push(PriorityEdge(10, 1));
    vertices[6].getPriorityEdges().push(PriorityEdge(11, 1));
    vertices[6].getPriorityEdges().push(PriorityEdge(12, 2));
    vertices[7].getPriorityEdges().push(PriorityEdge(9, 1));
    vertices[8].getPriorityEdges().push(PriorityEdge(7, 1));

    OrientedGraph<> graph(vertices, edges);

    std::vector<unsigned int> result = graph.computeMinimumDirectedSpanningTree(3);

    for (auto i : result) {
        std::cout << i << std::endl;
    }

}