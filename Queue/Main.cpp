#include <iostream>
#include "Queue.h"

int main() {
	Queue<int> queue;
	queue.push(10);
	queue.push(15);
	queue.push(20);

	Queue<int> queue2;
	queue2.push(40);
	queue2.push(50);
	queue2.push(60);

	queue.swap(queue2);

	while (!queue.empty()) {
		std::cout << queue.get_front() << " ";
		queue.pop();
	}
	std::cout << std::endl;


	
	while (!queue2.empty()) {
		std::cout << queue2.get_front() << " ";
		queue2.pop();
	}
	







	
	
}