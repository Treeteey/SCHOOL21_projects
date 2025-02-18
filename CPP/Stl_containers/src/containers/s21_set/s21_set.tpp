#include "s21_set.h"

// ----------------------- constructors --------------------
template <typename Key>
s21::Set<Key>::Set() {
  tree = new Tree<Key, int>;
  element_number = 0;
};

template <typename Key>
s21::Set<Key>::Set(std::initializer_list<Key> const& items) {
  tree = new Tree<Key, int>;
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
  element_number = tree->m_size;
};

template <typename Key>
s21::Set<Key>::Set(const Set& s) {
  tree = new Tree<Key, int>(*s.tree);
  element_number = s.element_number;
}

template <typename Key>
s21::Set<Key>::Set(Set&& s) : tree(nullptr) {  // move constructor
  if (s.tree != nullptr) {
    delete tree;
    tree = s.tree;
    s.tree = nullptr;
    this->element_number = s.element_number;
    s.element_number = 0;
  }
}

template <typename Key>
s21::Set<Key>::~Set() {
  delete tree;
};

template <typename Key>
s21::Set<Key>& s21::Set<Key>::operator=(Set&& s) {
  if (tree != s.tree) {
    delete tree;
    tree = s.tree;
    s.tree = nullptr;
  }
  return *this;
}

// -------------------------------------------- ITERATORS
// --------------------------------------
template <typename Key>
typename s21::Set<Key>::iterator s21::Set<Key>::begin() {
  return tree->begin(tree->root);
}

template <typename Key>
typename s21::Set<Key>::iterator s21::Set<Key>::end() {
  return tree->end(tree->root);
}

template <typename Key>
typename s21::Set<Key>::const_iterator s21::Set<Key>::cbegin() {
  return tree->cbegin(tree->root);
}

template <typename Key>
typename s21::Set<Key>::const_iterator s21::Set<Key>::cend() {
  return tree->cend(tree->root);
}

// ------------------------ SET CAPACITY ----------------------

template <typename Key>
bool s21::Set<Key>::empty() {
  return this->element_number == 0;
}

template <typename Key>
typename s21::Set<Key>::size_type s21::Set<Key>::size() {
  return element_number = tree->m_size;
}

template <typename Key>
typename s21::Set<Key>::size_type s21::Set<Key>::max_size() {
  return std::numeric_limits<size_t>::max();
}

// ----------------------- SET MODIFIERS ----------------------

template <typename Key>
void s21::Set<Key>::clear() {
  tree->clear(tree->root);
  element_number = tree->m_size = 0;
  tree->root = nullptr;
}

template <typename Key>
std::pair<typename s21::Set<Key>::iterator, bool> s21::Set<Key>::insert(
    const value_type& value) {
  std::pair<s21::Node<Key, int>*, bool> p = tree->TreeInsert(value, 0);
  iterator it = find(value);
  element_number = tree->m_size;
  return std::make_pair(it, p.second);
}

template <typename Key>
void s21::Set<Key>::erase(iterator& pos) {
  if (pos.getNode() != nullptr)  // check if iterator is not nullptr
    tree->erase(*pos);
  element_number = tree->m_size;
}

template <typename Key>
void s21::Set<Key>::swap(Set& other) {
  Tree<Key, int>* temp = tree;
  tree = other.tree;
  other.tree = temp;

  element_number = tree->m_size;
  other.element_number = other.tree->m_size;
}

template <typename Key>
void s21::Set<Key>::merge(Set& other) {
  for (iterator it = other.begin(); it != other.end(); it++) {
    Key temp = *it;
    if (!contains(temp)) insert(temp);
  }
}

//------------------------ SET LOOKUP ---------------------------

template <typename Key>
typename s21::Set<Key>::iterator s21::Set<Key>::find(const Key& key) {
  return tree->find(key);
}

template <typename Key>
bool s21::Set<Key>::contains(const Key& key) {
  return tree->find(key).getNode() == nullptr ? 0 : 1;
}

//------------------ CUSTOM PRINTING FUNCTIONS ------------------

template <typename Key>
void s21::Set<Key>::info_print() {
  tree->print();
}

template <typename Key>
void s21::Set<Key>::print() {
  iterator it(tree->root);
  for (it = this->begin(); it != this->end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}