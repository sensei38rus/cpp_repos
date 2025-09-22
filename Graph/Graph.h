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
	string id{};  //id узла
	unordered_map<string, int> output_nodes; //исходящие узлы(ID-вес)
	unordered_map<string, int> input_nodes; //входящие узлы(ID-вес)
public:
	Node(const string& id) : id(id){}
	friend class Graph;
};

class Graph{
	unordered_map<string, shared_ptr<Node>> nodes; // узлы(ID-указатель)
	void DFS(vector<vector<string>>& paths,vector<string>& vec, const string& id, const string& goal); //рекурсивный метод поиска в глубину
public:
	Graph() = default;
	Graph(const string& file_path); //конструктор который читает данные с файла
	size_t get_size() { return nodes.size(); } //кол-во узлов
	void add_node(const string& id, const string& output = {}, int weight = 0);//добавление ула
	void make_connection(const string& output, const string& input, int weight); //создание связи между двумя узлами
	void make_connections(const string& id, const vector<pair<string,int>>& output_ids); //создание связи между узлом и несколькими узлами
	void erase_node(const string& id); //удаление узла
	void clear(); //очистка графа
	void print_nodes(); //вывод связей узлов графа
	int distance(const string& output, const string& input); //вывод веса между двумя узлами
	bool find_way_BFS(const string& A, const string& B); //наличие пути по поиску в ширину
	pair<vector<string>, int> find_way_DFS(const string& A, const string& B); //поиск в глубину возвращает пару из вектора пути от A то B и int значение всего пути
	pair<vector<string>, int> dijkstra(const string& A, const string& B); //дийсктра, возвращает пару из вектора пути от A то B и int значение всего пути
};


