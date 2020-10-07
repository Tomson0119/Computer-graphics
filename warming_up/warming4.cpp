#include <iostream>
#include <Windows.h>
#include <cmath>

typedef struct _node
{
	int x, y, z;
	_node *next;

	_node(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		next = nullptr;
	}
	
	void print_node()
	{
		std::cout << x << " " << y << " " << z;
	}
} Node;

class List
{
private:
	Node* head;
	Node* tail;

	int max_length;
	int length;

	int head_index;
	int tail_index;

public:
	List(int max_length)
	{
		head = nullptr;
		tail = nullptr;
		this->max_length = max_length;

		length = 0;
		head_index = 0;
		tail_index = 0;
	}

	~List()
	{
		reset_list();
		delete head;
		delete tail;
	}

	int getLength() const
	{
		return length;
	}

	void add_first(Node* addNode)
	{
		if (length >= max_length)
			return;

		if (head == nullptr)
		{
			head = addNode;
			tail = addNode;
		}
		else
		{
			addNode->next = head;
			head = addNode;
		}
		length++;

		if (head_index > 0) {
			head_index--;
		}
		else
			tail_index = length - 1;
	}

	Node* pop_first()
	{
		if (head == nullptr)
			return nullptr;

		Node* popNode = head;
		head = head->next;

		length--;

		if (length == 0) {
			head_index = 0;
			tail_index = 0;
		}
		else
			head_index++;

		return popNode;
	}

	void add_last(Node* addNode)
	{
		if (length >= max_length)
			return;

		if (head_index > 0) {
			add_first(addNode);
			return;
		}

		if (head == nullptr)
		{
			head = addNode;
			tail = addNode;
		}
		else
		{
			tail->next = addNode;
			tail = addNode;
		}
		length++;

		tail_index = length - 1;
	}

	Node* pop_last()
	{
		if (head == nullptr)
			return nullptr;

		Node* popNode = tail;

		length--;

		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
		}
		else
			tail = getIndex(length);

		if (length == 0) {
			head_index = 0;
			tail_index = 0;
		}
		else if(tail_index > 0) 
			tail_index--;
		
		return popNode;		
	}

	void print_link()
	{
		Node* current = head;
		for (int i = 0; i < length; i++)
		{
			if (current != nullptr)
			{
				current->print_node();
				std::cout << " ¡æ ";
				current = current->next;
			}			
		}
		std::cout << std::endl;
	}
	
	Node* getIndex(int index) const 
	{
		Node* current = head;
		for (int i = 0; i < index - 1; i++) {
			if (current->next != nullptr)
				current = current->next;		
		}
		return current;
	}

	void print_list()
	{
		Node* current = nullptr;
		int cur_pos = length;

		for (int i = max_length - 1; i >= 0; i--)
		{
			std::cout << i << " : ";
			if (i >= head_index && i <= tail_index)
			{
				current = getIndex(cur_pos--);
				if (current != nullptr)
					current->print_node();			
			}
			std::cout << std::endl;
		}
		// std::cout << "Head Index : " << head_index << "  Tail Index : " << tail_index << std::endl;
	}

	void reset_list()
	{
		head_index = 0;
		tail_index = 0;

		Node* current = head;
		Node* removeNode = head;

		while (length > 0)
		{
			current = current->next;
			delete removeNode;
			removeNode = current;
			length--;
		}
		head = nullptr;
		tail = nullptr;
	}
	
	int get_distance(Node* target)
	{
		return pow(target->x, 2) + pow(target->y, 2) + pow(target->z, 2);
	}

	Node* get_longest_point()
	{
		Node* current = head;
		Node* longest = nullptr;

		int max = 0;

		while (current != nullptr)
		{
			int value = get_distance(current);
			if (max < value) {
				max = value;
				longest = current;
			}
			current = current->next;
		}

		return longest;
	}

	Node* get_shortest_point()
	{
		Node* current = head;
		Node* shortest = nullptr;

		int min = INT_MAX;

		while (current != nullptr)
		{
			int value = get_distance(current);
			if (min > value) {
				min = value;
				shortest = current;
			}
			current = current->next;
		}

		return shortest;
	}
	
	void swap_data(Node* node1, Node* node2)
	{		
		int temp_x, temp_y, temp_z;

		temp_x = node1->x;
		node1->x = node2->x;
		node2->x = temp_x;

		temp_y = node1->y;
		node1->y = node2->y;
		node2->y = temp_y;

		temp_z = node1->z;
		node1->z = node2->z;
		node2->z = temp_z;
	}

	void sort_by_distance()
	{
		if (length > 1)
		{
			for (int i = 0; i < length - 1; i++)
			{
				Node* current = head;
				Node* after = head->next;

				for (int j = 0; j < length - i - 1; j++)
				{
					if (get_distance(current) > get_distance(after))
					{
						swap_data(current, after);
					}
					current = after;
					after = after->next;
				}
			}
		}
		head_index = 0;
		tail_index = length - 1;
	}
};

int main()
{
	List* list = new List(10);

	while(1)
	{
		system("cls");

		list->print_list();
		// list->print_link();

		std::cout << "input command : ";

		char command;
		std::cin >> command;

		if (command == '+')
		{
			int x, y, z;
			std::cin >> x;
			std::cin >> y;
			std::cin >> z;

			Node* addNode = new Node(x, y, z);
			list->add_last(addNode);
		}
		else if (command == '-')
			list->pop_last();
		else if (command == 'e')
		{
			int x, y, z;
			std::cin >> x;
			std::cin >> y;
			std::cin >> z;

			Node* addNode = new Node(x, y, z);
			list->add_first(addNode);
		}
		else if (command == 'd')
			list->pop_first();
		else if (command == 'l') {
			std::cout << "Length of list : " << list->getLength() << std::endl;
			Sleep(1000);
		}
		else if (command == 'c')
			list->reset_list();
		else if (command == 'm')
		{
			std::cout << "Longedst point : (";
			list->get_longest_point()->print_node();
			std::cout << ")" << std::endl;
			Sleep(1000);
		}
		else if (command == 'n')
		{
			std::cout << "shortest point : (";
			list->get_shortest_point()->print_node();
			std::cout << ")" << std::endl;
			Sleep(1000);
		}
		else if (command == 's')
			list->sort_by_distance();
		else if (command == 'q')
			break;
	}
	delete list;
	return 0;
}