#pragma once
#include <vector>
#include <span>
#include <type_traits>
template <typename T>
int binary_search(std::vector<T> sorted_array, const T& value) {
	int left = 0;
	int right = sorted_array.size() - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		T guess = sorted_array[middle];
		if (value == guess)
			return middle;
		if (value > guess) {
			left = middle + 1;
		}
		if (value < guess) {
			right = middle - 1;
		}

	}
	return -1;
}


template <typename T, typename S>
concept is_ptr = requires(T first, S second) {
	*first; *second;
};
template <typename T>
concept is_cont = requires(T cont) {
	cont.begin();
};


template <typename T> requires is_ptr<T,T>
T Min_Element(T begin, T end) {
	T res = begin;
	while (begin != end) {
		if (*begin < *res)
			res = begin;
		++begin;
	}
	return res;
}


template <typename T>	requires is_ptr<T, T>
T Max_Element(T begin, T end)  {
	T res = begin;
	while (begin != end) {
		if (*begin > *res)
			res = begin;
		++begin;
	}
	return res;
}

template <typename T>
void quick_sort(std::vector<T>& vec) {
	if (vec.empty())
		return;
	auto cdm = Max_Element(vec.begin(), vec.end());
	auto max = *cdm;
	vec.erase(cdm);
	quick_sort(vec);
	vec.push_back(max);
	

}

template<typename T> requires is_ptr<T, T>
std::pair<T, T> MinMax(T begin, T end)  {
	std::pair<T, T> p(Min_Element(begin, end), Max_Element(begin, end));
	return p;
}

template <typename T, typename S> requires is_ptr<T, T>
T Find(T begin, T end, S value) {
	while (begin != end) {
		if (*begin == value)
			return begin;
		++begin;
	}
	return end;
}


template<typename T, typename S> requires is_ptr<T,S>
T Find_if(T begin, T end, S cond)  {
	while (begin != end) {
		if (cond(*begin))
			return begin;
		++begin;
	}
	return end;
}

template<typename T, typename S> requires is_ptr<T, S>
T Find_if_not(T begin, T end, S cond)  {
	while (begin != end) {
		if (!cond(*begin))
			return begin;
		++begin;
	}
	return end;
}


template<typename T,typename S> requires is_ptr<T,S>
S Copy(T source_start, T source_end, S dest_start)   {
	while (source_start != source_end) {
		*dest_start = *source_start;
		++source_start;
		++dest_start;
	}
	return dest_start;
}

template<typename T, typename S, typename C> requires is_ptr<T, S>
T Copy_if(T source_start, T source_end, S dest_start, C condition) {
	while (source_start != source_end) {
		if (condition(*source_start)) {
			*dest_start = *source_start;
			++dest_start;
		}
		++source_start;
	}
	return dest_start;
}





template<typename T, typename S> requires is_ptr<T,T>
T Remove(T start, T end, const S& value)  {
	size_t cap = (end - start) + 1;
	S* temp = new S[cap];
	S* ptr = &temp[0];
	T beg = start;
	int size = 0;
	while (start != end) {
		if (*start != value) {
			*ptr = *start;
			++ptr;
			++size;
		}
		++start;
	}
	Copy(&temp[0], &temp[size], beg);
	delete[] temp;
	return beg + size;
}

template<typename T, typename S> requires is_ptr<T, T>
T Remove_if(T start, T end, bool (*cond)(S)) {
	size_t cap = (end - start) + 1;
	S* temp = new S[cap];
	S* ptr = &temp[0];
	T beg = start;
	int size = 0;
	while (start != end) {
		if (!cond(*start)){
			*ptr = *start;
			++ptr;
			++size;
		}
		++start;
	}
	Copy(&temp[0], &temp[size], beg);
	delete[] temp;
	return beg + size;
}


template <typename T, typename S>	requires is_cont<T>
void Erase(T& cont, const S& value)  {
	auto iter = Remove(cont.begin(), cont.end(), value);
	cont.erase(iter, cont.end());
}
template <typename T, typename S>	requires is_cont<T>
void Erase_if(T& cont, S cond)	 {
	auto iter = Remove_if(cont.begin(), cont.end(), cond);
	cont.erase(iter, cont.end());
}
template <typename T> requires is_ptr<T, T>
void Sort(T start, T end) {
	for (auto i = start; i != end; ++i) {
		for (auto j = start; j != end - 1; ++j) {
			if (*j > *(j + 1)) {
				auto temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
			}
		}
	}
}

template <typename T, typename C> requires is_ptr<T, T>
void Sort(T start, T end, C compare) {
	for (auto i = start; i != end; ++i) {
		for (auto j = start; j != end - 1; ++j) {
			if (!compare(*j, *(j+1))) {
				auto temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
			}
		}
	}
}


template <typename T>
void Sort_Cont(T& cont) requires is_cont<T> {
	Sort(cont.begin(), cont.end());
}
template <typename T, typename C> requires is_cont<T>
void Sort_Cont(T& cont, C compare) {
	Sort(cont.begin(), cont.end(), compare);
}
template <typename T, typename C, typename F>
void Sort_Cont(T& cont, C compare, F proj)	requires is_cont<T> {
	for (auto i = cont.begin(); i != cont.end(); ++i) {
		for (auto j = cont.begin(); j != cont.end() - 1; ++j) {
			if (!compare(proj(*j),proj(*(j+1)))) {
				auto temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
			}
		}
	}
}

template <typename Cont, typename E>
Cont filter(const Cont& cont, bool (*filter)(E)) requires is_cont<Cont> {
	auto start = cont.begin();
	E* arr = new E[cont.size()];
	auto new_start = &arr[0];
	int real_size = 0;
	while (start != cont.end()) {
		if (filter(*start)) {
			*new_start = *start;
			++new_start;
			++real_size;
		}
		++start;
	}
	Cont new_cont(real_size);
	Copy(&arr[0], &arr[real_size], new_cont.begin());
	delete[] arr;
	return new_cont;
}



template <typename T, typename C, typename F>
class Transform_View {
	T* data{};
	int size = 0;
public:
	~Transform_View() { delete[] data; }
	Transform_View(const C& cont, T (*transformer)(F)) {
		size = cont.size();
		data = new T[size];
		T* ptr = &data[0];
		auto start = cont.begin();
		while (start != cont.end()) {
			*ptr = transformer(*start);
			++ptr;
			++start;
		}
	}
	const T* begin() const {
		return &data[0];
	}
	const T* end() const {
		return &data[size];
	}
};
template <typename T>
class Drop_View {
	T* data{};
	int size = 0;
public:
	~Drop_View() { delete[] data; }
	Drop_View(const std::span<T>& cont, int n) {
		data = new T[cont.size() - n];
		size = cont.size() - n;
		auto start = cont.begin();
		for (int i = 0; i < n; i++)
			++start;
		Copy(start, cont.end(), &data[0]);
	}
	const T* begin() { return &data[0]; }
	const T* end() { return &data[size]; }
};

template <typename T, typename Cont>
class Drop_View_While {
	T* data{};
	int size = 0;
public:
	~Drop_View_While() { delete[] data; }
	Drop_View_While(const Cont& cont, bool (*cond)(T)) {
		auto start = cont.begin();
		int r_size = cont.size();
		while (cond(*start)) {
			++start;
			--r_size;
		}
		size = r_size;
		data = new T[size];

		Copy(start, cont.end(), &data[0]);
		
	}
	const T* begin() { return &data[0]; }
	const T* end() { return &data[size]; }
};
template<typename T, typename Cont>
class Take_View {
	T* data{};
	int size = 0;
public:
	~Take_View() {delete[] data;}

	Take_View(const Cont& cont, int num, T type) {
		auto start = cont.begin();
		for (int i = 0; i < num; ++i, ++start) {}
		data = new T[num];
		size = num;
		Copy(cont.begin(), start, &data[0]);
	}
	const T* begin() { return &data[0]; }
	const T* end() { return &data[size]; }

};
template <typename T, typename Cont>
class Take_While_View {
	T* data{};
	int size = 0;
public:
	~Take_While_View() { delete[] data; }	
	Take_While_View(const Cont& cont, bool (*cond)(T)) {
		auto start = cont.begin();
		while (cond(*start)) {
			++start;
			++size;
		}
		data = new T[size];
		Copy(cont.begin(), start, &data[0]);
	}
	const T* begin() { return &data[0]; }
	const T* end() { return &data[size]; }
};