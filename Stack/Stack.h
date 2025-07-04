#pragma once
#include <memory>
#include <stdexcept>
using namespace std;


template <typename T>
class Stack;

template <typename T>
class StackElement {
	T data;
	unique_ptr<StackElement> previous;
public:
	StackElement(const T& adata) : data(adata){}

	friend class Stack<T>;

	template <typename U>
	friend ostream& operator<<(ostream& out, const Stack<U>& stack);
	
	
};

template <typename T>
class Stack {
	unique_ptr<StackElement<T>> top;
	int size = 0;
public:
	void push(const T& data);
	T pop();
	void swap(Stack& another);
	bool empty() { return !top; }
	const T& get_top() const { return top->data; }
	int get_size() const { return size; }
	template <typename U>
	friend ostream& operator<<(ostream& out, const Stack<U>& stack);
	
};


template <typename T>
void Stack<T>::push(const T& data) {
	unique_ptr<StackElement<T>> element = make_unique<StackElement<T>>(data);
	if (top)
		element->previous = move(top);
	top = move(element);
	size++;
}

template <typename T>
T Stack<T>::pop() {
	T data;
	if (empty()) throw runtime_error("Stack is empty");
	data = top->data;
	top = move(top->previous);
	size--;
	return data;
}

template <typename T>
void Stack<T>::swap(Stack<T>& another) {
	swap(top, another.top);
	swap(size, another.size);
}

template <typename U>
ostream& operator<<(ostream& out, const Stack<U>& stack){
	auto begin = stack.top.get();
	while (begin) {
		out << begin->data << " ";
		begin = begin->previous.get();
	}
	return out;
}
