template<typename V, typename E>
class Graph
{
public:
	using VertexID = size_t;

	VertexID addVertex(V);
	Graph& addEdge(VertexID, VertexID, E);

	/* ... */
};