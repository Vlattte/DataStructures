#pragma once
#include <cstdlib>

#include "QueueImplementation.h"
#include "MyVector.h"

// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorQueue : public QueueImplementation, public MyVector
{
public:
	VectorQueue() {};

	VectorQueue(VectorQueue& vec)
		:MyVector(vec) { }

	void enqueue(const ValueType& value)
	{
		pushBack(value);
	}

	void dequeue()
	{
		if (isEmpty() == true)
			throw std::out_of_range("Queue is empty");

		_currentHeadIndex++;

		if (float(size() / capacity()) < (float(1) / _coef * _coef))
		{
			size_t newSize = size() - _currentHeadIndex;
			MyVector buf(newSize, ResizeStrategy::Multiplicative, 2);
			
			for (size_t i = _currentHeadIndex, index = 0; i < size(); i++, index++)
			{
				buf[index] = this->operator[](i);   //перекидываем значения после _currentHeadIndex в буфер
			}
			_currentHeadIndex = 0;

			this->resize(newSize);
			for (size_t i = 0; i < size(); i++)
			{
				this->operator[](i) = buf[i];
			}
			buf.clear();
		}
	}

	const ValueType& front() const
	{
		return this->operator[](_currentHeadIndex); //отдаем последний элемент
	}

	bool isEmpty() const
	{
		if (size() == 0)
			return true;
		else 
			return false;
	}

	size_t size() const
	{
		return MyVector::size();
	}

	~VectorQueue() override {};

private:
	size_t _currentHeadIndex = 0;
	float _coef = 0.25;
};