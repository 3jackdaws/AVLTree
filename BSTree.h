/*************************************************************
* Author:		Ian Murphy
* Filename:		Array.h
* Date Created:	2/18/2016
* Modifications:	2/18/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: BSTree
*
* Purpose: This class implements a Binary Search Tree.
*
* Manager functions:
*	BSTree();
    BSTree(const BSTree & cp);
    ~BSTree();
    BSTree & operator = (const BSTree & rhs);
    
    virtual void Insert(T data);
		Inserts data correctly into tree
    virtual bool Delete(T data);
		Deletes the data passed in
    virtual void Purge();
		Deletes all nodes in the tree
    int Height();
		returns the height of the tree
    virtual void InOrderTraverse(void (*func)(T));
		traverses in order
    virtual void PreOrderTraverse(void (*func)(T));
		traverses in preorder
    virtual void PostOrderTraverse(void (*func)(T));
		traverses in post order
    virtual void BreadthFirstTraverse(void (*func)(T));
		ttraverses level by level
*		...
*************************************************************************/

#ifndef BSTree_h
#define BSTree_h

#include <queue>
#include "TNode.h"

template <typename T>
class BSTree
{
public:
    BSTree();
    BSTree(const BSTree & cp);
    ~BSTree();
    BSTree & operator = (const BSTree & rhs);
    
    virtual void Insert(T data);
    virtual bool Delete(T data);
    virtual void Purge();
    int Height();
    
    virtual void InOrderTraverse(void (*func)(T));
    virtual void PreOrderTraverse(void (*func)(T));
    virtual void PostOrderTraverse(void (*func)(T));
    virtual void BreadthFirstTraverse(void (*func)(T));
protected:
    void InOrderTraverse(TNode<T> * current_root, void (*func)(T));
    void PreOrderTraverse(TNode<T> * current_root, void (*func)(T));
    void PostOrderTraverse(TNode<T> * current_root, void (*func)(T));
    void BreadthFirstTraverse(TNode<T> * current_root, void (*func)(T));
    virtual bool Put(TNode<T> *& current_root, T & data);
    int Height(TNode<T> * current_root);
    virtual TNode<T> * Delete(TNode<T> *& current_root, T & data);
    void Unlink(TNode<T> * current_root);
    
    TNode<T> * _root;
};

/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      sets up an BSTree object so that it isn't filled with garbage
*
************************************************************************/
template <typename T>
BSTree<T>::BSTree() : _root(nullptr)
{
    
}

/**********************************************************************
* Purpose: constructs an BSTree object from another BSTree object
*
* Precondition:
*     cp should prolly be an BSTree object
*
* Postcondition:
*      There is now an identical BSTree object to the one passed in
*
************************************************************************/
template <typename T>
BSTree<T>::BSTree(const BSTree<T> & cp) : _root(nullptr)
{
    std::queue<TNode<T> *> queue;
    TNode<T> * current_node;
    queue.push(cp._root);
    while(!queue.empty())
    {
        current_node = queue.front();
        queue.pop();
        Insert(current_node->_data);
        if(current_node->_left)
        {
            queue.push(current_node->_left);
        }
        if(current_node->_right)
        {
            queue.push(current_node->_right);
        }
    }

}

/**********************************************************************
* Purpose: This looks like a destructor.
*
* Precondition:
*     Needs to be within valid object
*
* Postcondition:
*      deletes all newed memory
*
************************************************************************/
template <typename T>
BSTree<T>::~BSTree()
{
    Purge();
}

/**********************************************************************
* Purpose: Sets an already instantiated object to the values of another similar object.
*
* Precondition:
*     Needs two instantiated objects
*
* Postcondition:
*      the object on the left side of the = operator is now the same as the object on the right side
*
************************************************************************/
template <typename T>
BSTree<T> & BSTree<T>::operator = (const BSTree & rhs)
{
    if(this != &rhs)
    {
        Purge();
        std::queue<TNode<T> *> queue;
        TNode<T> * current_node;
        queue.push(rhs._root);
        while(!queue.empty())
        {
            current_node = queue.front();
            queue.pop();
            Insert(current_node->_data);
            if(current_node->_left)
            {
                queue.push(current_node->_left);
            }
            if(current_node->_right)
            {
                queue.push(current_node->_right);
            }
        }

    }
    return *this;
}

/**********************************************************************
* Purpose: Deletes every node in the tree
*
* Precondition:
*     noen
*
* Postcondition:
*      all newed memory is deleted and the tree will now contain zero nodes
*
************************************************************************/
template <typename T>
void BSTree<T>::Purge()
{
    if(_root)
        Unlink(_root);
    _root = nullptr;
}

/**********************************************************************
* Purpose: Used to delete all nodes in a way that allows chaining all the way back up to the root
*
* Precondition:
*     needs to be called on a valid node
*
* Postcondition:
*      the node is deleted and Unlink is called on all the child nodes
*
************************************************************************/
template <typename T>
void BSTree<T>::Unlink(TNode<T> * current_root)
{
    if(current_root->_left)
        Unlink(current_root->_left);
    if(current_root->_right)     //left
        Unlink(current_root->_right);
    delete current_root;
    current_root = nullptr;
}

/**********************************************************************
* Purpose: Public insert method
*
* Precondition:
*     data must eb valid
*
* Postcondition:
*      calls put and inserts the node
*
************************************************************************/
template <typename T>
void BSTree<T>::Insert(T data)
{
    Put(_root, data);
}


/**********************************************************************
* Purpose: Corerectly inserts a node in place
*
* Precondition:
*     idk
*
* Postcondition:
*      Inserts node
*
************************************************************************/
template <typename T>
bool BSTree<T>::Put(TNode<T> *& current_root, T & data)
{
    int rval = -1;
    if(!current_root)
    {
        current_root = new TNode<T>(nullptr, nullptr, data);
        rval = 0;
    }
    else if(data <= current_root->_data)     //left
    {
        Put(current_root->_left, data);
    }
    else                                    //right
    {
        Put(current_root->_right, data);
    }
    return rval;
}

/**********************************************************************
* Purpose: Public delete method
*
* Precondition:
*     none
*
* Postcondition:
*      returns true if the data was found and deleted
*
************************************************************************/
template <typename T>
bool BSTree<T>::Delete(T data)
{
    _root = Delete(_root, data);
    return true;
}

/**********************************************************************
* Purpose: Actuallly deletes an object
*
* Precondition:
*     must be called on a valid root
*
* Postcondition:
*      deletes the data
*
************************************************************************/
template <typename T>
TNode<T> * BSTree<T>::Delete(TNode<T> *& current_root, T & data)
{
    TNode<T> * rval = nullptr;
    if (current_root == nullptr);
    else if (data == current_root->_data)
    {
        // current_root is the node to be removed
        if (current_root->_left == nullptr && current_root->_right == nullptr)
        {
            rval = nullptr;
            delete current_root;
            current_root = nullptr;
        }
        else if (current_root->_left == nullptr)
        {
            rval = current_root->_right;
            delete current_root;
            current_root = nullptr;
        }
        else if (current_root->_right == nullptr)
        {
            rval = current_root->_left;
            delete current_root;
            current_root = nullptr;
        }
        else
        {
            TNode<T> * temp = current_root->_right;
            while(temp && temp->_left)
            {
                temp = temp->_left;
            }
            current_root->_data = temp->_data;
          
            current_root->_right = Delete(current_root->_right, temp->_data );
            
            rval = current_root;
        }
        
    }
    else if (data < current_root->_data)
    {
        current_root->_left = Delete(current_root->_left, data);
        rval = current_root;
    }
    else {
        current_root->_right = Delete(current_root->_right, data);
        rval = current_root;
    }
    return rval;
}

/**********************************************************************
* Purpose: Traverses the tree and applies the passed function in order
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::InOrderTraverse(void (*func)(T))
{
    InOrderTraverse(_root, func);
}

/**********************************************************************
* Purpose: Traverses the tree and applies the passed function in pre order
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::PreOrderTraverse(void (*func)(T))
{
    PreOrderTraverse(_root, func);
}

/**********************************************************************
* Purpose: Traverses the tree and applies the passed function in post order
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::PostOrderTraverse(void (*func)(T))
{
    PostOrderTraverse(_root, func);
}

/**********************************************************************
* Purpose: Traverses the tree and applies the passed function in breadth first order
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::BreadthFirstTraverse(void (*func)(T))
{
    BreadthFirstTraverse(_root, func);
}

/**********************************************************************
* Purpose: Actual implementation of In order traverse
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::InOrderTraverse(TNode<T> * current_root, void (*func)(T))
{
    if(current_root)
    {
        if(current_root->_left)
            InOrderTraverse(current_root->_left, func);
        
        func(current_root->_data);
        
        if(current_root->_right)     //left
            InOrderTraverse(current_root->_right, func);
    }
}

/**********************************************************************
* Purpose: Actual implementation of pre order traverse
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::PreOrderTraverse(TNode<T> * current_root, void (*func)(T))
{
    if(current_root)
    {
        func(current_root->_data);
        if(current_root->_left)
            PreOrderTraverse(current_root->_left, func);
        if(current_root->_right)     //left
            PreOrderTraverse(current_root->_right, func);
    }
}

/**********************************************************************
* Purpose: Actual implementation of post order traverse
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::PostOrderTraverse(TNode<T> * current_root, void (*func)(T))
{
    if(current_root)
    {
        if(current_root->_left)
            PostOrderTraverse(current_root->_left, func);
        if(current_root->_right)     //left
            PostOrderTraverse(current_root->_right, func);
        func(current_root->_data);
    }
    
}

/**********************************************************************
* Purpose: Actual implementation of Breadth first traverse
*
* Precondition:
*     none
*
* Postcondition:
*      function passed in is applied to every piece of data in the tree
*
************************************************************************/
template <typename T>
void BSTree<T>::BreadthFirstTraverse(TNode<T> * current_root, void (*func)(T))
{
    std::queue<TNode<T> *> queue;
    TNode<T> * current_node;
    queue.push(current_root);
    while(!queue.empty())
    {
        current_node = queue.front();
        queue.pop();
        func(current_node->_data);
        if(current_node->_left)
        {
            queue.push(current_node->_left);
        }
        if(current_node->_right)
        {
            queue.push(current_node->_right);
        }
    }  
}

/**********************************************************************
* Purpose: Public height method
*
* Precondition:
*     none
*
* Postcondition:
*      returns the hieght of the entire tree
*
************************************************************************/
template <typename T>
int BSTree<T>::Height()
{
    return Height(_root);
}

/**********************************************************************
* Purpose: Actual implementation of height method
*
* Precondition:
*     none
*
* Postcondition:
*      returns the height of the current root
*
************************************************************************/
template <typename T>
int BSTree<T>::Height(TNode<T> * current_root)
{
    if(current_root)
    {
        int lheight = 0;
        int rheight = 0;
        if(current_root->_left)
        {
            lheight++;
            lheight += Height(current_root->_left);
        }
        if(current_root->_right)
        {
            rheight++;
            rheight += Height(current_root->_right);
        }
        if(lheight > rheight)
            return lheight;
        else
            return rheight;
    }
    else
        return -1;
}


#endif /* BSTree_h */