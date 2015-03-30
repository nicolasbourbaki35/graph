#include <gtest/gtest.h>
#include <iostream>

#include "Graph.h"

using namespace std;

TEST(GraphTestSuite, TestEdge) 
{
    Edge e(10, 10);
    
    EXPECT_EQ(10, e.getDestination());
    EXPECT_EQ(10, e.getWeigth()     );

}

TEST(GraphTestSuite, Graph)
{
    Graph<> g(3);
    
    EXPECT_NO_THROW(g.addEdge(0,1));
    EXPECT_NO_THROW(g.addEdge(1,2));
    EXPECT_THROW(g.addEdge(2,3), std::out_of_range);
}


