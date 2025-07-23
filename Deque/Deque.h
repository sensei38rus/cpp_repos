#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
using namespace std;



template <typename T>
class Deque;




template <typename T>
class DequeElement {

	T data;
	shared_ptr<DequeElement> next;
public:
	DequeElement(T adata) : data(adata) {};
	friend class Deque<T>;
	
	template <typename U>
	friend ostream& operator<<(ostream& out, const Deque<U>& deque);
	
};

template <typename T>
class Deque {
	shared_ptr<DequeElement<T>> front;
	shared_ptr<DequeElement<T>> back;
	int size = 0;
public:
	const T& get_front() const { return front->data; }
	const T& get_back() const{ return back->data; }
	const T& at(int index) const;
	const int& get_size() const { return size; }
	void clear();
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	bool empty();
	void resize(int n);
	void insert(int pos, const T& value, int n = 1);

	

	Deque() = default;
	Deque(int n, const T& value);
	Deque(int n);
	Deque(const Deque& copy);
	Deque(const vector<T>& arr);
	const T& operator[](int index) const;
	template <typename U>
	friend ostream& operator<<(ostream& out, const Deque<U>& deque);

	class Iterator {
	public:
		shared_ptr<DequeElement<T>> ptr;
	public:
		Iterator(shared_ptr<DequeElement<T>> ptr) : ptr(ptr) {}
		Iterator() = default;
		Iterator& operator=(const Iterator& another) {
			ptr = another.ptr;
			return *this;
		}
		operator bool() const{
			return ptr.get();
		}
		const T& operator*() {
			return ptr->data;
		}
		Iterator& operator++() {
			ptr = ptr->next;
				
			return *this;
		}
		Iterator operator+(int n) {
			auto copy = *this;
			for (int i = 0; i < n; i++) {
				copy.ptr = copy.ptr->next;
					
			}
			return copy;
		}
		Iterator& operator+=(int n) {
			for (int i = 0; i < n; i++) {
				ptr = ptr->next;
			}
			return *this;
		}
		bool operator==(const Iterator& another) {
			return ptr.get() == another.ptr.get();
		}
		bool operator!=(const Iterator& another) {
			return ptr.get() != another.ptr.get();
		}
		bool operator>(const Iterator& another) {
			return ptr.get() > another.ptr.get();
		}
		bool operator<(const Iterator& another) {
			return ptr.get() < another.ptr.get();
		}
		bool operator<=(const Iterator& another) {
			return ptr.get() <= another.ptr.get();
		}
		bool operator>=(const Iterator& another) {
			return ptr.get() >= another.ptr.get();
		}
	};

	Iterator begin() const {
		return Iterator(front);
	}
	Iterator end() const {
		return Iterator(back);
	}
};



template <typename T>
void Deque<T>::push_back(const T& data) {
	shared_ptr<DequeElement<T>> element = make_shared<DequeElement<T>>(data);
	if (!front) {
		front = element;
	}
	else {
		back->next = element;
	}
	back = element;
	size++;
}

template <typename T>
void Deque<T>::push_front(const T& data) {
	shared_ptr<DequeElement<T>> element = make_shared<DequeElement<T>>(data);
	if (!front) {
		back = element;
	}
	else {
		element->next = front;
	}
	front = element;
	size++;
}

template <typename T>
bool Deque<T>::empty() {
	if (!front)
		return true;
	return false;
}

template <typename T>
void Deque<T>::pop_front() {
	if (!empty()) {
		if (front == back) {
			front = nullptr;
			back = nullptr;
			
		}
		else {
			front = front->next;
		}
		size--;
	}
}

template <typename T>
void Deque<T>::pop_back() {
	if (!empty()) {
		if (front == back) {
			front = nullptr;
			back = nullptr;
		}
		else {
			shared_ptr<DequeElement<T>> element = front;
			for (int i = 0; i < size - 2; i++) {
				element = element->next;
			}
			back = element;
			back->next = nullptr;
		}
		size--;
	}
}

template <typename T>
void Deque<T>::clear(){
	front = nullptr;
	back = nullptr;
	size = 0;
}

template <typename T>
const T& Deque<T>::at(int index) const{
	if (index < 0 || index >= size) {
		throw out_of_range("invalid index");
	}
	else {
		shared_ptr<DequeElement<T>> element = front;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element->data;
	}
	
}

template <typename T>
const T& Deque<T>::operator[](int index) const{
	return at(index);
}

template <typename T>
Deque<T>::Deque(int n) {
	T data{};
	for (int i = 0; i < n; i++) {
		push_back(data);
	}
}


template <typename T>
Deque<T>::Deque(int n, const T& value) {
	for (int i = 0; i < n; i++) {
		push_back(value);
	}
}

template <typename T>
Deque<T>::Deque(const Deque<T>& copy) {
	front = copy.front;
	back = copy.back;
}

template <typename T>
Deque<T>::Deque(const vector<T>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		push_back(vec[i]);
	}
}

template <typename T>
void Deque<T>::resize(int n) {

	if (n < size) {
		int j = size - n;
		for (int i = 0; i < j; i++) {
			pop_back();
		}
	}
	if (n > size) {
		int j = n - size;
		T element{};
		for (int i = 0; i < j; i++) {
			push_back(element);
		}
	}
	size = n;
}

template <typename T>
void Deque<T>::insert(int pos, const T& value, int n) {
	if (pos >= 0 && pos < size) {
		auto begin = front;
		for (int i = 0; i < pos-1; i++) {
			begin = begin->next;
		}
		for (int i = 0; i < n; i++) {
			auto element = make_shared<DequeElement<T>>(value);
			element->next = begin->next;
			begin->next = element;
			begin = element;
			size++;
			
		}
	}
}


template <typename T>
ostream& operator<<(ostream& out, const Deque<T>& deque) {
	auto begin = deque.front;
	while (begin) {
		out << begin->data << " ";
		begin = begin->next;
	}
	return out;
}





