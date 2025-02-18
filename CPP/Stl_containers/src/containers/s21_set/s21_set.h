#ifndef S21_SET
#define S21_SET


#include "../tree/tree.h"

namespace s21{

template<typename Key>
    class Set
    {
        private:
            Tree<Key,int> *tree;
            size_t element_number;  

        public:

            // ---------------------- TYPE REDEFINITIONS ----------------------
            using key_type = Key;
            using value_type = Key;            
            using reference = value_type &;
            using const_reference = const value_type &;
            //need 'typename' because  's21::Tree<Key, int>' is a dependent scope
            //it depends on TEMPLATE PARAMETER = <Key, int> !!!
            using iterator = typename s21::TreeIterator<Key,int>;
            using const_iterator = typename s21::ConstTreeIterator<Key,int>;
            using size_type = size_t;

            // ----------------------- constructors --------------------
            Set();
            Set(std::initializer_list<value_type> const &items);           
            Set(const Set &s); //copy constructor - calls Tree deep copy constructor
            Set(Set &&s);   //move constructor
            ~Set();
            Set& operator=(Set &&s);

            // ------------------------- ITERATORS --------------------- 
            iterator begin();
            iterator end();
            const_iterator cbegin();
            const_iterator cend();

            // ------------------------ SET CAPACITY ----------------------
            bool empty();
            size_type size();
            size_type max_size();

            // ----------------------- SET MODIFIERS ----------------------           
            void clear();           
            std::pair<iterator, bool> insert(const value_type& value);
            void erase(iterator& pos);
            void swap(Set& other);
            void merge(Set& other);
            
            //------------------------ SET LOOKUP ---------------------------
            iterator find(const Key& key);
            bool contains(const Key& key);

            //------------------ CUSTOM PRINTING FUNCTIONS ------------------
            void info_print();
            void print();            
    };

    #include "s21_set.tpp"


} //end namespace s21

#endif