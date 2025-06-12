#pragma once
#include <iostream>
class Test {
public:
	static inline int x = 5;


	static int add(int x, int y);
	
};

int inline Test::add(int x, int y) {
	return x + y;
}
