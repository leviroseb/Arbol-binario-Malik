#include <iostream>
#include <assert.h>
#include "binaryTree.h"
#include "bSearchTreeType.h"

void print(int &x);
void update(int &x);

using namespace std;

int main()
{
    bSearchTreeType<int> binarySearch;
   
	int num;
	cout << "Line 10: Enter numbers ending with -999" << endl;
	cin >> num;

	while(num != -999) {
		binarySearch.insert(num);
		cin >> num;
	}

	cout << endl << "Line 17: Tree nodes in inorder: ";
	binarySearch.inorderTraversal(print);
	
	cout << endl << "Line 19: Tree Height: " << binarySearch.treeHeight() << endl << endl;
	
	//binarySearch.deleteIntoAVL();
	
	cout << "Line 20: ******* Update Nodes *******" << endl;
	
	binarySearch.inorderTraversal(update);
	cout << "Line 22: Tree nodes in inorder after " << "the update: " << endl << "      ";
	
	binarySearch.inorderTraversal(print);
	cout << endl <<"Line 24: Tree Height: " << binarySearch.treeHeight() << endl;
    return 0;
	
//	cout<<"Eliminar: "<<deleteNode()<<endl;
//	binarySearch.inorderTraversal(print);	
}


void print( int & x)
{
	cout << x << " ";
} 

void update(int& x)
{
	x = 2 * x;
}

