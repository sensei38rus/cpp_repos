#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
	Map<string, int> map;
	
	map["apple"] = 10;
	map["zibra"] = 20;
	map["bibra"] = 30;

	try {
		map.erase("bibra");
		cout << map << endl;
	}
	catch (const invalid_argument& e) {
		cerr << e.what() << endl;
	}

	return 0;
}