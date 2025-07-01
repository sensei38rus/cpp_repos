#pragma once
#include <memory>
using namespace std;

template <typename T>
class Queue;


template <typename T>
class QueueElement {
	T data;
	shared_ptr<QueueElement> next;
public:
	QueueElement(T adata) : data(adata) {}
		
	
	friend class Queue<T>;
};


template <typename T>
class Queue {
	shared_ptr<QueueElement<T>> front;
	shared_ptr<QueueElement<T>> back;
	int size = 0;
public:
	int get_size() const { return size; };
	bool empty() const {
		return front ? false : true;
	}
		
	void push(const T& data);
	const T& get_front() const { return front->data; };
	const T& get_back() const { return back->data; };
	void pop();
	void swap(Queue& queue2);

};



template<typename T>
void Queue<T>::push(const T& data) {
	shared_ptr<QueueElement<T>> element = make_shared<QueueElement<T>>(data);
	
	if (!back) {
		front = element;
	}
	else {
		back->next = element;
	}
	back = element;
	size++;
}

template<typename T>
void Queue<T>::pop() {
	if (front == back) {
		back.reset();
	}

	if (!empty()) {
		front = front->next;
		size--;
	}
	
}

template<typename T>
void Queue<T>::swap(Queue& queue2) {

	Queue copy = queue2;

	queue2.front = front;
	queue2.back = back;
	queue2.size = size;

	front = copy.front;
	back = copy.back;
	size = copy.size;

	
}
