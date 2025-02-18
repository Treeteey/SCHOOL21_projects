namespace s21 {

template <class value_type>
List<value_type>::List() {
  ResetUnite();
}

template <class value_type>
List<value_type>::List(size_type n) : head_(nullptr), tail_(nullptr) {
  if (n == 0) {
    ResetUnite();
  } else {
    for (size_type i = 0; i < n; i++) {
      PushBack(0);
    }
  }
}

template <class value_type>
List<value_type>::List(std::initializer_list<value_type> const &items)
    : List<value_type>() {
  for (auto item : items) {
    PushBack(item);
  }
}

template <class value_type>
List<value_type>::List(const List &l) : List<value_type>() {
  *this = l;
}

template <class value_type>
List<value_type>::List(List &&l) : List<value_type>() {
  *this = std::move(l);
}

template <class value_type>
List<value_type> &List<value_type>::operator=(const List<value_type> &l) {
  if (this != &l) {
    CopyList(l);
  }
  return *this;
}

template <class value_type>
List<value_type> &List<value_type>::operator=(List<value_type> &&l) {
  Clear();
  Swap(l);
  return *this;
}

template <class value_type>
List<value_type>::~List() {
  Clear();
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::Insert(
    List<value_type>::iterator pos, List<value_type>::const_reference value) {
  if (Empty()) {
    PushBack(value);
    pos++;
  } else if (pos == Begin()) {
    PushFront(value);
    pos--;
  } else if (pos == End()) {
    PushBack(value);
    pos--;
  } else {
    Node<value_type> *new_node = new Node<value_type>();
    new_node->value_ = value;
    new_node->next_ = pos.cur_node_;
    pos--;
    pos.cur_node_->next_ = new_node;
    new_node->prev_ = pos.cur_node_;
    pos++;
    pos++;
    pos.cur_node_->prev_ = new_node;
    pos--;
  }
  return iterator(pos.cur_node_);
}

template <typename value_type>
void List<value_type>::PopBack() {
  if (tail_ == head_) {
    delete tail_;
    ResetUnite();
  } else {
    Node<value_type> *current = tail_;
    tail_ = tail_->prev_;
    tail_->next_ = &last_;
    last_.prev_ = tail_;
    delete current;
  }
}

template <typename value_type>
void List<value_type>::PopFront() {
  if (head_ == tail_) {
    delete head_;
    ResetUnite();
  } else {
    Node<value_type> *current = head_;
    head_ = head_->next_;
    head_->prev_ = &last_;
    last_.next_ = head_;
    delete current;
  }
}

template <typename value_type>
void List<value_type>::Erase(List<value_type>::iterator pos) {
  if (!Empty()) {
    if (pos == Begin() || tail_ == head_) {
      PopFront();
    } else if (pos.cur_node_ == tail_) {
      PopBack();
    } else {
      Node<value_type> *current = pos.cur_node_;
      pos--;
      pos.cur_node_->next_ = current->next_;
      pos++;
      pos.cur_node_->prev_ = current->prev_;
      delete current;
    }
  }
}

template <typename value_type>
void List<value_type>::Reverse() {
  for (auto i = Begin(); i != End(); i--) {
    std::swap(i.cur_node_->next_, i.cur_node_->prev_);
  }
  std::swap(head_, tail_);
  last_.next_ = head_;
  last_.prev_ = tail_;
}

template <typename value_type>
void List<value_type>::BubbleSwap(List<value_type>::iterator pos) {
  if (pos != End() && pos.cur_node_ != tail_) {
    int check_tail = 0;
    int check_head = 0;
    if (pos.cur_node_->next_ == tail_) check_tail = 1;
    if (pos.cur_node_ == head_) check_head = 1;
    pos--;
    Node<value_type> *previous = pos.cur_node_;
    pos++;
    Node<value_type> *current = pos.cur_node_;
    pos++;
    Node<value_type> *next_node = pos.cur_node_;
    pos++;
    Node<value_type> *post_node = pos.cur_node_;

    previous->next_ = next_node;
    next_node->prev_ = previous;
    next_node->next_ = current;
    current->prev_ = next_node;
    current->next_ = post_node;
    post_node->prev_ = current;
    if (check_tail) {
      tail_ = current;
    }
    if (check_head) {
      head_ = next_node;
    }
  }
}

template <typename value_type>
void List<value_type>::Sort() {
  int check_sort = 0;
  while (check_sort == 0) {
    int check = 0;
    for (auto i = Begin(); i != End(); i++) {
      auto j = i;
      j++;
      if (j != End() && *i > *j) {
        BubbleSwap(i);
        check++;
      }
    }
    if (check == 0) check_sort = 1;
  }
}

template <typename value_type>
void List<value_type>::Unique() {
  for (auto i = Begin(); !Empty() && i != End();) {
    auto j = i;
    ++j;
    if (j != End() && *j == *i) {
      Erase(j);
    } else {
      ++i;
    }
  }
}

template <typename value_type>
void List<value_type>::Splice(List<value_type>::const_iterator pos,
                              List<value_type> &other) {
  if (!other.Empty()) {
    other.Reverse();
    auto i = other.End();
    i--;
    for (; i != other.End(); i--) {
      Insert(pos, i.cur_node_->value_);
    }
    other.Clear();
  }
}

template <typename value_type>
void List<value_type>::Merge(List<value_type> &other) {
  if (this != &other) {
    if (Empty())
      Swap(other);
    else {
      TransferElem(other);
      other.ResetUnite();
    }
  }
}

template <typename value_type>
void List<value_type>::TransferElem(List<value_type> &other) {
  auto j = other.Begin();
  for (auto i = Begin(); i != End() && j != other.End(); i++) {
    if (*j < *i) {
      i = Insert(i, *j);
      j++;
      other.PopFront();
    }
  }
}

template <typename value_type>
void List<value_type>::Swap(List<value_type> &l) {
  if (Empty() && !l.Empty()) {
    tail_ = nullptr;
    head_ = nullptr;
    SwapingProc(l);
    PointerNewWay();
    l.tail_ = l.head_ = &l.last_;
  } else if (!Empty() && l.Empty()) {
    l.tail_ = nullptr;
    l.head_ = nullptr;
    SwapingProc(l);
    l.PointerNewWay();
    tail_ = head_ = &last_;
  } else if (!Empty() && !l.Empty()) {
    SwapingProc(l);
    PointerNewWay();
    l.PointerNewWay();
  }
}

template <class value_type>
void List<value_type>::PointerNewWay() {
  tail_->next_ = &last_;
  last_.prev_ = tail_;
  last_.next_ = head_;
  head_->prev_ = &last_;
}

template <class value_type>
void List<value_type>::SwapingProc(List<value_type> &l) {
  std::swap(head_, l.head_);
  std::swap(tail_, l.tail_);
}

template <class value_type>
void List<value_type>::PushFront(const_reference value) {
  Node<value_type> *new_node = new Node<value_type>();
  new_node->value_ = value;
  new_node->prev_ = nullptr;
  new_node->next_ = head_;
  if (Empty()) {
    head_ = new_node;
    tail_ = new_node;
    last_.prev_ = tail_;
  } else {
    head_->prev_ = new_node;
    head_ = new_node;
  }
  last_.next_ = head_;
  head_->prev_ = &last_;
}

template <class value_type>
void List<value_type>::Clear() {
  while (head_ != &last_) {
    PopBack();
  }
  ResetUnite();
}

template <class value_type>
void List<value_type>::PushBack(const_reference value) {
  Node<value_type> *new_node = new Node<value_type>();
  new_node->value_ = value;
  new_node->prev_ = tail_;
  new_node->next_ = &last_;
  if (Empty()) {
    new_node->prev_ = nullptr;
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  last_.prev_ = tail_;
  last_.next_ = head_;
  head_->prev_ = &last_;
}

template <class value_type>
bool List<value_type>::Empty() const {
  return (head_ == nullptr || head_ == &last_);
}

template <class value_type>
typename List<value_type>::size_type List<value_type>::Size() {
  typename List<value_type>::size_type size = 0;
  for (auto it = Begin(); it != End(); it++) {
    size++;
  }
  return size;
}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::Front() const {
  return head_->value_;
}

template <class value_type>
typename List<value_type>::const_reference List<value_type>::Back() const {
  return tail_->value_;
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::MaxSize() const {
  return SIZE_MAX / (sizeof(Node<value_type>) * 2);
}

template <class value_type>
void List<value_type>::ResetNode(Node<value_type> *node) {
  node->next_ = nullptr;
  node->prev_ = nullptr;
  node->value_ = value_type();
}

template <class value_type>
void List<value_type>::CopyList(const List<value_type> &l) {
  Clear();
  if (!l.Empty()) {
    for (auto it = l.Begin(); it != l.End(); ++it) {
      PushBack(*it);
    }
  }
}

template <class value_type>
void List<value_type>::ResetUnite() {
  ResetNode(&last_);
  head_ = tail_ = &last_;
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::Begin() {
  return iterator(head_);
}

template <class value_type>
typename List<value_type>::iterator List<value_type>::End() {
  return iterator(&last_);
}

template <class value_type>
typename List<value_type>::const_iterator List<value_type>::Begin() const {
  return const_iterator(head_);
}

template <class value_type>
typename List<value_type>::const_iterator List<value_type>::End() const {
  return const_iterator(tail_->next_);
}
//------------------ListIterator------------------------//

template <typename value_type>
inline typename List<value_type>::iterator &
List<value_type>::ListIterator::operator++() {
  cur_node_ = cur_node_->next_;
  return *this;
}

template <typename value_type>
inline typename List<value_type>::iterator &
List<value_type>::ListIterator::operator--() {
  cur_node_ = cur_node_->prev_;
  return *this;
}

template <typename value_type>
inline typename List<value_type>::iterator
List<value_type>::ListIterator::operator++(int) {
  iterator buff = *this;
  ++(*this);
  return buff;
}

template <typename value_type>
inline typename List<value_type>::iterator
List<value_type>::ListIterator::operator--(int) {
  iterator buff = *this;
  --(*this);
  return buff;
}
template <typename value_type>
inline bool List<value_type>::ListIterator::operator==(ListIterator iter) {
  return cur_node_ == iter.cur_node_;
}

template <typename value_type>
inline bool List<value_type>::ListIterator::operator!=(ListIterator iter) {
  return cur_node_ != iter.cur_node_;
}
template <typename value_type>
inline typename List<value_type>::reference
List<value_type>::ListIterator::operator*() {
  return cur_node_->value_;
}

template <typename value_type>
inline List<value_type>::ListIterator::operator typename List<
    value_type>::const_iterator() {
  return List<value_type>::const_iterator(cur_node_);
}

//------------------ConstListIterator------------------------//

template <typename value_type>
inline typename List<value_type>::const_iterator &
List<value_type>::ListConstIterator::operator++() {
  cur_node_ = cur_node_->next_;
  return *this;
}

template <typename value_type>
inline typename List<value_type>::const_iterator &
List<value_type>::ListConstIterator::operator--() {
  cur_node_ = cur_node_->prev_;
  return *this;
}

template <typename value_type>
inline typename List<value_type>::const_iterator
List<value_type>::ListConstIterator::operator++(int) {
  const_iterator buff = *this;
  ++(*this);
  return buff;
}

template <typename value_type>
inline typename List<value_type>::const_iterator
List<value_type>::ListConstIterator::operator--(int) {
  const_iterator buff = *this;
  --(*this);
  return buff;
}
template <typename value_type>
inline bool List<value_type>::ListConstIterator::operator==(
    ListConstIterator iter) const {
  return cur_node_ == iter.cur_node_;
}

template <typename value_type>
inline bool List<value_type>::ListConstIterator::operator!=(
    ListConstIterator iter) const {
  return cur_node_ != iter.cur_node_;
}
template <typename value_type>
inline typename List<value_type>::const_reference
List<value_type>::ListConstIterator::operator*() const {
  return cur_node_->value_;
}

template <typename value_type>
inline List<value_type>::ListConstIterator::operator typename List<
    value_type>::iterator() {
  return List<value_type>::iterator(cur_node_);
}

}  // namespace s21