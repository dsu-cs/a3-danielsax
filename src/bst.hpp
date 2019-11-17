#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);

    void printVec(std::vector<T> *);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    Node<T> *insertHelper(T, Node<T> *)
    std::vector<T> *inorderHelper(Node<T> *);
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    vec = insertHelper(root, vec);
    return vec;
}

template<class T>
 std::vector<T> * BST<T>::inorderHelper(Node<T> *sub_root, std::vector<T> *head)
{
    std::vector<T> *vec = new std::vector<T>;
    if (sub_root != NULL) {
        
    }

    return vec;
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;

    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = BST<T>::insertHelper(new_data, root);
}

template<class T>
Node<T> * BST<T>::insertHelper(T new_data, Node<T> *sub_root)
{
    if (sub_root == NULL) {
        Node<T> *new_node = new Node<T>(new_data);
        sub_root = new_node;
        count++;
        return 
    }
    else if (sub_root->get_data() == new_data) {
        return NULL;
    }
    else if (new_data < sub_root->get_data()) {
        insertHelper(new_data, sub_root->get_left())
    }
    else {
        insertHelper(new_data, sub_root->get_right())
    }
    return 0;
}


template<class T>
Node<T> *BST<T>::search(T val)
{

}



template<class T>
void BST<T>::remove(T val)
{

}



template<class T>
int BST<T>::get_size()
{

}

void BST<T>::printVec(std::vector<T> *head)
{
    while (!head->empty()) {
        std::cout << head->back() << " ";
        head->pop_back();
    }
    std::cout << endl;
}