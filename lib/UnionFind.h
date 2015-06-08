#include <vector>
#include <numeric>

class UnionFind
{
public:
    UnionFind(size_t nb_indices)
        : m_tree(nb_indices)
        , m_depth(nb_indices, 1)
    {
        std::iota(m_tree.begin(), m_tree.end(), 0);
    }

    bool unite(unsigned int p, unsigned int q)
    {
        const unsigned int i = root(p);
        const unsigned int j = root(q);
        const bool union_done = (i != j);

        if (m_depth[i] < m_depth[j])
        {
            m_tree[i] = j;
            m_depth[j] += m_depth[i];
        }
        else
        {
            m_tree[j] = i;
            m_depth[i] += m_depth[j];
        }

        return union_done;
    }

    bool find(unsigned int p, unsigned int q)
    {
        return root(p) == root(q);
    }

    unsigned int root(unsigned int node)
    {
        if (node > m_tree.size())
        {
            throw std::out_of_range("Node index is out of range.");
        }

        while (m_tree[node] != node)
        {
            m_tree[node] = m_tree[m_tree[node]];
            node = m_tree[node];
        }

        return node;
    }

private:
    using Tree = std::vector<unsigned int>;
    using Depth = std::vector<unsigned int>;

    Tree m_tree;
    Depth m_depth;
};
