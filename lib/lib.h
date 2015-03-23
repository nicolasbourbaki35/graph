
/*
Graph.h
*/

#include <queue>


struct Edge
{
    int number;
    unsigned int weight;

    bool operator<(const Edge & edge) const
    {
        return weight < edge.weight;
    }

    bool operator>(const Edge & edge) const
    {
        return weight > edge.weight;
    }
};


struct EmptyData
{
	/* empty */
};

template <typename Data=EmptyData>
struct EdgeWithData : public Edge
{
	Data data;
};


class FunctorIsDestination
{
public:
    bool operator()(const Edge & edge) const
    {
        return false;
    }
};

using Edges = std::vector<Edge>;
using AdjacencyList = std::vector<Edges>;
using Heap = std::priority_queue<Edge,  std::vector<Edge>, std::greater<Edge> >;
/*
Edges dijkstra(const AdjacencyList & graph, const FunctorIsDestination & destination)
{
    const Heap heap = graphToHeap(graph);



    return compute(heap, destination);
}
*/
Heap graphToHeap(const AdjacencyList & graph)
{
    Heap heap;

    for (auto edges : graph)
    {
        for (auto edge : edges)
        {
            heap.push(edge);
        }
    }

    return heap;
}

Edges compute(Heap & heap, const FunctorIsDestination & destination)
{

}