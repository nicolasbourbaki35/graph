#include <vector>
#include <queue>
#include <algorithm>

/*
 * Edge
 */
class Edge
{
public:
    Edge(size_t dest, int weight = 0) 
        : m_destination(dest)
        , m_weight(weight)
    {}

    size_t getDestination() const { return m_destination; };
    int    getWeigth()      const { return m_weight;      };

private:
    size_t m_destination;
    int m_weight;
};

/*
 * Graph data struct
 */
template<typename EdgeT = Edge>
class Graph
{
public:
    using EdgeType  = EdgeT;
    using Edges     = std::vector<EdgeType>;
    using NodeEdges = std::vector<Edges>;
    
    Graph(size_t capacity) : 
        m_node_edges(capacity)
    {}
    
    void addEdge(size_t from, size_t to, int weight = 0, bool directed = false)
    {
        Edge new_edge(to, weight);
        
        m_node_edges.at(from).push_back(new_edge);
        
        if (directed == false)
        {
            addEdge(to, from, weight, true);
        }
    }

    /*
     * Breadth first search
     */
    void bfs(int start)
    {
        if (start > m_node_edges.size() - 1)
        {
            throw std::out_of_range("Start position is out of range");
        }

        std::queue<size_t>  q;
        std::vector<bool> discovered(m_node_edges.size(), false);
        std::vector<bool> processed (m_node_edges.size(), false);
        
        q.push(start); 
        discovered[start] = true;

        while (!q.empty()) 
        {
            size_t vertice = q.front();
            q.pop();
            //process vertice early       
            processed[vertice] = true;
            
            Edges const & edges = m_node_edges.at(vertice); 
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

private:
    NodeEdges m_node_edges;
};

