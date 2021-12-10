#pragma once
#include <iostream>
//Same rool in the black-red tree
//1)Main root - black
//2)Red root -> only two black knot
//	black root -> any knot
//3)leaf -> black
//4)Must be same number of black nodes from the root to  the leaves (black height)
//Inserted node is always colored red!

enum COLOR_BLACK_RED_TREE {BLACK,RED};

template <class T>
struct BLACK_RED_TREE
{
private:
	T value;
	COLOR_BLACK_RED_TREE color;
	BLACK_RED_TREE* parent;
	BLACK_RED_TREE* left;
	BLACK_RED_TREE* right;

protected:
	void repainting(BLACK_RED_TREE* root);
	
	BLACK_RED_TREE* leftTurn(BLACK_RED_TREE* root);
	BLACK_RED_TREE* rightTurn(BLACK_RED_TREE* root);

	void deleteRootWithLeftBranch(BLACK_RED_TREE*& root);
	void deleteRootWithRightBranch(BLACK_RED_TREE*& root);
	void deleteEnternalNode(BLACK_RED_TREE*& root);
	
	BLACK_RED_TREE* searchLeftReplacements(BLACK_RED_TREE* root);
	BLACK_RED_TREE* searchRightReplacements(BLACK_RED_TREE* root);
	
	BLACK_RED_TREE* searchSubTree(BLACK_RED_TREE* root, T elem);

public:
	BLACK_RED_TREE(T elem, COLOR_BLACK_RED_TREE Color = RED, BLACK_RED_TREE* parentTree = nullptr, BLACK_RED_TREE* leftTree = nullptr, BLACK_RED_TREE* rightTree = nullptr);
	~BLACK_RED_TREE();

	void insert(BLACK_RED_TREE*& root, T elem);
	BLACK_RED_TREE* removeElem(BLACK_RED_TREE*& root, T elem);
	void clearTree(BLACK_RED_TREE*& root);


	bool isElemInTree(BLACK_RED_TREE* root,T elem);
	
	int findHeightTree(BLACK_RED_TREE* root, int counter=0);

	void printTree(BLACK_RED_TREE* root,int count = 0);

	//void findPathMinimalRedRoot();
};

template<class T>
BLACK_RED_TREE<T>::BLACK_RED_TREE(T elem,COLOR_BLACK_RED_TREE Color, BLACK_RED_TREE* parentTree, BLACK_RED_TREE* leftTree, BLACK_RED_TREE* rightTree)
{
	value = elem;
	parent = parentTree;
	color = Color;
	left = leftTree;
	right = rightTree;
}

template<class T>
BLACK_RED_TREE<T>::~BLACK_RED_TREE()
{
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}



template<class T>
void BLACK_RED_TREE<T>::insert(BLACK_RED_TREE*& root, T elem) 
{
	static bool isFind = isElemInTree(root,elem);

	if (!isFind)
	{
		if (root != nullptr)
		{
			if (elem < root->value)
			{
				insert(root->left, elem);
				root->left->parent = root;
			}
			else
				if (elem > root->value)
				{
					insert(root->right, elem);
					root->right->parent = root;
				}
		}
		else root = new BLACK_RED_TREE(elem);
	}
}
 


template<class T>
void BLACK_RED_TREE<T>::clearTree(BLACK_RED_TREE*& root)
{
	if (root)
	{
		clearTree(root->left);
		clearTree(root->right);
		delete root;
		root = nullptr;
	}
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::removeElem(BLACK_RED_TREE*& root, T elem)
{
	if (isElemInTree(root, elem))
	{
		BLACK_RED_TREE* current = root->searchSubTree(root, elem);

		if (current->left != nullptr && current->right != nullptr) deleteEnternalNode(current);
		else
			if (current->right == nullptr)  deleteRootWithLeftBranch(current);
			else if (current->right != nullptr) deleteRootWithRightBranch(current);
		
	}

	return root;
}

template<class T>
void BLACK_RED_TREE<T>::deleteRootWithLeftBranch(BLACK_RED_TREE*& root)
{
	if (root->parent != nullptr)
	{
		if (root->parent->left->value == root->value) root->parent->left = root->left;
		else root->parent->right = root->left;

		if(root->left != nullptr) root->left->parent = root->parent;

		delete root;
		root = nullptr;
	}
	else
	{
		BLACK_RED_TREE* dop = root;
		root = root->left;
		
		delete dop;
		dop = nullptr;
	}
	
}

template<class T>
void BLACK_RED_TREE<T>::deleteRootWithRightBranch(BLACK_RED_TREE*& root)
{
	 if (root->parent != nullptr)
	 {
		if (root->parent->right->value == root->value) root->parent->right = root->right;
		else root->parent->left = root->right;

		if(root->right != nullptr) root->right->parent = root->parent;

		delete root;
		root = nullptr;
	 }
	 else
	 {
		 BLACK_RED_TREE* dop = root;
		 root = root->right;

		 delete dop;
		 dop = nullptr;
	 }
}

template<class T>
void BLACK_RED_TREE<T>::deleteEnternalNode(BLACK_RED_TREE*& root)
{
	BLACK_RED_TREE* dop = searchLeftReplacements(root->left);

	root->color = dop->color;
	root->value = dop->value;

	deleteRootWithLeftBranch(dop);
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::searchLeftReplacements(BLACK_RED_TREE* root)
{
	while (root->right != nullptr)
		root=root->right;
	return root;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::searchRightReplacements(BLACK_RED_TREE* root)
{
	while (root->left != nullptr)
		root = root->left;
	return root;
}



template<class T>
bool BLACK_RED_TREE<T>::isElemInTree(BLACK_RED_TREE* root, T elem)
{
	 bool isFind = false;

	 while ((root != nullptr) && (!isFind))
		 if (root->value != elem)
			 if (elem > root->value) root = root->right;
			 else root = root->left;
		 else isFind = true;

	 return isFind;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::searchSubTree(BLACK_RED_TREE* root, T elem)
{
	 bool isFind = false;

	 while ((root != nullptr) && (!isFind))
		 if (root->value != elem)
			 if (elem > root->value) root = root->right;
			 else root = root->left;
		 else isFind = true;

	 return root;
}

template<class T>
int BLACK_RED_TREE<T>::findHeightTree(BLACK_RED_TREE* root, int counter)
{
	static int maxHeight = 0;

	if (root != nullptr)
	{
		counter++;

		if (maxHeight < counter) maxHeight = counter;

		if (root->left != nullptr) findHeightTree(root->left, counter);
		if (root->right != nullptr) findHeightTree(root->right, counter);

	}
	return maxHeight;
}



template<class T>
void BLACK_RED_TREE<T>::printTree(BLACK_RED_TREE* root,int count)
{	 
	if (root->left != nullptr) printTree(root->left,count+1);

	for (size_t i = 0; i < count; i++)
		std::cout << "\t";

	std::cout << root->value<<"[" << root->color<<"]"<< "->{" << "\n";

	if (root->right != nullptr)	printTree(root->right,count+1);

	count--;
}


template<class T>
void BLACK_RED_TREE<T>::repainting(BLACK_RED_TREE* root)  //TODO
{
	root->color = BLACK;
	if (root->left == nullptr && root->right == nullptr)
	{

	}
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::leftTurn(BLACK_RED_TREE* root)
{
	BLACK_RED_TREE* newRoot = root;

	if (root->right != nullptr)
	{
		newRoot = root->right;
		root->right = newRoot->left;
		newRoot->left = root;

		newRoot->parent = nullptr;
		root->parent = newRoot;
		root->right->parent = root;
	}

	return newRoot;
}

template<class T>
BLACK_RED_TREE<T>* BLACK_RED_TREE<T>::rightTurn(BLACK_RED_TREE* root)
{
	BLACK_RED_TREE* newRoot = root;

	if (root->left != nullptr)
	{
		newRoot = root->left;
		root->left = newRoot->right;
		newRoot->right = root;

		newRoot->parent = nullptr;
		root->parent = newRoot;
		root->left->parent = root;
	}

	return newRoot;
}