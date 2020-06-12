#pragma once

#include "StackImplementation.h"
#include "MyVector.h"

#include <cstdlib>

// ������� � �������������� ����� ����������� ������� � �������������� ������������
// ���� �� ������ �� ��� ����������, �� ���� �� ������������ ������ �� ����������
// ������������� ������������ ����� �������� �� ����������
class VectorStack : public StackImplementation, public MyVector
{
public:
	VectorStack() {};

	VectorStack(VectorStack& vec)
		:MyVector(vec) { }

	void push(const ValueType& value);
	void pop();
	const ValueType& top() const;
	bool isEmpty() const;
	size_t size() const;
	~VectorStack() override {};
};