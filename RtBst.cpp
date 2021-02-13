// RightThreadedBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Written By : R. Anush Narayanan.
Date: feb-12th-2021.
Content : This file contains the methods for inserting a node(Key and Value Pair) into a
right-threaded binary search tree(BST), printing the nodes at a level
'i' of the (BST) and de-allocating the nodes created.
*/
#include"pch.h"
#include <iostream>
#include<limits.h>

using namespace std;

template<typename KEY, typename T>
struct Elem
{
	KEY key;
	T data;
	Elem *left;
	Elem *right;
	bool rightThread; //normal right child link(false) or a threadlink(true)
	static Elem *_root;//dummy node
	static int _size;
	//Default constructor
	Elem() :data(INT_MAX), key(INT_MAX), left(NULL), right(NULL), rightThread(false)
	{
	}
	//parametrized constructor for creating the Elem object.
	Elem(KEY key, T data) : key(key), data(data), left(NULL),
		right(NULL), rightThread(true)
	{
		//_size++;
	}
	/*we overload the new and delete operator to update the size of the map i.e.,
	the number of nodes in BST.*/
	void * operator new(size_t sz) {
		_size++;
		return ::new Elem();
	}

	void operator delete(void *) {
		_size--;
	}
};

template<typename KEY, typename T>
Elem<KEY, T> * Elem<KEY, T>::_root = new Elem();

template<typename KEY, typename T>
int Elem<KEY, T>::_size = -1;//not including the dummy node.

/*If the key value pair is inserted successfully,
the insert function returns true, else it returns false.*/

template<typename KEY, typename T>
bool insert(Elem<KEY, T> *& root, const KEY &key, const T &data, Elem<KEY, T> *lastLeft = Elem<KEY, T>::_root) {
	//If there is no node still inserted 
	if (root == NULL) {

		Elem<KEY, T> *p = new Elem<KEY, T>(key, data);
		if (p != NULL)
		{
			root = p;
			root->right = lastLeft;
			root->rightThread = true;
			return (root)->rightThread;

		}
		else return false; //not able to insert the key value pair.
	}

	//If the value that is going to be inserted is lesser than the root's data
	if (key < root->key)
	{
		if (root->left == NULL)
		{
			Elem<KEY, T> *p = new Elem<KEY, T>(key, data);
			if (p != NULL)
			{
				root->left = p;
				p->right = root;//make the childs right pointer point to its inorder successor(root)
				p->rightThread = true;//therefore make the rightThread to be true for the child.
				return p->rightThread;

			}
			else return false; //not able to insert the key value pair.
		}
		return insert(root->left, key, data);
	}

	//If the value that is going to be inserted is greater than the root's data.
	else if (key > root->key)
	{
		if (root->rightThread)
		{
			Elem<KEY, T> *p = new Elem<KEY, T>(key, data);
			if (p != NULL)
			{
				p->right = root->right;//make the childs right pointer point to its inorder successor(root)
				root->right = p;
				p->rightThread = true;//therefore make the rightThread to be true for the child.
				root->rightThread = false;//root has got a right child therefore it is not a normal threadLink.
				return p->rightThread;

			}
			else return false;//Not able to insert the Key Value Pair.
		}
		return insert(root->right, key, data);
	}
	else return false;//duplicate keys are not allowed.
}

template<typename KEY, typename T>
void printTree(ostream& os, int level, Elem<KEY, T> *root)
{
	if (root == NULL || root == Elem<KEY, T>::_root)return;
	if (level == 0) {
		os << "KEY: " << root->key << " Data: " << root->data << endl;
		return;
	}
	printTree(os, level - 1, root->left);
	printTree(os, level - 1, root->right);
}

/*We perform a post order traversal and delete the nodes of the BST.*/
template<typename KEY, typename T>
void destructCode(Elem<KEY, T> *& root) {
	if (root == NULL || root == Elem<KEY, T>::_root)return;
	destructCode<KEY, T>(root->left);
	if(!root->rightThread)
		destructCode<KEY, T>(root->right);
	delete root;
}

int main()       
{
	Elem<int, int> *ptrToRoot = NULL;
	char ch;
	int choice;
	int key, data;/*here i have taken both the key and val to be int.
	but it will work fine for other kind of primitive data types as well.*/
	int level = 0;//the root node(not sentinel but the first ever node inserted.) is considered  to be at level 0.
	do
	{
		cout << "\nRightThreadedBinarySearchTree Operations\n";
		cout << "1. Insert " << endl;
		cout << "2. Print" << endl;
		cout << "3. Clear Right Threaded BST" << endl;
		cout << "4. see the size of the BST" << endl;
		cout << "Enter Your Choice: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Enter the key and value to  be inserted: ";
			cin >> key >> data;
			bool res = insert<int, int>(ptrToRoot, key, data);
			if (res)cout << "insert of key, value successful." << endl;
			else cout << "cannot allocate memory or duplicate is entered." << endl;
		}
		break;
		case 2:
		{
			cout << "Enter the level at which the nodes are present:" << endl;
			cin >> level;
			printTree<int, int>(std::cout, level, ptrToRoot);

		}
		break;
		case 3:
			destructCode<int, int>(ptrToRoot);
			break;
		case 4:
			cout << "The Size of the BST is : " << Elem<int, int>::_size << endl;
			break;
		default:
			cout << "Wrong Input" << endl;
			break;
		}
		cout << "Do you want to continue(enter y or Y to continue)?" << endl;
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	return 0;
}
