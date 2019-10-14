#ifndef BSEARCHTREETYPE_H
#define BSEARCHTREETYPE_H
#include <iostream>
#include "binaryTree.h"

using namespace std;

template <class elemType>
class bSearchTreeType : public binaryTreeType<elemType>
{
    public:

        bool search(const elemType& searchItem) const;
        //Function to determine if searchItem is in the binary
        //search tree.
        //Postcondition: Returns true if searchItem is found in the
        // binary search tree; otherwise, returns false.

        void insert(const elemType& insertItem);
        //Function to insert insertItem in the binary search tree.
        //Postcondition: If no node in the binary search tree has the
        // same info as insertItem, a node with the info insertItem
        // is created and inserted in the binary search tree.

        void deleteNode(const elemType& deleteItem);
        //Function to delete deleteItem from the binary search tree.
        //Postcondition: If a node with the same info as deleteItem
        // is found, it is deleted from the binary search tree.
        
        void rotateToLeft(AVLNode<elemType>* &root);
        
        void rotateToRight(AVLNode<elemType>* &root);
        
        void balanceFromLeft(AVLNode<elemType>* &root);
        
        void balanceFromRight(AVLNode<elemType>* &root);
        
        elemType deletemin (AVLNode<elemType>* &root);
        
        void deleteIntoAVL(AVLNode<elemType>* &root,const elemType& item);

    private:
        void deleteFromTree(AVLNode<elemType>* &p);
        //Function to delete the node to which p points is deleted
        //from the binary search tree.
        //Postcondition: The node to which p points is deleted from
        // the binary search tree.
        
        void insertIntoAVL(AVLNode<elemType>* &root, AVLNode<elemType> *newNode, bool& isTaller);
};

template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem) const
{
    AVLNode<elemType> *current;
    bool found = false;
    if (this->root == NULL)
        cerr << "Cannot search the empty tree." << endl;
    else
    {
        current = this->root;
        while (current != NULL && !found)
        {
            if (current->info == searchItem)
                found = true;
            else if (current->info > searchItem)
                current = current->llink;
            else
                current = current->rlink;
        }//end while
    }//end else
    return found;
}//end search

template <class elemType>
void bSearchTreeType<elemType>::rotateToLeft(AVLNode<elemType>* &root) {
    AVLNode<elemType> *p; //pointer to the root of the
    //right subtree of root
    if (root == NULL)
        cerr << "Error in the tree" << endl;
    else if (root->rlink == NULL)
        cerr << "Error in the tree:" <<" No right subtree to rotate." << endl;
    else {
        p = root->rlink;
        root->rlink = p->llink; //the left subtree of p becomes
        //the right subtree of root
        p->llink = root;
        root = p;
        //make p the new root node
    }
}//rotateLeft

template <class elemType>
void bSearchTreeType<elemType>::rotateToRight(AVLNode<elemType>* &root) {
    AVLNode<elemType> *p; //pointer to the root of
    //the left subtree of root
    if (root == NULL)
        cerr << "Error in the tree" << endl;
    else if (root->llink == NULL)
        cerr << "Error in the tree:" << " No left subtree to rotate." << endl;
    else {
        p = root->llink;
        root->llink = p->rlink; //the right subtree of p becomes
        //the left subtree of root
        p->rlink = root;
        root = p;
        //make p the new root node
    }
}//end rotateRight



template <class elemType>
void bSearchTreeType<elemType>::balanceFromLeft(AVLNode<elemType>* &root) {
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->llink;
    //p points to the left subtree of root
    switch (p->bfactor)
    {
        case -1:
            root->bfactor = 0;
            p->bfactor = 0;
            rotateToRight(root);
            break;
        case 0:
            cerr << "Error: Cannot balance from the left." << endl;
            break;
        case 1:
            w = p->rlink;
            switch (w->bfactor) //adjust the balance factors
            {
                case -1:
                    root->bfactor = 1;
                    p->bfactor = 0;
                    break;
                case 0:
                    root->bfactor = 0;
                    p->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = 0;
                    p->bfactor = -1;
            }//end switch
            w->bfactor = 0;
            rotateToLeft(p);
            root->llink = p;
            rotateToRight(root);
    }//end switch;
}//end balanceFromLeft

template <class elemType>
void bSearchTreeType<elemType>::balanceFromRight(AVLNode<elemType>* &root)
{
    AVLNode<elemType> *p;
    AVLNode<elemType> *w;
    p = root->rlink;
    //p points to the left subtree of root
    switch (p->bfactor)
    {
        case -1:
            w = p->llink;
            switch (w->bfactor) //adjust the balance factors
            {
                case -1:
                    root->bfactor = 0;
                    p->bfactor = 1;
                    break;
                case 0:
                    root->bfactor = 0;
                        p->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = -1;
                    p->bfactor = 0;
            }//end switch
            w->bfactor = 0;
            rotateToRight(p);
            root->rlink = p;
            rotateToLeft(root);
            break;
        case 0:
            cerr << "Error: Cannot balance from the left." << endl;
            break;
        case 1:
            root->bfactor = 0;
            p->bfactor = 0;
            rotateToLeft(root);
    }//end switch;
}//end balanceFromRight

template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& newItem)
{
    bool isTaller = false;
    AVLNode<elemType> *newNode;
    newNode = new AVLNode<elemType>;
    newNode->info = newItem;
    newNode->bfactor = 0;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    
    insertIntoAVL(this->root, newNode, isTaller);
}

template <class elemType>
void bSearchTreeType<elemType>::insertIntoAVL(AVLNode<elemType>* &root, AVLNode<elemType> *newNode, bool& isTaller) {
    if (root == NULL)
    {
        root = newNode;
        isTaller = true;
    }
    else if (root->info == newNode->info)
        cerr << "No duplicates are allowed." << endl;
    else if (root->info > newNode->info) //newItem goes in the left subtree
    {
        insertIntoAVL(root->llink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew in height
        switch (root->bfactor)
        {
            case -1:
                balanceFromLeft(root);
                isTaller = false;
                break;
            case 0:
                root->bfactor = -1;
                isTaller = true;
                break;
            case 1:
                root->bfactor = 0;
                isTaller = false;
        }//end switch
    }//end if
    else {
        insertIntoAVL(root->rlink, newNode, isTaller);
        if (isTaller) //after insertion, the subtree grew in height
        switch (root->bfactor) {
            case -1:
                root->bfactor = 0;
                isTaller = false;
                break;
            case 0:
                root->bfactor = 1;
                isTaller = true;
                break;
            case 1:
                balanceFromRight(root);
                isTaller = false;
        }//end switch
    }//end else
}//insertIntoAVL


/*
template <class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
    AVLNode<elemType> *current; //pointer to traverse the tree
    AVLNode<elemType> *trailCurrent; //pointer behind current
    AVLNode<elemType> *newNode; //pointer to create the node
    newNode = new AVLNode<elemType>;
    assert(newNode != nullptr);
    newNode->info = insertItem;
    newNode->llink = nullptr;
    newNode->rlink = nullptr;
    if (this->root == nullptr)
        this->root = newNode;
    else
    {
        current = this->root;
        while (current != nullptr)
        {
            trailCurrent = current;
            if (current->info == insertItem)
            {
                cerr << "The insert item is already in the list-";
                cerr << "duplicates are not allowed."
                << insertItem << endl;
                return;
            }
            else if (current->info > insertItem)
                current = current->llink;
            else
                current = current->rlink;
        }//end while
        if (trailCurrent->info > insertItem)
            trailCurrent->llink = newNode;
        else
            trailCurrent->rlink = newNode;
    }
}//end insert*/


template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree(AVLNode<elemType>* &p)
{
    AVLNode<elemType> *current;//pointer to traverse the tree
    AVLNode<elemType> *trailCurrent; //pointer behind current
    AVLNode<elemType> *temp; //pointer to delete the node
    if (p == NULL)
        cerr << "Error: The node to be deleted is nullptr." << endl;
    else if(p->llink == NULL && p->rlink == NULL)
    {
        temp = p;
        p = NULL;
        delete temp;
    } else if(p->llink == NULL)
    {
        temp = p;
        p = temp->rlink;
        delete temp;
    } else if(p->rlink == NULL)
    {
        temp = p;
        p = temp->llink;
        delete temp;
    } else
    {
        current = p->llink;
        trailCurrent = NULL;
        while (current->rlink != NULL)
        {
            trailCurrent = current;
            current = current->rlink;
        }//end while
        p->info = current->info;
        if (trailCurrent == NULL) //current did not move;
            //current == p->llink; adjust p
            p->llink = current->llink;
        else
            trailCurrent->rlink = current->llink;
        delete current;
    }//end else
}//end deleteFromTree

/*template <class elemType>
void bSearchTreeType<elemType>::deleteAVL(const elemType& itemE)
{
	deleteIntoAVL(this->root,itemE);
}

template <class elemType>
void bSearchTreeType<elemType>::deleteIntoAVL(AVLNode<elemType>* &root,const elemType& item)
{
	AVLNode<elemType> *p;
	if(root == NULL)
	{
		cerr<<"No existe el arbol";
	}
	else
	{
		if(item==root->info)
		{
			delete root;
			root = 0;
		}
	
	else
	{
		if(item<root->info)
		{
			deleteIntoAVL(root->llink,item);
		}
		else if(item > root->info)
		{
			deleteIntoAVL(root->rlink,item);
		}
		else if((root->llink==NULL) && (root->rlink==NULL))
		{
			p=root;
			delete p;
			root=NULL;
		}
		else if(root->llink==NULL)
		{
			p=root;
			delete p;
			root=root->rlink;
		}
		else if(root->rlink==NULL)
		{
			p=root;
			delete p;
			root=root->llink;
		}
		else
			root->info=deletemin(root->rlink);
	}
}
}

template <class elemType>
elemType bSearchTreeType<elemType>::deletemin(AVLNode<elemType>* &p)
{
	elemType c;
	cout<<endl;
	if(p->llink==NULL)
	{
		c=p->info;
		p=p->rlink;
		return c;
	}
	else
	{
		c=deletemin(p->llink);
		return c;
	}
}
*/
template <class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
    AVLNode<elemType> *current; //pointer to traverse the tree
    AVLNode<elemType> *trailCurrent; //pointer behind current
    bool found = false;
    if (this->root == NULL)
        cout << "Cannot delete from the empty tree." << endl;
    else
    {
        current = this->root;
        trailCurrent = this->root;
        while (current != NULL && !found)
        {
            if (current->info == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                if (current->info > deleteItem)
                    current = current->llink;
                else
                    current = current->rlink;
            }
        }//end while
        if (current == NULL)
            cout << "The delete item is not in the tree." << endl;
        else if (found)
        {
            if (current == this->root)
                deleteFromTree(this->root);
            else if (trailCurrent->info > deleteItem)
                deleteFromTree(trailCurrent->llink);
            else
                deleteFromTree(trailCurrent->rlink);
        }//end if
    }
}//end deleteNode


#endif // BSEARCHTREETYPE_H
