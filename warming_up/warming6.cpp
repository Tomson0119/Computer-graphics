#include <iostream>

class Rectangle
{
private:
	int **board;

	int length;

	int rect_x1, rect_y1;
	int rect_x2, rect_y2;

public:
	Rectangle(int length)
	{
		board = new int* [length];
		for (int i = 0; i < length; i++) {
			board[i] = new int[length];
			memset(board[i], 0, sizeof(int)*length);
		}

		this->length = length;

		rect_x1 = -1, rect_x2 = -1;
		rect_y1 = -1, rect_y2 = -1;
	}

	~Rectangle()
	{
		for (int i = 0; i < length; i++)
			delete[] board[i];
		delete board;
	}

	void make_rect(int x1, int y1, int x2, int y2)
	{
		rect_x1 = x1, rect_x2 = x2;
		rect_y1 = y1, rect_y2 = y2;

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (i >= rect_y1 && i <= rect_y2
					&& j >= rect_x1 && j <= rect_x2)
					board[i][j] = 1;
				else
					board[i][j] = 0;
			}
		}
	}

	void print_board()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (board[i][j] == 0)
					std::cout << ".";
				else
					std::cout << "O";
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	void move_x(int x1, int x2)
	{
		for (int i = rect_y1; i <= rect_y2; i++)
		{
			if (rect_x2 < x2)
			{
				board[i][rect_x1] = 0;
				board[i][x2] = 1;
			}
			if (rect_x2 > x2)
			{
				board[i][x1] = 1;
				board[i][rect_x2] = 0;
								
			}
		}
		rect_x1 = x1;
		rect_x2 = x2;
	}

	void move_y(int y1, int y2)
	{
		for (int i = rect_x1; i <= rect_x2; i++)
		{
			if (rect_y2 < y2)
			{
				board[rect_y1][i] = 0;
				board[y2][i] = 1;
			}
			if (rect_y2 > y2)
			{
				board[y1][i] = 1;
				board[rect_y2][i] = 0;

			}
		}
		rect_y1 = y1;
		rect_y2 = y2;
	}

	void resize_rect(int x, int y)
	{
		resize_x(x);
		resize_y(y);		
	}

	void resize_x(int x)
	{
		for (int i = rect_y1; i <= rect_y2; i++)
		{
			if (rect_x2 < x)
			{
				board[i][x] = 1;
			}
			if (rect_x2 > x)
			{
				board[i][rect_x2] = 0;
			}
		}
		rect_x2 = x;
	}

	void resize_y(int y)
	{
		for (int i = rect_x1; i <= rect_x2; i++)
		{
			if (rect_y2 < y)
			{
				board[y][i] = 1;
			}
			if (rect_y2 > y)
			{
				board[rect_y2][i] = 0;
			}
		}
		rect_y2 = y;
	}
};

void swap(int &a, int &b)
{
	int temp = b;
	b = a;
	a = temp;
}

void input_xy(int& x1, int& y1, int& x2, int& y2, int length)
{
	while (1) {
		std::cout << "input coord value : ";
		std::cin >> x1;
		std::cin >> y1;
		std::cin >> x2;
		std::cin >> y2;

		if (x1 < 1 || x1 > length || x2 < 1 || x2 > length
			|| y1 < 1 || y1 > length || y2 < 1 || y2 > length) {
			std::cout << "1 ~ 30 사이 정수를 입력하시오" << std::endl;
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		else
		{
			x1--;
			x2--;
			y1--;
			y2--;
			break;
		}
	}
	
	if (x1 > x2) swap(x1, x2);
	else if (x1 == x2) x2 += 1;
	if (y1 > y2) swap(y1, y2);
	else if (y1 == y2) y2 += 1;
}

int main()
{
	int length = 30;

	Rectangle* rect = new Rectangle(length);
	
	int x1, y1, x2, y2;
	
	input_xy(x1, y1, x2, y2, length);

	rect->make_rect(x1, y1, x2, y2);

	while (1) 
	{
		system("cls");

		rect->print_board();

		std::cout << "\tCommand : ";
		char command;
		
		std::cin >> command;

		if (command == 'q')
			break;
		else if (command == 'x')
		{
			if(x2 + 1 < length)
				rect->move_x(++x1, ++x2);
		}
		else if (command == 'X')
		{
			if (x1 - 1 >= 0)
				rect->move_x(--x1, --x2);
		}
		else if (command == 'y')
		{
			if (y2 + 1 < length)
				rect->move_y(++y1, ++y2);
		}
		else if (command == 'Y')
		{
			if (y1 - 1 >= 0)
				rect->move_y(--y1, --y2);
		}
		else if (command == 's')
		{
			if (x2 - 1 > x1 && y2 - 1 > y1)
				rect->resize_rect(--x2, --y2);
		}
		else if (command == 'S')
		{
			if (x2 + 1 < length && y2 + 1 < length)
				rect->resize_rect(++x2, ++y2);
		}
		else if (command == 'i')
		{
			if (x2 + 1 < length)
				rect->resize_x(++x2);
		}
		else if (command == 'j')
		{
			if (x2 - 1 > x1)
				rect->resize_x(--x2);
		}
		else if (command == 'k')
		{
			if (y2 + 1 < length)
				rect->resize_y(++y2);
		}
		else if (command == 'l')
		{
			if (y2 - 1 > y1)
				rect->resize_y(--y2);
		}
		else if (command == 'r')
		{
			input_xy(x1, y1, x2, y2, length);
			rect->make_rect(x1, y1, x2, y2);
		}
	}
	delete rect;
	return 0;
}