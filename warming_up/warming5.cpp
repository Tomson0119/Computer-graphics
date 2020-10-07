#include <iostream>
#include <cstdlib>
#include <ctime>

typedef struct _node
{
	int x, y;
	_node* next;

	_node(int x, int y)
	{
		this->x = x;
		this->y = y;
		next = nullptr;
	}
} Node;

class Stack
{
private:
	Node* head;
	Node* tail;

	int length;
	int continuous;

public:
	Stack()
	{
		head = nullptr;
		tail = nullptr;
		length = 0;
		continuous = 1;
	}

	Node* getLast()
	{
		if (length == 0)
			return nullptr;

		Node* popNode = tail;
		return popNode;
	}

	int getContinous(int x, int y)
	{
		if (length > 0 && tail->x == x && tail->y == y)
			return continuous + 1;
		return continuous;
	}

	void push(int x, int y)
	{
		Node* addNode = new Node(x, y);

		if (head == nullptr)
		{
			head = addNode;
			tail = addNode;
		}
		else
		{
			if (tail->x == x && tail->y == y)
				continuous++;

			tail->next = addNode;
			tail = addNode;
		}
		length++;
	}

	void pop()
	{
		if (head == nullptr)
			return;

		Node* popNode = tail;
		Node* current = head;

		while (current->next != tail)
			current = current->next;

		tail = current;

		delete popNode;
	}

};

class Path_Maker
{
private:
	int** map;
	int max_length;

	Stack* stack;

	const int wall = 0;
	const int visited = 1;
	const int invaild = 2;

public:
	Path_Maker(int max_length)
	{
		map = new int* [max_length];
		for (int i = 0; i < max_length; i++) {
			map[i] = new int[max_length];
			memset(map[i], 0, sizeof(int)*max_length);
		}

		this->max_length = max_length;

		stack = new Stack();

		srand((unsigned int)time(0));
	}

	~Path_Maker()
	{
		for (int i = 0; i < max_length; i++)
			delete[] map[i];
		delete map;

		delete stack;
	}

	void print_map()
	{
		for (int i = 0; i < max_length; i++)
		{
			for (int j = 0; j < max_length; j++)
			{
				if (map[i][j] == wall)
					std::cout << "¡Ü";
				else if (map[i][j] == visited)
					std::cout << "¡Û";
			}
			std::cout << std::endl;
		}
	}

	bool check_close_path(int row, int column)
	{
		if (row - 1 >= 0 && map[row - 1][column] == invaild)
			return false;
		else if (row + 1 < max_length && map[row + 1][column] == invaild)
			return false;
		else if (column - 1 >= 0 && map[row][column - 1] == invaild)
			return false;
		else if (column + 1 < max_length && map[row][column + 1] == invaild)
			return false;
		else
			return true;
	}

	bool make_path(int row, int column)
	{
		if (row < 0 || row >= max_length || column < 0 || column >= max_length)
			return false;
		else if (map[row][column] != wall)
			return false;
		else if (!check_close_path(row, column))
			return false;
		else if (stack->getContinous(row, column) > 5)
			return false;
		else if (row == max_length - 1 && column == max_length - 1)
			return true;
		else
		{
			map[row][column] = visited;
			stack->push(row, column);

			if (make_path(row - 1, column) || make_path(row + 1, column)
				|| make_path(row, column - 1) || make_path(row, column + 1))
				return true;

				
			stack->pop();
			return false;
		}
	}
};

int main()
{
	Path_Maker* path = new Path_Maker(50);	

	path->make_path(0,0);

	while (1)
	{
		path->print_map();

		std::cout << "\t : ";
		char command;
		std::cin >> command;

		if (command == 'r')
		{
			// remake path
		}
		else if (command == 'q')
			break;
	}

	delete path;
	return 0;
}