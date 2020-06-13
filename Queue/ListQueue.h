#pragma once

#include "QueueImplementation.h"
#include "LinkedList.h"
#include "QueueImplementation.h"

#include <cstdlib>

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListQueue : public QueueImplementation, public LinkedList
{
public:
	ListQueue();

	ListQueue(ListQueue& list);

	void enqueue(const ValueType& value);
	
	void dequeue();

	const ValueType& front() const;

	bool isEmpty() const;

	size_t size() const;

	~ListQueue() override {};
};

