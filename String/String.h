#pragma once
#include <iostream>
class String {
	char* str = nullptr;
	int size = 0;
public:
	int get_size() const { return size; }
	String(const char* string);
	String(const String& string);
	String(String&& moved) noexcept;
	String() = default;
	~String() {
		delete[] str;
	}

	char operator[](int index) const;
	String& operator=(const String& string);
	String& operator=(String&& moved) noexcept;
	String operator+(const String& string);
	String operator+=(const String& string);
	friend std::ostream& operator<<(std::ostream& out, const String& string);
	friend String int_to_str(int num);
	friend int str_to_int(const String& string);
};
String int_to_str(int num);
int str_to_int(const String& string);