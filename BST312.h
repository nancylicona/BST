/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()       //constructor
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)     //copy constructor
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()       //destructor
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)           //IF original tree is empty..
        copy = NULL;                    //THEN copy tree is set as empty.
    else
    {
        copy = new TreeNode;            //create new tree..
        copy->data = originalTree->data;            //copy the data from node

        copyTree(copy->left, originalTree->left);   //recursively: copy all the left side of the original tree...
        copyTree(copy->right, originalTree->right); //...and then copy all the right side of the original tree.
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;            //set temporary to point to the node send

    if (t->left == NULL)            //assign pointer to the right node and delete present node
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)      //assign pointer to the left node and delete present node
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);          //get the info of the largest node in left subtree....
        t->data = info;                         //....info is store where the target delete node is.
        deleteItem(t->left, info);              //delete node with that was just obtain in getPredecessor
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)            //the right (which contains the largest node) does not equal NULL
        t = t->right;                   //continue going to the right

    data = t->data;                     //get the data of the largest in left subtree

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)  //transverse the tree from a starting node (t) to find the node that match the data to delete it
{
    if (t == NULL)
        return;                                 //no need to transverse the tree
    else if (newItem < t->data)                 //if data is smaller than current node, then...
        deleteItem(t->left, newItem);           //...go to the left where smaller data is located
    else if (newItem > t->data)                 //if data is larger than current node, then...
        deleteItem(t->right, newItem);          //...go to the right where larger data is located
    else
        deleteNode(t);                          //found node to delete
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)        //transverse the tree, starting from the node, to delete node in tree containing newItem data.
{
    deleteItem(root, newItem);              //call function to transverse the tree starting from node and then delete node with newItem data

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
     while(t->left!=NULL && t->right!=NULL) {         //while the root is not set as NULL
         deleteNode(t);            //delete the children and root
     }
     deleteNode(t);
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem) {
    if(!isFull()) {
        if (newItem < t->data) {
            if (t->left == NULL) {
                TreeNode *goIn = new TreeNode;
                goIn->data = newItem;
                goIn->left = NULL;
                goIn->right = NULL;
                t->left = goIn;
            } else { insertItem(t->left, newItem); }
        } else if (newItem > t->data) {
            if (t->right == NULL) {
                TreeNode *goIn = new TreeNode;
                goIn->data = newItem;
                goIn->left = NULL;
                goIn->right = NULL;
                t->right = goIn;
            } else { insertItem(t->right, newItem); }
        }
    }
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    if(!isEmpty()) {
        insertItem(root, newItem);
    } else {
        TreeNode *goIn = new TreeNode;
        goIn->data = newItem;
        goIn->left = NULL;
        goIn->right = NULL;
        root=goIn;
    }
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE

}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    countNodes(root);           //start counting from the root
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{

    //YOUR CODE GOES HERE
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{

  //YOUR CODE GOES HERE

}
#endif

