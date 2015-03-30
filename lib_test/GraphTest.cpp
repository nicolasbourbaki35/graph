#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "Graph.h"

using namespace std;

TEST(GraphTestSuite, TestEdge) 
{
    Edge e(10, 10);
    
    EXPECT_EQ(10, e.getDestination());
    EXPECT_EQ(10, e.getWeigth()     );

}

TEST(GraphTestSuite, VerticeEdge) 
{
    Edge e1(10);
    Edge e2(11);
    Edge e3(12);

    Vertex<> v(10);
    
    v.addEdge(e1);
    v.addEdge(e2);
    v.addEdge(e3);
    
    EXPECT_EQ(10, v.getId());
   
    int i = 10;
    for (Edge const & e: v )
    {
        EXPECT_EQ(i++, e.getDestination());
    } 
}


TEST(GraphTestSuite, Graph)
{
    Graph<> g(3);

    EXPECT_NO_THROW(g.addEdge(0,1));
    EXPECT_NO_THROW(g.addEdge(1,2));
    EXPECT_THROW(g.addEdge(2,3), std::out_of_range);
}


