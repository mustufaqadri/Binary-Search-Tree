#include "BTNode.h"
#include "BinarySearchTree.h"

#include <bits/stdc++.h>
using namespace std;

template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
    Root=0;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(T Data)
{
    BTNode<T> *NewNode=new BTNode<T>;
    NewNode->SetData(Data);
    Root=NewNode;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BTNode<T> &RHS)
{
    if(RHS.Root!=0)
    {
        BTNode<T> *newnode;
		newnode=new BTNode<T>(RHS.root->getData());
		Root=newnode;
		CopyTree(RHS.Root,-1,Root);
    }
    else
    {
        Root=0;
    }
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>:: operator =(const BTNode<T> &RHS)
{
    if(this!=&RHS)
    {
        DeleteAll();
        BTNode<T> *newnode;
		newnode=new BTNode<T>(RHS.root->getData());
		Root=newnode;
		CopyTree(RHS.Root,-1,Root);
    }
    else
    {
        return (*this);
    }
}

template<class T>
void BinarySearchTree<T>::CopyTree(BTNode<T> *RHS,int flag,BTNode<T> *Tree)
{
    if(RHS!=0)
    {
        Tree=InsertCopy(RHS->getData(),flag,Tree);
    }
    if(RHS->GetLeft()!=0)
    {
        CopyTree(RHS->GetLeft(),0,Tree);
    }
    if(RHS->GetRight()!=0)
    {
        CopyTree(RHS->GetRight(),1,Tree);
    }
}

template<class T>
BTNode<T>* BinarySearchTree<T>::InsertCopy(int data,int flag,BTNode<T> *Tree)
{
    if(flag==-1)
    {
        return Tree;
    }
    BTNode<T> *newnode;
    newnode=new BTNode<T>(data);
    if(flag==0)
    {
        Tree->SetLeft(newnode);
        return Tree->GetLeft();
    }
    else
    {
        Tree->SetRight(newnode);
        return Tree->GetRight();
    }
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    if(Root!=0)
    {
        cout<<"\n\nDestroying Nodes\n";
        DeleteAll(Root);
    }
    Root=0;
}

template<class T>
void BinarySearchTree<T>::SetRoot(BTNode<T>* NewRoot)
{
    delete Root;
    Root=new BTNode<T>;
    Root=NewRoot;
}

template<class T>
BTNode<T>* BinarySearchTree<T>:: GetRoot()
{
    return Root;
}

template<class T>
T BinarySearchTree<T>::GetRootData()
{
    return Root->Data;
}

template<class T>
bool BinarySearchTree<T>::Insert(T Data)
{
    BTNode<T> *NewNode=new BTNode<T>;
    NewNode->SetData(Data);
    if(Root==0)
    {
        Root=NewNode;
    }
    else
    {
        BTNode<T> *Current=Root;
        BTNode<T> *Parent=0;
        while(Current!=0)
        {
            if(Current->GetData()==Data)
            {
                return false;
            }
            else if(Current->GetData()>Data)
            {
            	Parent=Current;
            	Current=Current->GetLeft();
            }
            else
            {
            	Parent=Current;
            	Current=Current->GetRight();
            }
        }
        if(Parent->GetData()>Data)
        {
			Parent->SetLeft(NewNode);
        }
        else
        {
			Parent->SetRight(NewNode);
        }
    }
    return true;
}

template<class T>
void BinarySearchTree<T>::Delete(T Data)
{
    if(Root==0)
    {
        cout<<"\n\nTree is empty...\n\n";
    }
    else
    {
        BTNode<T> *Current=Root,*Temp=0;
        while(Current!=0)
        {
            if(Current->GetData()<Data)
            {
                Temp=Current;
                Current=Current->GetRight();
            }
            else if(Current->GetData()>Data)
            {
                Temp=Current;
                Current=Current->GetLeft();
            }
            else
            {
                if(Current->GetLeft()==0 && Current->GetRight()==0)
                {
                    if(Temp->GetLeft()==Current)
                    {
                       Temp->SetLeft(0);
                       break;
                    }
                    else
                    {
                        Temp->SetRight(0);
                        break;
                    }
                }
                else if(Current->GetLeft()==0)
                {
                    if(Temp->GetLeft()==Current)
                    {
                        Temp->SetLeft(Current->GetRight());
                        Current->SetRight(0);
                        break;
                    }
                    else
                    {
                        Temp->SetRight(Current->GetRight());
                        Current->SetRight(0);
                        break;
                    }
                }
                else if(Current->GetRight()==0)
                {
                    if(Temp->GetLeft()==Current)
                    {
                        Temp->SetLeft(Current->GetLeft());
                        Current->SetLeft(0);
                        break;
                    }
                    else
                    {
                        Temp->SetRight(Current->GetLeft());
                        Current->SetLeft(0);
                        break;
                    }
                }
                else if(Current->GetLeft()!=0 && Current->GetRight()!=0)
                {
                    BTNode<T> *Next=Current->GetRight();
                    BTNode<T> *Min=Next;
                    Temp=Current;
                    while(Next->GetLeft()!=0)
                    {
                        Temp=Next;
                        Next=Next->GetLeft();
                    }
                    Min=Next;
                    Current->SetData(Min->GetData());
                    Data=Min->GetData();
                    Current=Min;
                }

            }
        }
    }

}

template<class T>
unsigned int BinarySearchTree<T>::Diameter(BTNode<T>* root)
{
    if(root==0)
    {
        return 0;
    }
    else
    {
        unsigned int Case1=GetHeight(root->GetLeft()) + GetHeight(root->GetRight());
        unsigned int Case2=Diameter(root->GetLeft());
        unsigned int Case3=Diameter(root->GetRight());
        unsigned int Diameter=std::max(Case1,std::max(Case2,Case3)) + 1;
    }
}

template<class T>
void BinarySearchTree<T>::DeleteAll(BTNode<T> *root)
{
    if(root!=0)
    {
        DeleteAll(root->GetLeft());
        root->SetLeft(0);
        DeleteAll(root->GetRight());
        root->SetRight(0);
        cout<<"\nDeleting "<<root->GetData()<<" ...";
        delete root;
        root=0;
    }
}

template<class T>
unsigned int BinarySearchTree<T>::GetHeight(BTNode<T> *root)
{
    if(root==0)
    {
        return 0;
    }
    else
    {
        unsigned int LeftSubTree=GetHeight(root->GetLeft());
        unsigned int RightSubTree=GetHeight(root->GetRight());
        return LeftSubTree > RightSubTree ? LeftSubTree+1: RightSubTree+1;
    }
}

template<class T>
unsigned int BinarySearchTree<T>::GetWidth(BTNode<T> *root)
{
	if (root==0)
    {
        return 0;
    }
    else
    {
        list<BTNode<T>*> L;
        L.push_back(Root);
        BTNode<T>* Temp=0;
        int Max=0;
        int Width=0;
        while(!L.empty())
        {
            Width = L.size();
            if(Max<Width)
            {
                Max=Width;
            }
            while(Width--)
            {
                Temp=L.front();
                L.pop_front();
                if(Temp->GetLeft()!=0)
                {
                    L.push_back(Temp->GetLeft());
                }
                if(Temp->GetRight()!=0)
                {
                    L.push_back(Temp->GetRight());
                }
            }
        }
        return Max;
    }
}

template<class T>
void BinarySearchTree<T>::PreOrder(BTNode<T>* root)
{
    if(root!=0)
    {
        cout<<root->GetData()<<" ";
        PreOrder(root->GetLeft());
        PreOrder(root->GetRight());
    }
}

template<class T>
void BinarySearchTree<T>::PostOrder(BTNode<T>* root)
{
    if(root!=0)
    {
        PostOrder(root->GetLeft());
        PostOrder(root->GetRight());
        cout<<root->GetData()<<" ";
    }
}

template<class T>
void BinarySearchTree<T>::InOrder(BTNode<T>* root)
{
    if(root!=0)
    {
        InOrder(root->GetLeft());
        cout<<root->GetData()<<" ";
        InOrder(root->GetRight());
    }
}

template<class T>
unsigned int BinarySearchTree<T>::GetMin(BTNode<T> *root)
{
    if(root==0)
    {
        return INT_MAX;
    }
    else
    {
        unsigned int Min=root->GetData();
        unsigned int LeftMin=GetMin(root->GetLeft());
        unsigned int RightMin=GetMin(root->GetRight());
        if(LeftMin<Min)
        {
            Min=LeftMin;
        }
        if(RightMin<Min)
        {
            Min=RightMin;
        }
        return Min;
    }
}

template<class T>
unsigned int BinarySearchTree<T>::GetMax(BTNode<T> *root)
{
    if(root==0)
    {
        return 0;
    }
    else
    {
        unsigned int Max=root->GetData();
        unsigned int LeftMax=GetMax(root->GetLeft());
        unsigned int RightMax=GetMax(root->GetRight());
        if(LeftMax>Max)
        {
            Max=LeftMax;
        }
        if(RightMax>Max)
        {
            Max=RightMax;
        }
        return Max;
    }
}

template<class T>
bool BinarySearchTree<T>::Search(T Data)
{
    if(Root==0)
    {
        return false;
    }
    else
    {
        queue<BTNode<T>*> Q;
        Q.push(Root);
        BTNode<T> *Temp=0;
        while(Q.empty()!=1)
        {
            Temp=Q.front();
            if (Temp->GetData()==Data)
            {
                return true;
            }
            if(Temp->GetLeft()!=0)
            {
                Q.push(Temp->GetLeft());
            }
            if(Temp->GetRight()!=0)
            {
                Q.push(Temp->GetRight());
            }
            Q.pop();
        }
        return false;
    }
}

template<class T>
void BinarySearchTree<T>::LevelOrder()
{
    BTNode<T> *Temp=Root;
    queue<BTNode<T>*> Q;
    Q.push(Root);
    while(!Q.empty())
    {
        Temp=Q.front();
        cout<<Temp->GetData()<<"\n";
        if(Temp->GetLeft()!=0)
        {
            Q.push(Temp->GetLeft());
        }
        if(Temp->GetRight()!=0)
        {
            Q.push(Temp->GetRight());
        }
        Q.pop();
    }
}

template<class T>
bool BinarySearchTree<T>::AreMirror(BTNode<T> *LHSRoot,BTNode<T> *RHSRoot)
{
    if(LHSRoot==NULL && RHSRoot==NULL)
    {
        return true;
    }
    if(LHSRoot==NULL || RHSRoot==NULL)
    {
        return false;
    }
    return  LHSRoot->GetData()==RHSRoot->GetData() &&
            AreMirror(LHSRoot->GetLeft(),RHSRoot->GetRight()) &&
            AreMirror(LHSRoot->GetRight(),RHSRoot->GetLeft());
}

template<class T>
bool BinarySearchTree<T>::IsSkew()
{
    if(Root!=0)
    {
        int LeftTreeHeight=GetHeight(Root->GetLeft());
        int RightTreeHeight=GetHeight(Root->GetRight());
        int Diff=0;
        if(LeftTreeHeight>RightTreeHeight)
        {
            Diff=abs(LeftTreeHeight-RightTreeHeight);
        }
        else
        {
            Diff=abs(RightTreeHeight-LeftTreeHeight);
        }
        if(Diff>2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

template<class T>
unsigned int BinarySearchTree<T>::CountInternalNodes(BTNode<T> *root)
{
    unsigned int Count = 0;
    if (root->GetLeft() != NULL || root->GetRight() != NULL)
    {
        Count = 1;
        if (root->GetLeft() != NULL)
        {
            Count += CountInternalNodes(root->GetLeft());
        }
        if (root->GetRight() != NULL)
        {
            Count += CountInternalNodes(root->GetRight());
        }
    }
    return Count;
}

template<class T>
unsigned int BinarySearchTree<T>::CountExternalNodes(BTNode<T> *root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->GetLeft() == NULL && root->GetRight()==NULL)
    {
        return 1;
    }
    else
    {
        return CountExternalNodes(root->GetLeft())+CountExternalNodes(root->GetRight());
    }
}
