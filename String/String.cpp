#include "String.h"
#include <deque>
#include <stdexcept>
String::String(const char* string) {
	int str_size = 0;
	for (auto ptr = string; *ptr != '\0'; ptr++) {
		str_size++;
	}
	size = str_size;
	str = new char[str_size+1];
	for (int i = 0; i < str_size; i++) {
		str[i] = string[i];
	}
	str[size] = '\0';
}

String::String(const String& string) {
	size = string.size;
	str = new char[size];
	for (int i = 0; i < size; i++) {
		str[i] = string.str[i];
	}
}


String::String(String&& moved) noexcept {
	size = moved.size;
	str = moved.str;
	moved.str = nullptr;
}

std::ostream& operator<<(std::ostream& out, const String& string) {
	for (int i = 0; i < string.size; i++) {
		out << string.str[i];
	}
	return out;
}
String String::operator+(const String& string) {
	int str_size = size + string.size;
	char* new_str = new char[str_size+1];
	for (int i = 0; i < size; i++) {
		new_str[i] = str[i];
	}
	for (int i = size, j = 0; i < str_size; i++, j++) {
		new_str[i] = string.str[j];
	}
	new_str[str_size] = '\0';
	String new_string;
	new_string.str = new_str;
	new_string.size = str_size;
	
	return new_string;
}

String& String::operator=(const String& string) {
	if (this != &string) {
		size = string.size;
		delete str;
		str = new char[size + 1];
		for (int i = 0; i < size; i++) {
			str[i] = string.str[i];
		}
		str[size] = '\0';
	}
	return *this;
}

String& String::operator=(String&& moved) noexcept{
	size = moved.size;
	str = moved.str;
	moved.str = nullptr;
	return *this;
}


String String::operator+=(const String& string) {
	*this = *this + string;
	return *this;
}

char String::operator[](int index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("invalid index");
	}
	return str[index];
}

String int_to_str(int number) {
	const char* nums = "0123456789";
	std::deque<int> digits;

	int num = number >= 0 ? number : -number;
	while (num > 0) {
		digits.push_front(num % 10);
		num /= 10;
	}
	char* arr{};
	if (number >= 0) {
		arr = new char[digits.size() + 1];
		for (int i = 0; i < digits.size(); i++) {
			arr[i] = nums[digits[i]];
		}
	}
	if (number < 0) {
		arr = new char[digits.size() + 2];
		arr[0] = '-';
		for (int i = 0, j = 1; i < digits.size(); i++, j++) {
			arr[j] = nums[digits[i]];
		}
	}
	int size = number >= 0 ? digits.size() : digits.size() + 1;
	arr[size] = '\0';
	String string;
	string.str = arr;
	string.size = size;

	return string;
}

double pow(double number, int degree) {
	int num = number;
	int deg = degree >= 0 ? degree : -degree;
	if (deg == 0)
		return 1;
	for (int i = 1; i < deg; i++) {
		num *= number;
	}
	return degree > 0 ? num : 1/num;
}

int str_to_int(const String& string) {
	const char* nums = "0123456789";
	std::deque<int> digits;
	for (int i = 0; i < string.size; i++) {
		for (int j = 0; j < 10; j++) {
			if (string[i] == nums[j]) {
				digits.push_front(j);
			}
		}
	}
	if ((digits.size() != string.size && string[0] != '-') || (string[0] == '-' && digits.size() + 1 != string.size) )
		throw std::invalid_argument("not a number");
	int number{};
	for (int i = digits.size() - 1; i >= 0; i--) {
		number += (digits[i] * pow(10, i));
	}
	return string[0] == '-' ? -number : number;
	
}

