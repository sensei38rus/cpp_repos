#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <initializer_list>

using namespace std;

class Graph;
class Node {
	string id{};
	unordered_map<string, int> output_nodes;
	unordered_map<string, int> input_nodes;
public:
	Node(const string& id) : id(id){}
	friend class Graph;
};

class Graph{
	unordered_map<string, shared_ptr<Node>> nodes;
	size_t size{};
	void DFS(vector<vector<string>>& paths,vector<string>& vec, const string& id, const string& goal);
public:
	Graph() = default;
	Graph(const string& file_path);
	size_t get_size() { return size; }
	void add_node(const string& id, const string& output = {}, int weight = 0);
	void make_connection(const string& output, const string& input, int weight);
	void make_connections(const string& id, const vector<pair<string,int>>& output_ids);
	void erase_node(const string& id);
	void clear();
	void print_nodes();
	int distance(const string& output, const string& input);
	bool find_way_BFS(const string& A, const string& B);
	pair<vector<string>, int> find_way_DFS(const string& A, const string& B);
	pair<vector<string>, int> dijkstra(const string& A, const string& B);
};


template <typename T>
class Binary_Tree;

template <typename T>
class Tree_Node {
	T data{};
	unique_ptr<Tree_Node> left{};
	unique_ptr<Tree_Node> right{};
public:
	Tree_Node(const T& data) : data(data){}
	
	template<typename T>
	friend class Binary_Tree;
	
};

template <typename T>
class Binary_Tree {
	unique_ptr<Tree_Node<T>> root{};
	
	void add(unique_ptr<Tree_Node<T>>& ptr, vector<T>& vec);
public:
	Binary_Tree() = default;
	Binary_Tree(const initializer_list<T>& lst);
	void add_node(const T& value);
	void erase_node(const T& value);
	bool count(const T& value);

	vector<T> get_nodes();

};


template <typename T>
Binary_Tree<T>::Binary_Tree(const initializer_list<T>& lst) {
	auto start = lst.begin();
	while (start != lst.end()) {
		add_node(*start);
		++start;
	}
}



template <typename T>
bool Binary_Tree<T>::count(const T& value) {
	if (!root)
		throw invalid_argument("Empty tree");
	auto start = root.get();
	while (true) {
		if (value == start->data)
			return true;
		if (value > start->data) {
			if (!start->right)
				return false;
			start = start->right.get();
		}
		if (value < start->data) {
			if (!start->left)
				return false;
			start = start->left.get();
		}
	}
	return false;
}

template <typename T>
void Binary_Tree<T>::add_node(const T& value) {
	if (!root) {
		root = make_unique<Tree_Node<T>>(value);
		return;
	}
	auto start = root.get();
	while (true) {
		if (value == start->data)
			return;
		if (value > start->data) {
			if (start->right) {
				start = start->right.get();
			}
			else {
				start->right = make_unique<Tree_Node<T>>(value);
				
				return;
			}
		}
		if (value < start->data) {
			if (start->left) {
				start = start->left.get();
			}
			else {
				start->left = make_unique<Tree_Node<T>>(value);
				return;
			}
		}
	}
}
template <typename T>
void Binary_Tree<T>::add(unique_ptr<Tree_Node<T>>& ptr, vector<T>& vec) {
	if (!ptr->left) {
		vec.push_back(ptr->data);
		if (ptr->right)
			add(ptr->right,vec);
		return;
	}
	add(ptr->left,vec);

	vec.push_back(ptr->data);
	if(ptr->right)
		add(ptr->right,vec);

}

template <typename T>
vector<T> Binary_Tree<T>::get_nodes() {
	vector<T> vec{};
	add(root, vec);
	return vec;
}

template <typename T>
void Binary_Tree<T>::erase_node(const T& value) {
	if (!root)
		throw invalid_argument("Node does not exists");
	auto start = root;
	while (start) {
		if (value == start->data) {

		}
	}
}