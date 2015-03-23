#include <gtest/gtest.h>
#include <iostream>
#include "lib.h"

using namespace std;

TEST(TestSuite, GraphToHeap) 
{

    const AdjacencyList graph = { {Edge{1, 1}, Edge{2, 4}},
                            {Edge{3, 6}, Edge{2, 2}}, 
                            {Edge{3, 3}}, 
                          };


    Heap heap = graphToHeap(graph);

    
    const Edge min_edge{1, 1};

    EXPECT_EQ(heap.top().number, min_edge.number);
}


