#include<iostream>
#include<memory>

template<typename T>
class shared_ptr
{
private:
	T* ptr;
	int* ref_count; // Reference count
public:
	// Default constructor
	explicit shared_ptr(T* pointer = nullptr) : ptr(pointer), ref_count(new int(1)) {}

	// Copy constructor
	shared_ptr(const shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
		++(*ref_count);
	}

	// Move constructor
	shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
		other.ptr = nullptr;
		other.ref_count = nullptr;
	}

	// Constructor for arrays
	shared_ptr(T* arrayPtr, size_t size) : ptr(arrayPtr), ref_count(new int(1 + size)) {
		--(*ref_count);
	}

	shared_ptr& operator=(const shared_ptr& other) {
		if (this != &other) {
			if (ptr && --(*ref_count) == 0) {
				delete ptr;
				delete ref_count;
			}
			ptr = other.ptr;
			ref_count = other.ref_count;
			++(*ref_count);
		}
		return *this;
	}

	T& operator*() {
		return *ptr;
	}

	T* operator->() {
		return ptr;
	}

	~shared_ptr() {
		if (ptr) {
			if (--(*ref_count) == 0) {
				if (std::is_array<T>::value)
					delete[] ptr;
				else
					delete ptr;

				delete ref_count;
			}
			else {
				ptr = nullptr;
				ref_count = nullptr;
			}
		}
	}
};
