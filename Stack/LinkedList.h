#pragma once

#include <cassert>
#include <iostream>
#include <cstdlib>

using ValueType = double;

class LinkedList
{
		//класс узла списка
		//по своей сути, может содержать любые данные,
		//можно реализовать и ассоциативный массив, просто добавив
		//поле с ключем в узел и, с учетом этого, поменять методы LinkedList
		//(доступ по ключу, поиск по ключу и т.д.)
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
		LinkedList(); //конструктор по умолчанию
		LinkedList(const LinkedList& copyList); //конструктор копирования
		LinkedList& operator=(const LinkedList& copyList); 

		LinkedList(LinkedList&& moveList) noexcept; // перемещение с последующим очищением старого
		LinkedList& operator=(LinkedList&& movelist) noexcept;
		~LinkedList();
		//==========================================================//

		// доступ к значению элемента по индексу
		ValueType& operator[](const size_t pos) const;
		//доступ к узлу по индексу
		LinkedList::Node* getNode(const size_t pos) const;

		//вставка элемента по индексу, сначала ищем, куда вставлять (O(n)), потом вставляем (O(1))
		void insert(const size_t pos, const ValueType& value);
		//вставка элемента после узла, (O(1))
		void insertAfterNode(Node* node, const ValueType& value);
		//вставка в конец (O(n))
		void pushBack(const ValueType& value);
		//вставка в начало (O(1))
		void pushFront(const ValueType& value);

		// удаление
		void remove(const size_t pos);
		void removeNextNode(Node* node);
		void removeFront();
		void removeBack();

		//поиск, (O(n))
		long long int findIndex(const ValueType& value) const; //поиск индекса узла с этим value
		Node* findNode(const ValueType& value) const; //поиск узла с таким value

		//разворот списка
		void reverse();
		LinkedList reverse() const;
		LinkedList getReverseList() const;

		size_t size() const;

		void write() const; //метод написания списка

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
	Node* newNode = new Node(value, this->next); //создаем новый узел со значением value
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

	// головной узел этого узла = (выделяем память и вставляем туда значение головного узла)
	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head->next;
	while (currentCopyNode)
	{
		// next для текущего узла = текущий скопированный узел
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
		return *this; //если копируем самого себя
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
		return *this;	//если это мы, то возвращаем себя же
	}

	forceNodeDelete(_head); //удаляем this

	this->_size = movelist._size;
	this->_head = movelist._head;

	movelist._size = 0;
	movelist._head = nullptr;

	return *this; //возвращаем себя скопированного
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
		assert(pos < 0); //ошибка: размер меньше нуля
	}
	else if (pos >= this->_size)
	{
		assert(pos >= this->_size); //ошибка: вышли за границу списка
	}

	Node* bufNode = this->_head; // создаем буфер для хранения головного узла
	for (size_t i = 0; i < pos; i++)
	{
		bufNode = bufNode->next; //перебираем элементы до нужного
	}

	return bufNode;
}

template <class ValueType>
void LinkedList<ValueType>::insert(const size_t pos, const ValueType & value)
{
	if (pos < 0)
	{
		assert(pos < 0); //ошибка: размер меньше нуля
	}
	else if (pos > this->_size)
	{
		assert(pos > this->_size); //ошибка: вышли за границу списка
	}

	if (pos == 0) //если нужно вставить в начало списка, то pushFront
	{
		pushFront(value);
	}
	else //иначе перебираем узлы и вставляем на нужную позицию
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
	_head = new Node(value, _head); // перезаписываем головной узел
	++_size;
}

template <class ValueType>
void LinkedList<ValueType>::remove(const size_t pos)
{
	if (pos < 0)
	{
		assert(pos < 0); //ошибка: размер меньше нуля
	}
	else if (pos > this->_size)
	{
		assert(pos > this->_size); //ошибка: вышли за границу списка
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
	size_t cutSize; //уменьшенный в два раза размер
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
