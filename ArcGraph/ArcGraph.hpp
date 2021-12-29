#include <iostream>
#include <vector>
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

class ArcGraph : public IGraph {
public:
	ArcGraph(int vertices_count): vertices_count(vertices_count) {}

	ArcGraph(const IGraph& graph);

	void AddEdge(int from, int to) override {
		vertices.push_back(std::make_pair(from, to));
	}

	int VerticesCount() const override {
		return vertices_count;
	}

	std::vector<int> GetNextVertices(int vertex) const override;

	std::vector<int> GetPrevVertices(int vertex) const override;

	~ArcGraph() {}
private:
	std::vector<std::pair<int,int>> vertices;
	int vertices_count;
};