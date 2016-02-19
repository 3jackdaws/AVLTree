/*************************************************************
* Author:		Ian Murphy
* Filename:		AVLNode.h
* Date Created:		2/18/2016
* Modifications:	2/18/16 - Added documentation
*
**************************************************************/

/************************************************************************
* Class: AVLNode
*
* Purpose: This class implements an AVLNode that inherits from TNode.
*
* Manager functions:
* 	AVLNode();
    AVLNode(AVLNode<T> * left, AVLNode<T> * right, T data);
	AVLNode(const AVLNode<T> & cp);
	~AVLNode();
	AVLNode<T> & operator = (const AVLNode<T> & rhs );
    Balance GetBalance();
		gets the balance by value
    void SetBalance(Balance val);
		sets the balance
    Balance & Balance();
		returns the balance by reference so it can be manipulated directly
*		...
*************************************************************************/

#ifndef AVLNode_h
#define AVLNode_h
#include "TNode.h"

enum Balance
{
    LH, EH, RH
};

template <typename T> class AVLTree;

template <typename T>
class AVLNode : public TNode<T>
{
    friend class AVLTree<T>;
public:
    AVLNode();
    AVLNode(AVLNode<T> * left, AVLNode<T> * right, T data);
	AVLNode(const AVLNode<T> & cp);
	~AVLNode();
	AVLNode<T> & operator = (const AVLNode<T> & rhs );
    Balance GetBalance();
    void SetBalance(Balance val);
    Balance & Balance();
private:
    
    enum Balance _balance;
};

/**********************************************************************
* Purpose: This is a default ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      sets up an AVLNode object so that it isn't filled with garbage
*
************************************************************************/
template <typename T>
AVLNode<T>::AVLNode() : _balance(EH)
{
    
}

/**********************************************************************
* Purpose: This is a three arg ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      sets up an AVLNode object so that can have three values set on instatiation
*
************************************************************************/
template <typename T>
AVLNode<T>::AVLNode(AVLNode<T> * left, AVLNode<T> * right, T data) : _balance(EH), TNode<T>(left, right, data)
{
 
}

/**********************************************************************
* Purpose: This is a copy ctor.
*
* Precondition:
*     None
*
* Postcondition:
*      copies 
*
************************************************************************/
template <typename T>
AVLNode<T>::AVLNode(const AVLNode<T> & cp) : _balance(cp._balance), TNode<T>(nullptr, nullptr, cp._data)
{

}

/**********************************************************************
* Purpose: Dtor
*
* Precondition:
*     None
*
* Postcondition:
*      destroys the object
*
************************************************************************/
template <typename T>
AVLNode<T>::~AVLNode()
{

}

/**********************************************************************
* Purpose: Operator = overload
*
* Precondition:
*     None
*
* Postcondition:
*      allows the redefinition of an object by assigning the values of the right object
*
************************************************************************/
template <typename T>
AVLNode<T> & AVLNode<T>::operator = (const AVLNode<T> & rhs)
{
	if (this != &rhs)
	{
		_left = nullptr;
		_right = nullptr;
		_data = rhs._data;
		_balance = rhs._balance;
	}
	return *this;
}

/**********************************************************************
* Purpose: Gets the balance
*
* Precondition:
*     None
*
* Postcondition:
*      returns the balance by value
*
************************************************************************/
template <typename T>
Balance AVLNode<T>::GetBalance()
{
    return _balance;
}

/**********************************************************************
* Purpose: sets the balance.
*
* Precondition:
*     None
*
* Postcondition:
*      balanace is set to the passed in value
*
************************************************************************/
template <typename T>
void AVLNode<T>::SetBalance(enum Balance val)
{
    _balance = val;
}

/**********************************************************************
* Purpose: Returns the balance by reference so that it can be directly manipulated
*
* Precondition:
*     None
*
* Postcondition:
*      returns balance by ref
*
************************************************************************/
template <typename T>
Balance & AVLNode<T>::Balance()
{
    return _balance;
}
#endif /* AVLNode_h */
