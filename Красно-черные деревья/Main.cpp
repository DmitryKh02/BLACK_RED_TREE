#include "Tree.h"

//template<class T>
int main()
{
	int count;
	std::cout << "Enter count of number: ";
	std::cin >> count;
	int value;
	std::cout << "Enter numbers: ";
	std::cin >> value;
	BLACK_RED_TREE<int>* example = new BLACK_RED_TREE<int> (value);

	for (size_t i = 1; i < count; i++)
	{
		std::cin >> value;
		example->insert(example,value);
	}
	example->printTree(example);

	
	std::cout << "Enter delete number: ";
	std::cin >> value;
	while (value != 0)
	{
	example->removeElem(example, value);

	example->printTree(example);

	std::cout << "Enter delete number: ";
	std::cin >> value;
	}
	
	std::cout<<"\nMax height: "<<example->findHeightTree(example);
	example->clearTree(example);

	std::cin.ignore().get();
	return 0;
}