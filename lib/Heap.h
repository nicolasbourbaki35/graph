#include <vector>

template <typename Data> 
class Heap
{
public:
    Heap();
    size_t insert(const Data & element);
    Data extractRoot() throw (std::out_of_range);
    size_t size() const { return m_NbElements; }
    bool empty() const { return m_NbElements == 0; }

protected:
    size_t parent  (size_t index) const { return (index == 0) ? index : (index - 1) / 2; }
    size_t left    (size_t index) const { return 2 * index + 1; }
    size_t right   (size_t index) const { return 2 * (index + 1); }
    size_t smallestChild(size_t index) const;

    size_t bubbleUp(size_t index);
    void bubbleDown(size_t index);
    bool internalMin(size_t left_index, size_t right_index) const
    { return m_InternalData[left_index] < m_InternalData[right_index]; }  

protected:
    using InternalData = std::vector<Data>;
    InternalData m_InternalData;
    unsigned int m_NbElements;
};

#include "Heap.hpp"