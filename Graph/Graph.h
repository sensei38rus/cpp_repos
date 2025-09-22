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

