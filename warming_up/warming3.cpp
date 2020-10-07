#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

struct rectangle
{
	int x1, x2;
	int y1, y2;
};

class Collision
{
private:
	rectangle s1, s2;

	int boundary;

	bool check_boundary(int n)
	{
		if (n > boundary || n < 0)
			return false;
		else
			return true;
	}

	void insert_rand_num(rectangle &s)
	{
		int x1 = rand() % boundary;
		int x2 = rand() % boundary;
		int y1 = rand() % boundary;
		int y2 = rand() % boundary;

		if (x1 > x2) 
		{
			int temp = x2;
			x2 = x1;
			x1 = temp;
		}
		else if (x1 == x2)
		{
			if (x1 == boundary)
				x1 -= 1;
			else
				x2 += 1;
		}

		if (y1 > y2) 
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
		}
		else if (y1 == y2)
		{
			if (y1 == boundary)
				y1 -= 1;
			else
				y2 += 1;
		}

		s.x1 = x1;
		s.x2 = x2;
		s.y1 = y1;
		s.y2 = y2;
	}
public:
	Collision(int max_boundary)
	{
		boundary = max_boundary;

		srand((unsigned int)time(0));
		
		insert_rand_num(s1);
		insert_rand_num(s2);
	}

	void reset_rectangle()
	{
		insert_rand_num(s1);
		insert_rand_num(s2);
	}

	bool check_collision()
	{
		if (s1.x2 >= s2.x1 && s1.x1 <= s2.x2 &&
			s1.y2 >= s2.y1 && s1.y1 <= s2.y2)
			return true;
		else
			return false;
	}

	void print_values()
	{
		std::cout << "Random values : \n\t Rectangle 1 : (" << s1.x1 << ", " << s1.y1 << ") ("
			<< s1.x2 << ", " << s1.y2 << ")\n\t Rectangle 2 : (" << s2.x1 << ", " << s2.y1 << ") ("
			<< s2.x2 << ", " << s2.y2 << ")" << std::endl;
	}

	char getUserInput()
	{
		while(1)
		{
			if (GetAsyncKeyState(0x57) & 0x8000) {
				return 'w';
			}
			else if (GetAsyncKeyState(0x41) & 0x8000) {
				return 'a';
			}
			else if (GetAsyncKeyState(0x53) & 0x8000) {
				return 's';
			}
			else if (GetAsyncKeyState(0x44) & 0x8000) {
				return 'd';
			}
			else if (GetAsyncKeyState(0x52) & 0x8000) {
				return 'r';
			}
		}
	}

	void move_rectangle(char command, int n)
	{
		int x_move = 0;
		int y_move = 0;

		if (command == 'w')
			y_move = 1;
		else if (command == 'a')
			x_move = -1;
		else if (command == 's')
			y_move = -1;
		else if (command == 'd')
			x_move = 1;
		
		if (check_boundary(s2.x1 + x_move * n) &&
			check_boundary(s2.x2 + x_move * n))
		{
			s2.x1 += x_move * n;
			s2.x2 += x_move * n;
		}
		else
			std::cout << "Error : Boundary Exception !" << std::endl;

		if (check_boundary(s2.y1 + x_move * n) &&
			check_boundary(s2.y1 + x_move * n))
		{
			s2.y1 += y_move * n;
			s2.y2 += y_move * n;
		}		
		else
			std::cout << "Error : Boundary Exception !" << std::endl;
	}
};

int main()
{
	Collision col = Collision(500);

	while (1)
	{
		col.print_values();

		if (col.check_collision())
			std::cout << "Rectangle 1 & 2 Collide!" << std::endl;

		std::cout << "intput command(w, a, s, d)" << std::endl;
		char command = col.getUserInput();
		Sleep(300);

		std::cout << "Key Pressed : " << command << std::endl << std::endl;

		if (command == 'r')
			col.reset_rectangle();
		else
			col.move_rectangle(command, 50);		
	}
}