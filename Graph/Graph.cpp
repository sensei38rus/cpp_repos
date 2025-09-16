#include "Graph.h"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;


void Graph::add_node(const string& id, const string& output_id, int weight) {
	shared_ptr<Node> new_node = make_shared<Node>(id);
	nodes[id] = new_node;
	if (!output_id.empty()) {
		if (nodes.count(output_id))
			nodes[output_id]->input_nodes[id] = weight;
		else
			throw invalid_argument("Output node does not exists");
	}
}

void Graph::make_connection(const string& output, const string& input, int weight) {

	if (!nodes.count(output)) 
		add_node(output);
	
	if (!nodes.count(input))
		add_node(input);

	nodes[output]->output_nodes[input] = weight;
	nodes[input]->input_nodes[output] = weight;
}
	


void Graph::erase_node(const string& id) {
	if (nodes.count(id)) {
		for (auto node : nodes[id]->input_nodes) {
			nodes[node.first]->output_nodes.erase(id);
		}
		for (auto node : nodes[id]->output_nodes) {
			nodes[node.first]->input_nodes.erase(id);
		}
		nodes.erase(id);
	}
	else
		throw invalid_argument("Node does not exists");
}

void Graph::clear() {
	nodes.clear();
}

void Graph::print_nodes() {
	for (auto node : nodes) {
		cout << node.first << "->";
		for (auto output : node.second->output_nodes) {
			cout << output.first << " & ";
		}
		cout << endl;
	}
}

int Graph::distance(const string& output, const string& input) {
	if (!nodes.count(output) || !nodes.count(input))
		throw invalid_argument("Node or nodes do not exist");
	return  nodes[output]->output_nodes.count(input) ? nodes[output]->output_nodes[input] : 0;
}

bool Graph::find_way_BFS(const string& A, const string& B) {
	if (!nodes.count(A) || !nodes.count(B))
		throw invalid_argument("Node or nodes do not exist");
	queue<string> visits;
	visits.push(A);
	vector<string> visited;
	while (!visits.empty()) {
		if (visits.front() == B)
			return true;
		if (find(visited.begin(), visited.end(), visits.front()) != visited.end()) {
			visits.pop();
			continue;
		}
		for (auto e : nodes[visits.front()]->output_nodes) {
			visits.push(e.first);
		}
		visited.push_back(visits.front());
		visits.pop();
	}
	return false;

}


void Graph::DFS(vector<vector<string>>& paths,vector<string>& vec, const string& id, const string& goal) {
	vector<string> curr_path = vec;
	curr_path.push_back(id);
	for (auto node : nodes[id]->output_nodes) {
		if (find(curr_path.begin(), curr_path.end(), node.first) != curr_path.end())
			continue;

		if (node.first == goal) {
			curr_path.push_back(node.first);
			paths.push_back(curr_path);
			return;
		}
		
		DFS(paths, curr_path, node.first, goal);
		
	}
}

pair<vector<string>, int> Graph::find_way_DFS(const string& A, const string& B) {
	if(!nodes.count(A) || !nodes.count(B))
		throw invalid_argument("Node or nodes do not exist");
	if (A == B)
		return { {},0 };
	vector<vector<string>> paths;
	vector<string> path;
	DFS(paths, path, A, B);
	int min_distance = numeric_limits<int>::max();
	for (auto el : paths) {
		int sum_dist = 0;
		for (int i = 0; i < el.size() - 1; i++) {
		
			sum_dist += distance(el[i], el[i + 1]);
		}
		
		if (sum_dist < min_distance) {
			min_distance = sum_dist;
			path = el;
		}
	}
	return { path, min_distance };
	
}

void Graph::make_connections(const string& origin, const vector<pair<string, int>>& output_ids) {
	if (!nodes.count(origin))
		add_node(origin);

	for (auto id : output_ids) {
		if (!nodes.count(id.first))
			add_node(id.first);
		nodes[origin]->output_nodes[id.first] = id.second;
		nodes[id.first]->input_nodes[origin] = id.second;
	}
}




pair<vector<string>, int> Graph::dijkstra(const string& A, const string& B){
	unordered_map<string, int> node_weight; //хэш таблица узел-вес
	unordered_map<string, string> node_parent; //хэш таблица узел-родитель

	auto comparator = [&node_weight](const string& node1, const string& node2) {
		return node_weight[node1] > node_weight[node2];
	};
	//queue<string> check; //очередь приоритета
	priority_queue<string, std::vector<string>, decltype(comparator)> check(comparator);

		for (auto node : nodes) {
		if (node.first == A)
			continue;
		if (nodes[A]->output_nodes.count(node.first)) {
			node_weight[node.first] = nodes[A]->output_nodes[node.first];
			node_parent[node.first] = A;
			check.push(node.first);
		}
		else {
			node_weight[node.first] = numeric_limits<int>::max();
			node_parent[node.first] = "-";
		}
	}

	while (!check.empty()) {
		for (auto node : nodes[check.top()]->output_nodes) {
			/*if (node.first == B) {
				node_weight[B] = nodes[check.top()]->output_nodes[node.first] + node_weight[check.top()];
				node_parent[B] = check.top();
				break;
			}*/

			if (nodes[check.top()]->output_nodes[node.first] + node_weight[check.top()] < node_weight[node.first]) {
				node_weight[node.first] = nodes[check.top()]->output_nodes[node.first] + node_weight[check.top()];
				node_parent[node.first] = check.top();
				check.push(node.first);
			}
		}
		check.pop();
	}

	vector<string> path{B};
	int distance = node_weight[B];
	auto curr_node = B;
	//while (curr_node != A) {
	//	path.push_back(node_parent[curr_node]);
	//	curr_node = node_parent[curr_node];
	//}
	for (int i = 0; i < node_weight.size(); i++) {
		path.push_back(node_parent[curr_node]);
		curr_node = node_parent[curr_node];
		if (curr_node == A) {
			return { path,distance };
		}
			
	}
	path = {};
	distance = 0;
	return { path, distance };
}


Graph::Graph(const string& file_path) {
	ifstream file(file_path);
	string str{};
	while (getline(file,str)) {
		string output{};
		string input{};
		string weight{};

		stringstream stream(str);
		stream >> output >> input >> weight;
		int w_int{};
		try {
			w_int = stoi(weight);
		}
		catch (const exception& e) {
			continue;
		}
		make_connection(output, input, w_int);

	}
	file.close();
}