//
//  AVLTree.h
//  AVL Tree
//
//  Created by Ian Murphy on 2/16/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h
#include "BSTree.h"
#include "AVLNode.h"

template <typename T>
class AVLTree : public BSTree<T>
{
public:
    AVLTree();
    AVLTree(const AVLTree<T> & cp);
    ~AVLTree();
    AVLTree & operator = (const AVLTree<T> & rhs);
    void Insert(T data);
    int Height();
    bool Delete(T data);
    void InOrderTraverse(void (*func)(T));
    void PreOrderTraverse(void (*func)(T));
    void PostOrderTraverse(void (*func)(T));
    void BreadthFirstTraverse(void (*func)(T));
    
    void Purge();
private:
    AVLNode<T> * Delete(AVLNode<T> * current_root, T & data, bool & shorter, bool & success);
    int Height(AVLNode<T> * );
    AVLNode<T> * Insert(AVLNode<T> * root, AVLNode<T> * nn, bool &taller);
    AVLNode<T> * LeftRotate(AVLNode<T> * rop);
    AVLNode<T> * RightRotate(AVLNode<T> * rop);
    AVLNode<T> * LeftBalance(AVLNode<T> * current_root, bool & taller);
    AVLNode<T> * RightBalance(AVLNode<T> * current_root, bool & taller);
    AVLNode<T> * DeleteRightBalance(AVLNode<T> * current_root, bool & shorter);
    AVLNode<T> * DeleteLeftBalance(AVLNode<T> * current_root, bool & shorter);
    
    AVLNode<T> * _root;
};

template <typename T>
AVLTree<T>::AVLTree() : _root(nullptr)
{
    
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree & cp) : _root(nullptr)
{
    std::queue<AVLNode<T> *> queue;
    AVLNode<T> * current_node;
    queue.push(cp._root);
    while(!queue.empty())
    {
        current_node = queue.front();
        queue.pop();
        Insert(current_node->_data);
        if(current_node->_left)
        {
            queue.push((AVLNode<T> *)current_node->_left);
        }
        if(current_node->_right)
        {
            queue.push((AVLNode<T> *)current_node->_right);
        }
    }
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    Purge();
    _root = nullptr;
}

template <typename T>
AVLTree<T> & AVLTree<T>::operator = (const AVLTree<T> &rhs)
{
    if(this != &rhs)
    {
        Purge();
        std::queue<AVLNode<T> *> queue;
        AVLNode<T> * current_node;
        queue.push(rhs._root);
        while(!queue.empty())
        {
            current_node = queue.front();
            queue.pop();
            Insert(current_node->_data);
            if(current_node->_left)
            {
                queue.push((AVLNode<T> *)current_node->_left);
            }
            if(current_node->_right)
            {
                queue.push((AVLNode<T> *)current_node->_right);
            }
        }
    }
    return *this;
}

template <typename T>
void AVLTree<T>::Insert(T data)
{
    bool taller;
    AVLNode<T> * nn = new AVLNode<T>(nullptr, nullptr, data);
    _root = Insert(_root, nn, taller);
}

template <typename T>
AVLNode<T> * AVLTree<T>::Insert(AVLNode<T> * root, AVLNode<T> *nn, bool &taller)
{
    //AVLNode<T> * returnNode=nullptr;
    if(!root)
    {
        root = nn;
        taller = true;
        //return root;
    }
    else if(nn->_data <= root->_data)
    {
        root->_left = AVLTree<T>::Insert(((AVLNode<T>*)root->_left), nn, taller);
        if(taller)
        {
            switch(((AVLNode<T>*)root)->_balance)
            {
                case LH:
                    root = LeftBalance(root, taller);
                    break;
                case EH:
                    root->_balance = LH;
                    break;
                case RH:
                    root->_balance = EH;
                    taller = false;
                    break;
            }
            
        }
    }
    else
    {
        root->_right = Insert((AVLNode<T>*)root->_right, nn, taller);
        if(taller)
        {
            switch(root->_balance)
            {
                case RH:
                    root = RightBalance(root, taller);
                    break;
                case EH:
                    root->_balance = RH;
                    break;
                case LH:
                    root->_balance = EH;
                    taller = false;
                    break;
            }
            
        }

    }
    return root;
}



template <typename T>
AVLNode<T> * AVLTree<T>::LeftRotate(AVLNode<T> * rop)
{
    AVLNode<T> * temp = (AVLNode<T>*)rop->_right;
    rop->_right = temp->_left;
    temp->_left = rop;
    
    return temp;
}

template <typename T>
AVLNode<T> * AVLTree<T>::RightRotate(AVLNode<T> * rop)
{
    AVLNode<T> * temp = (AVLNode<T>*)rop->_left;
    rop->_left = temp->_right;
    temp->_right = rop;
    
    return temp;
     
}

template <typename T>
AVLNode<T> * AVLTree<T>::LeftBalance(AVLNode<T> * current_root, bool & taller)
{
    
    AVLNode<T> * left_tree = (AVLNode<T>*)current_root->_left;
    if(left_tree->_balance == LH)
    {
        current_root->_balance = EH;
        left_tree->_balance = EH;
        current_root = RightRotate(current_root);
        taller = false;
    }
    else
    {
        AVLNode<T> * right_tree = (AVLNode<T>*)left_tree->_right;
        if(right_tree)
        {
            switch(right_tree->_balance)
            {
                case LH:
                    current_root->_balance = RH;
                    left_tree->_balance = EH;
                    break;
                case EH:
                    current_root->_balance = EH;
                    left_tree->_balance = EH;
                    break;
                case RH:
                    current_root->_balance = EH;
                    left_tree->_balance = LH;
            }
            right_tree->_balance = EH;
            current_root->_left = LeftRotate(left_tree);
            current_root = RightRotate(current_root);
            taller = false;
        }
        
    }
    return current_root;
}

template <typename T>
AVLNode<T> * AVLTree<T>::RightBalance(AVLNode<T> *current_root, bool & taller)
{
    AVLNode<T> * right_tree = (AVLNode<T>*)current_root->_right;
    if(right_tree->_balance == RH)
    {
        current_root->_balance = EH;
        right_tree->_balance = EH;
        current_root = LeftRotate(current_root);
        taller = false;
    }
    else
    {
        AVLNode<T> * left_tree = (AVLNode<T>*)right_tree->_left;
        if(left_tree)
        {
            switch(left_tree->_balance)
            {
                case LH:
                    current_root->_balance = EH;
                    right_tree->_balance = RH;
                    break;
                case EH:
                    //current_root->_balance = EH;
                    right_tree->_balance = EH;
                    break;
                case RH:
                    current_root->_balance = LH;
                    right_tree->_balance = EH;
            }
            left_tree->_balance = EH;
            current_root->_right = RightRotate(right_tree);
            current_root = LeftRotate(current_root);
            taller = false;
        }
    }
    return current_root;
}

template <typename T>
int AVLTree<T>::Height()
{
    return Height(_root);
}

template <typename T>
int AVLTree<T>::Height(AVLNode<T> * current_root)
{
    if(current_root)
    {
        int lheight = 0;
        int rheight = 0;
        if(current_root->_left)
        {
            lheight++;
            lheight += Height((AVLNode<T>*)current_root->_left);
        }
        if(current_root->_right)
        {
            rheight++;
            rheight += Height((AVLNode<T>*)current_root->_right);
        }
        if(lheight > rheight)
            return lheight;
        else
            return rheight;
    }
    else
        return -1;
}

template <typename T>
bool AVLTree<T>::Delete(T data)
{
    bool shorter;
    bool success;
    AVLNode<T> * newRoot = Delete(_root, data, shorter, success);
    if(success)
    {
        _root = newRoot;
        return true;
    }
    return false;
}

template <typename T>
AVLNode<T> * AVLTree<T>::Delete(AVLNode<T> * current_root, T & data, bool & shorter, bool & success)
{
    if(!current_root)
    {
        shorter = false;
        success = false;
        return nullptr;
    }
    else if (data < current_root->_data)
    {
        current_root->_left = Delete((AVLNode<T>*)current_root->_left, data, shorter, success);
        if(shorter)
        {
            current_root = DeleteRightBalance(current_root, shorter);
        }
    }
    else if (data > current_root->_data)
    {
        current_root->_right = Delete((AVLNode<T>*)current_root->_right, data, shorter, success);
        if(shorter)
        {
            current_root = DeleteLeftBalance(current_root, shorter);
        }
    }
    else
    {
        AVLNode<T> * deleteNode = current_root;
        if(!current_root->_right)
        {
            AVLNode<T> * newRoot = (AVLNode<T>*)current_root->_left;
            success = true;
            shorter = true;
            delete deleteNode;
            return newRoot;
        }
        else if(!current_root->_left)
        {
            AVLNode<T> * newRoot = (AVLNode<T>*)current_root->_right;
            success = true;
            shorter = true;
            delete deleteNode;
            return newRoot;
        }
        else
        {
            AVLNode<T> * exchange = (AVLNode<T>*)current_root->_left;
            while(exchange && exchange->_right)
            {
                exchange = (AVLNode<T>*)exchange->_right;
            }
            current_root->_data = exchange->_data;
            current_root->_left = Delete((AVLNode<T>*)current_root->_left, exchange->_data, shorter, success);
            if(shorter)
            {
                DeleteRightBalance(current_root, shorter);
            }
        }
    }
    return current_root;
}

template <typename T>
AVLNode<T> * AVLTree<T>::DeleteLeftBalance(AVLNode<T> *current_root, bool &shorter)
{
    if(current_root->_balance == RH)
    {
        current_root->_balance = EH;
    }
    else if (current_root->_balance == EH)
    {
        current_root->_balance = LH;
        shorter = false;
    }
    else
    {
        AVLNode<T> * left_tree = (AVLNode<T>*)current_root->_left;
        if(left_tree && left_tree->_balance == LH)
        {
            AVLNode<T> * right_tree = (AVLNode<T>*)left_tree->_right;
            if(right_tree)///////////////////////////////////////////////////////
            {
                if(right_tree->_balance == RH)
                {
                    left_tree->_balance = LH;
                    current_root->_balance = EH;
                }
                else if(right_tree->_balance == EH)
                {
                    current_root->_balance = RH;
                    left_tree->_balance = EH;
                }
                else
                {
                    current_root->_balance = RH;
                    right_tree->_balance = EH;
                }
                right_tree->_balance = EH;
                current_root->_left = LeftRotate(left_tree);
                current_root = RightRotate(current_root);
            }
            
        }
        else if(left_tree)
        {
            if(left_tree->_balance != EH)
            {
                current_root->_balance = EH;
                left_tree->_balance = EH;
            }
            else
            {
                current_root->_balance = LH;
                left_tree->_balance = RH;
                shorter = false;
            }
            current_root = RightRotate(current_root);
        }
    }
    return current_root;

}

template <typename T>
AVLNode<T> * AVLTree<T>::DeleteRightBalance(AVLNode<T> *current_root, bool &shorter)
{
    if(current_root->_balance == LH)
    {
        current_root->_balance = EH;
    }
    else if (current_root->_balance == EH)
    {
        current_root->_balance = RH;
        shorter = false;
    }
    else
    {
        AVLNode<T> * right_tree = (AVLNode<T>*)current_root->_right;
        if(right_tree && right_tree->_balance == LH)
        {
            AVLNode<T> * left_tree = (AVLNode<T>*)right_tree->_left;
            if(left_tree)///////////////////////////////////////////////
            {
                if(left_tree->_balance == LH)
                {
                    right_tree->_balance = RH;
                    current_root->_balance = EH;
                }
                else if(left_tree->_balance == EH)
                {
                    current_root->_balance = LH;
                    right_tree->_balance = EH;
                }
                else
                {
                    current_root->_balance = LH;
                    right_tree->_balance = EH;
                }
                left_tree->_balance = EH;
                current_root->_right = RightRotate(right_tree);
                current_root = LeftRotate(current_root);
            }
            
        }
        else if(right_tree)
        {
            if(right_tree->_balance != EH)
            {
                current_root->_balance = EH;
                right_tree->_balance = EH;
            }
            else
            {
                current_root->_balance = RH;
                right_tree->_balance = LH;
                shorter = false;
            }
            current_root = LeftRotate(current_root);
        }
    }
    return current_root;
}
template <typename T>
void AVLTree<T>::InOrderTraverse(void (*func)(T))
{
    BSTree<T>::InOrderTraverse(AVLTree<T>::_root, func);
}

template <typename T>
void AVLTree<T>::PreOrderTraverse(void (*func)(T))
{
    BSTree<T>::PreOrderTraverse(AVLTree<T>::_root, func);
}

template <typename T>
void AVLTree<T>::PostOrderTraverse(void (*func)(T))
{
    BSTree<T>::PostOrderTraverse(AVLTree<T>::_root, func);
}

template <typename T>
void AVLTree<T>::BreadthFirstTraverse(void (*func)(T))
{
    if(_root)
        BSTree<T>::BreadthFirstTraverse(AVLTree<T>::_root, func);
}

template <typename T>
void AVLTree<T>::Purge()
{
    if(_root)
        BSTree<T>::Unlink(_root);
    _root = nullptr;
}
#endif /* AVLTree_h */
