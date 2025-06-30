#include "Manager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;


bool check_input() {
	if (!cin) {
		cin.clear();
		cin.ignore(10000000, '\n');
		cout << "Invalid input! Try again!\n";
		return false;
	}
	return true;
}


Manager::Manager() {
	cout << "Hello it's your file manager!\nWhat do you want to do?\n";
	bool working = true;
	while (working) {
		cout << "1.Create file\n2.Delete file\n3.Check file\n4.Update file\n5.Check History\n6.Exit\n";
		int pick;
		while (true) {
			cin >> pick;
			if (!check_input()) {
				continue;
			}

			if (pick > 6 || pick < 1) {
				cout << "Incorrect input! Try again!\n";
				continue;
			}
			break;
		}

		string file_name;
		cout << "Enter the file name: ";
		while (true) {
			cin >> file_name;
			if (check_input())
				break;
		}

		switch (pick) {
		case 1:
			create_file(file_name);
			break;
		case 2:
			delete_file(file_name);
			break;
		case 3:
			check_file(file_name);
			break;
		case 4:
			update_file(file_name);
			break;
		case 5:
			check_history();
			break;
		default:
			working = false;
		}
	}
	load_history();
	
	

}

void Manager::create_file(const string& file_name) {
	ofstream file(file_name);
	if (file) {
		cout << "File was succesfully created!\n";
		created_files.push_back(file_name);
	}
	else {
		cerr << "Error: cannot create file!\n";
	}
	file.close();
}

void Manager::delete_file(const string& file_name) {
	if (!filesystem::exists(file_name)) {
		cout << "File does not exist!\n";
		return;
	}
	if (filesystem::remove(file_name)) {
		cout << "File was succesfully deleted!\n";
		deleted_files.push_back(file_name);
	}

}


void Manager::check_file(const string& file_name) {
	ifstream file(file_name);
	string line;
	if (!file) {
		cerr << "Cannot open this file!\n";
		return;
	}

	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
}


void Manager::update_file(const string& file_name) {
	ofstream file(file_name, ios::app);
	cin.ignore(100000000, '\n');
	if (!file) {
		cerr << "Cannot open this file!\n";
		return;
	}
	cout << "Enter what do you want to add in file: \n";
	string line;
	
	getline(cin, line);
	file << endl;
	file << line << endl;
	file.close();
	updated_files.push_back(file_name);
}

void Manager::load_history() {
	ofstream file("History.txt");
	file << "Created files: \n";
	for (auto str : created_files) {
		file << str << endl;
	}
	file << "Deleted files: \n";
	for (auto str : deleted_files) {
		file << str << endl;
	}
	file << "Updated files: \n";
	for (auto str : updated_files) {
		file << str << endl;
	}
	file.close();
}

void Manager::check_history() {
	ifstream file("History.txt");
	string line;
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
}
