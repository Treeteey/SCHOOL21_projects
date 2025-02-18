#ifndef S21_MAP
#define S21_MAP

#include <stdexcept>
#include "../tree/tree.h"

namespace s21{

template<typename Key, typename T>
    class Map
    {
        private:
            Tree<Key,T> *tree;
            size_t element_number;  

        public:

            // ---------------------- TYPE REDEFINITIONS ----------------------
            using key_type = Key;
            using mapped_type = T;
            using value_type = std::pair<const key_type,mapped_type>;            
            using reference = value_type &;
            using const_reference = const value_type &;
            //need 'typename' because  's21::Tree<Key, int>' is a dependent scope
            //it depends on TEMPLATE PARAMETER = <Key, int> !!!

            using iterator = typename s21::TreeIterator<Key,T>;
            using const_iterator = typename s21::ConstTreeIterator<Key,T>;
            using size_type = size_t;

            // ----------------------- constructors --------------------
            Map();
            Map(std::initializer_list<value_type> const &items);
            Map(const Map &m);
            Map(Map &&m);   //move constructor
            ~Map();
            Map& operator=(Map &&m);


            // -------------------- Map Element access ------------------
            //access specified element with bounds checking  
            T& at(const Key& key);

            //access or insert specified 
            //if there is no node with that key = create node with that key and value = 0
            //if that key exists -> return value
            T& operator[](const Key& key);

            // ------------------------- ITERATORS --------------------- 

            iterator begin();
            iterator end();
            const_iterator cbegin();
            const_iterator cend();

            // ------------------------ MAP CAPACITY ----------------------
            bool empty();
            size_type size();
            size_type max_size();

            // ----------------------- MAP MODIFIERS ----------------------           
            void clear();
           
            //inserts node and returns iterator to where the element is in the container 
            //and bool denoting whether the insertion took place
            std::pair<iterator, bool> insert(const value_type& value);

            //inserts value by key and returns iterator to where the element is in the container 
            //and bool denoting whether the insertion took place
            std::pair<iterator, bool> insert(const Key& key, const T& obj);

            //inserts an element or assigns to the current element if the key already exists
            //means that key is same but objs differ - so we need to replace obj at key position
            std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

            void erase(iterator& pos);
            void swap(Map& other);
            void merge(Map& other);
            
            //------------------------ MAP LOOKUP ---------------------------

            iterator find(const Key& key);
            bool contains(const Key& key);


        //------------------ CUSTOM PRINTING FUNCTIONS ------------------
        //change to PUBLIC to have access
        private:            
            void info_print();
            void print();            
    };

    #include "s21_map.tpp"


} //end namespace s21

#endif