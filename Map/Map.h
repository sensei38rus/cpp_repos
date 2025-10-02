#ifndef MAP_H
#define MAP_H
#include <memory>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T, typename S>
class Map;


template <typename T, typename S>
class MapElement {
	shared_ptr<MapElement<T, S>> next;
public:
	T key;
	S value{};
	MapElement(const T& akey) : key(akey){}
	friend Map<T, S>;




	template <typename U, typename D>
	friend ostream& operator<<(ostream& out, const Map<U, D>& map);
};

template <typename T, typename S>
class Map {
	shared_ptr<MapElement<T,S>> first;
	int size = 0;
public:
	S& operator[](const T& key);
	bool empty() const { return !first; }
	bool count(const T& key) const;
	void erase(const T& key);
	int get_size() const { return size; }
	template <typename U, typename D>
	friend ostream& operator<<(ostream& out, const Map<U, D>& map);
};

template <typename T, typename S>
S& Map<T,S>::operator[](const T& key) {
	auto new_element = make_shared<MapElement<T, S>>(key);
	if (empty()) {
		first = new_element;
		size++;
		return first->value;
	}

	
	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element;
	};

	int left_ind = 0;
	auto left = first;

	int right_ind = size - 1;
	auto right = iter(right_ind);

	if (key < left->key) {
		new_element->next = first;
		first = new_element;
		size++;
		return first->value;
	}
	if (key > right->key) {
		right->next = new_element;
		size++;
		return new_element->value;
	}

	if (key == left->key)
		return left->value;
	if (key == right->key)
		return right->value;

	while (left->next != right) {
		int middle_ind = (left_ind + right_ind) / 2;
		auto middle = iter(middle_ind);

		if (key == middle->key)
			return middle->value;
		if (key > middle->key) {
			left = middle;
			left_ind = middle_ind;
			continue;
		}
		if (key < middle->key) {
			right = middle;
			right_ind = middle_ind;
		}
	}
	new_element->next = right;
	left->next = new_element;
	size++;
	return new_element->value;
	
	
}

template <typename T, typename S>
ostream& operator<<(ostream& out, const Map<T, S>& map) {
	auto start = map.first;
	while (start) {
		out << "[" << start->key << "]" << "=" << start->value << "\n";
		start = start->next;
	}
	return out;
}


template <typename T, typename S>
bool Map<T, S>::count(const T& key) const{
	if (empty())
		return 0;

	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element;
		};
	int left_ind = 0;
	auto left = first;

	int right_ind = size - 1;
	auto right = iter(right_ind);

	
	if (key == right->key || key == left->key)
		return true;
	
	if (key < left->key || key > right->key)
		return false;
	while (left->next != right) {
		int middle_ind = (left_ind + right_ind) / 2;
		auto middle = iter(middle_ind);

		if (key == middle->key)
			return true;
		if (key > middle->key) {
			left = middle;
			left_ind = middle_ind;
			continue;
		}
		if (key < middle->key) {
			right = middle;
			right_ind = middle_ind;
		}
	}
	return false;

}

template <typename T, typename S>
void Map<T, S>::erase(const T& key) {
	if (!count(key))
		throw invalid_argument("Element does not exist");

	auto iter = [this](int index) {
		auto element = first;
		for (int i = 0; i < index; i++) {
			element = element->next;
		}
		return element;
	};
	int left_ind = 0;
	auto left = first;

	int right_ind = size - 1;
	auto right = iter(right_ind);

	if (key == left->key) {
		first = first->next;
		size--;
		return;
	}
	if (key == right->key) {
		auto elem = iter(right_ind - 1);
		elem->next = nullptr;
		size--;
		return;
	}

	while (left->next != right) {
		int middle_ind = (left_ind + right_ind) / 2;
		auto middle = iter(middle_ind);

		if (key == middle->key) {
			auto elem = iter(middle_ind - 1);
			elem->next = middle->next;
			size--;
			return;
		}
		if (key > middle->key) {
			left = middle;
			left_ind = middle_ind;
		}
		if (key < middle->key) {
			right = middle;
			right_ind = middle_ind;
		}
	}


}

#endif 