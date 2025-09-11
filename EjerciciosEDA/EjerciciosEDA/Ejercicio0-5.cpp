#include <iostream>

int main()
{
	int numCasos;
	std::cin >> numCasos;

	while (numCasos-- > 0)
	{
		int numElem;
		std::cin >> numElem;

		for (int i = 0; i < numElem; i++)
		{
			int dato;
			std::cin >> dato;
			std::cout << dato * 2 << " ";
		}
		std::cout << "\n";
	}
}