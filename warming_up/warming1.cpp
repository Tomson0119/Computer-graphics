#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

class MyProgram
{
private:
	int length;
	int result[10][10];

	void refresh()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				result[i][j] = 0;
			}
		}
	}

public:
	MyProgram(int length)
	{
		this->length = length;
		memset(result, -1, sizeof(result));
	}

	void multiply(int arr1[][10], int arr2[][10])
	{
		refresh();
		for (int i = 0; i < length; i++) 
		{
			for (int j = 0; j < length; j++)
			{
				for (int k = 0; k < length; k++) 
					result[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}

	void add(int arr1[][10], int arr2[][10])
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				result[i][j] = arr1[i][j] + arr2[i][j];
			}
		}
	}

	void subtract(int arr1[][10], int arr2[][10])
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				result[i][j] = arr1[i][j] - arr2[i][j];
			}
		}
	}

	int determinant(int arr[][10], int k)
	{
		int det = 0;

		if (k <= 2)
			det = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
		else
		{
			int sub_array[10][10];

			for (int n = 0; n < k; n++)
			{
				int sub_i = 0;
				for (int i = 1; i < k; i++)
				{
					int sub_j = 0;
					for (int j = 0; j < k; j++)
					{
						if (j != n)
						{
							sub_array[sub_i][sub_j++] = arr[i][j];
						}
					}
					sub_i++;
				}
				det += pow(-1, n) * arr[0][n] * determinant(sub_array, k - 1);
			}
		}
		return det;
	}

	void transpose(int arr[][10], int (&trans)[10][10])
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				trans[i][j] = arr[j][i];
			}
		}
	}

	void resize(int arr[][10], int(&resized)[10][10])
	{
		for (int i = 0; i < length + 1; i++)
		{
			for (int j = 0; j < length + 1; j++)
			{
				if (j == length && i == length)
					resized[i][j] = 1;
				else if (i == length || j == length)
					resized[i][j] = 0;
				else
					resized[i][j] = arr[i][j];
			}
		}
	}

	void printResult()
	{
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++)
			{
				std::cout << result[i][j] << " ";
			}
			std::cout << std::endl;
		}		
	}

	void printArray(int arr[][10], int size)
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
			{
				std::cout << arr[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void randomize(int arr[][10])
	{
		for (int i = 0; i < length; i++)	{
			for (int j = 0; j < length; j++)	{
				arr[i][j] = rand() % 2;
			}
		}
	}	
};

void drawMenu(int arr1[][10], int arr2[][10])
{
	std::cout << "// Array1 //   // Array2 //" << std::endl;

	for (int i = 0; i < 3; i++) {
		std::cout << "   ";
		for (int j = 0; j < 3; j++) {
			std::cout << arr1[i][j] << " ";
		}
		std::cout << "         ";
		for (int k = 0; k < 3; k++) {
			std::cout << arr2[i][k] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::srand((unsigned int)time(NULL));

	int first[10][10] = { -1, };
	int second[10][10] = { -1, };

	MyProgram* program = new MyProgram(3);

	program->randomize(first);
	program->randomize(second);

	char select = '/0';

	drawMenu(first, second);

	while (true)	{

		std::cout << std::endl << " Command : ";
		std::cin >> select;

		system("cls");

		drawMenu(first, second);

		std::cout << std::endl << "// Result //" << std::endl;

		if (select == 'm' || select == 'M') {
			program->multiply(first, second);			
			program->printResult();
		}
		else if (select == 'a' || select == 'A')
		{
			program->add(first, second);
			program->printResult();
		}
		else if (select == 'd' || select == 'D')
		{
			program->subtract(first, second);
			program->printResult();
		}
		else if (select == 'r' || select == 'R')
		{
			std::cout << " Array1 value : " << program->determinant(first, 3) << std::endl;
			std::cout << " Array2 value : " << program->determinant(second, 3) << std::endl;
		}
		else if (select == 't' || select == 'T')
		{
			int trans1[10][10];
			int trans2[10][10];

			std::cout << std::endl << "// Transposed 1 //" << std::endl;
			program->transpose(first, trans1);
			program->printArray(trans1,3);
			std::cout << " value : " << program->determinant(trans1, 3) << std::endl;

			std::cout << std::endl << "// Transposed 2 //" << std::endl;
			program->transpose(second, trans2);
			program->printArray(trans2,3);
			std::cout << " value : " << program->determinant(trans1, 3) << std::endl;
		}
		else if (select == 'h' || select == 'H')
		{
			int resized1[10][10];
			int resized2[10][10];

			std::cout << std::endl << "// Resized 1 //" << std::endl;
			program->resize(first, resized1);
			program->printArray(resized1, 4);
			std::cout << " value : " << program->determinant(resized1, 4) << std::endl;

			std::cout << std::endl << "// Resized 2 //" << std::endl;
			program->resize(second, resized2);
			program->printArray(resized2, 4);
			std::cout << " value : " << program->determinant(resized2, 4) << std::endl;
		}
		else if (select == 's' || select == 'S')
		{
			program->randomize(first);
			program->randomize(second);

			system("cls");

			drawMenu(first, second);
		}
		else if (select == 'q' || select == 'Q')
			break;
	}

	delete program;
	return 0;
}