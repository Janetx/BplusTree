//cmpt454 programming project
//Jia Yun Xuan
//301230410
//janetx@sfu.ca

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class BpTree
{
	public:
    BpTree();//default constructor
	BpTree(int n );//Constructor: creates an empty tree, the parameter sets the number of keys that can be stored in each node (leaf and interior)
	void insert(int n, string value ); //inserts the key (int) and value (string) into the tree
	void remove(int n);// searches the tree for the key (int), if found removes the key and associated value from the tree
	string find(int n);// searches the tree for the key (int), if found returns the matching value
	void printKeys();//prints the keys in each node with nodes of the same level appearing on the same line
	void printValues(); //prints the values in key (not value) order
	~BpTree();//destructor
	
    

    private:
	//copy constructor
    BpTree(const BpTree & BpTree);
	//overload assignment operator
	BpTree& operator=(const BpTree &bp);//n=key
    //max number of keys in a node
    int max_num_keys;
    //key of the tree
    int key;
    //the value in a node
    string  *value;
    //maximum length of a string in the node
    int max_length;
    //boolean for checking if the node is a leaf
    bool IsLeaf;
    //declare a node with pointers
    struct node{
        int max_num_keys;//number of data and keys
        string  *data;//value
        node ** child_ptr;//pointer that points to the node's child
        node ** parent_ptr;//pointer that points to the node's parent
        bool leaf;//if this node is a leaf
        int  *key;//the key
        //node *root = NULL;
    } *root=NULL,*np = NULL, *x = NULL;
    //initialize the b plus tree node
    node * init();
    //traverse/iterate through the b plus tree, help search
    void traverse(node *p);
    //sometimes bplus tree needs to split nodes while inserting
    void split_child(node *x, int n, string value);
    //search function: if the key exist
    bool search(int n);
    //check if a node has no space
    bool IsNodeFull(node * nodename);
    //check if a node is empty
    bool IsNodeEmpty(node * nodename);
    //check is a node has at least half full
    bool IsNodeHalfFull(node * nodename);
    //remove all the nodes in the tree
    void removeAll();
    //deep copy the tree, return a complete tree
    BpTree deepcopy(const BpTree & BpTree);
    //deep copy a node,return a node
//    BpTree* copynode(const BpTree & node);

};