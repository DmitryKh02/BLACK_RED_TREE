#pragma once
#include <iostream>
//Same rool in the black-red tree
//1)Main root - black
//2)Red root -> only two black knot
//	black root -> any knot
//3)leaf -> black
//4)Must be same number of black nodes from the root to  the leaves (black height)
//Inserted node is always colored red!

enum COLOR_BLACK_RED_TREE {BLACK = 0,RED = 1}; 

template <class T>
struct BLACK_RED_TREE
{
private:
	T value;
	int countValue;
	COLOR_BLACK_RED_TREE color;
	BLACK_RED_TREE* left;
	BLACK_RED_TREE* right;
	int cKnot;
protected:
	
	bool isRed(BLACK_RED_TREE* root);
	bool isFind(BLACK_RED_TREE* root, T data);

	BLACK_RED_TREE* leftTurn(BLACK_RED_TREE* root);
	BLACK_RED_TREE* rightTurn(BLACK_RED_TREE* root);

	void flipColors(BLACK_RED_TREE* root);
	
	BLACK_RED_TREE* insert(BLACK_RED_TREE* root, T data);

	BLACK_RED_TREE* deleteData(BLACK_RED_TREE* root, T elem);
	BLACK_RED_TREE* deleteWithBranch(BLACK_RED_TREE* root);
	BLACK_RED_TREE* findMin(BLACK_RED_TREE* root);
	BLACK_RED_TREE* fixTheHeight(BLACK_RED_TREE* root, bool& isFixed);

public:
	BLACK_RED_TREE(T _value,int countKnot, COLOR_BLACK_RED_TREE _color);
	~BLACK_RED_TREE();

	void addElevInTree(BLACK_RED_TREE*& root, T data);

	int blackHeight(BLACK_RED_TREE* root);

	void printTree(BLACK_RED_TREE* root, int count = 0);
	
	int size(BLACK_RED_TREE* root);

	void deleteValue(BLACK_RED_TREE*& root, T value);

	void clearTree(BLACK_RED_TREE*& root);

	void printBlackBranch(BLACK_RED_TREE* root);
};

template<class T>
BLACK_RED_TREE<T>::BLACK_RED_TREE(T _value,int countKnot, COLOR_BLACK_RED_TREE _color)
{
	value = _value;
	cKnot = countKnot;
	countValue = 1;
	color = _color;

	left = nullptr;
	right = nullptr;
}

template<class T>
BLACK_RED_TREE<T>::~BLACK_RED_TREE()
{
	left = nullptr;
	right = nullptr;
}



template<class T>
void BLACK_RED_TREE<T>::addElevInTree(BLACK_RED_TREE*& root, T data)
{
	BLACK_RED_TREE* pointer = root;

	if (!isFind(pointer, data))
	{
		root = insert(root, data);
		root->color = BLACK;
	}
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::insert(BLACK_RED_TREE* root, T data)
{
	if (root != nullptr)
	{
		if (root->value < data) root->right = insert(root->right, data);
		if (root->value > data) root->left = insert(root->left, data);
		else root->countValue++;

		if (isRed(root->right) && !isRed(root->left)) root = leftTurn(root);
		if (isRed(root->left) && isRed(root->left->left)) root = rightTurn(root);
		if (isRed(root->left) && isRed(root->right)) flipColors(root);

		root->cKnot = 1 + size(root->left) + size(root->right);
	}
	else root = new BLACK_RED_TREE(data,1, RED);


	return root;
}



template<class T>
void BLACK_RED_TREE<T>::clearTree(BLACK_RED_TREE*& root)
{
	if(root->left != nullptr) clearTree(root->left);
	if(root->right != nullptr) clearTree(root->right);

	delete root;
	root = nullptr;
}

template<class T>
void BLACK_RED_TREE<T>::printBlackBranch(BLACK_RED_TREE* root)
{
	if (root != nullptr)
	{
		while (root)
		{
			std::cout << root->value<<" ";
			root = root->right;
		}
	}
}

template<class T>
void BLACK_RED_TREE<T>::printTree(BLACK_RED_TREE* root, int count)
{
	if (root->right != nullptr)	printTree(root->right, count + 1);

	for (size_t i = 0; i < count; i++)
		std::cout << "\t";

	std::cout << root->value << "[" << root->color << "]" << "->{" << "\n";

	
	if (root->left != nullptr) printTree(root->left, count + 1);
	count--;
	/*if (root->left != nullptr) printTree(root->left, count + 1);

	for (size_t i = 0; i < count; i++)
		std::cout << "\t";

	std::cout << root->value << "[" << root->color << "]" << "->{" << "\n";

	if (root->right != nullptr)	printTree(root->right, count + 1);

	count--;*/
}


template<class T>
bool BLACK_RED_TREE<T>::isRed(BLACK_RED_TREE* root)
{
	bool result = true;

	if (root != nullptr) root->color == RED ? result = true : result = false;
	else result = false;

	return result;
}

template<class T>
bool BLACK_RED_TREE<T>::isFind(BLACK_RED_TREE* root, T data)
{
	bool result = false;

	while (root != nullptr && !result)
	{
		if (root->value > data) root = root->left;
		else if (root->value < data) root = root->right;
		else
		{
			root->countValue++;
			result = true;
		}
	}

	return result;
}



template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::leftTurn(BLACK_RED_TREE* root)
{
	BLACK_RED_TREE* current = root->right;

	root->right = current->left;
	current->left = root;
	current->color = root->color;
	root->color = RED;
	current->cKnot = root->cKnot;
	root->cKnot = 1 + size(root->left) + size(root->right);

	return current;
} //rotateleft

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::rightTurn(BLACK_RED_TREE* root)
{
	BLACK_RED_TREE* current = root->left;

	root->left = current->right;
	current->right = root;
	current->color = root->color;
	root->color = RED;
	current->cKnot = root->cKnot;
	root->cKnot = 1 + size(root->left) + size(root->right);

	return current;
} //rotateright



template<class T>
void BLACK_RED_TREE<T>::flipColors(BLACK_RED_TREE* root)
{
	root->color = RED;
	root->left->color = BLACK;
	root->right->color = BLACK;
}

template<class T>
int BLACK_RED_TREE<T>::size(BLACK_RED_TREE* root)
{
	return (root== nullptr) ? 0 : 1 + size(root->left) + size(root->right);
}



template<class T>
void BLACK_RED_TREE<T>::deleteValue(BLACK_RED_TREE*& root, T value)
{
	if (isFind(root, value))
	{
		if (!isRed(root->left) && !isRed(root->right)) root->color = RED;

		root = deleteData(root, value);

		if (root) root->color = BLACK;
	}
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::deleteData(BLACK_RED_TREE* root, T elem)
{
	static bool needToFixHeigh = false;
	if (root->value > elem)	root->left = deleteData(root->left, elem);
	else if (root->value < elem) root->right = deleteData(root->right, elem);
	else
	{
		if (root->left != nullptr && root->right != nullptr)
			{
				root->value = findMin(root->right)->value;
				root->right = deleteData(root->right, root->value);
			}
		else
			if (root->left == nullptr || root->right == nullptr)
			{	
				root = deleteWithBranch(root);
				needToFixHeigh = true;
			}
	}
	if (root!=nullptr && needToFixHeigh) root = fixTheHeight(root, needToFixHeigh);

	return root;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::deleteWithBranch(BLACK_RED_TREE* root)
{
	BLACK_RED_TREE* result = nullptr;

	if (root->left != nullptr) result = root->left;
	else result = root->right;

	delete root;
	root = nullptr;

	return result;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::findMin(BLACK_RED_TREE* root)
{
	if (root->left != nullptr)  findMin(root->left);
	else return root;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::fixTheHeight(BLACK_RED_TREE* root, bool& isFixed)
{
	if ((root->color == RED && root->left && root->left->color == RED)) root->left->color = BLACK;

	if (root->left != nullptr && root->right != nullptr)
	{
		int hl = blackHeight(root->left), hr = blackHeight(root->right);

		if (hl < hr)
		{
			if (root->left->left == nullptr && root->left->right == nullptr)
			{
				if (root->left->color == RED)
				{
				root = root->leftTurn(root);
				root->left->flipColors(root->left);
				}
				else
				{
					BLACK_RED_TREE* q = root->right;
					q = q->rightTurn(q);
					root = root->leftTurn(root);
				}
			}
		}
		else 
			if (hl > hr)
			{
				if (root->right->left == nullptr && root->right->right == nullptr)
				{
					if (root->left->color == BLACK) root->left->color = RED;
					else
					{
						root->left->color = BLACK;
						root->leftTurn(root);
						if (root->right->left) root->right->left->color = RED;
					}
				}
				else root->right->left->color = BLACK;
				
			}
	}
	return root;
}



template<class T>
int BLACK_RED_TREE<T>::blackHeight(BLACK_RED_TREE* root)
{
	int hLeft = 0, hRight = 0, h = 0;
	if (root != nullptr)
	{
		if (root->left) hLeft = blackHeight(root->left);
		if (root->right) hRight = blackHeight(root->right);
		h = ((hLeft > hRight) ? hLeft : hRight);
		if (root->color == BLACK) h++;
	}
	return h;
}
