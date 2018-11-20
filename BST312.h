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

//Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
//Preconditions: BST has been initialized.
//Postconditions: none
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

//inserts an item to the binary tree
//preconditions: must not insert the ones that are already in the binary tree
//postcondition: none
    void insertItem(TreeNode*& t, const ItemType& newItem);

//Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
//Preconditions: BST has been initialized
//Postconditions: none
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;

 //   Function: Counts the number of nodes in the BST
 //   Preconditions: BST has been initialized.
 //   Postconditions: returns the number of nodes in the BST
    int countNodes(TreeNode* t) const;

//    Function: Removes target from BST.
//    Preconditions: BST has been initialized.
//    Postconditions: If found, element has been removed from BST.
    void deleteNode(TreeNode*& node);

//Function: Removes all the items from the BST.
//Preconditions: BST has been initialized
//Postconditions: All the items have been removed
    void makeEmpty(TreeNode*& t);

//Function: Removes target from BST.
//Preconditions: BST has been initialized.
//Postconditions: If found, element has been removed from BST.
    void deleteItem(TreeNode*& t, const ItemType& newItem);

//gets the largest number on the left subtree
//preconditions: tree has been initialized
//postconditions: saves the largest number on data
    void getPredecessor(TreeNode* t, ItemType& data);

 //Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
 //Preconditions: BST has been initialized.
 //Postconditions: none
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;

  //Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
  //Preconditions: BST has been initialized.
  //Postconditions: none
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;

 //Function: copies one tree onto a new one
 //Preconditions: BST has been initialized.
 //Postconditoins: none
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

 //Function: Counts the number of nodes in the BST
 //Preconditions: BST has been initialized.
 //Postconditions: returns the number of nodes in the BST
    int countNodesHelper(TreeNode* t, int counter) const;

//Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
//Preconditions: BST has been initialized.
//Postconditions: none
    void preOrderHelper(TreeNode* t,vector<ItemType>& result) const;

 //Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
 //Preconditions: BST has been initialized.
 //Postconditions: none
    void inOrderHelper(TreeNode* t,vector<ItemType>& result) const;

 //Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
 //Preconditions: BST has been initialized.
 //Postconditions: none
    void postOrderHelper(TreeNode* t,vector<ItemType>& result) const;
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


//[not written by you]
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
    if (t==NULL) {                             //if tree is empty
        TreeNode *goIn = new TreeNode;     //allocate space for node
        goIn->data = newItem;           //set data
        goIn->left = NULL;              //set left pt
        goIn->right = NULL;             //set right pt
        t = goIn;                      //initialize root to new node
    }
    else if (!isFull()) {
        if (newItem < t->data) {                //if item is less than current node
            if (t->left == NULL) {              //if you can insert a new node
                TreeNode *goIn = new TreeNode;      //allocate space for node
                goIn->data = newItem;           //initialize data of new node
                goIn->left = NULL;              //initialize left pt of new node
                goIn->right = NULL;             //initialize right pt of new node
                t->left = goIn;                 //link tree with node
            } else { insertItem(t->left, newItem); }        //else keep looking for a place to insert new node
        } else if (newItem > t->data) {         //if item is bigger than current node
            if (t->right == NULL) {             //if you can insert a new node
                TreeNode *goIn = new TreeNode;      //allocate space for node
                goIn->data = newItem;           //initialize data of new node
                goIn->left = NULL;              //initialize left pt of new node
                goIn->right = NULL;             //initialize right pt of new node
                t->right = goIn;                //link tree with node
            } else { insertItem(t->right, newItem); }       //else keep looking for a place to insert new node
        } else if (newItem == t->data) {
            return;                             //if the same do nothing
        }
    }
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem);
}

template<class ItemType>
int BST_312 <ItemType>::countNodesHelper(TreeNode* t, int counter)const
{
    if(t->left==NULL && t->right==NULL){                //if node with no children
        counter++;                                      //increment counter and return it
        return counter;
    }
    if(t->left!=NULL){                                  //if left is not NULL then....
        counter=countNodesHelper(t->left, counter);    //..keep going left
    }
    if(t->right!=NULL){                                 //if right is not NULL then....
        counter=countNodesHelper(t->right, counter);   //..keep going right
    }
    counter++;                                          //once you finished going right and left increment counter
    return counter;                                     //return counter updated
}

template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    int NodeNumbers=0;
    if(isEmpty()){return NodeNumbers;}                  //base case
    else{return countNodesHelper(t, NodeNumbers);}      //recursively count the nodes
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    return (countNodes(root));           //start counting from the root
}

template<class ItemType>
void BST_312 <ItemType>::preOrderHelper(TreeNode* t,vector<ItemType>& result) const{
    if(t!=NULL){
        result.push_back(t->data);            //first the node
    }
    if(t->left!=NULL){
        preOrderHelper(t->left, result);    //then go left node
    }
    if(t->right!=NULL){
        preOrderHelper(t->right, result);       //finally go right node
    }
    return;
}


template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    result.resize(0);
    int nodesnumber=countNodes(t);      //count the number of nodes
    if(nodesnumber==0){                 //base case
        return;
    } else {
        preOrderHelper(t, result);      //other cases solved recursively
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> preOrder;              //declare vector with results
    preOrderTraversal(root, preOrder);      //call to start traversal from root and fill vector
    return preOrder;                        //return vector with results
}

template<class ItemType>
void BST_312 <ItemType>::inOrderHelper(TreeNode* t,vector<ItemType>& result) const{
    if(t->left == NULL && t->right==NULL){          //when you reach a leave
        result.push_back(t->data);
        return;
    }
    if(t->left != NULL){                            //go left and ...
        inOrderHelper(t->left, result);             //...keep going left
    }
    result.push_back(t->data);                      //push the middle node
    if(t->right !=NULL){                            //go right and...
        inOrderHelper(t->right, result);            // keep going right
    }
}


template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    result.resize(0);                   //initialize vector
    int nodesnumber=countNodes(t);      //count the number of nodes
    if(nodesnumber==0){
        return;                         //base case
    } else {
        inOrderHelper(t, result);       //other cases solved recursively
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> inOrder;              //declare vector with results
    inOrderTraversal(root, inOrder);      //call to start traversal from root and fill vector
    return inOrder;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderHelper(TreeNode* t,vector<ItemType>& result) const{
    if(t->left == NULL && t->right==NULL){
        result.push_back(t->data);
        return;
    }
    if(t->left != NULL){
        postOrderHelper(t->left, result);     //keep going left...
    }
    if(t->right!=NULL){             //goes right...
        postOrderHelper(t->right, result);        //keeps going right and start checking left again
    }
    result.push_back(t->data);
    return;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    result.resize(0);                   //initialize vector
    int nodesnumber= countNodes(t);      //count the number of nodes
    if(nodesnumber==0){
        return;                         //base case
    } else {
        postOrderHelper(t, result);       //other cases solved recursively
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> postOrder;              //declare vector with results
    postOrderTraversal(root, postOrder);      //call to start traversal from root and fill vector
    return postOrder;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
    vector<ItemType> vectortree;                //initialize vector
    vectortree=postOrderTraversal();            //tranverse the tree
    int flag=0;
    for(flag=0; flag<vectortree.size(); flag++){
        if(vectortree[flag]==item){             //use the vector from tranverse to check if item is in the vector
            return true;
        }
    }
    return false;
}
#endif

