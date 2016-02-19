//
//  main.cpp
//  BinarySearchTree
//
//  Created by Ian Murphy on 2/11/16.
//  Copyright © 2016 Ian Murphy. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include "AVLTree.h"
#define _CRTDBG_MAP_ALLOC

void Print(int data)
{
    std::cout<<data<< " " ;
    fflush(stdout);
}

int main(int argc, const char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    AVLTree<int> tree;
    cout<<"Inserting several values"<<endl;
    tree.Insert(8);
    tree.Insert(9);
    tree.Insert(10);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(6);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(11);
    tree.BreadthFirstTraverse(&Print);
    cout<<endl<<tree.Height()<<endl;
    //tree.Purge();
//    
//    for (int i = 20; i>0; i--) {
//        tree.Insert(i);
//    }
    cout<<tree.Height()<<endl;
    tree.BreadthFirstTraverse(&Print);
    cout<<endl;
    
    cout<<"Testing Traversals: "<<endl;
    cout<<"\n\nIn Order"<<endl;
    tree.InOrderTraverse(&Print);
    cout<<"\n\nPre Order"<<endl;
    tree.PreOrderTraverse(&Print);
    cout<<"\n\nPost Order"<<endl;
    tree.PostOrderTraverse(&Print);
    cout<<"\n\nBreadth Fist"<<endl;
    tree.BreadthFirstTraverse(&Print);
    
    //tree.Purge();
    //tree.PostOrderTraverse(&Print);
    
    
    
    cout<<"\n\nTest delete 10"<<endl;
    cout<<"\n\nBefore"<<endl;
    tree.InOrderTraverse(&Print);
    tree.Delete(10);
    cout<<"\n\nAfter"<<endl;
    tree.InOrderTraverse(&Print);

    cout<<"\n\nTest Canonicals: "<<endl;
    cout<<"Test Copy c'tor: "<<endl;
    AVLTree<int> tree2(tree);
    tree.InOrderTraverse(&Print);
    cout<<"\n";
    tree2.InOrderTraverse(&Print);
    
    cout<<"\n\nTest OP =: "<<endl;
    tree2.Delete(10);
    tree2.Delete(40);
    tree2.Delete(60);
    tree = tree2;
    tree.InOrderTraverse(&Print);
    cout<<"\n";
    tree2.InOrderTraverse(&Print);
    
    cout<<"Test Purge empty list: "<<endl;
    tree.Purge();
    tree.Purge();
    cout<<"\n\nTest Purge tree with one node: "<<endl;
    tree.Insert(1);
    tree.Purge();
    cout<<"\n\nTest height: "<<endl;
    cout<<tree.Height()<<endl;
    tree.Insert(50);
    cout<<tree.Height()<<endl;
    tree.Insert(60);
    cout<<tree.Height()<<endl;
    tree.Insert(40);
    cout<<tree.Height()<<endl;
    tree.Insert(30);
    cout<<tree.Height()<<endl;
    tree.Insert(30);
    cout<<tree.Height()<<endl;
    tree.Insert(30);
    cout<<tree.Height()<<endl;
    tree.InOrderTraverse(&Print);
    cout<<endl;
    
    tree.Delete(30);
    tree.InOrderTraverse(&Print);
    
    for (int i = 0; i<100; i++)
    {
        tree.Insert(30);
        tree.Delete(30);
    }
//
    return 0;
}
