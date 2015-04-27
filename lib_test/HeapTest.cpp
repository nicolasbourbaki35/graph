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

    bool operator== (const Data & other) const
    {
        return key == other.key;
    }

    int key;
};

using TestData = std::vector<Data>;

bool equal(const TestData & ref, const TestData & test)
{
    return std::equal(ref.cbegin(), ref.cend(), test.cbegin());
}


TEST(HeapTestSuite, TestIndicesGetter)
{
    using PHeap = Heap<Data>;

    class HeapTest : public PHeap
    {
    public:
        size_t parent  (size_t index) const { return PHeap::parent(index); }
        size_t left    (size_t index) const { return PHeap::left(index);   }
        size_t right   (size_t index) const { return PHeap::right(index);  }
    };

    HeapTest heap;

    EXPECT_EQ(0, heap.parent(0));
    EXPECT_EQ(0, heap.parent(1));
    EXPECT_EQ(0, heap.parent(2));
    EXPECT_EQ(4, heap.parent(9));
    EXPECT_EQ(6, heap.parent(13));
    EXPECT_EQ(6, heap.parent(14));

    EXPECT_EQ(1, heap.left(0));
    EXPECT_EQ(3, heap.left(1));
    EXPECT_EQ(5, heap.left(2));
    EXPECT_EQ(13, heap.left(6));

    EXPECT_EQ(2, heap.right(0));
    EXPECT_EQ(4, heap.right(1));
    EXPECT_EQ(6, heap.right(2));
    EXPECT_EQ(14, heap.right(6));
}

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

    EXPECT_EQ(0, heap.insert(data));
    EXPECT_EQ(1, heap.size());
    EXPECT_EQ(false, heap.empty());
}

TEST(HeapTestSuite, TestExtractRootEmpty) 
{
    Heap<Data> heap;
    
    EXPECT_EQ(true, heap.empty());
    EXPECT_THROW(heap.extractRoot(), std::out_of_range);
}

TEST(HeapTestSuite, TestExtractRoot) 
{
    
    Heap<Data> heap;
    Data data;
    data.key = 5;
    Data extracted;

    EXPECT_EQ(0, heap.insert(data));
    EXPECT_EQ(1, heap.size());
    EXPECT_NO_THROW(extracted = heap.extractRoot());

    EXPECT_EQ(data.key, extracted.key);
}

TEST(HeapTestSuite, TestInsertionInExistingHeap)
{
    using PHeap = Heap<Data>;

    class HeapTest : public PHeap
    {
    public:
        HeapTest(const std::vector<Data> & init)
        {
            m_NbElements = init.size();
            m_InternalData = init;
        }

        const InternalData & getInternalData() const { return m_InternalData; }
    };

    std::vector<Data> initial_data { {4}, {4}, {8}, {9}, {4}, {12}, {9}, {11}, {13}, {7}, {20} };
    std::vector<Data> resulting_data { {4}, {4}, {5}, {9}, {4}, {8}, {9}, {11}, {13}, {7}, {20}, {12} };
    Data inserted_data = { 5 };

    HeapTest heap(initial_data);

    EXPECT_EQ(false, heap.empty());
    EXPECT_EQ(initial_data.size(), heap.size());
    EXPECT_EQ(true, equal(initial_data, heap.getInternalData()));

    EXPECT_EQ(2, heap.insert(inserted_data));
    EXPECT_EQ(resulting_data.size(), heap.size());
    EXPECT_EQ(true, equal(resulting_data, heap.getInternalData()));
}

TEST(HeapTestSuite, TestExtractRootInExistingHeap)
{
    using PHeap = Heap<Data>;

    class HeapTest : public PHeap
    {
    public:
        HeapTest(const std::vector<Data> & init)
        {
            m_NbElements = init.size();
            m_InternalData = init;
        }

        const InternalData & getInternalData() const { return m_InternalData; }
    };

    std::vector<Data> initial_data { {4}, {4}, {8}, {9}, {4}, {12}, {9}, {11}, {13} };
    std::vector<Data> resulting_data { {4}, {4}, {8}, {9}, {13}, {12}, {9}, {11} };

    HeapTest heap(initial_data);
    EXPECT_EQ(true, equal(initial_data, heap.getInternalData()));

    Data extracted;
    Data expected = { 4 };
    EXPECT_NO_THROW(extracted = heap.extractRoot());
    EXPECT_EQ(expected, extracted);

    EXPECT_EQ(resulting_data.size(), heap.size());
    EXPECT_EQ(true, equal(resulting_data, heap.getInternalData()));
}