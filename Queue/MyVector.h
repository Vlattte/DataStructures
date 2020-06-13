#pragma once
#include <cstdlib>

enum class ResizeStrategy
{
	Additive,
	Multiplicative
};

enum class SortedStrategy
{
	FromLittleToBig,
	FromBigToLittle
};

//��� �������� � �������
//����� ����� ������� �� ���������
using ValueType = double;

class MyVector
{
public:

	class Iterator
	{
	public:
		Iterator(ValueType* ptr) 
			: pointer(ptr)
		{ }

		Iterator operator+ (int n)
		{
			return Iterator(pointer + n);		//operator +
		}

		Iterator operator- (int n)
		{
			return Iterator(pointer - n);		//operator -
		}

		Iterator operator++ ()
		{
			return pointer++;					//operator ++
		}

		Iterator operator-- ()
		{
			return pointer--;					//operator --
		}

		Iterator operator++ (int)
		{
			return pointer++;					//operator ++ (int)
		}

		Iterator operator-- (int)
		{
			return pointer--;					//operator -- (int)
		}

		bool operator!= (const Iterator& it)
		{
			return pointer != it.pointer;		//operator !=
		}

		bool operator== (const Iterator& it)
		{
			return pointer == it.pointer;		//operator ==
		}


		ValueType& operator*() const
		{
			return *pointer;					//operator *
		}
	private:
		ValueType* pointer;
	};


	MyVector(size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
	MyVector(size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);

	MyVector(const MyVector& copy);
	MyVector& operator=(const MyVector& copy);

	~MyVector();

	size_t capacity() const;
	size_t size() const;
	float loadFactor();

	//������ � ��������,
	//������ �������� �� �(1)
	ValueType& operator[](const size_t i) const;

	//�������� � �����,
	//������ �������� �� amort(O(1))
	void pushBack(const ValueType& value);

	//��������,
	//������ �������� �� �(n)
	void insert(const size_t i, const ValueType& value);	//������ ��� ������ ��������
	void insert(const size_t i, const MyVector& value);		//������ ��� �������

	//������� � �����,
	//������ �������� �� amort(O(1))
	void popBack();

	//�������,
	//������� �������� �� amort(O(1))
	void erase(const size_t i);
	void erase(const size_t i, const size_t len);	//������� len ��������� ������� � i

	//����� �������,
	//������ �������� �� O(n)
	//���� isBegin == true, ����� ������ ������� ��������, ������� value, ����� ����������
	//���� �������� �������� ���, ������� -1
	long long int find(const ValueType& value, bool isBegin = true) const;

	//��������������� ������ (������������� ������ capacity)
	void reserve(const size_t capacity);

	//�������� ������
	//���� ����� ������ ������ ��������, �� ����� �������� ���������� ���������� ����������
	//���� ������ - �������� capacity
	void resize(const size_t, const ValueType = 0.0);

	//������� �������, ��� ���������
	void clear();

	Iterator begin()
	{
		return Iterator(_data);
	}

	Iterator end()
	{
		return Iterator(_data + _size);
	}

	const ValueType* cbegin()
	{
		return _data;
	}

	const ValueType* cend()
	{
		return _data + _size;
	}

	MyVector sortedSquares(const MyVector& vec, SortedStrategy strategy);
private:
	ValueType* _data;
	size_t _size = 0;
	size_t _capacity = 0;
	float _coef = 1.5f;
	ResizeStrategy _resizeStrategy;
	size_t regulator = 0;
};

