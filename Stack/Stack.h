#pragma once
#include <cstdlib>
// ”ровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке
using ValueType = double;

// на основе какого контейнера работает стек
enum class StackContainer {
	Vector = 0,
	List = 1,
	// можно дополн€ть другими контейнерами
};

// деклараци€ класса с реализацией
class StackImplementation;

class Stack
{
public:
	// Ѕольша€ п€терка
	Stack(StackContainer container = StackContainer::Vector);
	// элементы массива последовательно подкладываютс€ в стек
	Stack
	(const ValueType* valueArray, const size_t arraySize, StackContainer container = StackContainer::Vector);

	explicit Stack(const Stack& copyStack);
	Stack& operator=(const Stack& copyStack);

	// «десь как обычно
	// Stack(Stack&& moveStack) noexcept;
	// Stack& operator=(Stack&& moveStack) noexcept;

	~Stack();

	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
private:
	// указатель на имплементацию (уровень реализации)
	StackImplementation* _pimpl = nullptr;
	// тип контейнера, наверн€ка понадобитс€
	StackContainer _containerType;
};
