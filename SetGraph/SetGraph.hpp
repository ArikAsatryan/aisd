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

template<typename T>
struct DefaultComparator {
	int operator() (const T& l, const T& r) const {
		if (l < r) {
			return -1;
		}
		else if (l > r) {
			return 1;
		}
		else {
			return 0;
		}
	}
};

template<typename Key, class Comparator = DefaultComparator<Key>>
class AvlTree {
	struct Node {
		Node* right;
		Node* left;

		Key key;
		int height;
		int elem_num;

		Node(const Key& key) : right(nullptr), left(nullptr), key(key), height(1), elem_num(1) {}
		~Node() {
			delete left;
			delete right;
		}
	};
public:
	AvlTree(Comparator comp = Comparator()) : root(nullptr), comp(comp) {}

	~AvlTree() {
		delete root;
	}

	bool has(const Key& key) const {
		return hasInternal(key, root);
	}

	void insert(const Key& key) {
		root = insertInternal(key, root);
		for_dump.push_back(key);
	}

	void erase(const Key& key) {
		root = eraseInternal(key, root);
		for_dump.erase(key);
	}

	void print() {
		if (!root) {
			return;
		}
		printInternal(root);
	}

	int kth_stat(int pos) {
		return kthInternal(root, pos + 1);
	}

	std::vector<Key> dump() const {
		return for_dump;
	}

private:

	int kthInternal(Node* node, int pos) {
		if (elem_num(node->left) + 1 == pos) {
			return node->key;
		}
		else  if (elem_num(node->left) < pos) {
			return kthInternal(node->right, pos - elem_num(node->left) - 1);
		}
		else {
			return kthInternal(node->left, pos);
		}
	}


	void printInternal(Node* node) {
		if (!node) {
			return;
		}
		printInternal(node->left);
		std::cerr << "key: " << node->key << "  elemcount: " << node->elem_num << std::endl;
		printInternal(node->right);
	}


	bool hasInternal(const Key& key, Node* node) const {
		if (!node) {
			return false;
		}

		int cmp_res = comp(key, node->key);
		if (cmp_res == -1) {
			return hasInternal(key, node->left);
		}
		else {
			return hasInternal(key, node->right);
		}
		return true;
	}

	Node* insertInternal(const Key& key, Node* node) {
		if (!node) {
			return new Node(key);
		}

		int cmp_res = comp(key, node->key);
		if (cmp_res == -1) {
			node->left = insertInternal(key, node->left);
		}
		else {
			node->right = insertInternal(key, node->right);
		}
		return balance(node);
	}

	int height(Node* node) {
		if (!node) {
			return 0;
		}
		return node->height;
	}

	int elem_num(Node* node) {
		if (node) {
			return node->elem_num;
		}
		return 0;
	}

	int bfactor(Node* node) {
		return height(node->right) - height(node->left);
	}

	void fix_height(Node* node) {
		if (!node) {
			return;
		}
		node->height = std::max(height(node->left), height(node->right)) + 1;
		node->elem_num = elem_num(node->left) + elem_num(node->right) + 1;
	}

	Node* rotate_left(Node* node) {
		Node* tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;
		fix_height(node);
		fix_height(tmp);
		return tmp;
	}

	Node* rotate_right(Node* node) {
		Node* tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;
		fix_height(node);
		fix_height(tmp);
		return tmp;
	}

	Node* balance(Node* node) {
		fix_height(node);
		int bf = bfactor(node);
		if (bf == 2) {
			if (bfactor(node->right) < 0) {
				node->right = rotate_right(node->right);
			}
			return rotate_left(node);
		}
		else if (bf == -2) {
			if (bfactor(node->left) > 0) {
				node->left = rotate_left(node->left);
			}

			return rotate_right(node);
		}
		return node;
	}

	Node* eraseInternal(const Key& key, Node* node) {
		if (!node) {
			return nullptr;
		}
		int cmp_res = comp(key, node->key);
		if (cmp_res == -1) {
			node->left = eraseInternal(key, node->left);
		}
		else if (cmp_res == 1) {
			node->right = eraseInternal(key, node->right);
		}
		else {
			Node* left = node->left;
			Node* right = node->right;

			if (!right) {
				return left;
			}

			Node* min_node = find_min(right);
			min_node->right = remove_min(right);
			min_node->left = left;
			node->left = nullptr;
			node->right = nullptr;
			delete node;
			return balance(min_node);
		}
		return balance(node);
	}

	Node* remove_min(Node* node) {
		if (!node->left) {
			return node->right;
		}
		node->left = remove_min(node->left);
		return balance(node);
	}
	Node* find_min(Node* node) {
		if (!node->left) {
			return node;
		}
		return find_min(node->left);
	}

	Node* root;
	std::vector<Key> for_dump;
	Comparator comp;
};


class SetGraph : public IGraph {
public:
	SetGraph(int vertices_count) {
		vertices.resize(vertices_count);
	}

	SetGraph(const IGraph& graph) {
		size_t size = graph.VerticesCount();
		if (size == 0) {
			SetGraph(0);
			return;
		}
		vertices.resize(size);;

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

	void AddEdge(int from, int to) override {
		if (!vertices[from].has(to)) {
			vertices[from].insert(to);
		}
	}

	int VerticesCount() const override {
		return vertices.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		return vertices[vertex].dump();
	}

	std::vector<int> GetPrevVertices(int vertex) const override {
		std::vector<int> result;
		for (int i = 0; i < vertices.size(); ++i) {
			if (vertices[i].has(vertex)) {
				result.push_back(i);
			}
		}
		return result;
	}

	~SetGraph() {}
private:
	std::vector<AvlTree<int>> vertices;
};