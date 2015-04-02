#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "Graph.h"

using namespace std;
using namespace GraphLib;

TEST(GraphTestSuite, TestEdge) 
{
    Edge e(1, 10, 10);
    
    EXPECT_EQ(1u , e.getSource()    );
    EXPECT_EQ(10u, e.getDestination());
    EXPECT_EQ(10 , e.getWeight()     );
}

TEST(GraphTestSuite, VerticeEdge) 
{
    Edge e1(1, 10, 10);
    Edge e2(1, 11, 11);
    Edge e3(1, 12, 12);

    Vertex<> v(10);
    
    v.addEdge(e1);
    v.addEdge(e2);
    v.addEdge(e3);
    
    EXPECT_EQ(10u, v.getId());
   
    unsigned int i = 10;
    for (Edge const & e: v )
    {
        EXPECT_EQ(1u , e.getSource()             );
        EXPECT_EQ(i, e.getDestination()          );
        EXPECT_EQ(i, (unsigned int)e.getWeight() );
        i++;
    } 
}

TEST(GraphTestSuite, Graph)
{
    Graph<> g(3);

    EXPECT_NO_THROW(g.addEdge(Edge(0,1,1)));
    EXPECT_NO_THROW(g.addEdge(Edge(0,2,2)));
    EXPECT_THROW(g.addEdge(Edge(3,2,3)), std::out_of_range);
}

struct VertexProcessor
{
    void operator()(Vertex<> & vertex) 
    {
        indices.push_back(vertex.getId());
    }
    std::vector<unsigned int> indices;
};

struct EdgeProcessor
{
    void operator()(Edge & edge) 
    {
        weights.push_back(edge.getWeight());
    }
    std::vector<int> weights;
};

TEST(GraphTestSuite, BreadthFirstSearch)
{
    VertexProcessor vp;
    EdgeProcessor   ep;
    Graph<> g(7);
    
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
    
    g.bfs(0, std::ref(vp), std::ref(ep));
    
    for(unsigned int i=0; i<vp.indices.size(); ++i)
    { 
        EXPECT_EQ(i, vp.indices[i]);
    }

    for(unsigned int i=0; i<ep.weights.size(); ++i)
    {
        EXPECT_EQ(i+1, (unsigned int)ep.weights[i]);
    }
}

