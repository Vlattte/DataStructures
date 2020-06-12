#include "MyVector.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <exception>
#include <cassert>


MyVector::MyVector(size_t size, ResizeStrategy resizeStrategy, float coef)
	:_size(size), _resizeStrategy(resizeStrategy), _coef(coef), _capacity(0)
{
	if (_size == 0)
	{
		_capacity = 1;
		_data = new ValueType[_capacity];
	}
	else if (_resizeStrategy == ResizeStrategy::Additive)
	{
		_capacity = ceil(_size + _coef);
		_data = new ValueType[_capacity];
	}
	else if (_resizeStrategy == ResizeStrategy::Multiplicative)
	{
		_capacity = ceil(_size * _coef);
		_data = new ValueType[_capacity];
	}

	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = ValueType();
	}

	if (_size < 0)
		throw std::invalid_argument("Invalid size");
	if (coef < 0)
		throw std::invalid_argument("Invalid coef");
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy, float coef)
	:_size(size), _resizeStrategy(resizeStrategy), _coef(coef), _capacity(0)
{
	if (_size == 0)
	{
		_capacity = 1;
		_data = new ValueType[_capacity];
	}
	else if (_resizeStrategy == ResizeStrategy::Additive)
	{
		_capacity = ceil(_size + _coef);
		_data = new ValueType[_capacity];
	}
	else if (_resizeStrategy == ResizeStrategy::Multiplicative)
	{
		_capacity = ceil(_size * _coef);
		_data = new ValueType[_capacity];
	}

	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = value;
	}

	if (_size < 0)
		throw std::invalid_argument("Invalid size");
	if (coef < 0)
		throw std::invalid_argument("Invalid coef");
}

MyVector::MyVector(const MyVector & copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
	_resizeStrategy = copy._resizeStrategy;
	_coef = copy._coef;
	regulator = copy.regulator;
		
	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = copy._data[i];
	}

}

MyVector& MyVector::operator=(const MyVector & copy)
{
	if (&copy == this)
	{
		return *this;
	}

	_size = copy._size;
	_capacity = copy._capacity;
	_resizeStrategy = copy._resizeStrategy;
	_coef = copy._coef;
	regulator = copy.regulator;

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = copy._data[i];
	}

	return *this;
}

MyVector::~MyVector()
{
	if (_data)
	{
		delete[] _data;
		_data = nullptr;
	}
	_size = 0;
	_capacity = 0;
}

size_t MyVector::capacity() const
{
	return _capacity;
}

size_t MyVector::size() const
{
	return _size;
}

float MyVector::loadFactor()
{
	if (_size == 0)
	{
		return 1;
	}

	else
	{
		return float(size()) / float(capacity());
	}
}

ValueType& MyVector::operator[](const size_t i) const
{
	if (i < 0 || i >= _size)
	{
		throw std::out_of_range("Index out of range");
	}

	return _data[i];
}

void MyVector::pushBack(const ValueType & value)
{
	if (_capacity > _size)
	{
		_data[_size] = value;
		_size++;
	}
	else
	{
		resize(_size + 1);
		_data[_size] = value;
	}
}

void MyVector::popBack()
{
	regulator++;
	_size--;
	if (regulator == 20)
	{
		resize(_size);
	}
}

void MyVector::erase(const size_t i)
{
	//если удаляем последний
	if (i == _size - 1)	
	{
		popBack();
	}
	//если удаялем в середине
	else
	{
		for (size_t idx = i; idx < _size - 1; idx++)
		{
			_data[idx] = _data[idx + 1];
		}
		_size--;
	}
}

void MyVector::erase(const size_t i, const size_t len)
{
	size_t idx = i;
	if (idx + len < _size)
	{
		while (idx + len < _size)
		{
			_data[idx] = _data[idx + len];			//[0, 1, 2, 3, 4, 5, 6, 7] len = 2 idx = 3
			++idx;
		}
		resize(_size - len);
	}
	else
	{
		resize(idx);
	}
	if (_capacity == 0)
	{
		reserve(1);
	}
	
}

long long int MyVector::find(const ValueType & value, bool isBegin) const
{
	int flag = -1;

	if (isBegin == true)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] == value)
			{
				flag = 1;
				return i;
			}
		}
	}
	else if (isBegin == false)
	{
		for (int i = _size - 1 ; i > -1; i--)
		{
			if (_data[i] == value)
			{
				flag = 1;
				return i;
			}
		}
	}

	if (flag == -1)
	{
		std::cout << "invalid index";
		return -1;
	}
}

void MyVector::insert(const size_t i, const ValueType & value)
{
	if (i < 0)
	{
		assert(i < 0); //ошибка: размер меньше нуля
	}
	else if (i > this->_size)
	{
		assert(i > this->_size); //ошибка: вышли за границу вектора
	}

	size_t oldSize = _size;
	ValueType giver;
	
	if (i == 0) //если вставляем в начало
	{
		ValueType* buff = new ValueType[_size + 1];
		buff[0] = value;

		//переносим старые значения в буфер
		for (size_t idx = 0; idx < _size; idx++)
		{
			giver = _data[idx];
			buff[idx + 1] = giver;
		}

		//увеличиваем _data если не хвататет места
		if (_capacity <= _size)
			resize(_size + 1);
		else
			_size++;

		std::swap(_data, buff);

		//чистим буфер
		delete[] buff;
		buff = nullptr;
	}

	//если вставляем в конец, то pushBack
	if (oldSize == i && oldSize != 0)
	{
		pushBack(value);
	}

	//если вставляем в середину
	if (i > 0 && i < oldSize)
	{
		ValueType* buff = new ValueType[_size + 1];

		//переносим все элементы с начала до i в буфер
		for (size_t idx = 0; idx < i; idx++)
		{
			giver = _data[idx];
			buff[idx] = giver;
		}

		//переносим все элементы от i до конца в буфер
		for (size_t idx = i; idx < _size; idx++)
		{
			giver = _data[idx];
			buff[idx + 1] = giver;
		}

		buff[i] = value;   //вставляем новый элемент
		resize(_size + 1); //расширяем _data

		std::swap(_data, buff);

		delete[] buff;
		buff = nullptr;
	}

}

void MyVector::insert(const size_t i, const MyVector & value)
{
	if (_capacity < _size + value._size);
		resize(_size + value._size);

	size_t size = value._size;

	for (size_t idx = i, n = 0; n < size; idx++, n++)
	{
		_data[idx + size] = _data[idx];
		_data[idx] = value._data[n];
	}
}

void MyVector::reserve(const size_t capacity)
{
		ValueType* buff = new ValueType[capacity];		//буфер для старых значений
		ValueType giver;							    //переменная для передачи значений

		for (size_t i = 0; i < _size; ++i)
		{
			giver = _data[i];
			buff[i] = giver;						    //переносим старые значения
		}

		_data = nullptr;
		_data = buff;
		_capacity = capacity;
}

void MyVector::resize(const size_t size, const ValueType value)
{
	if (size > _size)
	{
		if (size > _capacity)
		{
			reserve(size);
		}
		
		for (size_t idx = _size; idx < size; idx++)
		{
			_data[idx] = value;
		}

		_size = size;
		if (loadFactor() >= 1)
		{
			if (_resizeStrategy == ResizeStrategy::Multiplicative)
			{
				reserve(ceil(_coef * _capacity));
			}
			else if (_resizeStrategy == ResizeStrategy::Additive)
			{
				reserve(ceil(_capacity + _coef));
			}
		}
	}
	else if (size < _size)
	{
		ValueType* buf = new ValueType[size];
		for (size_t idx = 0; idx < size; idx++)
		{
			buf[idx] = _data[idx];
		}

		std::swap(_data, buf);
		delete[] buf;
		_size = size;
		_capacity = _size;

		if (loadFactor() >= 1)
		{
			if (_resizeStrategy == ResizeStrategy::Multiplicative)
			{
				reserve(ceil(_coef * _capacity));
			}
			else if (_resizeStrategy == ResizeStrategy::Additive)
			{
				reserve(ceil(_capacity + _coef));
			}
		}
	}
	else
	{
		if (_resizeStrategy == ResizeStrategy::Multiplicative)
		{
			reserve(ceil(_coef * _capacity));
		}
		else if (_resizeStrategy == ResizeStrategy::Additive)
		{
			reserve(ceil(_capacity + _coef));
		}
	}

}

void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = ValueType();
	}
	_size = 0;
}

MyVector MyVector::sortedSquares(const MyVector& vec, SortedStrategy strategy)
{
	MyVector outVec = vec;
	MyVector buf = vec;

	for (size_t idx = 0; idx < vec._size; idx++)
	{
		buf[idx] = buf[idx] * buf[idx];
	}
	
	size_t right = _size - 1;
	size_t left = 0;

	while (left <= right)
	{
		if (buf[left] > buf[right])
		{
			if (strategy == SortedStrategy::FromLittleToBig)
			{
				outVec[right - left] = buf[left];
			}
			else if (strategy == SortedStrategy::FromBigToLittle)
			{
				size_t pos = buf._size - (right + 1) + left;
				outVec[pos] = buf[left];
			}
			left++;
		}
		else if (buf[left] <= buf[right])
		{
			if (strategy == SortedStrategy::FromLittleToBig)
			{
				outVec[right - left] = buf[right];
			}
			else if (strategy == SortedStrategy::FromBigToLittle)
			{
				size_t pos = buf._size - (right + 1) + left;
				outVec[pos] = buf[right];
			}
			right--;
		}
	}

	return outVec;
}


