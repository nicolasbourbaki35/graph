#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>

#include "Heap.h"

using namespace std;

struct Data
{
    bool operator< (const Data & other) const
    {
        return key < other.key;
    }

    int key;
};

TEST(HeapTestSuite, TestCreateHeap) 
{
    Heap<Data> heap;

    EXPECT_EQ(0, heap.size());
    EXPECT_EQ(true, heap.empty());
}

TEST(HeapTestSuite, TestInsertHeap)
{
    Heap<Data> heap;
    Data data;
    data.key = 5;

    EXPECT_EQ(true, heap.insert(data));
    EXPECT_EQ(1, heap.size());
    EXPECT_EQ(false, heap.empty());
}

TEST(TestSuite, TestExtractRootEmpty) 
{

    //EXPECT_THROW(g.addEdge(2,3), std::out_of_range);
}

TEST(TestSuite, TestExtractRoot) 
{
    
}

