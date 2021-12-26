#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
	BinarySearchTree t;
	
	int arr[] = { 107,59,14,2,17,702,8,35 };

	cout << "Kasatkin Andrey gr.0309" << endl;

	cout << "\nOrder of adding to three: " << endl;
	for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << ' ';
	cout << endl;

	for (size_t i = 0; i < sizeof(arr) / sizeof(int); i++)
		t.insert(arr[i]);

	cout << "\nDepth traversing: " << endl;
	DepthIterator di = t.create_dft_iterator();

	for (di; di.has_next(); di.next())
		cout << di.get_value() << ' ';
	cout << endl;


	cout << "\nBreadth traversing: " << endl;
	BreadthIterator bi = t.create_bft_iterator();

	for (bi; bi.has_next(); bi.next())
		cout << bi.get_value() << ' ';

	cout << endl;

	BinarySearchTree t2(t);

	cout << "\nDepth traversing: " << endl;

	di = t2.create_dft_iterator();

	for (di; di.has_next(); di.next())
		cout << di.get_value() << ' ';
	cout << endl;

	cout <<  "\nBreadth traversing: " << endl;
	bi = t2.create_bft_iterator();

	for (bi; bi.has_next(); bi.next())
		cout << bi.get_value() << ' ';

	cout << endl;

	return 0;
}