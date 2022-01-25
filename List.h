#pragma once
//Fahad Waheed

template <typename T>
class List
{
	struct Node
	{
		T data;
		Node* next, * previous;

		Node() : data(T()), next(NULL), previous(NULL) {};

		Node(T data) : data(data), next(NULL), previous(NULL) {};
	};

	Node* head, * tail;

	void firstNodeCreation(T data)
	{
		Node* newNode = new Node(data);
		head = tail = newNode;
	}

	Node* Search(T data)
	{
		Node* currnode = head;
		while (currnode && currnode->data != data)
			currnode = currnode->next;
		return currnode;
	}

public:
	List() : head(NULL), tail(NULL) {};

	List(const List<T>& obj) : head(NULL), tail(NULL)
	{
		Node* currnode = head;
		while (currnode)
		{
			this->Append(currnode->data);
			currnode = currnode->next;
		}
	}

	List& operator=(const List<T>& obj)
	{
		this->clear();
		Node* currnode = head;
		while (currnode)
		{
			this->Append(currnode->data);
			currnode = currnode->next;
		}
		return *this;
	}

	bool isEmpty()
	{
		return head == NULL && tail == NULL;
	}

	void Append(T data)
	{
		if (isEmpty())
		{
			firstNodeCreation(data);
		}
		else
		{
			Node* newNode = new Node(data);
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
		}
	}

	void InsertinFirst(T data)
	{
		if (isEmpty())
		{
			firstNodeCreation(data);
		}
		else
		{
			Node* newNode = new Node(data);
			newNode->next = head;
			head->previous = newNode;
			head = newNode;
		}
	}

	void Insert(T data, int index = 0)
	{
		if (index == 0)
		{
			InsertinFirst(data);
		}
		else if (index > 0)
		{
			int count = 0;
			Node* currnode = head;
			while (currnode && count != index)
			{
				currnode = currnode->next;
				count++;
			}

			if (count == index && currnode == NULL)
			{
				Append(data);
			}

			else if (currnode && count == index)
			{
				Node* newNode = new Node(data);
				newNode->next = currnode;
				newNode->previous = currnode->previous;
				currnode->previous->next = newNode;
				currnode->previous = newNode;
			}
		}
	}

	void Remove(T data)
	{
		Node* dNode = Search(data);
		if (dNode)
		{
			if (dNode == head && dNode == tail)
			{
				head = tail = NULL;
			}
			else if (dNode == head)
			{
				head->next->previous = NULL;
				head = head->next;
			}
			else if (dNode == tail)
			{
				tail->previous->next = NULL;
				tail = tail->previous;
			}
			else
			{
				dNode->previous->next = dNode->next;
				dNode->next->previous = dNode->previous;
			}

			delete dNode;
		}
	}

	void Update(T oldData, T newData)
	{
		Node* currnode = Search(oldData);

		if (currnode)
			currnode->data = newData;
	}

	int Find(T data)
	{
		int count = 0;

		Node* currnode = head;
		while (currnode && currnode->data != data)
		{
			currnode = currnode->next;
			count++;
		}

		if (currnode) 
			return count;
		return -1;
	}

	void SelectionSort()
	{
		Node* lastNode = tail;
		Node* maxNode;

		while (lastNode != head)
		{
			maxNode = head;
			Node* currnode = head->next;

			while (currnode != lastNode->next)
			{
				if (currnode->data > maxNode->data)
					maxNode = currnode;

				currnode = currnode->next;
			}

			if (maxNode->data > lastNode->data)
			{
				T data = maxNode->data;
				maxNode->data = lastNode->data;
				lastNode->data = data;
			}
			lastNode = lastNode->previous;
		}
	}

	void InsertionSort()
	{
		for (Node* i = head->next; i; i = i->next)
		{ 
			T temp = i->data;

			Node* j = i;
			for (; j != head && temp < j->previous->data; j = j->previous) 
			{
				j->data = j->previous->data;
			}
			j->data = temp;
		}
	}

	void BubbleSort()
	{
		Node* lastNode = tail;
		bool exchange;

		do
		{
			exchange = false;
			for (Node* currnode = head; currnode != lastNode; currnode = currnode->next)
			{
				if (currnode->data > currnode->next->data)
				{
					T data = currnode->data;
					currnode->data = currnode->next->data;
					currnode->next->data = data;
					exchange = true;
				}
			}

			lastNode = lastNode->previous;
		} while (exchange);
	}

	class Interator
	{
		Node* it;

	public:
		Interator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = node;
		}

		T operator*()
		{
			return it->data;
		}

		void operator++()
		{
			it = it->next;
		}

		void operator++(int)
		{
			it = it->next;
		}

		bool operator==(Node* node)
		{
			return this->it == node;
		}

		bool operator!=(Node* node)
		{
			return this->it != node;
		}
	};

	Node* begin()
	{
		return head;
	}

	Node* end()
	{
		if (tail)
			return tail->next;
		return NULL;
	}

	void clear()
	{
		Node* currnode = head;
		while (currnode)
		{
			head = head->next;
			delete currnode;
			currnode = head;
		}
		tail = head;
	}

	T operator[](int index)
	{
		int i = 0;
		Node* currnode = head;
		while (currnode && i != index)
		{
			currnode = currnode->next;
			i++;
		}
		if (currnode)
			return currnode->data;
		return T();
	}

	~List()
	{
		clear();
	}
};