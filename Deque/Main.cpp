#include "Deque.h"
#include <iostream>
#include <stdexcept>

int main() {
	Deque<int> deque({1,2,3,4,5,6});
	/*try {
		std::cout << deque.at(10) << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}*/
	
	
	Deque<int>::Iterator iter = deque.begin();
	while (iter) {
		std::cout << *iter << " ";
		++iter;
	}
	
	
}
