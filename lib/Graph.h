#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <ostream>

#include "Graphviz.h"

#include "Heap.h"

namespace GraphLib 
{

/*
 * Edge
 */
class Edge
{
public:
    Edge(unsigned int source, unsigned int dest, int weight = 0) 
        : m_source(source)
        , m_destination(dest)
        , m_weight(weight)
    {
    }

    unsigned int getSource()      const { return m_source;      };
    unsigned int getDestination() const { return m_destination; };
    int          getWeight()      const { return m_weight;      };

    bool operator< (const Edge & other)  const { return m_weight < other.m_weight; }
    bool operator== (const Edge & other) const { return m_destination == other.m_destination; }

private:
    unsigned int m_source;
    unsigned int m_destination;
    int m_weight;
};

template<typename EdgeT = Edge>
class Vertex
{
public:
    using EdgeType       = EdgeT;
    using Edges          = std::vector<EdgeType>;
    using iterator       = typename Edges::iterator;
    using const_iterator = typename Edges::const_iterator;
    
    Vertex() : m_id(0)
    {}

    Vertex(unsigned int id) : m_id(id)
    {}

    void addEdge(const EdgeType & edge)
    {
        m_edges.push_back(edge);
    }

    iterator       begin()  { return m_edges.begin();  }
    const_iterator cbegin() { return m_edges.cbegin(); }
    iterator       end()    { return m_edges.end();    }
    const_iterator cend()   { return m_edges.cend();   }
    
    unsigned int getId() const { return m_id; }

private:
    unsigned int m_id;
    Edges m_edges;
};

/*
 * Graph data struct
 */
template<typename VertexT = Vertex< Edge > >
class Graph
{
public:
    using VertexType      = VertexT;
    using EdgeType        = typename VertexType::EdgeType;
    using Vertices        = std::vector<VertexType>;
    using VertexProcessor = std::function<void(VertexType&)>;
    using EdgeProcessor   = std::function<void(EdgeType&)>;
    using HeapType        = Heap<EdgeType>;
    
    Graph(size_t capacity, std::string caption = "")
        : m_caption(caption)
    {
        for (unsigned int index = 0; index < capacity; ++index)
        {
            m_vertices.push_back(VertexType(index));
        }
    }
    
    void addEdge(EdgeType const & edge, bool directed = false)
    {
        m_vertices.at(edge.getSource()).addEdge(edge);
    }

    std::string const & getCaption() { return m_caption; } 

    void findShortestPath( unsigned int start
                             , VertexProcessor vp = VertexProcessor()
                             , EdgeProcessor ep = EdgeProcessor())
    {
        std::vector<bool> processed(m_vertices.size(), false);
        std::vector<int> lengthFromStart(m_vertices.size(), 0);
        HeapType heap;
        
        processed[start] = true;

        if (start > m_vertices.size() - 1)
        {
            throw std::out_of_range("Start position is out of range");
        }
        
        VertexType vertex = m_vertices.at(start);
        if (vp)
            vp(vertex);

        for(EdgeType & edge : vertex) 
        {
            heap.insert(edge);
        }

        for (unsigned int i = 0; i < m_vertices.size() - 1; ++i)
        {
            auto edge = heap.extractRoot();
            size_t dest = edge.getDestination();
            
            while (processed[dest])
            {
                edge = heap.extractRoot();
            }

            processed[dest] = true;
            lengthFromStart[dest] = edge.getWeight();
            VertexType vertex_dest = m_vertices[dest];
            
            if (ep)
                ep(edge);
            if (vp)
                vp(vertex_dest);

            for (EdgeType new_edge : vertex_dest)
            {
                if (!processed[new_edge.getDestination()])
                {
                    int position = heap.find(new_edge);
                    bool deleted = false;

                    if (position != -1)
                    {
                        auto concurrent_edge = heap.get(position);
                        if (lengthFromStart[dest] + new_edge.getWeight() < concurrent_edge.getWeight())
                        {
                            heap.erase(position);
                            deleted = true;
                        }
                    }

                    if (position == -1 || deleted)
                    {
                        EdgeType edge(dest, new_edge.getDestination(), new_edge.getWeight() + lengthFromStart[dest]);
                        heap.insert(edge);
                    }
                }
            }
        }
    }

    /*
     * Breadth first search
     */
    void bfs(unsigned int start
            , VertexProcessor vp = VertexProcessor()
            , EdgeProcessor ep = EdgeProcessor())
    {
        if (start > m_vertices.size() - 1)
        {
            throw std::out_of_range("Start position is out of range");
        }

        std::queue<size_t> q;
        std::vector<bool> discovered(m_vertices.size(), false);
        std::vector<bool> processed (m_vertices.size(), false);
        
        q.push(start); 
        discovered[start] = true;

        while (!q.empty()) 
        {
            size_t vertice_id = q.front();
            q.pop();
            VertexType vertex = m_vertices.at(vertice_id);

            // process vertex 
            if (vp)
                vp(vertex);
            
            processed[vertice_id] = true;
            
            for(EdgeType & edge : vertex) 
            {
                size_t dest = edge.getDestination();

                //process edge
                if (ep && processed[dest] == false)
                {
                   ep(edge);
                }

                if (discovered[dest] == false)
                {
                    q.push(dest);
                    discovered[dest] = true;         
                }        
            }
        }
    }

    /*
     * Print graph to dot format
     */
    void printToDot(std::ostream & os, unsigned int start_vertex)
    {
        os << "digraph " << m_caption << " {" << std::endl;

        GraphvizEdgeProcessor<EdgeType> ep(os);
        bfs(start_vertex, VertexProcessor(), ep);
        
        os << " } " << std::endl;
    }

private:
    Vertices m_vertices;
    std::string m_caption;
};

} // namespace GraphLib

#endif

