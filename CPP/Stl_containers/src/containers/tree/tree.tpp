#include "tree.h"

//------------ NODE CLASS ---------------------------------

template <class K, class V>
s21::Node<K, V>* s21::Node<K, V>::max_element(Node* root) {
  if (root == nullptr) {
    throw std::out_of_range("max_element called on nullptr");
  }
  Node* temp = root;
  while (temp->right != nullptr) temp = temp->right;
  return temp;
}

template <class K, class V>
const s21::Node<K, V>* s21::Node<K, V>::max_element(const Node* root) const {
  if (root == nullptr) {
    throw std::out_of_range("max_element called on nullptr");
  }
  const Node* temp = root;
  while (temp->right != nullptr) temp = temp->right;
  return temp;
}

template <class K, class V>
s21::Node<K, V>* s21::Node<K, V>::min_element(Node* root) {
  if (root == nullptr) {
    return nullptr;
  }
  Node* temp = root;
  while (temp->left != nullptr) temp = temp->left;
  return temp;
}

template <class K, class V>
const s21::Node<K, V>* s21::Node<K, V>::min_element(const Node* root) const {
  if (root == nullptr) {
    return nullptr;
  }
  const Node* temp = root;
  while (temp->left != nullptr) temp = temp->left;
  return temp;
}

//------------------------ TREE ITERATOR class -----------------------
template <class K, class V>
s21::TreeIterator<K, V>::TreeIterator() {
  tree_root = nullptr;
  node = nullptr;
}

template <class K, class V>
s21::TreeIterator<K, V>::TreeIterator(s21::Node<K, V>* root) {
  tree_root = root;
  node = nullptr;
}

template <class K, class V>
s21::TreeIterator<K, V>::TreeIterator(s21::Node<K, V>* root, s21::Node<K, V>* n)
    : tree_root(root), node(n){};

template <class K, class V>
s21::TreeIterator<K, V>::TreeIterator(const TreeIterator& it) {
  node = it.node;
  tree_root = it.tree_root;
}

template <class K, class V>
s21::TreeIterator<K, V>& s21::TreeIterator<K, V>::operator=(
    const TreeIterator& it) {
  node = it.node;
  tree_root = it.tree_root;
  return *this;
}

template <class K, class V>
s21::Node<K, V>* s21::TreeIterator<K, V>::getNode() {
  return node;
}

template <class K, class V>
s21::Node<K, V>* s21::TreeIterator<K, V>::getRootNode() {
  return tree_root;
}

template <class K, class V>
s21::TreeIterator<K, V>& s21::TreeIterator<K, V>::operator++() {
  if (node == nullptr) {
    return *this;
  }
  if (node->right != nullptr) {
    // find the smallest node on the right subtree
    s21::Node<K, V>* temp = node->right;
    while (temp->left != nullptr) {
      temp = temp->left;
    }
    node = temp;
  } else {
    // finished with right subtree and there is no right
    // search up for first parent with non-null right child
    // or nullptr
    auto parent = node->parent;
    while (parent != nullptr && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return *this;
}

template <class K, class V>
s21::TreeIterator<K, V> s21::TreeIterator<K, V>::operator++(int) {
  TreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <class K, class V>
s21::TreeIterator<K, V>& s21::TreeIterator<K, V>::operator--() {
  if (node == nullptr) {
    node = node->max_element(tree_root);
    return *this;
  }
  if (node->left != nullptr) {
    // find the smallest node on the right subtree
    node = node->max_element(node->left);
  } else {
    // finished with left subtree and there is no next left
    // search up for first parent with non-null right child
    // or nullptr
    auto parent = node->parent;
    while (parent != nullptr && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return *this;
}

template <class K, class V>
s21::TreeIterator<K, V> s21::TreeIterator<K, V>::operator--(int) {
  TreeIterator temp = *this;
  --(*this);
  return temp;
}

template <class K, class V>
bool s21::TreeIterator<K, V>::operator==(const TreeIterator& other) {
  if (other.node && this->node)
    return node->key == other.node->key;
  else
    return false;
}

template <class K, class V>
bool s21::TreeIterator<K, V>::operator!=(const TreeIterator& other) {
  return node != other.node;
}

template <class K, class V>
typename s21::TreeIterator<K, V>::reference
s21::TreeIterator<K, V>::operator*() {
  return node->key;
}

template <class K, class V>
typename s21::TreeIterator<K, V>::value_type&
s21::TreeIterator<K, V>::getValue() {
  return node->value;
}

template <class K, class V>
typename s21::TreeIterator<K, V>::pointer
s21::TreeIterator<K, V>::operator->() {
  return &(node->key);
}

// -------------------------- CONST ITERATOR CLASS ----------------

template <class K, class V>
s21::ConstTreeIterator<K, V>::ConstTreeIterator() {
  tree_root = nullptr;
  node = nullptr;
}

template <class K, class V>
s21::ConstTreeIterator<K, V>::ConstTreeIterator(s21::Node<K, V>* root) {
  tree_root = root;
  node = nullptr;
}

template <class K, class V>
s21::ConstTreeIterator<K, V>::ConstTreeIterator(const ConstTreeIterator& it) {
  tree_root = it.tree_root;
  node = it.node;
}

template <class K, class V>
s21::ConstTreeIterator<K, V>& s21::ConstTreeIterator<K, V>::operator=(
    const ConstTreeIterator& it) {
  tree_root = it.tree_root;
  node = it.node;
  return *this;
}

template <class K, class V>
const s21::Node<K, V>* s21::ConstTreeIterator<K, V>::getNode() {
  return node;
}

template <class K, class V>
s21::ConstTreeIterator<K, V>& s21::ConstTreeIterator<K, V>::operator++() {
  if (node == nullptr) {
    return *this;
  }
  if (node->right != nullptr) {
    // find the smallest node on the right subtree
    s21::Node<K, V>* temp = node->right;
    while (temp->left != nullptr) {
      temp = temp->left;
    }
    node = temp;
  } else {
    // finished with right subtree and there is no right
    // search up for first parent with non-null right child
    // or nullptr
    auto parent = node->parent;
    while (parent != nullptr && node == parent->right) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return *this;
}

template <class K, class V>
s21::ConstTreeIterator<K, V> s21::ConstTreeIterator<K, V>::operator++(int) {
  ConstTreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <class K, class V>
s21::ConstTreeIterator<K, V>& s21::ConstTreeIterator<K, V>::operator--() {
  if (node == nullptr) {
    node = node->max_element(tree_root);
    return *this;
  }
  if (node->left != nullptr) {
    // find the smallest node on the right subtree
    node = node->max_element(node->left);
  } else {
    // finished with left subtree and there is no next left
    // search up for first parent with non-null right child
    // or nullptr
    auto parent = node->parent;
    while (parent != nullptr && node == parent->left) {
      node = parent;
      parent = parent->parent;
    }
    node = parent;
  }
  return *this;
}

template <class K, class V>
s21::ConstTreeIterator<K, V> s21::ConstTreeIterator<K, V>::operator--(int) {
  ConstTreeIterator temp = *this;
  --(*this);
  return temp;
}

template <class K, class V>
bool s21::ConstTreeIterator<K, V>::operator==(const ConstTreeIterator& other) {
  if (other.node && this->node)
    return node->key == other.node->key;
  else
    return false;
}

template <class K, class V>
bool s21::ConstTreeIterator<K, V>::operator!=(const ConstTreeIterator& other) {
  return node != other.node;
}

template <class K, class V>
typename s21::ConstTreeIterator<K, V>::const_reference
s21::ConstTreeIterator<K, V>::operator*() const {
  return node->key;
}

template <class K, class V>
const typename s21::ConstTreeIterator<K, V>::value_type&
s21::ConstTreeIterator<K, V>::getValue() {
  return node->value;
}

template <class K, class V>
typename s21::ConstTreeIterator<K, V>::const_pointer
s21::ConstTreeIterator<K, V>::operator->() const {
  return &(node->key);
}

// ------------------------------------------- TREE TEMPLATE CLASS
// ---------------------------

template <class K, class V>
s21::TreeIterator<K, V> s21::Tree<K, V>::begin(s21::Node<K, V>* root) {
  s21::Node<K, V>* temp = root->min_element(root);
  s21::TreeIterator<K, V> it(root, temp);
  return it;
}

template <class K, class V>
s21::ConstTreeIterator<K, V> s21::Tree<K, V>::cbegin(
    s21::Node<K, V>* root) const {
  s21::Node<K, V>* temp = root;
  while (temp->left) {
    temp = temp->left;
  }
  s21::ConstTreeIterator<K, V> it(root, temp);
  return it;
}

template <class K, class V>
s21::TreeIterator<K, V> s21::Tree<K, V>::end(s21::Node<K, V>* root) {
  return s21::TreeIterator<K, V>(root);
}

template <class K, class V>
s21::ConstTreeIterator<K, V> s21::Tree<K, V>::cend(
    s21::Node<K, V>* root) const {
  return s21::ConstTreeIterator<K, V>(root);
}

template <class K, class V>
s21::TreeIterator<K, V> s21::Tree<K, V>::find(const K& key) {
  s21::Node<K, V>* temp = findNode(key, root);
  s21::TreeIterator<K, V> it(root, temp);
  return it;
}

template <class K, class V>
s21::ConstTreeIterator<K, V> s21::Tree<K, V>::find(const K& key) const {
  s21::Node<K, V>* temp = findNode(key, root);
  s21::ConstTreeIterator<K, V> it(temp);
  return it;
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::findNode(const K& key,
                                           s21::Node<K, V>* root) {
  if (root == nullptr) return nullptr;
  if (root->key == key) {
    return root;
  } else if (root->key < key) {
    return findNode(key, root->right);
  } else
    return findNode(key, root->left);
}

template <class K, class V>
void s21::Tree<K, V>::inorder(s21::Node<K, V>* root, int height, char wing) {
  if (root == NULL) {
    return;
  }
  height++;
  char curWing;
  if (wing == 'l')
    curWing = 'l';
  else if (wing == 'r')
    curWing = 'r';
  else
    curWing = 'b';
  // int rootValue = root->parent->data;
  inorder(root->left, height, 'l');
  // std::cout << root->data << " " ;
  if (root->parent != nullptr)
    std::cout << root->key << ", value " << root->value << " ,parent "
              << root->parent->key << ", height " << height << ", wing "
              << curWing << "\n";
  else
    std::cout << root->key << ", value " << root->value << " ,no parent "
              << ", height " << height << ", wing " << curWing << "\n";
  inorder(root->right, height, 'r');
}

template <class K, class V>
bool s21::Tree<K, V>::containsNode(s21::Node<K, V>* root, K d) {
  if (root == nullptr) {
    return 0;
  }
  bool is_contain = root->key == d ? 1 : 0;
  // bitwise OR to check if is_contatin or left or right subtree contain given
  // data
  return is_contain | containsNode(root->left, d) |
         containsNode(root->right, d);
}

/* ------------------INSERT-----------------------
_________________________________
|            5
        /           \           |
|     2               6
    /   \           /   \
|  -     -          -    -      |
---------------------------------
add 3:
    3 < 5 -> add to left subtree of 5 node
    3 > 2 -> add to right subtree of 2 node
    right subtree of 2 is nullptr -> create new node
_________________________________
|            5                  |
        /           \           |
|     2               6         |
    /   \           /   \       |
|  -     3          -    -      |

add 4:
    adding to right of 3 node
 _________________________________
|            5                  |
|       /           \           |
|     2              6          |
|   /   \           /   \       |
|  -     3          -    -      |
|       /  \                    |
|      -     4                  |
---------------------------------
after adding we need to check every node if its balanced or not
now tree is unbalanced because height of left subtree is 3 (2,3,4), height of
right is 1 (6) where root is 5! difference in heights MUST be between -1 and 1!

To balance we need make rotations:
   1) Single left rotation (pivot is 20, root is 10)
        10(root)
        \
         20(pivot) ->   20 (root)
           \           /  \
           30         10  30

        root->right = pivot->left;
        pivot->left = root;
        root = pivot;
    2) Single right rotation (pivot is 20, root is 30)
            30
           /
          20     ->          20
         /                  /  \
        10                 10  30
        root->left = pivot->right
        pivot->right = root
        root = pivot
    3) Left right rotation
            30                  30
           /                   /
          10      ->          20        ->      20
            \                /                 /  \
            20              10                10  30
        left rotation with  pivot is 20, root is 10
        right rotation with  pivot is 20, root is 30
    4) Right left rotation
            10          10
               \          \
                30  ->     20     ->      20
               /            \            /  \
              20             30         10  30
        right rotation with  pivot is 20, root is 30
        left rotation with  pivot is 20, root is 10
*/

template <class K, class V>
std::pair<s21::Node<K, V>*, bool> s21::Tree<K, V>::NodeInsert(
    K key, V value, s21::Node<K, V>*& root, s21::Node<K, V>* parent) {
  bool is_inserted = 0;
  if (root == NULL && this->m_size < std::numeric_limits<size_t>::max()) {
    root = new s21::Node<K, V>(key, value, nullptr, nullptr, parent);
    root->heigth = 1;
    this->m_size++;
    is_inserted = 1;

  } else if (root->key > key) {
    std::pair<s21::Node<K, V>*, bool> p =
        NodeInsert(key, value, root->left, root);
    root->left = p.first;
    is_inserted = p.second;
  } else if (root->key < key) {
    std::pair<s21::Node<K, V>*, bool> p =
        NodeInsert(key, value, root->right, root);
    root->right = p.first;
    is_inserted = p.second;
  }
  if (root) {
    updateHeight(root);
    root = balance(root);
  }

  // if tree rotated after balancing then address where key was placed could
  // changed need to find its pos and return!!!!!
  return std::make_pair(root, is_inserted);
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::R_Rotation(s21::Node<K, V>*& root) {
  s21::Node<K, V>* pivot = root->left;
  root->left = pivot->right;
  pivot->right = root;

  pivot->parent = root->parent;
  root->parent = pivot;
  if (root->left) root->left->parent = root;
  updateHeight(root);
  updateHeight(pivot);
  return pivot;
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::L_Rotation(s21::Node<K, V>*& root) {
  s21::Node<K, V>* pivot = root->right;
  root->right = pivot->left;
  pivot->left = root;

  pivot->parent = root->parent;
  root->parent = pivot;
  if (root->right) root->right->parent = root;
  updateHeight(root);
  updateHeight(pivot);
  return pivot;
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::LR_Rotation(s21::Node<K, V>*& root) {
  root->left = L_Rotation(root->left);
  return R_Rotation(root);
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::RL_Rotation(s21::Node<K, V>*& root) {
  root->right = R_Rotation(root->right);
  return L_Rotation(root);
}

template <class K, class V>
s21::Node<K, V>* s21::Tree<K, V>::balance(s21::Node<K, V>*& root) {
  int balance_factor = height(root->left) - height(root->right);

  if (balance_factor > 1) {
    if (height(root->left->left) > height(root->left->right)) {
      root = R_Rotation(root);
    } else
      root = LR_Rotation(root);
  } else if (balance_factor < -1) {
    if (height(root->right->right) > height(root->right->left)) {
      root = L_Rotation(root);
    } else
      root = RL_Rotation(root);
  }
  return root;
};

template <class K, class V>
void s21::Tree<K, V>::updateHeight(s21::Node<K, V>* root) {
  if (root != nullptr) {
    root->heigth = 1 + std::max(height(root->left), height(root->right));
  }
}

template <class K, class V>
int s21::Tree<K, V>::height(s21::Node<K, V>* root) {
  int h = 0;
  if (root != nullptr) {
    h = root->heigth;
  }
  return h;
}

/*
      5                      5
     /  \                   / \
    3    6 -> erase 3 ->   2   6
   /
  2

      5                       5
     /  \                   /   \
    3    6 -> erase 3 ->   2     6
     \
     2

              30                        20
            /   \                      /  \
          20     70 -> erase 30 ->    10   70
         /      /                         /
       10      50                        50
              /  \                      /  \
             40  60                    40  60
    1) find the largest value on the left - 20
    2) assing to 30 node new found value 30.data = 20
    3) assing to 30.left = 20.left


             30                         40
            /   \                      /  \
          20     70 -> erase 30 ->    20   70
         /      /                    /    /
       10      50                   10   50
              /  \                      /  \
             40  60                   (40)  60
    1) find the smallest value on the right - 40
    2) assing to 30 node new found value 30.data = 20
    3) delete that last node 40
*/

template <class K, class V>
void s21::Tree<K, V>::eraseNode(const K& key, s21::Node<K, V>*& root) {
  if (root == nullptr) return;

  if (key < root->key) {
    return eraseNode(key, root->left);
  } else if (key > root->key) {
    return eraseNode(key, root->right);
  }
  // if value == root->data and root has both subtrees
  if (root->left != nullptr && root->right != nullptr) {
    // two children
    // replace node value with smallest value from the right subtree

    if (height(root->left) < height(root->right)) {
      s21::Node<K, V>* min = root->min_element(root->right);
      root->key = min->key;
      return eraseNode(root->key, root->right);
    } else {
      s21::Node<K, V>* max = root->max_element(root->left);
      root->key = max->key;
      return eraseNode(root->key, root->left);
    }
  } else {
    // if value == root->data but root has one or none subtrees
    // remove a leaf node or node with 1 subtree
    if (root->left != nullptr || root->right != nullptr) {  // with 1 subtree
      s21::Node<K, V>* temp = root->parent;
      root = (root->left != nullptr) ? root->left : root->right;
      root->parent = temp;
    } else {  // no subtrees
      s21::Node<K, V>* temp = root->parent;
      root = (root->left != nullptr) ? root->left : root->right;
      // if removed last subtree from parent - decrease parents height
      if (temp->left == nullptr && temp->right == nullptr) temp->heigth -= 1;
    }
    this->m_size--;
  }
}  // end eraseNode function

template <class K, class V>
s21::Tree<K, V>::Tree() {
  root = nullptr;
  m_size = 0;
};

template <class K, class V>
s21::Tree<K, V>::Tree(const K& key, const V& value) {
  root = new s21::Node<K, V>();
  root->key = key;
  root->value = value;
  m_size = 1;
}

template <class K, class V>
s21::Tree<K, V>::Tree(const Tree& other) {
  *this = other;
}

template <class K, class V>
s21::Tree<K, V>& s21::Tree<K, V>::operator=(const Tree& other) {
  const_iterator it = other.cbegin(other.root);
  if (it.node) {
    root = new s21::Node<K, V>();
    root->key = *it;
    root->value = it.getValue();
    m_size = 1;
    ++it;
    for (; it != other.cend(other.root); it++) {
      TreeInsert(*it, it.getValue());
    }
  } else {
    root = nullptr;
    m_size = 0;
  }
  return *this;
}

template <class K, class V>
s21::Tree<K, V>::Tree(Tree&& other) {
  if (this != other) {
    delete root;
    root = other.root;
    other.root = nullptr;
  }
}

template <class K, class V>
s21::Tree<K, V>& s21::Tree<K, V>::operator=(const Tree&& other) {
  if (this != other) {
    delete root;
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <class K, class V>
s21::Tree<K, V>::~Tree() {
  clear(root);
}

template <class K, class V>
std::pair<s21::Node<K, V>*, bool> s21::Tree<K, V>::TreeInsert(const K& key,
                                                              const V& value) {
  return NodeInsert(key, value, root, nullptr);
}

template <class K, class V>
void s21::Tree<K, V>::print() {
  if (root != nullptr) {
    inorder(root, 0, 'b');
    std::cout << std::endl;
  }
}

template <class K, class V>
bool s21::Tree<K, V>::contains(K key) {
  return containsNode(root, key);
}

template <class K, class V>
void s21::Tree<K, V>::erase(const K& key) {
  eraseNode(key, root);
}

template <class K, class V>
void s21::Tree<K, V>::clear(s21::Node<K, V>* root) {
  if (root == nullptr) {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
  root = nullptr;
}

// ------------------ friend function ---------------------------
template <class K, class V>
typename s21::Tree<K, V>::Node* max_element(
    typename s21::Tree<K, V>::Node*& root) {
  if (root == nullptr) {
    throw std::out_of_range("max_element called on nullptr");
  }
  while (root->right != nullptr) root = root->right;
  return root;
};