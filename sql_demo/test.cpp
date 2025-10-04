#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include "base.h"

using namespace std;

int main()
{
	try{
		Base base("base");
		base.create_table("workers", "ID", {"NAME", "JOB", "NUMBER"});
		base.insert("workers", "0", {"MIKE", "MANAGER", "12345"});
		base.insert("workers", "1", {"JOHN", "MANAGER", "1123123"});

		base.create_table("orders", "ORDER_ID", {"DATE", "STATUS", "PROFIT"});
		base.insert("orders", "0", {"11.01.25", "FINISHED", "200"});
		base.print();
	}
	catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return 0;
}