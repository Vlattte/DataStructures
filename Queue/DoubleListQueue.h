#include "QueueImplementation.h"
#include "DoubleLinkedList.h"

#include <cstdlib>
#include <stdexcept>

// ������� � �������������� ����� ����������� ������ � �������������� ������������
// ���� �� ������ �� ��� ����������, �� ���� �� ������������ ������ �� ����������
// ������������� ������������ ����� �������� �� ����������
class DoubleListQueue : public QueueImplementation, public DoubleLinkedList
{
public:
	DoubleListQueue()
	{ }

	DoubleListQueue(DoubleListQueue& list)
		:DoubleLinkedList(list)
	{ }

	void enqueue(const ValueType& value)
	{
		pushBack(value);
	}

	void dequeue()
	{
		if (isEmpty() == true)
			throw std::out_of_range("Queue is empty");
		removeFront();
	}

	const ValueType& front() const
	{
		return getNode(0)->value;
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
		return DoubleLinkedList::size();
	}

	~DoubleListQueue() override {};
};

