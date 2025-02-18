#pragma once

#include <iostream>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <limits>
// #include "s21_set.h"

namespace s21{

//------------ NODE CLASS ---------------------------------
template <class K, class V>
struct Node{
    K key;
    V value;
    Node *left;
    Node *right;
    Node *parent; //for iterator
    int heigth;
    Node(const K& key = K{},
        const V& value = V{},
        Node * left_ = nullptr, 
        Node * right_ = nullptr, 
        Node * parent_ = nullptr) 
        : key{key}, value{value}, left{left_}, right{right_}, parent{parent_}{}
    
    Node* max_element(Node* root);
    const Node* max_element(const Node* root) const;
    Node* min_element(Node* root);
    const Node* min_element(const Node* root) const;
}; 
//----------- END NODE CLASS  


    //------------------------ TREE ITERATOR class -----------------------
template <class K, class V>
    struct TreeIterator{
        typedef K key_type;
        typedef V value_type;
        typedef K* pointer;
        typedef K& reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;        
    public:
        
        s21::Node<K,V>* tree_root;  
        s21::Node<K,V>*  node;         
        int number_elements = 0;

        TreeIterator();
        TreeIterator(s21::Node<K,V>* root);
        TreeIterator(s21::Node<K,V>* root, s21::Node<K,V>* n);
        TreeIterator(const TreeIterator& it);
        TreeIterator& operator=(const TreeIterator& it);

        s21::Node<K,V>* getNode();
        s21::Node<K,V>* getRootNode();
        //prefix increment
        TreeIterator& operator++();
        //postfix increment, int argument is dummy used to differentiate from prefix
        //need to return copy of current pos of iterator, and make increment in original
        TreeIterator operator++(int);
        TreeIterator& operator--();
        TreeIterator operator--(int);
        bool operator==(const TreeIterator& other);
        bool operator!=(const TreeIterator& other);

        /*dereference operator overload: 
            TreeIterator it;
            *it = key            
        */
        reference operator*();
        value_type& getValue();
        pointer operator->();
    }; 
    //----------------- END ITERATOR CLASS -------------------------



// -------- CONST ITERATOR CLASS ----------------
template <class K, class V>
struct ConstTreeIterator{
    typedef K key_type;
    typedef V value_type;
    typedef K* const_pointer;
    typedef const K& const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    
public:    
    s21::Node<K,V> const * tree_root;   
    s21::Node<K,V> const * node;        
    size_t number_elements = 0;

    ConstTreeIterator();
    ConstTreeIterator(s21::Node<K,V>* root);
    ConstTreeIterator(s21::Node<K,V>* root, s21::Node<K,V>* n) : tree_root(root), node(n){};
    ConstTreeIterator(const ConstTreeIterator& it);
    ConstTreeIterator& operator=(const ConstTreeIterator& it);
    const s21::Node<K,V>* getNode();

    //prefix increment
    ConstTreeIterator& operator++();
    //postfix increment, int argument is dummy used to differentiate from prefix
    //need to return copy of current pos of iterator, and make increment in original
    ConstTreeIterator operator++(int);
    ConstTreeIterator& operator--();
    ConstTreeIterator operator--(int);
    bool operator==(const ConstTreeIterator& other);
    bool operator!=(const ConstTreeIterator& other);

    /*dereference operator overload: 
        TreeIterator it;
        *it = key            
    */
    const_reference operator*() const;
    const value_type& getValue();
    const_pointer operator->() const;
};
//----------------- END CONST ITERATOR CLASS -------------------------



// ------------------------------------------- TREE TEMPLATE CLASS ---------------------------
template <class K, class V>
class Tree{    
    public:
        typedef V value_type;
        typedef K key_type;
        typedef typename s21::TreeIterator<K,V> iterator; //we dont want to reassign data using iterator!!!
        typedef typename s21::ConstTreeIterator<K,V> const_iterator ;

        s21::Node<K,V>* root;           //pointer to the root of BST (binary search tree)
        size_t m_size;        //current element count 

        //------------- Tree constructors -------------------
        Tree();
        Tree(const K& key, const V& value);              
        Tree(const Tree& other);// copy construct and assign          
        Tree& operator=(const Tree& other);// deep copy        
        Tree(Tree&& other);// move construct and assign
        Tree& operator=(const Tree&& other);        
        ~Tree();

        std::pair<s21::Node<K,V>*, bool> TreeInsert(const K& key, const V& value);

        void print();
        bool contains(K key);
        void erase(const K& key);
        void clear(s21::Node<K,V>* root);

        s21::TreeIterator<K,V> begin(s21::Node<K,V>* root);
        s21::TreeIterator<K,V> end(s21::Node<K,V>* root);
        s21::ConstTreeIterator<K,V> cbegin(s21::Node<K,V>* root) const;
        s21::ConstTreeIterator<K,V> cend(s21::Node<K,V>* root) const;
        s21::TreeIterator<K,V> find(const K& key);
        s21::ConstTreeIterator<K,V> find(const K& key) const;

    private:
        s21::Node<K,V>* findNode(const K& key, s21::Node<K,V>* root);         
        void inorder(s21::Node<K,V> *root, int height, char wing);//function to print inorder tree        
        bool containsNode(s21::Node<K,V> *root, K d);//checks if tree contains given data 'd' in all tree
        std::pair<s21::Node<K,V>*, bool> NodeInsert(K key, V value, s21::Node<K,V>*& root, s21::Node<K,V> *parent);
        s21::Node<K,V>* R_Rotation(s21::Node<K,V>* &root);
        s21::Node<K,V>* L_Rotation(s21::Node<K,V>* &root);
        s21::Node<K,V>* LR_Rotation(s21::Node<K,V> * &root);
        s21::Node<K,V>* RL_Rotation(s21::Node<K,V> * &root);
        s21::Node<K,V>* balance(s21::Node<K,V>* &root);
        void updateHeight(s21::Node<K,V>* root);
        int height(s21::Node<K,V> *root);
        void eraseNode(const K& key, s21::Node<K,V>*& root);
}; // end Tree class

#include "tree.tpp"

} //end namespace s21
