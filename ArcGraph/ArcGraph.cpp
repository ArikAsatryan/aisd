#include "ArcGraph.hpp"

#include <utility>


ArcGraph::ArcGraph(const IGraph& graph) {
	size_t size = graph.VerticesCount();
	if (size == 0) {
		ArcGraph(0);
		return;
	}
	vertices_count = size;
	std::vector<bool> visited(size, false);
	for (int i = 0; i < size; ++i) {
		if (!visited[i]) {
			visited[i] = true;
			for (auto& vertex : graph.GetNextVertices(i)) {
				this->AddEdge(i, vertex);
			}
		}
	}
}


std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
	std::vector<int> result;
	for (auto& pair : vertices) {
		if (std::get<0>(pair) == vertex) {
			result.push_back(std::get<1>(pair));
		}
	}
	return result;
}


std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
	std::vector<int> result;
	for (auto& pair : vertices) {
		if (std::get<1>(pair) == vertex) {
			result.push_back(std::get<0>(pair));
		}
	}
	return result;
}