#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

template < typename T, typename A = allocator<T> >
class Vector
{
	A alloc;
	T* data;
	int capacity;
	int position;

	void reserve(int);
public:

	class Iterator
	{

		T* elem;
	public:

		Iterator(T* = nullptr);
		Iterator(const Vector&);
		Iterator(const Iterator&);

		Iterator& operator=(const Iterator&);
		Iterator& operator=(const T*);

		Iterator& operator++();
		Iterator& operator--();

		void operator*() const;
		T& operator*();

		bool operator==(const Iterator&);
		bool operator==(const T*);

		bool operator!=(const T*);
		bool operator!=(const Iterator&) const;

		~Iterator();

	};

	explicit Vector(int = 10);
	Vector(const Vector&);
	Vector(Vector&&);
	Vector(initializer_list<T>);

	void push_back(const T&);

	int size() const;

	const T& operator[](size_t) const;
	T& operator[](size_t);

	Vector& operator=(const Vector&);
	Vector& operator=(initializer_list<T>);
	Vector& operator=(Vector&&);

	T* begin();
	T* end();

	T& at(size_t);
	const T& at(size_t) const;

	~Vector();
};

template<typename T, typename A>
Vector<T,A>::Iterator::Iterator(T* dat)
	: elem(dat)
{
}

template<typename T, typename A>
Vector<T,A>::Iterator::Iterator(const Vector<T,A>& t)
	: elem(t.begin())
{
}

template<typename T, typename A>
Vector<T,A>::Iterator::Iterator(const typename Vector<T,A>::Iterator& it)
	: elem(it.elem)
{
}

template<typename T, typename A>
typename Vector<T,A>::Iterator& Vector<T,A>::Iterator::operator=(const typename Vector<T,A>::Iterator& it)
{
	if (this != &it)
	{
		elem = it.elem;
	}

	return *this;
}

template<typename T, typename A>
typename Vector<T,A>::Iterator& Vector<T,A>::Iterator::operator=(const T* dat)
{
	if (this->elem != dat)
	{
		elem = dat;
	}

	return *this;
}

template<typename T, typename A>
typename Vector<T,A>::Iterator& Vector<T,A>::Iterator::operator++()
{
	++elem;

	return *this;
}

template<typename T, typename A>
typename Vector<T,A>::Iterator& Vector<T,A>::Iterator::operator--()
{
	--elem;

	return *this;
}

template<typename T, typename A>
void Vector<T,A>::Iterator::operator*() const
{
	return *elem;
}

template<typename T, typename A>
T& Vector<T,A>::Iterator::operator*()
{
	return *elem;
}

template<typename T, typename A>
bool Vector<T,A>::Iterator::operator==(const typename Vector<T,A>::Iterator& it)
{
	return (elem == it.elem);
}

template<typename T, typename A>
bool Vector<T,A>::Iterator::operator==(const T* el)
{
	return elem == el;
}

template<typename T, typename A>
bool Vector<T,A>::Iterator::operator!=(const T*el)
{
	return !(elem == el);
}

template<typename T, typename A>
bool Vector<T,A>::Iterator::operator!=(const typename Vector<T,A>::Iterator& it) const
{
	return !(elem == it.elem);
}

template<typename T, typename A>
Vector<T,A>::Iterator::~Iterator()
{
}

template<typename T, typename A>
void Vector<T,A>::reserve(int num)
{
	try
	{
		T* buf = alloc.allocate(num);

		for (size_t i = 0; i < position; ++i)
		{
			alloc.construct(&buf[i], data[i]);
		}

		for (size_t i = 0; i < position; ++i)
		{
			alloc.destroy(&data[i]);
		}

		alloc.deallocate(data, capacity);

		capacity = num;
		data = buf;
	}
	catch (exception& e)
	{
		cout << "Smth wrong: " << e.what() << endl;
	}
}

template<typename T, typename A>
Vector<T,A>::Vector(int size)
	: capacity(size),
	position(0)
{
	data = new T[capacity];
}

template<typename T, typename A>
Vector<T,A>::Vector(const Vector<T,A>& v)
	: capacity(v.capacity),
	position(v.position)
{
	if (v.position == 0)
	{
		data = nullptr;
	}
	else
	{
		data = new T[position];
		for (size_t i = 0; i < position; ++i)
		{
			data[i] = v.data[i];
		}
	}
}

template<typename T, typename A>
Vector<T,A>::Vector(Vector<T,A>&& v)
	: position(v.position),
	capacity(v.capacity),
	data(v.data)
{

	v.position = 0;
	v.capacity = 0;
	v.data = nullptr;

}

template<typename T, typename A>
Vector<T,A>::Vector(initializer_list<T> num)
{
	data = new T[num.size()];
	position = num.size();
	capacity = num.size() * 2;

	for (size_t i = 0; i < position; ++i)
	{
		data[i] = *(num.begin() + i);
	}
}

template<typename T, typename A>
void Vector<T,A>::push_back(const T& el)
{
	if (position == capacity)
	{
		reserve(2 * capacity);
	}

	data[position++] = el;
}

template<typename T, typename A>
const T& Vector<T,A>::operator[](size_t index) const
{
	if (index < position)
	{
		return data[index];
	}
}

template<typename T, typename A>
int Vector<T,A>::size() const
{
	return position;
}

template<typename T, typename A>
T& Vector<T,A>::operator[](size_t index)
{
	if (index < position)
	{
		return data[index];
	}
}

template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(const Vector<T,A>& v)
{
	T* buffer = new T[v.position];
	position = v.position;
	capacity = v.capacity;

	delete[] data;
	data = buffer;

	return *this;
}

template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(initializer_list<T> num)
{
	delete[] data;
	data = new T[num.size()];
	position = num.size();
	capacity = num.size() * 2;

	for (size_t i = 0; i < position; ++i)
	{
		data[i] = *(num.begin() + i);
	}

	return *this;
}

template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(Vector<T,A>&& v)
{
	delete[] data;
	position = v.position;
	capacity = v.capacity;
	data = v.data;

	v.position = 0;
	v.capacity = 0;
	v.data = nullptr;

	return *this;
}

template<typename T, typename A>
T* Vector<T,A>::begin()
{
	return data;
}

template<typename T, typename A>
T* Vector<T,A>::end()
{
	return data + position;
}

template<typename T, typename A>
T& Vector<T,A>::at(size_t index)
{
	if (index < position)
	{
		return data[index];
	}
	else
	{
		throw runtime_error("attempt to access a non-existing vector element");
	}
}

template<typename T, typename A>
const T& Vector<T,A>::at(size_t index) const
{
	if (index < position)
	{
		return data[index];
	}
	else
	{
		throw runtime_error("attempt to access a non-existing vector element");
	}
}

template<typename T, typename A>
Vector<T,A>::~Vector()
{
	delete[] data;
}
