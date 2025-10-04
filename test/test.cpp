#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include "../Algo/Algo.h"
#include "../sql_demo/base.h"

using namespace std;



class Element{
	int i_data{};
	string s_data{};
	double d_data{};

	string type = "string";
public:
	Element() = default;
	Element(int i) : i_data(i){type = "int";}
	Element(const string& s) : s_data(s){type = "string";}
	Element(double d) : d_data(d){type = "double";}
	friend ostream& operator<<(ostream& out, const Element& e);
	
};
ostream& operator<<(ostream& out, const Element& e){
		if(e.type == "int")
			out << e.i_data;
		else if(e.type == "string")
			out << e.s_data;
		else 
			out << e.d_data;
		return out;
	}

int main()
{


	// unordered_map<string, unordered_map<string, Element>> base;
	

	// base["0"]["NAME"] = Element("MIKE");
	// base["0"]["NUMBER"] = Element(1234);
	// base["0"]["JOB"] = Element("DEVELOPER");

	// base["1"]["NAME"] = Element("JOHN");
	// base["1"]["NUMBER"] = Element(4515);
	// base["1"]["JOB"] = Element("MANAGER");

	// for(auto person : base){
	// 	cout << "ID---" << person.first << endl; 
	// 	for(auto data : person.second){
	// 		cout << data.first << "---" << data.second << endl;
	// 	}
	// 	cout << endl;
	// }

	Base base("base");

	Table& people_table = base["people"];

	unordered_map<string,string>& john_data = people_table["0"];
	john_data["name"] = "john";
	john_data["work"] = "manager";
	john_data["number"] = "1214144";

	unordered_map<string,string>& mike_data = people_table["1"];
	mike_data["name"] = "mike";
	mike_data["work"] = "developer";
	mike_data["number"] = "121414436536";


	Table& orders_table = base["orders"];
	unordered_map<string,string>& first_order = orders_table["0"];
	first_order["date"] = "11.05.25";
	first_order["price"] = "125";

	cout << base << endl;


	return 0;
}