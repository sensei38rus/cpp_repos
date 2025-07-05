#include "Set.h"
#include <iostream>

int main() {
	Set<int> set;
	set.insert(10);
	set.insert(15);
	set.insert(20);
	
	set.erase(20);
	
	std::cout << set;
	return 0;
}