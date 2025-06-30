#pragma once
#include <vector>
#include <string>
using namespace std;

class Manager {
	vector<string> created_files;
	vector<string> deleted_files;
	vector<string> updated_files;
public:
	Manager();
	void create_file(const string& file_name);
	void delete_file(const string& file_name);
	void update_file(const string& file_name);
	void check_file(const string& file_name);
	void load_history();
	void check_history();
};