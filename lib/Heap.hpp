#include <iostream>

template <typename Data>
Heap<Data>::Heap() : m_InternalData(), m_NbElements(0)
{}

template <typename Data>
size_t Heap<Data>::smallestChild(size_t index) const
{
    const size_t left_index = left(index);
    const size_t right_index = right(index);

    if (right_index > m_NbElements)
    {
        if (left_index > m_NbElements)
        {
            return index;
        }
        return left_index;
    }

    return internalMin(left_index, right_index) ? left_index : right_index;
}

template <typename Data>
void Heap<Data>::bubbleDown(size_t index)
{
    size_t child = smallestChild(index);

    while (internalMin(child, index))
    {
        std::swap(m_InternalData[child], m_InternalData[index]);
        index = child;
        child = smallestChild(index);
    }
}

template <typename Data>
void Heap<Data>::bubbleUp(size_t index)
{
    size_t parent_index = parent(index);

    while (internalMin(index, parent_index))
    {
        std::swap(m_InternalData[index], m_InternalData[parent_index]);
        index = parent_index;
        parent_index = parent(index);
    }
}

template <typename Data>
bool Heap<Data>::insert(const Data & element)
{
    ++m_NbElements;
    if (m_NbElements == (m_InternalData.size() + 1)) {
        m_InternalData.push_back(element);
    }
    else
    {
        m_InternalData[m_NbElements - 1] = element;
    }
    bubbleUp(m_NbElements - 1);

    return true;
}

template <typename Data>
Data Heap<Data>::extractRoot()
{
    const Data root = m_InternalData[0];
    m_InternalData[0] = m_InternalData[m_NbElements - 1];
    --m_NbElements;
    bubbleDown(0);
    return root;
}
