#include "s21_map.h"

// ----------------------- constructors --------------------
template <typename Key, typename T>
s21::Map<Key, T>::Map() {
  tree = new Tree<Key, T>;
}

template <typename Key, typename T>
s21::Map<Key, T>::Map(std::initializer_list<value_type> const& items) {
  tree = new Tree<Key, T>;
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
  element_number = tree->m_size;
}

template <typename Key, typename T>
s21::Map<Key, T>::Map(const Map& m) {
  tree = new Tree<Key, T>(*m.tree);
  element_number = m.element_number;
}

template <typename Key, typename T>
s21::Map<Key, T>::Map(Map&& m) : tree(nullptr) {
  if (m.tree != nullptr) {
    tree = m.tree;
    m.tree = nullptr;
  }
}

template <typename Key, typename T>
s21::Map<Key, T>::~Map() {
  delete tree;
  tree = nullptr;
}

template <typename Key, typename T>
s21::Map<Key, T>& s21::Map<Key, T>::operator=(Map&& m) {
  if (tree != m.tree) {
    tree = m.tree;
    m.tree = nullptr;
    m.element_number = 0;
  }
  return *this;
}

// -------------------- Map Element access ------------------
// access specified element with bounds checking
template <typename Key, typename T>
T& s21::Map<Key, T>::at(const Key& key) {
  s21::Map<Key, T>::iterator it = this->find(key);
  if (it.getNode()) {
    return it.getValue();
  } else {
    throw std::out_of_range("map::at\n");
  }
}

// access or insert specified
// if there is no node with that key = create node with that key and value = 0
// if that key exists -> return value
template <typename Key, typename T>
T& s21::Map<Key, T>::operator[](const Key& key) {
  s21::Map<Key, T>::iterator it = this->find(key);
  if (it.getNode()) {  // found node with that key
    return it.getValue();
  } else {     // didnt found node -> create node with that key and zero value
    T temp{};  // default T constructor - to make zero value
    this->insert(key, temp);
    return this->find(key).getValue();
  }
}

// ------------------------- ITERATORS ---------------------

template <typename Key, typename T>
typename s21::Map<Key, T>::iterator s21::Map<Key, T>::begin() {
  return tree->begin(tree->root);
}

template <typename Key, typename T>
typename s21::Map<Key, T>::iterator s21::Map<Key, T>::end() {
  return tree->end(tree->root);
}

template <typename Key, typename T>
typename s21::Map<Key, T>::const_iterator s21::Map<Key, T>::cbegin() {
  return tree->cbegin(tree->root);
}

template <typename Key, typename T>
typename s21::Map<Key, T>::const_iterator s21::Map<Key, T>::cend() {
  return tree->cend(tree->root);
}

// ------------------------ MAP CAPACITY ----------------------

template <typename Key, typename T>
bool s21::Map<Key, T>::empty() {
  return tree->m_size == 0;
}

template <typename Key, typename T>
typename s21::Map<Key, T>::size_type s21::Map<Key, T>::size() {
  if (tree != nullptr) {
    element_number = tree->m_size;
  } else
    element_number = 0UL;
  return element_number;
}

template <typename Key, typename T>
typename s21::Map<Key, T>::size_type s21::Map<Key, T>::max_size() {
  return std::numeric_limits<size_t>::max();
}

// ----------------------- MAP MODIFIERS ----------------------
template <typename Key, typename T>
void s21::Map<Key, T>::clear() {
  tree->clear(tree->root);
  element_number = tree->m_size = 0;
  tree->root = nullptr;
}

// inserts node and returns iterator to where the element is in the container
// and bool denoting whether the insertion took place
template <typename Key, typename T>
std::pair<typename s21::Map<Key, T>::iterator, bool> s21::Map<Key, T>::insert(
    const value_type& value) {
  std::pair<s21::Node<Key, T>*, bool> p =
      tree->TreeInsert(value.first, value.second);
  iterator it = find(value.first);
  element_number = tree->m_size;
  return std::make_pair(it, p.second);
}

// inserts value by key and returns iterator to where the element is in the
// container and bool denoting whether the insertion took place
template <typename Key, typename T>
std::pair<typename s21::Map<Key, T>::iterator, bool> s21::Map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<s21::Node<Key, T>*, bool> p = tree->TreeInsert(key, obj);
  iterator it = find(key);
  element_number = tree->m_size;
  return std::make_pair(it, p.second);
}

// inserts an element or assigns to the current element if the key already
// exists means that key is same but objs differ - so we need to replace obj at
// key position
template <typename Key, typename T>
std::pair<typename s21::Map<Key, T>::iterator, bool>
s21::Map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  std::pair<iterator, bool> p = insert(key, obj);
  if (p.second == false) {
    if ((p.first).getNode()->value != obj) {
      (p.first).getNode()->value = obj;
      p.second = true;
    }
  }
  return p;
}

template <typename Key, typename T>
void s21::Map<Key, T>::erase(iterator& pos) {
  if (pos.getNode() !=
      nullptr)  // check if iterator is pointing to existing node
    tree->erase(*pos);
  element_number = tree->m_size;
}

template <typename Key, typename T>
void s21::Map<Key, T>::swap(Map& other) {
  Tree<Key, T>* temp = tree;
  tree = other.tree;
  other.tree = temp;

  element_number = tree->m_size;
  other.element_number = other.tree->m_size;
}

template <typename Key, typename T>
void s21::Map<Key, T>::merge(Map& other) {
  s21::Map<Key, T>::iterator it;
  for (it = other.begin(); it != other.end(); it++) {
    insert(*it, it.getNode()->value);
  }
}

//------------------------ MAP LOOKUP ---------------------------
template <typename Key, typename T>
typename s21::Map<Key, T>::iterator s21::Map<Key, T>::find(const Key& key) {
  return tree->find(key);
}

template <typename Key, typename T>
bool s21::Map<Key, T>::contains(const Key& key) {
  return tree->find(key).getNode() == nullptr ? 0 : 1;
}

//------------------ CUSTOM PRINTING FUNCTIONS ------------------

template <typename Key, typename T>
void s21::Map<Key, T>::info_print() {
  tree->print();
}

template <typename Key, typename T>
void s21::Map<Key, T>::print() {
  s21::Set<int>::iterator it;
  for (it = this->begin(); it != this->end(); it++) {
    std::cout << *it << " " << it.getValue() << "\n";
  }
  std::cout << "\n";
}
