#include <iostream>
#include <string>
#include <string_view>

class Test
{
public:
	int value{ 0 };
	Test& add(int x) {
		value += x;
		return *this;
	}

	Test& subtract(int x) {
		value -= x;
		return *this;
	}

};



int main()
{
	Test t;
	t.add(5).subtract(2);
	std::cout << t.value;

	return 0;
}