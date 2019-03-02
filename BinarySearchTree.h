#pragma once
#include "BTNode.h"

#include<iostream>
using namespace std;

template<class T>
class BinarySearchTree
{
    private:
        BTNode<T> *Root;

    public:

        //Basic Functions
        BinarySearchTree();
        BinarySearchTree(T Data);
        BinarySearchTree(const BTNode<T> &RHS);
        BinarySearchTree& operator =(const BTNode<T> &RHS);
        ~BinarySearchTree();

        //Special Functions
        void SetRoot(BTNode<T>* NewRoot);
        BTNode<T>* GetRoot();
        T GetRootData();
        void CopyTree(BTNode<T> *RHS,int flag,BTNode<T> *Tree);
        BTNode<T>* InsertCopy(int data,int flag,BTNode<T> *Tree);
        void DeleteAll(BTNode<T> *root);
        bool Insert(T Data);
        void Delete(T Data);
        unsigned int Diameter(BTNode<T>* root);;
        unsigned int GetHeight(BTNode<T> *root);
        unsigned int GetWidth(BTNode<T> *root);
        void PreOrder(BTNode<T> *root);
        void PostOrder(BTNode<T>* root);
        void InOrder(BTNode<T>* root);
        void LevelOrder();
        unsigned int GetMin(BTNode<T> *root);
        unsigned int GetMax(BTNode<T> *root);
        unsigned int CountInternalNodes(BTNode<T> *root);
        unsigned int CountExternalNodes(BTNode<T> *root);
        bool IsSkew();
        bool AreMirror(BTNode<T> *LHSRoot,BTNode<T> *RHSRoot);
        bool Search(T Data);
};

