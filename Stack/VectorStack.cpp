#include "VectorStack.h"
#include <stdexcept>

#include <cstdlib>


void VectorStack::push(const ValueType& value)
{
	this->pushBack(value);
}

void VectorStack::pop()
{
	if (VectorStack::size() == 0)
		throw std::out_of_range("Stack is empty");
	this->popBack();
}

const ValueType& VectorStack::top() const
{
	return operator[](size() - 1); //отдаем последний элемент
}

bool VectorStack::isEmpty() const
{
	if (size() == 0)
		return true;
	else if (size() != 0)
		return false;
}

size_t VectorStack::size() const
{
	return MyVector::size();
}