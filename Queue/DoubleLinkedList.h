#pragma once
#include <cstdlib>

using ValueType = double;

class DoubleLinkedList
{
public:
	//����� ���� ������
	//�� ����� ����, ����� ��������� ����� ������,
	//����� ����������� � ������������� ������, ������ �������
	//���� � ������ � ���� �, � ������ �����, �������� ������ LinkedList
	//(������ �� �����, ����� �� ����� � �.�.)
	struct Node
	{
		Node(const ValueType& value, Node* next = nullptr, Node* previous = nullptr); //done
		~Node();																	  //done

		void insertNext(const ValueType& value);									  //done
		void insertPrevious(const ValueType& value);								  //done
		void removeNext();									  						  //done
		void removePrevious();                                                        //done

		ValueType value;									                          
		Node* next;
		Node* previous;
	};

public:
	//==========================================================//
	DoubleLinkedList(); //����������� �� ���������									  //done
	DoubleLinkedList(const DoubleLinkedList& copyList); //����������� �����������     //done
	DoubleLinkedList& operator=(const DoubleLinkedList& copyList);                    //done

	DoubleLinkedList(DoubleLinkedList&& moveList) noexcept; // ����������� � ����������� ��������� �������  //done
	DoubleLinkedList& operator=(DoubleLinkedList&& movelist) noexcept;				  //done
	~DoubleLinkedList();															  //done
	//==========================================================//

	// ������ � �������� �������� �� �������
	ValueType& operator[](const size_t pos) const;									  //done
	//������ � ���� �� �������
	DoubleLinkedList::Node* getNode(const size_t pos) const;						  //done

	//������� �������� �� �������, ������� ����, ���� ��������� (O(n)), ����� ��������� (O(1))
	void insert(const size_t pos, const ValueType& value);							  //done
	//������� �������� ����� ����, (O(1))
	void insertAfterNode(Node* node, const ValueType& value);	              //done
	//������� �������� ����� �����
	void insertBeforeNode(Node* node, const ValueType& value);		          //done
	//������� � ����� (O(n))
	void pushBack(const ValueType& value);									          //done
	//������� � ������ (O(1))
	void pushFront(const ValueType& value);									          //done

	// ��������
	void remove(const size_t pos);									                  //done
	void removeNextNode(Node* node);									              //done
	void removePreviousNode(Node* node);									          //done
	void removeFront();									                              //done
	void removeBack();									                              //done

	//�����, (O(n))
	long long int findIndex(const ValueType& value) const; //����� ������� ���� � ���� value //done
	Node* findNode(const ValueType& value) const;          //����� ���� � ����� value        //done

	//�������� ������
	void reverse();									                                  //done
	DoubleLinkedList reverse() const;									              //done
	DoubleLinkedList getReverseList() const;									      //done

	size_t size() const;									                          //

	void write() const; //����� ��������� ������									  //
	void writeTail();
private:
	Node* _head;
	Node* _tail;
	size_t _size;

	void forceNodeDelete(Node* node);									              //
};

