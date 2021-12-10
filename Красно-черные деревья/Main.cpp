#include "Tree.h"

void menu();

int main()
{
	std::cout << "Welcome to the Black-red-tree!";
	int chose = 0;
	BLACK_RED_TREE<int>* example = nullptr;
	bool isEmpty = true;

	do 
	{
		menu();

		std::cout << "\nEnter menu: ";
		std::cin >> chose;

		switch (chose)
		{
		case 1:
		{
			if(isEmpty!=true) example->clearTree(example);

			int count,data;
			std::cout << "\nEnter count of elements: ";
			std::cin >> count;
			std::cout << "\nEnter value: ";

			for (size_t i = 0; i < abs(count); i++)
			{
				std::cin >> data;
				example->addElevInTree(example, data);
			}
			isEmpty = false;
		}break;
		case 2:
		{
			int data;
			std::cout << "\nEnter add value: ";
			std::cin >> data;
			example->addElevInTree(example, data);

			isEmpty = false;
		}break;
		case 3:
		{
			if (isEmpty!=true)
			{
				int data;
				std::cout << "\nEnter delete value: ";
				std::cin >> data;
				example->deleteValue(example, data);

				if (example == nullptr) isEmpty = true;
			}
			else std::cout << "\nTree is empty!";
		}break;
		case 4:
		{
			if (isEmpty != true)
			{
				example->printTree(example);
				std::cout << "\nBlack height in tree: " << example->blackHeight(example);
				std::cout << "\nBlack branch is: ";
				example->printBlackBranch(example);
			}
			else std::cout << "\nTree is empty!";
		}break;
		case 5:
		{
			if(isEmpty!=true) example->clearTree(example);
		}break;
		}
	} while (chose != 6);

	example->clearTree(example);

	std::cin.ignore().get();
	return 0;
}

void menu()
{
	std::cout << "\n_________________________";
	std::cout << "\n1)Filling";
	std::cout << "\n2)Add element";
	std::cout << "\n3)Delete element";
	std::cout << "\n4)Print ";
	std::cout << "\n5)Clear tree";
	std::cout << "\n6)Exit";
	std::cout << "\n_________________________";
}
