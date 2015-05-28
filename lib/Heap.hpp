#include <iostream>

template <typename Data>
Heap<Data>::Heap() : m_InternalData(), m_NbElements(0)
{}

template <typename Data>
Heap<Data>::Heap(const std::vector<Data> & data) : m_InternalData(), m_NbElements(0)
{
    for (auto data_item : data)
    {
        insert(data_item);
    }
}

template <typename Data>
size_t Heap<Data>::smallestChild(size_t index) const
{
    const size_t left_index = left(index);
    const size_t right_index = right(index);

    if (right_index >= m_NbElements)
    {
        if (left_index >= m_NbElements)
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
size_t Heap<Data>::bubbleUp(size_t index)
{
    size_t parent_index = parent(index);

    while (internalMin(index, parent_index))
    {
        std::swap(m_InternalData[index], m_InternalData[parent_index]);
        index = parent_index;
        parent_index = parent(index);
    }

    return index;
}

template <typename Data>
size_t Heap<Data>::insert(const Data & element)
{
    ++m_NbElements;
    if (m_NbElements == (m_InternalData.size() + 1)) {
        m_InternalData.push_back(element);
    }
    else
    {
        m_InternalData[m_NbElements - 1] = element;
    }
    const size_t final_index = bubbleUp(m_NbElements - 1);

    return final_index;
}

template <typename Data>
Data Heap<Data>::extractRoot() throw (std::out_of_range)
{
    if (m_NbElements == 0)
    {
        throw std::out_of_range("extractRoot on empty heap !");
    }

    const Data root = m_InternalData[0];
    m_InternalData[0] = m_InternalData[m_NbElements - 1];
    --m_NbElements;
    bubbleDown(0);
    return root;
}

template <typename Data>
int Heap<Data>::find(const Data & data) const
{
    int index = -1;
    bool found = false;

    for (auto internal_data : m_InternalData)
    {
        ++index;

        if (internal_data == data)
        {
            found = true;
            break;
        }
    }

    return found ? index : -1;
} 

template <typename Data>
bool Heap<Data>::erase(size_t index)
{
    if (index > m_NbElements)
    {
        throw std::out_of_range("trying to erase at position not in heap !");
    }

    std::swap(m_InternalData[index], m_InternalData[m_NbElements - 1]);
    --m_NbElements;

    if (internalMin(index, parent(index)))
    {
        bubbleUp(index);
    }
    else
    {
        bubbleDown(index);
    }

    return true;
}
