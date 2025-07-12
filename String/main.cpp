#include "String.h"
#include <deque>
#include <stdexcept>
int main() {
	String str("some string");
	
	try {
		String test("-120");
		
		int num = str_to_int(test);
		std::cout << num << std::endl;
	
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	
}