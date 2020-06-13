#pragma once
#include <cstdlib>

using ValueType = double;

class QueueImplementation
{
public:
	//добавление в хвост
	virtual void enqueue(const ValueType& value) = 0;
	//удаление первого узла
	virtual void dequeue() = 0;
	//посмотреть элемент в хвосте
	virtual const ValueType& front() const = 0;
	//проверка на пустоту 
	virtual bool isEmpty() const = 0;
	//размер
	virtual size_t size() const = 0;
	//виртуальный деструктор
	virtual ~QueueImplementation() {};
};

