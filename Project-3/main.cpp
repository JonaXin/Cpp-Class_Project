#include<iostream>
#include "avl_tree.h"

using namespace std;

int main()
{
	
	AVLTree<int, int> avl;
	avl[14] = 14;
	avl[5] = 5;	
	avl[24] = 24;	
	avl[9] = 9;
	avl[6] = 6;

	/*
	AVLTree<char, string> avl;
	avl['g'] = "graph";
	avl['h'] = "hack";
	avl['i'] = "isolate";
	avl['j'] = "jack";
	avl['k'] = "king";
	avl['l'] = "lll";
	avl['m'] = "mmm";
	*/

	cout << "root is: " << avl.root()->key() << endl; 
	cout << "root's left is: " << avl.root()->left()->key() << endl;
	cout << "root's right is: " << avl.root()->right()->key() << endl;
	
	cout << "root's balance factor is " << avl.root()->balance_factor() << endl;
	cout << "root's left balance factor is " << avl.root()->left()->balance_factor() << endl;
	cout << "root's left left balance factor is " << avl.root()->left()->left()->balance_factor() << endl;
	cout << "root's height is " << avl.root()->height(avl.root()) << endl;
	cout << "root's left height is " << avl.root()->height(avl.root()->left()) << endl;
	cout << "root's left right height is " << avl.root()->height(avl.root()->left()->right()) << endl;
}