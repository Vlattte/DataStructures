#pragma once
#include <cstdlib>

// ”ровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке
using ValueType = double;

// на основе какого контейнера работает стек
enum class QueueContainer {
	Vector = 0,
	SinglyLinkedList = 1,
	DoublyLinkedList = 2
	// можно дополн€ть другими контейнерами
};

// деклараци€ класса с реализацией
class QueueImplementation;

class Queue
{
public:
	// Ѕольша€ п€терка
	Queue(QueueContainer container = QueueContainer::Vector);
	// элементы массива последовательно подкладываютс€ в стек
	Queue
	(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector);

	explicit Queue(const Queue& copyStack);
	Queue& operator=(const Queue& copyStack);

	// «десь как обычно
	// Stack(Stack&& moveStack) noexcept;
	// Stack& operator=(Stack&& moveStack) noexcept;

	~Queue();

	// добавление в хвост
	void enqueue(const ValueType& value);
	// удаление с хвоста
	void dequeue();
	// посмотреть элемент в хвосте
	const ValueType& front() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	QueueImplementation* _pimpl = nullptr;
	// тип контейнера, наверн€ка понадобитс€
	QueueContainer _containerType;
};
