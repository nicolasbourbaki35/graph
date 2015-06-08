#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "OrientedGraph.h"

using namespace std;
using namespace GraphLib;

TEST(GraphTestSuite, TestOrientedGraph) 
{
    Edge e(1, 10, 10);
    
    EXPECT_EQ(1u , e.getSource()    );
    EXPECT_EQ(10u, e.getDestination());
    EXPECT_EQ(10 , e.getWeight()     );
}