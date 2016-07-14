//cmpt454 programming project
//Jia Yun Xuan
//301230410
//janetx@sfu.ca



#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "BpTree.h"

using namespace std;


//public:
//default constructor
BpTree::BpTree()
{
    node();
}
//Constructor: creates an empty tree, the parameter sets the number of keys that can be stored in each node (leaf and interior)
BpTree::BpTree(int n)
{
    np= new node;
    np->child_ptr=new node * [n+1];
    np->parent_ptr=NULL;
    np->key = new int[n];
    for(int i=0; i<n+1; i++)
    {
        np->child_ptr[i]= NULL;
    }
    max_num_keys=n;
    if(IsLeaf)
    {
        np->leaf = true;
        np->data = new string [n];
    }
}
//inserts the key (int) and value (string) into the tree
void BpTree::insert(int n, string value )
{
    if(search(n))
    {
        perror("the key already exists");
        return;//find the key, insert failed because no duplicate key allowed
    }
    x=new node;
    do
    {
        
        //for loop for iterate through each node
        for(int i=0; i<max_num_keys; i++)
        {
//            if(n > x->key[i]&& x->leaf==true && x->key[i+1]==0)
//            {
//                x->key[i+1]=n;
//                x->data[i+1]=value;
//                return;
//            }
            if(n> x->key[i]&& x->leaf==false)
            {
                continue;
            }
            else if(n> x->key[i]&& x->leaf==true)
            {
                if(IsNodeFull(x))
                {
                    split_child(x,n,value);
                    return;
                }
                for(int j=i; j<max_num_keys;j++)
                {
                    if(x->key[j]==0)
                    {
                        x->key[j]=n;
                        x->data[j]=value;
                        return;
                    }
                }
            }
            else if(n< x->key[i]&& x->leaf==false)
            {
                x=x->child_ptr[i];
                break;
            }
            else if(n > x->key[i] )
            {
                continue;
            }
//            else if(x->key[i]==0)
//            {
//                x=x->child_ptr[i];
//                break;
//            }
        }//end for
        
    }while(x->leaf==false);//end while
    perror("the key has not been inserted");//search all the node in the leaf, still cannot find the a place to put the key
    exit(-1);
}
// searches the tree for the key (int), if found removes the key and associated value from the tree
void BpTree::remove(int n)
{
    if(search(n)==false)
    {
        perror("the key does not exist");
        return;//find the key, insert failed because no duplicate key allowed
    }
    x=new node;
    //while loop for iterate through the tree
    do
    {
        //for loop for iterate through each node
        for(int i=0; i<max_num_keys; i++)
        {
            if(n== x->key[i]&& x->leaf==true)
            {
                x->key[i]=0;
                //x->data[i]=NULL;
            }
            else if(n== x->key[i]&& x->leaf==false)
            {
                x=x->child_ptr[i+1];
                break;
            }
            else if(n < x->key[i])
            {
                x=x->child_ptr[i];
                break;
            }
            else if(n > x->key[i])
            {
                continue;
            }
            else if(x->key[i]==0)
            {
                x=x->child_ptr[i+1];
                break;
            }
        }//end for
        
    }while(x->leaf==false);//end while
    perror("the key does not exist");//search all the node in the leaf, still cannot find the key
    exit(-1);


}
// searches the tree for the key (int), if found returns the matching value
string  BpTree::find(int n)
{
    x=new node;
    //while loop for iterate through the tree
    do
    {
        //for loop for iterate through each node
        for(int i=0; i<max_num_keys; i++)
        {
            if(n== x->key[i]&& x->leaf==true)
            {
                return x->data[i];
            }
            else if(n== x->key[i]&& x->leaf==false)
            {
                x=x->child_ptr[i+1];
                break;
            }
            else if(n < x->key[i])
            {
                x=x->child_ptr[i];
                break;
            }
            else if(n > x->key[i] )
            {
                continue;
            }
            else if(x->key[i]==0)
            {
                x=x->child_ptr[i+1];
                break;
            }
        }//end for
        
    }while(x->leaf==false);//end while
    perror("the key does not exist");//search all the node in the leaf, still cannot find the key
    exit(-1);
}
//prints the keys in each node with nodes of the same level appearing on the same line
void BpTree::printKeys()
{
    x=root;
    do
    {
        for (int i = 0; i<max_num_keys; i++)
        {
            if(x->key[i]!=0)
            {
                cout << x->key[i];
            }
        }
    }while(x->leaf!=true);
}
//prints the values in key (not value) order
void BpTree::printValues()
{
    x=root;
    do
    {
        for (int i = 0; i<max_num_keys; i++)
        {
            if(x->data[i]!="/0")
            {
                cout << x->data[i]<<endl;
            }
        }
    }while(x->leaf!=true);
    

}
//destructor
BpTree::~BpTree()
{
    removeAll();
}
//private:
//copy constructor
BpTree::BpTree(const BpTree & BpTree)
{
    deepcopy(BpTree);

}
//overload assignment operator
BpTree& BpTree::operator=(const BpTree &bp)
{
    if(this!= &bp)
    {
        removeAll();
        deepcopy(bp);
    }
    return *this;

}

//initialize the b plus tree node
//node * BpTree::init()
//{
//    np= new node;
//    np->child_ptr=new node * [n+1];
//    np->parent_ptr=NULL;
//    np->key = new int[n];
//    for(int i=0; i<n+1; i++)
//    {
//        np->child_ptr[i]= NULL;
//    }
//    max_num_keys=n;
//    if(IsLeaf)
//    {
//        np->leaf = true;
//        np->data = new string [n];
//    }
//    return np;
//}
//traverse/iterate through the b plus tree, help search
//void BpTree::traverse(node *p)
//{
//    cout<<endl;
//    int i;
//    for (i=0; i<p->n; i++)
//    {
//        if(p->leaf == false)
//        {
//            traverse(p->child_ptr[i]);
//        }
//        cout << " " << p->data[i];
//    }
//    if(p->leaf == false)
//    {
//        traverse(p>child_ptr[i]);
//    }
//    cout<<endl;
//}
//sometimes bplus tree needs to split nodes while inserting
void BpTree::split_child(node *x, int n, string value)
{
//    int j;
//    string mid;
//    node *np1, *np3, *y;
//    np3= init();
//    np3->leaf= true;
//    np->data = new string [n];
//
//    if(x->parent_ptr==NULL || IsNodeFull(x->parent_ptr)==true)
//    {
//        mid = x -> data[max_num_keys/2];
//        x->data[max_num_keys/2]="/0";
//        x=x->child_ptr;
//        np1=init();
//        np1->leaf = false;
//        x->leaf = true;
//        for(j=max_num_keys/2+1; j<max_num_keys; j++)
//        {
//            np3->data[j-max_num_keys/2-1]=x->data[j];
//            np3->child_ptr[j-max_num_keys/2-1] =x->child_ptr[j];
//            np3=np3->child_ptr;
//            x->data[j]="/0";
//            x=x->child_ptr;
//        }
//        for(j=0; j<max_num_keys+1; j++)
//        {
//            x->child_ptr[j]=nullptr;
//        }
//        np1->data[0] = mid;
//        //not done
//        np1->child_ptr[np1->] = x;
//        np1 -> child_ptr[np1->np +1] =np3;
//        np1 -> n++;
//        root = np1;
//    }
//    else
//    {
//        y = x->child_ptr[n];
//        mid = y->data[max_num_keys/2];
//        y->data[max_num_keys/2] = NULL;
//        y->n--;
//        for(j=max_num_keys/2+1; j<max_num_keys; j++)
//        {
//            np3->data[j-max_num_keys/2-1] = y->data[j];
//            np3->n++;
//            y->data[j]=NULL;
//            y->n--;
//        }
//        x->child_ptr[n+1] = y;
//        x->child_ptr[n+1] = np3;
//    }
    //return mid;
    
}
//search function: if the key exist
bool BpTree::search(int n)
{
    x=new node;
    //while loop for iterate through the tree
    do
    {
        //for loop for iterate through each node
        for(int i=0; i<max_num_keys; i++)
        {
            if(n== x->key[i])
            {
                return true;
            }
            else if(n < x->key[i])
            {
                x=x->child_ptr[i];
                break;
            }
            else if(n > x->key[i] )
            {
                continue;
            }
            else if(x->key[i]==0)
            {
                x=x->child_ptr[i+1];
                break;
            }
        }//end for
        
    }while(x->leaf==false);//end while
    return false;//search all the node in the leaf, still cannot find the key
}
//check if a node has no space
bool BpTree::IsNodeFull(node * nodename)
{
    x= nodename;
    for(int i=0; i<max_num_keys; i++)
    {
        if(x->key[i]==0)
        {
            return false;
        }
    }
    return true;
}
//check if a node is empty
bool BpTree::IsNodeEmpty(node * nodename)
{
    x= nodename;
    for(int i=0; i<max_num_keys; i++)
    {
        if(x->key[i]!=0)
        {
            return false;
        }
    }
    return true;
}
//check if a node is at least half full
bool BpTree::IsNodeHalfFull(node * nodename)
{
    x= nodename;
    int counter=0;
    for(int i=0; i<max_num_keys; i++)
    {
        if(x->key[i]!=0)
        {
            counter++;
        }
    }
    if(counter>max_num_keys)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//remove all the nodes in the tree
void BpTree::removeAll()
{
    x=new node;
    //while loop for iterate through the tree
    do
    {
        //for loop for iterate through each node
        for(int i=0; i<max_num_keys; i++)
        {
            
        }//end for
        
    }while(x->leaf==false);//end while
    return;//search all the node in the leaf, still cannot find the key
}
////deep copy the tree
BpTree BpTree::deepcopy (const BpTree & BpTree)
{
    x=new node;
    node* y=BpTree.root;
    int i;
    do
    {
        for(i=0; i<max_num_keys+1;i++)
        {
            x->child_ptr[i]=y->child_ptr[i];
            if(x->child_ptr[i]!=NULL)
            {
                
            }
        }
        
        for(i=0;i<max_num_keys+1;i++)
        {
            x=x->child_ptr[i];
            y=y->child_ptr[i];
        }
        
        
    }while(x->leaf==true);
    return BpTree;
}
//deep copy a node
//BpTree* BpTree::copynode(const BpTree & node)
//{
//    
//    x= new node;
//    x->leaf=node.leaf;
//    for(int i=0, i<max_num_keys+1, i++)
//    {
//        x->child_ptr[i]=node.child_ptr[i];
//        if(x->leaf==true)
//        {
//            x->data[i]=node->data[i];
//        }
//            
//    }
//    return x;
//}
