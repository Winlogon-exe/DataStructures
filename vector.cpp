#include <iostream>

template<typename T>
class vector {
private:
	T* data;
	size_t size;
	size_t capacity;
public:
	// Default constructor
	vector(): data(nullptr), size(0), capacity(0) {}

	// Initializer list constructor
	vector(std::initializer_list<T> initList): data(nullptr), size(0), capacity(0)
	{
		reserve(initList.size());
		for (const T& val : initList) {
			push_back(val);
		}
	}

	// Copy constructor
	vector(const T& other) : data(nullptr), size(0), capacity(0)
	{
		*this = other;
	}

	~vector()
	{
		clear();
	}

	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

	const T* begin() const 
	{
		return data;
	}

	const T* end() const 
	{
		return data + size;
	}

	T& operator[](size_t index)
	{
		if (index >= size)
			throw std::out_of_range("Index out of range");

		return data[index];
	}

	// Copy assignment operator (using const reference since we don't modify 'other')
	vector& operator=(const vector& other)
	{
		if (this == &other)
			return *this;

		clear();

		size = other.size;
		capacity = other.capacity;
		data = new T[capacity];

		for (size_t i = 0; i < size; ++i)
		{
			data[i] = other.data[i];
		}

		return *this;
	}

	// Move assignment operator (not using const reference since we modify 'other')
	vector&& operator=(vector&& other) noexcept
	{
		if (this == &other) {
			return *this; 
		}

		clear();

		// Move resources from 'other' to the current vector
		data = other.data;
		size = other.size;
		capacity = other.capacity;

		// Reset 'other' so it does not own the resources after the move
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

		return *this;
	}

	void clear()
	{
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	void push_back(const T& val)
	{
		if (size == capacity)
		{
			reserve(capacity == 0 ? 1 : capacity * 2); 
		}
		data[size++] = val;
	}

	size_t getsize() const 
	{
		return size;
	}
	 
	bool empty() const 
	{
		return size == 0;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity <= capacity) {
			return;
		}
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < size; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}
};
