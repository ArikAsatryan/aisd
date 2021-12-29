#include <iostream>
#include <sstream>


#include "ListGraph.h"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

void dfs_iter_inner(int s, const IGraph& graph, std::vector<bool>& visited, void(*callback)(int v)) {
		std::stack<int> stack;
		stack.push(s);

		while (!stack.empty()) {
			int s = stack.top();
			stack.pop();

			if (!visited[s]) {
				visited[s] = true;
				callback(s);
			}
			std::vector<int> children = graph.GetNextVertices(s);
			for (auto& child : children) {
				if (!visited[child]) {
					stack.push(child);
				}
			}
		}
}

void dfs_iter(const IGraph& graph, void(*callback)(int v)) {
	std::vector<bool> visited(graph.VerticesCount(), false);

	for (int i = 0; i < graph.VerticesCount(); ++i) {
		if (!visited[i]) {
			dfs_iter_inner(i, graph, visited, callback);
		}
	}
}


void bfs_iter_inner(int i, const IGraph& graph, std::vector<bool>& visited, void(*callback)(int v)) {
	std::queue<int> q;
	visited[i] = true;
	q.push(i);

	while (!q.empty()) {
		int s = q.front();
		q.pop();
		callback(s);

		std::vector<int> children = graph.GetNextVertices(s);
		for (auto& child : children) {
			if (!visited[child]) {
				visited[child] = true;
				q.push(child);
			}
		}
	}
}

void bfs_iter(const IGraph& graph, void(*callback)(int v)) {
	std::vector<bool> visited(graph.VerticesCount(), false);

	for (int i = 0; i < graph.VerticesCount(); ++i) {
		if (!visited[i]) {
			bfs_iter_inner(i, graph, visited, callback);
		}
	}
}


int main() {
	IGraph* graph = new ListGraph(9);
	//IGraph* Mgraph = new MatrixGraph(9);
	//IGraph* Sgraph = new SetGraph(9);
	//IGraph* Agraph = new ArcGraph(9);

	graph->AddEdge(0, 1);
	graph->AddEdge(1, 5);
	graph->AddEdge(6, 0);
	graph->AddEdge(1, 2);
	graph->AddEdge(2, 3);
	graph->AddEdge(3, 4);
	graph->AddEdge(4, 2);
	graph->AddEdge(0, 7);
	graph->AddEdge(0, 8);

	//IGraph* graph = new ListGraph(*Mgraph);
	IGraph* Mgraph = new MatrixGraph(*graph);
	IGraph* Sgraph = new SetGraph(*Mgraph);
	IGraph* Agraph = new ArcGraph(*Sgraph);



	std::cout << "------------DFS------------" << std::endl;
	std::cout << "ListG" << std::endl;
	// dfs(*graph, [](int v) {
	// 	std::cout << v << std::endl;
	// });
	//std::cout << std::endl;
	dfs_iter(*graph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "MatrixG" << std::endl;
	dfs_iter(*Mgraph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "ArcG" << std::endl;
	dfs_iter(*Agraph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "SetG" << std::endl;
	dfs_iter(*Sgraph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "------------BFS-------------" << std::endl;
	std::cout << "ListG" << std::endl;
	bfs_iter(*graph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "MatrixG" << std::endl;
	bfs_iter(*Mgraph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "ArcG" << std::endl;
	bfs_iter(*Agraph, [](int v) {
		std::cout << v << std::endl;
	});

	std::cout << "SetG" << std::endl;
	bfs_iter(*Sgraph, [](int v) {
		std::cout << v << std::endl;
	});

	return 0;
}

