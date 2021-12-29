#include "ListGraph.h"

ListGraph::ListGraph(const IGraph& graph) {
	size_t size = graph.VerticesCount();
	if (size == 0) {
		ListGraph(0);
		return;
	}
	std::vector<bool> visited(size, false);
	vertices.resize(size);
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			for (auto& vertex : graph.GetNextVertices(i)) {
				this->AddEdge(i, vertex);
			}
		}
	}
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
	std::vector<int> result;
	for (int parent = 0; parent < vertices.size(); ++ parent) {
		for (auto& child : vertices[parent]) {
			if (child == vertex) {
				result.push_back(parent);
				break;
			}
		}
	}
	return result;
}