#pragma once
#include <memory>



template <typename T>
class Unique_Ptr {
	T* raw_ptr{};
public:
	~Unique_Ptr() {
		delete raw_ptr;
	}
	
	Unique_Ptr(T* ptr) : raw_ptr(ptr) {}
	Unique_Ptr(Unique_Ptr&& moved) {
		raw_ptr = moved.raw_ptr;
		moved.raw_ptr = nullptr;
	}
	Unique_Ptr() = default;
	T* get() { return raw_ptr; }

	operator bool() const {
		return raw_ptr;
	}
	Unique_Ptr& operator=(const Unique_Ptr& second) = delete;
	Unique_Ptr& operator=(Unique_Ptr&& moved) noexcept {
		raw_ptr = moved.raw_ptr;
		moved.raw_ptr = nullptr;
		return *this;
	}
	
	T* release() {
		auto temp = raw_ptr;
		raw_ptr = nullptr;
		return temp;
	}
	void reset(T* new_ptr = nullptr) {
		raw_ptr = new_ptr;
	}

	T* operator->() {
		return raw_ptr;
	}
	T& operator*() {
		return *raw_ptr;
	}
	template <typename T, typename... Args>
	friend Unique_Ptr<T> make_unique(Args&&... data);

	
};

template <typename T, typename... Args>
Unique_Ptr<T> make_unique(Args&&... args) {
	return Unique_Ptr<T>(new T(std::forward<Args>(args)...));
}

