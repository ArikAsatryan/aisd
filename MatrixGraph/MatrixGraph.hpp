#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <cassert>
#include <sstream>
#include <math.h>
#include <string>
#include <cstring>

#ifndef IGRAPH
#define IGRAPH
struct IGraph {
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
#endif

class MatrixGraph : public IGraph {
public:
	MatrixGraph(int vertices_count) {
		matrix.resize(vertices_count);
		for (int i = 0; i < vertices_count; ++i) {
			matrix[i].resize(vertices_count, 0);
		}
	}

	MatrixGraph(const IGraph& graph);

	void AddEdge(int from, int to) override {
		matrix[from][to] = 1;
	}

	int VerticesCount() const override {
		return matrix[0].size();
	}

	std::vector<int> GetNextVertices(int vertex) const override;

	std::vector<int> GetPrevVertices(int vertex) const override;

	~MatrixGraph() {}
private:
	std::vector<std::vector<int>> matrix;
};
