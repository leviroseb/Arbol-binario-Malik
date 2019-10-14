#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>

using namespace std;

template <class elemType>
struct AVLNode
{
    elemType info;
    int bfactor; // balance factor
    AVLNode<elemType> *llink;
    AVLNode<elemType> *rlink;
};

//Definition of the class
template <class elemType>
class binaryTreeType {
    public:
        const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>&);
        //Overload the assignment operator.

        bool isEmpty() const;
        //Returns true if the binary tree is empty;
        //otherwise, returns false.

        void inorderTraversal() const;
        //Function to do an inorder traversal of the binary tree.
        
        void inorderTraversal(void (*visit) (elemType&));
        //Function to do an inorder traversal of the binary tree.
        //The parameter visit, which is a function, specifies the
        //action to be taken at each node.

        void preorderTraversal() const;
        //Function to do a preorder traversal of the binary tree.

        void postorderTraversal() const;
        //Function to do a postorder traversal of the binary tree.

        int treeHeight() const;
        //Returns the height of the binary tree.

        int treeNodeCount() const;
        //Returns the number of nodes in the binary tree.

        int treeLeavesCount() const;
        //Returns the number of leaves in the binary tree.

        void destroyTree();
        //Deallocates the memory space occupied by the binary tree.
        //Postcondition: root = NULL;

        binaryTreeType(const binaryTreeType<elemType>& otherTree);
        //copy constructor

        binaryTreeType();
        //default constructor

        ~binaryTreeType();
        //destructor

    protected:
        AVLNode<elemType> *root;

    private:
        void copyTree(AVLNode<elemType>* &copiedTreeRoot, AVLNode<elemType>* otherTreeRoot);
        //Makes a copy of the binary tree to which
        //otherTreeRoot points. The pointer copiedTreeRoot
        //points to the root of the copied binary tree.

        void destroy(AVLNode<elemType>* &p);
        //Function to destroy the binary tree to which p points.
        //Postcondition: p = NULL

        void inorder(AVLNode<elemType> *p) const;
        //Function to do an inorder traversal of the binary
        //tree to which p points.

        void preorder(AVLNode<elemType> *p) const;
        //Function to do a preorder traversal of the binary
        //tree to which p points.

        void postorder(AVLNode<elemType> *p) const;
        //Function to do a postorder traversal of the binary
        //tree to which p points.

        int height(AVLNode<elemType> *p) const;
        //Function to return the height of the binary tree
        //to which p points.

        int max(int x, int y) const;
        //Returns the larger of x and y.

        int nodeCount(AVLNode<elemType> *p) const;
        //Function to return the number of nodes in the binary
        //tree to which p points

        int leavesCount(AVLNode<elemType> *p) const;
        //Function to return the number of leaves in the binary
        //tree to which p points
        
        void inorder(AVLNode<elemType> *p, void (*visit) (elemType&));
        //Function to do an inorder traversal of the binary
        //tree, starting at the node specified by the parameter p.
        //The parameter visit, which is a function, specifies the
        //action to be taken at each node.
};


template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
    return (root == NULL);
}

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
    root = NULL;
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
    inorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
    preorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
    postorder(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
    return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class elemType>
void binaryTreeType<elemType>::inorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        inorder(p->llink);
        cout << p->info << " ";
        inorder(p->rlink);
    }
}

template <class elemType>
void binaryTreeType<elemType>::preorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        cout << p->info << " ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}

template <class elemType>
void binaryTreeType<elemType>::postorder(AVLNode<elemType> *p) const
{
    if (p != NULL)
    {
        postorder(p->llink);
        postorder(p->rlink);
        cout << p->info << " ";
    }
}

template <class elemType>
int binaryTreeType<elemType>::height(AVLNode<elemType> *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->llink), height(p->rlink));
}

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}

template <class elemType>
void binaryTreeType<elemType>::copyTree(AVLNode<elemType>* &copiedTreeRoot, AVLNode<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == NULL)
        copiedTreeRoot = NULL;
    else
    {
        copiedTreeRoot = new AVLNode<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->llink, otherTreeRoot->llink);
        copyTree(copiedTreeRoot->rlink, otherTreeRoot->rlink);
    }
} //end copyTree

template <class elemType>
void binaryTreeType<elemType>::destroy(AVLNode<elemType>* &p)
{
    if (p != NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
    }
}

template <class elemType>
void binaryTreeType<elemType>::destroyTree()
{
    destroy(root);
}

//copy constructor
template <class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
    if (otherTree.root == NULL) //otherTree is empty
       root = NULL;
    else
       copyTree(root, otherTree.root);
}

//destructor
template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
    destroy(root);
}

//overloading the assignment operator
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
    if (this != &otherTree) //avoid self-copy
    {
        if (root != NULL) //if the binary tree is not empty,
            //destroy the binary tree
            destroy(root);
        if (otherTree.root == NULL) //otherTree is empty
            root = NULL;
        else
            copyTree(root, otherTree.root);
    }//end else
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal(void (*visit) (elemType& item))
{
    inorder(root, *visit);
}

template <class elemType>
void binaryTreeType<elemType>::inorder(AVLNode<elemType>* p, void (*visit) (elemType& item))
{
    if (p != NULL)
    {
        inorder(p->llink, *visit);
        (*visit)(p->info);
        inorder(p->rlink, *visit);
    }
}

#endif // BINARYTREE_H

