#include<iostream>
#include<memory>

template<typename T>
class shared_ptr
{
private:
	T* ptr;
	int* ref_count;

public:
	//default
	explicit shared_ptr(T*ptr = nullptr) :ptr(ptr), ref_count(new int(1)) {}
	//ctor copy
	shared_ptr(const shared_ptr& other) :ptr(other.ptr), ref_count(other.ref_count) {
		++(*ref_count);
	};
	//ctor move
	shared_ptr(shared_ptr&& other) noexcept :ptr(other.ptr), ref_count(other.ref_count) {
		other.ptr = nullptr;
		other.ref_count = nullptr;
	};
	//ctor for mass
	shared_ptr(T*arraPtr,size_t size):ptr(arraPtr),ref_count(new int (1+size)){
		--(*ref_count);
	}

	 T& operator*() const {
		return *ptr;
	}

	 T* operator->(){ 
		return ptr;
	}

	shared_ptr&& operator=(const shared_ptr&& other) {
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
