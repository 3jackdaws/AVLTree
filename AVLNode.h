//
//  AVLNode.h
//  AVL Tree
//
//  Created by Ian Murphy on 2/16/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

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
    Balance GetBalance();
    void SetBalance(Balance val);
    Balance & Balance();
private:
    
    enum Balance _balance;
    //AVLNode<T> * _left;
    //AVLNode<T> * _right;
    //T _data;
};

template <typename T>
AVLNode<T>::AVLNode() : _balance(EH)
{
    
}

template <typename T>
AVLNode<T>::AVLNode(AVLNode<T> * left, AVLNode<T> * right, T data) : _balance(EH), TNode<T>(left, right, data)
{
    //_left(left), _right(right),
}

template <typename T>
Balance AVLNode<T>::GetBalance()
{
    return _balance;
}

template <typename T>
void AVLNode<T>::SetBalance(enum Balance val)
{
    _balance = val;
}

template <typename T>
Balance & AVLNode<T>::Balance()
{
    return _balance;
}
#endif /* AVLNode_h */
