#pragma once
#include <memory>
#include <stdexcept>
using namespace std;

template <typename T>
class Set;

template <typename T>
class SetElement {
	T data;
	shared_ptr<SetElement> next;
public:
	SetElement(const T& adata) : data(adata){}
	friend class Set<T>;
	template <typename U>
	friend ostream& operator<<(ostream& out, const Set<U>& set);
};

template <typename T>
class Set {
	shared_ptr<SetElement<T>> first;
	int size = 0;
public:
	bool empty() const { return !first; }
	int get_size() const { return size; }
	bool insert(const T& data);
	bool count(const T& data) const;
	void erase(const T& data);
	template <typename U>
	friend ostream& operator<<(ostream& out, const Set<U>& set);
	
};


template <typename T>
bool Set<T>::insert(const T& data) {
	if (empty()) {
		first = make_shared<SetElement<T>>(data);
		size++;
		return true;
	}
	
	shared_ptr<SetElement<T>> new_element = make_shared<SetElement<T>>(data);

	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
			}
		return element;
		};


	shared_ptr<SetElement<T>> left = first;
	shared_ptr<SetElement<T>> right = iter(size - 1);

	if (data < left->data) {
		new_element->next = first;
		first = new_element;
		size++;
		return true;
	}
	if (data > right->data) {
		right->next = new_element;
		size++;
		return true;
	}
	int ind_left = 0;
	int ind_right = size - 1;

	if (data == left->data || data == right->data) {
		return false;
	}
	while (left->next != right) {
			

		int ind_middle = (ind_left + ind_right) / 2;
		shared_ptr<SetElement<T>> middle = iter(ind_middle);

		if (data == left->data || data == right->data || data == middle->data) {
			return false;
		}

		if (data > middle->data) {
			left = middle;
			ind_left = ind_middle;

		}
		if (data < middle->data) {
			right = middle;
			ind_right = ind_middle;
		}
	}
	new_element->next = right;
	left->next = new_element;
	size++;
	return true;
}



template<typename T>
ostream& operator<<(ostream& out, const Set<T>& set) {
	auto begin = set.first;
	while (begin) {
		out << begin->data << " ";
		begin = begin->next;
	}
	return out;
}

template<typename T>
bool Set<T>::count(const T& data) const {
	if (empty())
		return false;

	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element;
		};
	auto left = first;
	auto right = iter(size - 1);
	if (data == left->data || data == right->data)
		return true;
	int ind_left = 0;
	int ind_right = size - 1;
	while (left->next != right) {
		int ind_middle = (ind_left + ind_right) / 2;
		auto middle = iter(ind_middle);

		if (data == left->data || data == right->data || data == middle->data) {
			return true;
		}
		if (data > middle->data) {
			left = middle;
			ind_left = ind_middle;

		}
		if (data < middle->data) {
			right = middle;
			ind_right = ind_middle;
		}
	}
	return false;
	
}

template<typename T>
void Set<T>::erase(const T& data) {
	if (!count(data))
		throw invalid_argument("Element does not exist");

	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element;
	};
	int ind_left = 0;
	int ind_right = size - 1;

	auto left = first;
	auto right = iter(ind_right);

	int ind_elem{};
	shared_ptr<SetElement<T>> elem;

	while (!elem) {

		int ind_middle = (ind_left + ind_right) / 2;
		auto middle = iter(ind_middle);

		if (left->data == data) {
			ind_elem = ind_left;
			elem = left;
		}
		if (right->data == data) {
			ind_elem = ind_right;
			elem = right;
		}
		if (middle->data == data) {
			ind_elem = ind_middle;
			elem = middle;
		}
		
		if (data > middle->data) {
			left = middle;
			ind_left = ind_middle;
		}
		if (data < middle->data) {
			right = middle;
			ind_right = ind_middle;
		}
	}
	if (ind_elem > 0) {
		auto previous = iter(ind_elem - 1);
		previous->next = elem->next;
	}
	else {
		first = elem->next;
	}
	size--;
		

		
}
