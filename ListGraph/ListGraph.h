#pragma once
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
#define IGRAPH

struct IGraph {
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
	ListGraph(int vertices_count) {
		vertices.resize(vertices_count);
	}

	ListGraph(const IGraph& graph);
	
	void AddEdge(int from, int to) override {
		vertices[from].push_back(to);
	}

	int VerticesCount() const override {
		return vertices.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		std::vector<int> result(vertices[vertex].begin(), vertices[vertex].end());
		return result;
	}

	std::vector<int> GetPrevVertices(int vertex) const override;
	
	~ListGraph() {}
private:
	std::vector<std::vector<int>> vertices;
};
