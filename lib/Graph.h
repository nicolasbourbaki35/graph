#include <vector>
#include <queue>
#include <algorithm>


/*
 * Edge
 */
class Edge
{
public:
    Edge(unsigned int dest, int weight = 0) 
        : m_destination(dest)
        , m_weight(weight)
    {}

    unsigned int getDestination() const { return m_destination; };
    int          getWeigth()      const { return m_weight;      };

private:
    unsigned int m_destination;
    int m_weight;
};



template<typename EdgeT = Edge>
class Vertex
{
public:
    using EdgeType = EdgeT;
    using Edges    = std::vector<EdgeType>;
    
    Vertex() : m_id(0)
    {}

    Vertex(unsigned int id) : m_id(id)
    {

    }

    void addEdge(const EdgeType & edge)
    {
        m_edges.push_back(edge);
    }

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
    using VertexType  = VertexT;
    using EdgeType  = typename VertexType::EdgeType;
    using Vertices  = std::vector<VertexType>;
    
    Graph(size_t capacity)
    {
        for (unsigned int index = 0; index < capacity; ++index)
        {
            m_vertices.push_back(VertexType(index));
        }
    }
    
    void addEdge(unsigned int from, unsigned int to, int weight = 0, bool directed = false)
    {
        const EdgeType new_edge(to, weight);

        m_vertices.at(from) = VertexType(from);
        
        m_vertices.at(from).addEdge(new_edge);
        
        if (!directed)
        {
            addEdge(to, from, weight, true);
        }
    }

    /*
     * Breadth first search
     */
     /*
    void bfs(int start)
    {
        if (start > m_vertices.size() - 1)
        {
            throw std::out_of_range("Start position is out of range");
        }

        std::queue<size_t>  q;
        std::vector<bool> discovered(m_vertices.size(), false);
        std::vector<bool> processed (m_vertices.size(), false);
        
        q.push(start); 
        discovered[start] = true;

        while (!q.empty()) 
        {
            size_t vertice = q.front();
            q.pop();
            //process vertice early       
            processed[vertice] = true;
            
            Edges const & edges = m_vertices.at(vertice); 
            std::for_each(edges.begin(), edges.end(), 
                [&] (EdgeType const & edge)
                {
                    size_t dest = edge.getDestination();
                    if (processed[dest] == false)
                    {
                        //process edge
                    }
                    if (discovered[dest] == false)
                    {
                        q.push(dest);
                        discovered[dest] = true;         
                    }        
                }
           );
           // process vertice late
        }
    }
    */

private:
    Vertices m_vertices;
};

