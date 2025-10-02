#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
	Map<string, int> map;
	
	cout << map["key"] << endl;

	return 0;
}