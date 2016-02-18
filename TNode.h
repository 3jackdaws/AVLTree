//
//  TNode.h
//  AVL Tree
//
//  Created by Ian Murphy on 2/16/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

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

template <typename T>
TNode<T>::TNode() : _left(nullptr), _right(nullptr)
{
    
}
template <typename T>
TNode<T>::TNode(TNode<T> * left, TNode<T> * right, T data): _left(left), _right(right), _data(data)
{
    
}
template <typename T>
TNode<T>::TNode(const TNode<T> & cp) : _left(nullptr), _right(nullptr), _data(cp.data)
{
    
}

template <typename T>
TNode<T>::~TNode()
{
    
}

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

template <typename T>
void TNode<T>::SetLeft(TNode * left)
{
    _left = left;
}

template <typename T>
void TNode<T>::SetRight(TNode * right)
{
    _right = right;
}

template <typename T>
TNode<T> *& TNode<T>::GetLeft()
{
    return _left;
}

template <typename T>
TNode<T> *& TNode<T>::GetRight()
{
    return _right;
}

template <typename T>
void TNode<T>::SetKey(T key)
{
    _data = key;
}

template <typename T>
T TNode<T>::GetKey()
{
    return _data;
}

#endif /* TNode_h */
