#pragma once
#include <stdexcept>
#include <initializer_list>
#include <iostream>

template <typename T, int arrsize>
class Array {
	T* arr = new T[arrsize];
public:
	~Array() {
		delete[] arr;
	}
	
	int size() const {
		return arrsize;
	}
	Array() = default;
	Array(std::initializer_list<T> lst) {
		if (lst.size() > arrsize)
			throw std::length_error("Too big to initialize");
		
		
		auto start = lst.begin();
		for (int i = 0; i < arrsize; i++) {
			if (i < lst.size()) {
				arr[i] = *start;
				start++;
			}
			else {
				arr[i] = T{};
			}
		}
		
	}
	Array(const Array& another) {
		for (int i = 0; i < arrsize; i++) {
			arr[i] = another.arr[i];
		}
	}
	Array(Array&& moved) noexcept {
		arr = moved.arr;
		moved.arr = nullptr;
		
	}
	Array& operator=(const Array& another) {
		if (this != &another) {
			for (int i = 0; i < arrsize; i++) {
				arr[i] = another.arr[i];
			}
		}
		return *this;
	}
	Array& operator=(Array&& moved) noexcept{
		arr = moved.arr;
		moved.arr = nullptr;
		return *this;

	}

	T& operator[](int index) {
		if (index < 0 || index >= arrsize)
			throw std::out_of_range("Invalid index");
		return arr[index];
	}

	template<typename U, int size>
	friend std::ostream& operator<<(std::ostream& out, const Array<U, size>& array) {
		out << "[";
		for (int i = 0; i < size; i++) {
			out << array.arr[i];
			if (i != size - 1)
				out << ",";
		}
		out << "]";
		return out;
	}


};