#include "Deque.h"
#include <iostream>


int main() {
	Deque<int> deque({1,2,3,4,5,6});
	
	deque.insert(2, 10,3);

	
	while (!deque.empty()) {
		std::cout << deque.get_front() << " ";
		deque.pop_front();
	}
}
