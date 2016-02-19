/*************************************************************
* Author:		Ian Murphy
* Filename:		TNode.h
* Date Created:	2/18/2016
* Modifications:	2/18/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: TNode
*
* Purpose: This class implements a node that is contained within the Binary Search Tree Class.
*
* Manager functions:
	TNode();
	TNode(TNode<T> * left, TNode<T> * right, T data);
	TNode(const TNode<T> & cp);
	~TNode();
	TNode<T> & operator = (const TNode<T> & rhs);

	virtual void SetLeft(TNode * left);
		sets the left child
	virtual void SetRight(TNode * right);
		sets the right child
	virtual TNode<T> *& GetLeft();
	virtual TNode<T> *& GetRight();
	virtual void SetKey(T key);
		sets the key
	virtual T GetKey();
		gets the key
*		...
*************************************************************************/

#ifndef TNode_h
#define TNode_h

template <typename T> class BSTree;
template <typename T> class AVLTree;
template <typename T>
class TNode
{
public:
    friend class BSTree<T>;
    friend class AVLTree<T>;
    
    TNode();
    TNode(TNode<T> * left, TNode<T> * right, T data);
    TNode(const TNode<T> & cp);
    ~TNode();
    TNode<T> & operator = (const TNode<T> & rhs);
    
    virtual void SetLeft(TNode * left);
    virtual void SetRight(TNode * right);
    virtual TNode<T> *& GetLeft();
    virtual TNode<T> *& GetRight();
    virtual void SetKey(T key);
    virtual T GetKey();
private:
    TNode<T> * _left;
    TNode<T> * _right;
    T _data;
};

/**********************************************************************
* Purpose: Default ctor
*
* Precondition:
*     
*
* Postcondition:
*      node is set correctly
*
************************************************************************/
template <typename T>
TNode<T>::TNode() : _left(nullptr), _right(nullptr)
{
    
}

/**********************************************************************
* Purpose: other ctor, allows settibng the node
*
* Precondition:
*
*
* Postcondition:
*      node is set correctly
*
************************************************************************/
template <typename T>
TNode<T>::TNode(TNode<T> * left, TNode<T> * right, T data): _left(left), _right(right), _data(data)
{
    
}

/**********************************************************************
* Purpose: copy ctor
*
* Precondition:
*
*
* Postcondition:
*      node is set correctly
*
************************************************************************/
template <typename T>
TNode<T>::TNode(const TNode<T> & cp) : _left(nullptr), _right(nullptr), _data(cp.data)
{
    
}

/**********************************************************************
* Purpose: dtor
*
* Precondition:
*
*
* Postcondition:
*      node is rekt correctly
*
************************************************************************/
template <typename T>
TNode<T>::~TNode()
{
    
}

/**********************************************************************
* Purpose: op = overload
*
* Precondition:
*
*
* Postcondition:
*      left is equal to right
*
************************************************************************/
template <typename T>
TNode<T> & TNode<T>::operator = (const TNode<T> & rhs)
{
    if(this != &rhs)
    {
        _left = nullptr;
        _right = nullptr;
        _data = rhs.data;
    }
    return *this;
}

/**********************************************************************
* Purpose: sets the left child
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
void TNode<T>::SetLeft(TNode * left)
{
    _left = left;
}

/**********************************************************************
* Purpose: sets the right child
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
void TNode<T>::SetRight(TNode * right)
{
    _right = right;
}

/**********************************************************************
* Purpose: gets the left child
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
TNode<T> *& TNode<T>::GetLeft()
{
    return _left;
}

/**********************************************************************
* Purpose: gets the right child
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
TNode<T> *& TNode<T>::GetRight()
{
    return _right;
}

/**********************************************************************
* Purpose: sets the data
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
void TNode<T>::SetKey(T key)
{
    _data = key;
}

/**********************************************************************
* Purpose: gets the data
*
* Precondition:
*		none
*
* Postcondition:
*		node is set correctly
*
************************************************************************/
template <typename T>
T TNode<T>::GetKey()
{
    return _data;
}

#endif /* TNode_h */
