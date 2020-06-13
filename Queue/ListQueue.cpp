#include "ListQueue.h"
#include <cstdlib>

ListQueue::ListQueue()
{ }

ListQueue::ListQueue(ListQueue& list)
	:LinkedList(list)
{ }

void ListQueue::enqueue(const ValueType& value)
{
	pushBack(value);
}

void ListQueue::dequeue()
{
	if (ListQueue::size() == 0)
		throw std::out_of_range("Queue is empty");
	removeFront();
}

const ValueType& ListQueue::front() const
{
	return getNode(0)->value; 
}

bool ListQueue::isEmpty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

size_t ListQueue::size() const
{
	return LinkedList::size();
}





