
#include <iostream>
#include <string>

enum tile_type {
	ground = 0,
	water = 1,
	mountain = 2,
};

void afficher(int map[20][10])
{
	for (int L = 0; L < 20; ++L)
	{
		for (int C = 0; C < 10; ++C)
		{
			if (L == 0 || L == 20)
			{
				std::cout << "A";

			}
			else if (C == 0 || C == 10)
			{
				std::cout << "A";
			}
			else if (L == 0 && C == 4)
			{
				std::cout << "~";
			}
			else
			{
				std::cout << ".";
			}
		}
		std::cout << '\n';
	}
}

int main()
{
	int map[20][10] = {};

	for (int L = 0; L < 20; ++L)
	{
		for (int C = 0; C < 10; ++C)
		{
			map[20][10] = 0;
		}
		std::cout << '\n';
	}
	
}
