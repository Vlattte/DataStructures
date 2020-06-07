#include "MyVector.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <exception>
#include <cassert>


MyVector::MyVector(size_t size, ResizeStrategy resizeStrategy, float coef)
	:_size(size), _resizeStrategy(resizeStrategy), _coef(coef), _capacity(0)
{
	if (_size > _capacity)
		resize(_size);
	else
		_capacity = 1;

	_data = new ValueType[_capacity];

	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0.0;
	}

	if (_size < 0)
		throw std::invalid_argument("Invalid size");
	if (coef < 0)
		throw std::invalid_argument("Invalid coef");
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy, float coef)
	:_size(size), _resizeStrategy(resizeStrategy), _coef(coef), _capacity(0), _defaultValue(value)
{
	if (_size > _capacity)
		resize(_size);
	else
		_capacity = 1;

	_data = new ValueType[_capacity];

	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = _defaultValue;
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

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = copy._data[i];
	}

}

MyVector& MyVector::operator=(const MyVector & copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
	_resizeStrategy = copy._resizeStrategy;
	_coef = copy._coef;

	_data = new ValueType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		_data[i] = copy._data[i];
	}

	return *this;
}

MyVector::~MyVector()
{
	delete[] _data;
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
	//���� ������� ���������
	if (i == _size - 1)	
	{
		popBack();
	}
	//���� ������� � ��������
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

	while (idx + len < _size)
	{
		_data[idx] = _data[idx + len];
		++idx;
	}

	resize(_size - len);
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
		assert(i < 0); //������: ������ ������ ����
	}
	else if (i > this->_size)
	{
		assert(i > this->_size); //������: ����� �� ������� �������
	}

	size_t oldSize = _size;
	ValueType giver;
	if (oldSize == 0)
	{
		reserve(1);
	}

	if (i == 0) //���� ��������� � ������
	{
		ValueType* buff = new ValueType[_size + 1];
		buff[0] = value;

		//��������� ������ �������� � �����
		for (size_t idx = 0; idx < _size; idx++)
		{
			giver = _data[idx];
			buff[idx + 1] = giver;
		}

		//����������� _data
		resize(_size + 1);

		//��������� ������ �������� � ����� ������� � ����������� _data
		for (size_t idx = 0; idx < _size; idx++)
		{
			giver = buff[idx];
			_data[idx] = giver;
		}

		//������ �����
		delete[] buff;
		buff = nullptr;
	}

	//���� ��������� � �����, �� pushBack
	if (oldSize == i && oldSize != 0)
	{
		pushBack(value);
	}

	//���� ��������� � ��������
	if (i > 0 && i < oldSize)
	{
		ValueType* buff = new ValueType[_size + 1];

		//��������� ��� �������� �� i �� ����� � �����
		for (size_t idx = i; idx < _size; idx++)
		{
			giver = _data[idx];
			buff[idx + 1] = giver;
		}

		//��������� ��� �������� � ������ �� i � �����
		for (size_t idx = 0; idx < i; idx++)
		{
			giver = _data[idx];
			buff[idx] = giver;
		}

		buff[i] = value;   //��������� ����� �������
		resize(_size + 1); //��������� _data

		//��������� �� ������ � _data
		for (size_t idx = 0; idx < _size; idx++)
		{
			giver = buff[idx];
			_data[idx] = giver;
		}

		delete[] buff;
		buff = nullptr;
	}

}

void MyVector::insert(const size_t i, const MyVector & value)
{
	resize(_size + value._size);
	for (size_t idx = _size; idx >= i + value._size; idx--) 
	{														
		_data[idx] = _data[idx - value._size];
	}

	for (size_t idx = i, n = 0; idx < i + value._size; idx++, n++)
	{
		_data[idx] = value._data[n];
	}
}

void MyVector::reserve(const size_t capacity)
{
		ValueType* buff = new ValueType[capacity];		//����� ��� ������ ��������
		ValueType giver;							    //���������� ��� �������� ��������

		for (size_t i = 0; i < _size; ++i)
		{
			giver = _data[i];
			buff[i] = giver;						    //��������� ������ ��������
		}

		delete[] _data;                                 //����������� ������ ������
		_data = nullptr;
		_data = buff;
		_capacity = capacity;
		/*		                        
		_data = new ValueType[capacity];                //�������� ����� ������ ����� �����

		for (size_t i = 0; i < _size; ++i)
		{
			giver = buff[i];
			_data[i] = giver;	                        //���������� ������ �������� �� ���� �����
		}
		*/
}

void MyVector::resize(const size_t size, const ValueType value)
{
	size_t oldSize = _size;
	_size = size;

	// ������� capacity �� ������� Multiplicative
	if (_resizeStrategy == ResizeStrategy::Multiplicative) 
	{
		while (_capacity < _size)
		{
			if (loadFactor() > 1)
				_capacity = ceil(_capacity * _coef);
			else if (loadFactor() < 1)
				_capacity = ceil(_capacity * loadFactor());
			else if (loadFactor() == 1)
				_capacity = _capacity;
		}
	}	
	// ������� capacity �� ������� Additive
	else if (_resizeStrategy == ResizeStrategy::Additive) 
	{
		while (_capacity < _size)
		{
			if (_capacity > _size)
				_capacity = _size;
			else if (_capacity < _size)
				while (_capacity >= _size)
				{
					_capacity = _capacity + 1;
				}
		}
	}
	if (oldSize != 0)
	{
		reserve(_capacity); // ����������� ������ ��� �������
	}
	else if (oldSize == 0)
	{
		_data = new ValueType[_capacity];
	}

	for (size_t i = oldSize; i < _capacity; ++i)
	{
		_data[i] = _defaultValue; // ��������� ����� ����� ���������� ����������
	}
}

void MyVector::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = _defaultValue;
	}
	_size = 0;
}

ValueType* MyVector::begin()
{
	return _data;
}

ValueType* MyVector::end()
{
	return _data + _size;
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


