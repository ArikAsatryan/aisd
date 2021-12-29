#include "MatrixGraph.hpp"

    MatrixGraph::MatrixGraph(const IGraph& graph) {
		size_t size = graph.VerticesCount();
		if (size == 0) {
			MatrixGraph(0);
			return;
		}
		matrix.resize(size);
		for (int i = 0; i < size; ++i) {
			matrix[i].resize(size, 0);
		}

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

    std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
		std::vector<int> result;
		for (int i = 0; i < matrix[0].size(); ++i) {
			if (matrix[vertex][i] != 0) {
				result.push_back(i);
			}
		}
		return result;
	}

	std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
		std::vector<int> result;
		for (int i = 0; i < matrix[0].size(); ++i) {
			if (matrix[i][vertex] != 0) {
				result.push_back(i);
			}
		}
		return result;
	}
	