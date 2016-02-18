//
//  BSTree.h
//  BinarySearchTree
//
//  Created by Ian Murphy on 2/11/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

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


template <typename T>
BSTree<T>::BSTree() : _root(nullptr)
{
    
}

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

template <typename T>
BSTree<T>::~BSTree()
{
    Purge();
}

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

template <typename T>
void BSTree<T>::Purge()
{
    if(_root)
        Unlink(_root);
    _root = nullptr;
}

template <typename T>
void BSTree<T>::Unlink(TNode<T> * current_root)
{
    if(current_root->_left)
        Unlink(current_root->_left);
    if(current_root->_right)     //left
        Unlink(current_root->_right);
//    delete current_root->_left;
//    current_root->_left = nullptr;
//    delete current_root->_right;
//    current_root->_right = nullptr;
    //cout<<"Deleting"<< current_root->_data<<endl;
    delete current_root;
    current_root = nullptr;
}

template <typename T>
void BSTree<T>::Insert(T data)
{
    Put(_root, data);
}

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

template <typename T>
bool BSTree<T>::Delete(T data)
{
    _root = Delete(_root, data);
    return true;
}

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
            // get smallest node
            TNode<T> * temp = current_root->_right;
            while(temp && temp->_left)
            {
                temp = temp->_left;
            }
            current_root->_data = temp->_data;
            //delete temp;///////////////////////////////////////////////////////////////////////////////
            // now delete temp from T's right subtree and return
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

template <typename T>
void BSTree<T>::InOrderTraverse(void (*func)(T))
{
    InOrderTraverse(_root, func);
}

template <typename T>
void BSTree<T>::PreOrderTraverse(void (*func)(T))
{
    PreOrderTraverse(_root, func);
}

template <typename T>
void BSTree<T>::PostOrderTraverse(void (*func)(T))
{
    PostOrderTraverse(_root, func);
}

template <typename T>
void BSTree<T>::BreadthFirstTraverse(void (*func)(T))
{
    BreadthFirstTraverse(_root, func);
}

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

template <typename T>
int BSTree<T>::Height()
{
    return Height(_root);
}

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