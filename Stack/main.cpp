#include "Stack.h"
#include <iostream>

int main() {

	Stack<int> stack;
	stack.push(10);
	stack.push(15);
	stack.push(20);
	std::cout << stack;
	return 0;
}
