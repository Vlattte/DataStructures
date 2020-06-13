#include "Queue.h"
#include "ListQueue.h"
#include "VectorQueue.h"
#include "DoubleListQueue.h"
#include "QueueImplementation.h"

#include <stdexcept>
#include <cstdlib>

Queue::Queue(QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue();
		break;
	}
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue();	
		break;
	}
	case QueueContainer::DoublyLinkedList: {
		_pimpl = new DoubleListQueue();
		break;
	}
	default:
		throw std::runtime_error("unknown type of container");
	}
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue();
		break;
	}
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue();
		break;
	}
	case QueueContainer::DoublyLinkedList: {
		_pimpl = new DoubleListQueue();
		break;
	}
	default:
		throw std::runtime_error("unknown type of container");
	}

	for (size_t i = 0; i < arraySize; i++)
	{
		_pimpl->enqueue(valueArray[i]);
	}
}

Queue::Queue(const Queue& copyQueue)
	:_containerType(copyQueue._containerType)
{
	switch (_containerType)
	{
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue(*(dynamic_cast<VectorQueue*>(copyQueue._pimpl)));
		break;
	}
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue(*dynamic_cast<ListQueue*>(copyQueue._pimpl));
		break;
	}
	case QueueContainer::DoublyLinkedList: {
		_pimpl = new DoubleListQueue(*(dynamic_cast<DoubleListQueue*>(copyQueue._pimpl)));
		break;
	}
	default:
		throw std::runtime_error("unknown type of container");
	}
}

Queue& Queue::operator=(const Queue& copyQueue)
{
	if (this == &copyQueue)
	{
		return *this;
	}
	
	delete _pimpl;
	_containerType = copyQueue._containerType;

	switch (_containerType)
	{
	case QueueContainer::Vector: {
		_pimpl = new VectorQueue(*(dynamic_cast<VectorQueue*>(copyQueue._pimpl)));
		break;
	}
	case QueueContainer::SinglyLinkedList: {
		_pimpl = new ListQueue(*dynamic_cast<ListQueue*>(copyQueue._pimpl));
		break;
	}
	case QueueContainer::DoublyLinkedList: {
		_pimpl = new DoubleListQueue(*(dynamic_cast<DoubleListQueue*>(copyQueue._pimpl)));
		break;
	}
	default:
		throw std::runtime_error("unknown type of container");
	}
	return *this;
}

Queue::~Queue()
{
	delete _pimpl;		// композиция!
}

void Queue::enqueue(const ValueType& value)
{
	_pimpl->enqueue(value);
}

void Queue::dequeue()
{
	_pimpl->dequeue();
}

const ValueType& Queue::front() const
{
	return _pimpl->front();
}

bool Queue::isEmpty() const
{
	return _pimpl->isEmpty();
}

size_t Queue::size() const
{
	return _pimpl->size();
}

