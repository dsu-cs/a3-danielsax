#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include <vector>
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

private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    Node<T> *insertHelper(T, Node<T> *);
    std::vector<T> *inorderHelper(Node<T> *, std::vector<T> *);
    std::vector<T> *preorderHelper(Node<T> *, std::vector<T> *);
    std::vector<T> *postorderHelper(Node<T> *, std::vector<T> *);
    Node<T> *searchHelper(T, Node<T> *);
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
    BST<T>::inorderHelper(root, vec);
    return vec;
}

template<class T>
 std::vector<T> * BST<T>::inorderHelper(Node<T> *sub_root, std::vector<T> *head)
{
    if (sub_root != NULL) {
        inorderHelper(sub_root->get_left(), head);
        head->push_back(sub_root->get_data());
        inorderHelper(sub_root->get_right(), head);
    }
    return head;
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    BST<T>::preorderHelper(root, vec);
    return vec;
}

template<class T>
 std::vector<T> * BST<T>::preorderHelper(Node<T> *sub_root, std::vector<T> *head)
{
    if (sub_root != NULL) {
        head->push_back(sub_root->get_data());
        preorderHelper(sub_root->get_left(), head);
        preorderHelper(sub_root->get_right(), head);
    }
    return head;
}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    BST<T>::postorderHelper(root, vec);
    return vec;
}

template<class T>
 std::vector<T> * BST<T>::postorderHelper(Node<T> *sub_root, std::vector<T> *head)
{
    if (sub_root != NULL) {
        postorderHelper(sub_root->get_left(), head);
        postorderHelper(sub_root->get_right(), head);
        head->push_back(sub_root->get_data());
    }
    return head;
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
        node_count++;
        return sub_root;
    }
    else if (sub_root->get_data() == new_data) {
        return sub_root;
    }
    else if (new_data < sub_root->get_data()) {
        sub_root->set_left(insertHelper(new_data, sub_root->get_left()));
    }
    else {
        sub_root->set_right(insertHelper(new_data, sub_root->get_right()));
    }
    return sub_root;
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    return BST<T>::searchHelper(val, root);
}

template<class T>
Node<T> *BST<T>::searchHelper(T val, Node<T> *sub_root)
{
    if (sub_root == NULL) {
        return NULL;
    }
    else if (sub_root->get_data() == val) {
        return sub_root;
    }
    else if (val < sub_root->get_data()) {
        return BST<T>::searchHelper(val, sub_root->get_left());
    }
    else if (val > sub_root->get_data()) {
        return BST<T>::searchHelper(val, sub_root->get_right());
    }
}

template<class T>
void BST<T>::remove(T val)
{
    Node<T> * del;                                                          //finds node to delete
    Node<T> * trail;                                                        //trails del inorder skip past
    Node<T> * replace;
    T replaceVal;
    del = root;
    trail = NULL;
    while (del != NULL) {                                                   //loop finds node to be deleted
        if (del->get_data() == val) {                                       //Node found
            if (del->get_left() == NULL && del->get_right() == NULL) {      //For leaf case
                if (trail == NULL) {                                        //Handles root case
                    root = NULL;
                    delete(del);
                } 
                else if (del == trail->get_right()) {                       //Handles right case
                    trail->set_right(NULL);
                    delete(del);
                }
                else {                                                      //Handles left case
                    trail->set_left(NULL);
                    delete(del);            
                }
            }
            else if (del->get_left() != NULL && del->get_right() != NULL) { //Handles two child case
                replace = del->get_left();
                while (replace->get_right() != NULL) {                      //Searches for largest Node in right branch
                    replace = replace->get_right();
                }
                replaceVal = replace->get_data();
                BST<T>::remove(replaceVal);
                del->set_data(replaceVal);
            }
            else if (del->get_left() != NULL) {                               //Handles one left child case
                if (trail == NULL) {                                        //Handles root case
                    root = del->get_left();
                    delete(del);
                }
                else if (trail->get_right() == del) {                       //Handles right case
                    trail->set_right(del->get_left());
                    delete(del);
                }
                else {                                                      //Handles left case
                    trail->set_left(del->get_left());
                    delete(del);
                }
            }
            else {                                                          //Handles one right child case
                if (trail == NULL) {                                        //Handles root case
                    root = del->get_right();
                    delete(del);
                }
                else if (trail->get_right() == del) {                       //Handles right case
                    trail->set_right(del->get_right());
                    delete(del);
                }
                else {                                                      //Handles left case
                    trail->set_left(del->get_right());
                    delete(del);
                }
            }
            return;
        }
        else if (val < del->get_data()) {                                   //searches left case
            trail = del;
            del = del->get_left();
        }
        else {                                                              //searches right case
            trail = del;
            trail = del->get_left();
        }
    }
}

template<class T>
int BST<T>::get_size()
{
    return node_count;
}