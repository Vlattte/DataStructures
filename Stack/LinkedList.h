#pragma once

#include <cassert>
#include <iostream>
#include <cstdlib>

using ValueType = double;

class LinkedList
{
		//����� ���� ������
		//�� ����� ����, ����� ��������� ����� ������,
		//����� ����������� � ������������� ������, ������ �������
		//���� � ������ � ���� �, � ������ �����, �������� ������ LinkedList
		//(������ �� �����, ����� �� ����� � �.�.)
		struct Node
		{
			Node(const ValueType& value, Node* next = nullptr);
			~Node();

			void insertNext(const ValueType& value);
			void removeNext();

			ValueType value;
			Node* next;
		};

	public:
		//==========================================================//
		LinkedList(); //����������� �� ���������
		LinkedList(const LinkedList& copyList); //����������� �����������
		LinkedList& operator=(const LinkedList& copyList); 

		LinkedList(LinkedList&& moveList) noexcept; // ����������� � ����������� ��������� �������
		LinkedList& operator=(LinkedList&& movelist) noexcept;
		~LinkedList();
		//==========================================================//

		// ������ � �������� �������� �� �������
		ValueType& operator[](const size_t pos) const;
		//������ � ���� �� �������
		LinkedList::Node* getNode(const size_t pos) const;

		//������� �������� �� �������, ������� ����, ���� ��������� (O(n)), ����� ��������� (O(1))
		void insert(const size_t pos, const ValueType& value);
		//������� �������� ����� ����, (O(1))
		void insertAfterNode(Node* node, const ValueType& value);
		//������� � ����� (O(n))
		void pushBack(const ValueType& value);
		//������� � ������ (O(1))
		void pushFront(const ValueType& value);

		// ��������
		void remove(const size_t pos);
		void removeNextNode(Node* node);
		void removeFront();
		void removeBack();

		//�����, (O(n))
		long long int findIndex(const ValueType& value) const; //����� ������� ���� � ���� value
		Node* findNode(const ValueType& value) const; //����� ���� � ����� value

		//�������� ������
		void reverse();
		LinkedList reverse() const;
		LinkedList getReverseList() const;

		size_t size() const;

		void write() const; //����� ��������� ������

	private:
		Node* _head;
		size_t _size;

		void forceNodeDelete(Node* node);
};

/*
template <class ValueType>
LinkedList<ValueType>::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

template <class ValueType>
LinkedList<ValueType>::Node::~Node()
{
	//nothing here
}

template <class ValueType>
void LinkedList<ValueType>::Node::insertNext(const ValueType & value)
{
	Node* newNode = new Node(value, this->next); //������� ����� ���� �� ��������� value
	this->next = newNode;
}

template <class ValueType>
void LinkedList<ValueType>::Node::removeNext()
{
	Node* removeNode = this->next;				
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

//==================================================================================================//
template <class ValueType>
LinkedList<ValueType>::LinkedList()
	:_head(nullptr), _size(0)
{
}

template <class ValueType>
LinkedList<ValueType>::LinkedList(const LinkedList & copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0)
	{
		this->_head = nullptr;
		return;
	}

	// �������� ���� ����� ���� = (�������� ������ � ��������� ���� �������� ��������� ����)
	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head->next;
	while (currentCopyNode)
	{
		// next ��� �������� ���� = ������� ������������� ����
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}

}

template <class ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(const LinkedList& copyList)
{
	if (this == &copyList)
	{
		return *this; //���� �������� ������ ����
	}

	this->_size = copyList._size;
	this->_head = copyList._head;

	return *this;
}

template <class ValueType>
LinkedList<ValueType>::LinkedList(LinkedList && moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

template <class ValueType>
LinkedList<ValueType>& LinkedList<ValueType>::operator=(LinkedList && movelist) noexcept
{
	if (this == &movelist)
	{
		return *this;	//���� ��� ��, �� ���������� ���� ��
	}

	forceNodeDelete(_head); //������� this

	this->_size = movelist._size;
	this->_head = movelist._head;

	movelist._size = 0;
	movelist._head = nullptr;

	return *this; //���������� ���� ��������������
}

template <class ValueType>
LinkedList<ValueType>::~LinkedList()
{
	forceNodeDelete(_head);
}

//_______________________________________________________________________//

template <class ValueType>
ValueType& LinkedList<ValueType>::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

template<class ValueType>
typename LinkedList<ValueType>::Node* LinkedList<ValueType>::getNode(const size_t pos) const
{
	if (pos < 0)
	{
		assert(pos < 0); //������: ������ ������ ����
	}
	else if (pos >= this->_size)
	{
		assert(pos >= this->_size); //������: ����� �� ������� ������
	}

	Node* bufNode = this->_head; // ������� ����� ��� �������� ��������� ����
	for (size_t i = 0; i < pos; i++)
	{
		bufNode = bufNode->next; //���������� �������� �� �������
	}

	return bufNode;
}

template <class ValueType>
void LinkedList<ValueType>::insert(const size_t pos, const ValueType & value)
{
	if (pos < 0)
	{
		assert(pos < 0); //������: ������ ������ ����
	}
	else if (pos > this->_size)
	{
		assert(pos > this->_size); //������: ����� �� ������� ������
	}

	if (pos == 0) //���� ����� �������� � ������ ������, �� pushFront
	{
		pushFront(value);
	}
	else //����� ���������� ���� � ��������� �� ������ �������
	{
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos - 1; ++i)
		{
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

template <class ValueType>
void LinkedList<ValueType>::insertAfterNode(Node* node, const ValueType & value)
{
	node->insertNext(value);
}

template <class ValueType>
void LinkedList<ValueType>::pushBack(const ValueType & value)
{
	if (_size == 0)
	{
		pushFront(value);
		return;
	}
	insert(_size, value);
}

template <class ValueType>
void LinkedList<ValueType>::pushFront(const ValueType & value)
{
	_head = new Node(value, _head); // �������������� �������� ����
	++_size;
}

template <class ValueType>
void LinkedList<ValueType>::remove(const size_t pos)
{
	if (pos < 0)
	{
		assert(pos < 0); //������: ������ ������ ����
	}
	else if (pos > this->_size)
	{
		assert(pos > this->_size); //������: ����� �� ������� ������
	}

	if (pos == 0)
	{
		this->_head = this->_head->next;
	}
	else
	{
		Node* bufNode = this->_head;
		while (bufNode->next != this->getNode(pos))
		{
			bufNode = bufNode->next;
		}
		bufNode->removeNext();
	}

	_size--;
}

template <class ValueType>
void LinkedList<ValueType>::removeNextNode(Node* node)
{
	size_t pos = findIndex(node->value);
	this->remove(pos);
}

template <class ValueType>
void LinkedList<ValueType>::removeFront()
{
	this->remove(0);
}

template <class ValueType>
void LinkedList<ValueType>::removeBack()
{
	this->remove(_size - 1);
}

template <class ValueType>
long long int LinkedList<ValueType>::findIndex(const ValueType& value) const
{
	size_t i = 0;

	while (i != _size)
	{
		if (getNode(i)->value == value)
			return i;
		++i;
	}
	std::cout << "There is no such value, so get an enormous index not from the list: ";
	return -1;
}

template <class ValueType>
typename LinkedList<ValueType>::Node* LinkedList<ValueType>::findNode(const ValueType & value) const
{
	return getNode(findIndex(value));
}

template <class ValueType>
void LinkedList<ValueType>::reverse()
{
	size_t cutSize; //����������� � ��� ���� ������
	if ((_size % 2) == 0)
	{
		cutSize = _size / 2;
	}
	else
	{
		cutSize = (_size - 1) / 2;
	}

	Node* swapper = nullptr;
	for (size_t idx = 0; idx < cutSize; ++idx)
	{
		swapper = getNode(idx);
		insert(_size - idx - 1, swapper->value);
		remove(idx);

		swapper = getNode(_size - idx - 1);
		insert(idx, swapper->value);
		remove(_size - idx - 1);
	}
}

template <class ValueType>
LinkedList<ValueType> LinkedList<ValueType>::reverse() const
{
	LinkedList bufList(*this);
	bufList.reverse();
	return bufList;
}

template <class ValueType>
LinkedList<ValueType> LinkedList<ValueType>::getReverseList() const
{
	LinkedList bufList(*this);
	bufList.reverse();
	return bufList;
}

template <class ValueType>
size_t LinkedList<ValueType>::size() const
{
	return _size;
}

template <class ValueType>
void LinkedList<ValueType>::forceNodeDelete(Node* node)
{
	size_t pos = findIndex(node->value);
	if (node == nullptr)
	{
		return;
	}

	while (node != nullptr)
	{
		remove(pos);
		node = node->next;
		pos++;
	}
}

template <class ValueType>
void LinkedList<ValueType>::write() const
{
	Node* bufNode = this->_head;
	while (bufNode)
	{
		std::cout << bufNode->value << "<>";
		bufNode = bufNode->next;
	}
	std::cout << "NULL" << std::endl;
}
*/
