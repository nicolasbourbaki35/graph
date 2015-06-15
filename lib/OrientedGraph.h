#include <vector>
#include <queue>
#include <numeric>
#include "UnionFind.h"
#include "Graph.h"

#include <iostream>

namespace GraphLib 
{

struct PriorityEdge
{
    PriorityEdge(int index, int weight = 0)
        : m_index(index), m_weight(weight)
    {
    }

    bool operator> (const PriorityEdge & other) const { return m_weight > other.m_weight; }

    int m_index;
    int m_weight;
};

class PriorityEdgeComp
{
public:
  bool operator() (const PriorityEdge & lhs, const PriorityEdge & rhs) const
  {
      return (lhs > rhs);
  }
};

class OrientedVertex
{
public:
    using Children       = std::vector<int>;
    using PriorityEdges  = std::priority_queue<PriorityEdge, std::vector<PriorityEdge>, PriorityEdgeComp>;//std::priority_queue< PriorityEdgeComp, std::vector<PriorityEdge> >;

    OrientedVertex()
        : m_id(0)
        , m_incomingEdgeIndex(-1)
        , m_constWeight(0)
        , m_previousVertexIndex(-1)
        , m_children()
        , m_incomingEdges()
    {}

    OrientedVertex(unsigned int id) : m_id(id)
    {}

    unsigned int getId() const { return m_id; }

    PriorityEdge extractMinEdge()
    {
        PriorityEdge edge = m_incomingEdges.top();
        std::cout << "extracting:" << edge.m_index << std::endl;
        m_incomingEdges.pop();
        return edge;
    }

    bool isEmpty() const { return m_incomingEdges.empty(); }

    PriorityEdges & getPriorityEdges() { return m_incomingEdges; }

    int getIncomingEdgeIndex() const { return m_incomingEdgeIndex; }
    void setIncomingEdgeIndex(int incoming_edge_index) { m_incomingEdgeIndex = incoming_edge_index; }

    int getPreviousVertexIndex() const { return m_previousVertexIndex; }
    void setPreviousVertexIndex(int previous_vertex_index) { m_previousVertexIndex = previous_vertex_index; }

    int getConstWeight() const { return m_constWeight; }
    void setConstWeight(int const_weight) { m_constWeight = const_weight; }

    void addChild(int child_ind) { m_children.push_back(child_ind); }
    const Children & getChildren() const { return m_children; }

private:
    unsigned int m_id;
    int m_incomingEdgeIndex;
    int m_constWeight;
    int m_previousVertexIndex;
    Children m_children;
    PriorityEdges m_incomingEdges;
};


template<typename VertexT = OrientedVertex, typename EdgeT = Edge>
class OrientedGraph
{
public:
    using VertexType      = VertexT;
    using PriorityEdges   = typename VertexType::PriorityEdges;
    using EdgeType        = EdgeT;
    using Vertices        = std::vector<VertexType>;
    using Edges           = std::vector<EdgeType>;

OrientedGraph(const Vertices & vertices, const Edges & edges)
    : m_vertices(vertices.size() * 2)
    , m_parents(vertices.size() * 2)
    , m_edges(edges)
    , m_nbNormalVertices(vertices.size())
{
    std::copy(vertices.begin(), vertices.end(), m_vertices.begin());
    std::iota(m_parents.begin(), m_parents.end(), 0);
}

std::vector<unsigned int> computeMinimumDirectedSpanningTree(unsigned int start)
{
    contract(start);
    return expand(start);
}

void contract(unsigned int start)
{
    unsigned int a_ind = 0;
    unsigned int lastInstanciedVertexIndex = m_nbNormalVertices - 1;

    while (!m_vertices[a_ind].isEmpty())
    {
        std::cout << "for index " << a_ind << " : min edges size: " << m_vertices[a_ind].getPriorityEdges().size()<< std::endl;
        const PriorityEdge & priority_edge = m_vertices[a_ind].extractMinEdge();
        const int edge_index = priority_edge.m_index;
        std::cout << "for index " << a_ind << ",min edge index=" << priority_edge.m_index << std::endl;
        VertexType & vertex = m_vertices[a_ind];

        const unsigned int b_ind = parent(m_edges[edge_index].getSource());
        std::cout << "for index " << a_ind << " source: " << m_edges[edge_index].getSource() << " from min edge: " << edge_index << ", and parent:" << b_ind << std::endl;

        if (a_ind != b_ind)
        {
            vertex.setIncomingEdgeIndex(edge_index);
            vertex.setPreviousVertexIndex(b_ind);

            std::cout << "for " << a_ind << " incoming edge = " << edge_index << std::endl;

            if (m_vertices[m_edges[edge_index].getSource()].getIncomingEdgeIndex() == -1)
            {
                a_ind = b_ind;
            }
            else
            {
                ++lastInstanciedVertexIndex;
                const int c_ind = lastInstanciedVertexIndex;

                std::cout << "creation of " << lastInstanciedVertexIndex << " super_vertex" << std::endl;

                VertexType & super_vertex = m_vertices[c_ind];

                while (m_parents[a_ind] == a_ind)
                {
                    std::cout << "updating parent of " << a_ind << " which was " << m_parents[a_ind] << std::endl;
                    m_parents[a_ind] = c_ind;
                    m_vertices[a_ind].setConstWeight(-weight(m_edges[m_vertices[a_ind].getIncomingEdgeIndex()]));
                    super_vertex.addChild(a_ind);
                    meld(m_vertices[a_ind].getPriorityEdges(), super_vertex.getPriorityEdges());
                    a_ind = m_vertices[a_ind].getPreviousVertexIndex();
                }

                std::cout << "finishing loop with " << a_ind << std::endl;
            }
        }
    }
}

private:

int weight(const EdgeType & edge) const
{
    int w = edge.getWeight();

    unsigned int vertex_index = edge.getDestination();
    VertexType vertex = m_vertices[vertex_index];

    while (vertex_index != m_parents[vertex_index])
    {
        w += vertex.getConstWeight();
        vertex_index = m_parents[vertex_index];
        vertex = m_vertices[vertex_index];
    }

    return w;
}

void meld(PriorityEdges & src_priority_edges, PriorityEdges & dst_priority_edges)
{
    PriorityEdges src_priority_edges_cpy(src_priority_edges);
       
    std::cout << "src size:" << src_priority_edges.size() << ", dst size:" << dst_priority_edges.size() << std::endl;

    while (!src_priority_edges_cpy.empty())
    {
        dst_priority_edges.push(src_priority_edges_cpy.top());
        src_priority_edges_cpy.pop();
    }
}

unsigned int parent(unsigned int vertex_index)
{
    unsigned int parent_index = m_parents[vertex_index];

    while (parent_index != m_parents[parent_index])
    {
        parent_index = m_parents[vertex_index];
    }

    return parent_index;
}

std::vector<unsigned int> expand(unsigned int start)
{
    std::vector<unsigned int> remaining;
    dismantle(start, remaining);

    while (remaining.size() != 0)
    {
        unsigned int c = remaining.back();
        remaining.pop_back();
        unsigned int edge_index = m_vertices[c].getIncomingEdgeIndex();
        m_vertices[m_edges[edge_index].getDestination()].setIncomingEdgeIndex(edge_index);
        dismantle(edge_index, remaining);
    }

    std::vector<unsigned int> result(m_nbNormalVertices);

    for (unsigned int i = 0; i < m_nbNormalVertices; ++i)
    {
        result[i] = m_vertices[i].getIncomingEdgeIndex();
    }

    return result;
}

void dismantle(unsigned int vertex_index, std::vector<unsigned int> & remaining)
{
    while (m_parents[vertex_index] != vertex_index)
    {
        unsigned int parent_index = m_parents[vertex_index];

        for (int child_ind : m_vertices[parent_index].getChildren())
        {
            m_parents[child_ind] = child_ind;
            if (m_vertices[child_ind].getChildren().size() != 0)
            {
                remaining.push_back(child_ind);
            }
        }
    }
}

private:
    Vertices m_vertices;
    std::vector<unsigned int> m_parents;
    Edges m_edges;
    size_t m_nbNormalVertices;

};

}
