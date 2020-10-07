#include <iostream>
#include <fstream>

void readFile()
{
	std::ifstream inFile;
	inFile.open("data.txt");

	if (inFile.is_open())
	{
		int alphabet_count = 0;
		int number_count = 0;

		char letter;
		while (!inFile.eof())
		{
			inFile.get(letter);
			std::cout << letter;

			if (isdigit(letter)!=0)
				number_count++;
			if (isalpha(letter)!=0)
				alphabet_count++;
		}
		std::cout << std::endl << std::endl;
		std::cout << "Alphabet Count : " << alphabet_count << std::endl;
		std::cout << "Number Count : " << number_count << std::endl;
	}
	
	inFile.close();
}

int main()
{
	readFile();
	return 0;
}