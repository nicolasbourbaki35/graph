#include <vector>
#include <queue>
#include "UnionFind.h"
#include "Graph.h"

namespace GraphLib 
{

struct PriorityEdge
{
    PriorityEdge(int index, int weight = 0)
        : m_index(index), m_weight(weight)
    {
    }

    bool operator< (const PriorityEdge & other) const { return m_weight < other.m_weight; }

    int m_index;
    int m_weight;
};

class PriorityEdgeComp
{
public:
  bool operator() (const PriorityEdge & lhs, const PriorityEdge & rhs) const
  {
      return (lhs < rhs);
  }
};

class OrientedVertex
{
public:
    using Children       = std::vector<int>;
    using PriorityEdges  = std::priority_queue< PriorityEdgeComp, std::vector<PriorityEdge> >;

    OrientedVertex() : m_id(0), m_parentIndex(-1)
    {}

    OrientedVertex(unsigned int id) : m_id(id)
    {}

    unsigned int getId() const { return m_id; }

    const PriorityEdge & extractMinEdge()
    {
        const PriorityEdge & edge = m_incomingEdges.top();
        m_incomingEdges.pop();
        return edge;
    }

    int getIncomingEdgeIndex() const { return m_incomingEdgeIndex; }
    void setIncomingEdgeIndex(int incoming_edge_index) { m_incomingEdgeIndex = incoming_edge_index; }

    void setPreviousVertexIndex(int previous_vertex_index) { m_previousVertexIndex = previous_vertex_index; }

    int getParentIndex() const { return m_parentIndex; }
    void setParentIndex(int parent_index) { m_parentIndex = parent_index; }

    int getConstWeight() const { return m_constWeight; }
    void setConstWeight(int const_weight) { m_constWeight = const_weight; }

    void addChild(int child_ind) { m_children.push_back(child_ind); }

private:
    unsigned int m_id;
    int m_incomingEdgeIndex;
    int m_previousVertexIndex;
    int m_parentIndex;
    int m_constWeight;
    Children m_children;
    PriorityEdges m_incomingEdges;
};


template<typename VertexT = OrientedVertex, typename EdgeT = Edge>
class OrientedGraph
{
public:
    using VertexType      = VertexT;
    using EdgeType        = EdgeT;
    using Vertices        = std::vector<VertexType>;
    using Edges           = std::vector<EdgeType>;

OrientedGraph(const Vertices & vertices, const Edges & edges)
    : m_vertices(vertices.size() * 2)
    , m_union(vertices.size() * 2)
    , m_edges(edges)
{
    std::copy(vertices.begin(), vertices.end(), m_vertices.begin());
}

void contract(unsigned int start)
{
    int a_ind = 0;
    int lastInstanciedVertexIndex = 0;

    while (!m_vertices[a_ind].isEmpty())
    {
        const PriorityEdge & priority_edge = m_vertices[a_ind].extractMinEdge();
        const int edge_index = priority_edge.m_index;
        VertexType & vertex = m_vertices[a_ind];

        int b_ind = parent(m_edges[edge_index].getSource());

        if (a_ind != b_ind)
        {
            vertex.setIncomingEdgeIndex(edge_index);
            vertex.setPreviousVertexIndex(b_ind);

            if (m_vertices[m_edges[edge_index].getSource()].getIncomingEdgeIndex() == -1)
            {
                a_ind = b_ind;
            }
            else
            {
                ++lastInstanciedVertexIndex;
                int c_ind = lastInstanciedVertexIndex;

                VertexType & super_vertex = m_vertices[c_ind];

                while (m_union[a_ind] == a_ind)
                {
                    m_vertices[a_ind].setParentIndex(c_ind);
                    m_vertices[a_ind].setConstWeight(0);
                    super_vertex.addChild(a_ind);
                    // super_vertex.meld(vertex.edges)
                    a_ind = c_ind;
                }
            }
        }
    }
}

int weight(const EdgeType & edge) const
{
    int w = edge.getWeight();

    unsigned int vertex_index = edge.getDestination();
    VertexType vertex = m_vertices[vertex_index];

    while (vertex_index != m_union[vertex_index])
    {
        w += vertex.getConstWeight();
        vertex_index = m_union[vertex_index];
        vertex = m_vertices[vertex_index];
    }

    return w;
}

unsigned int parent(unsigned int vertex_index)
{
    unsigned int parent_index = m_union[vertex_index];

    while (parent_index != m_union[parent_index])
    {
        parent_index = m_union[vertex_index];
    }

    return parent_index;
}

private:
    Vertices m_vertices;
    Edges m_edges;
    std::vector<unsigned int> m_union;

};

}
