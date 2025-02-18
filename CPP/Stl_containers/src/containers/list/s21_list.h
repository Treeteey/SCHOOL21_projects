#ifndef CPP2_S21_CONTAINERS_SRC_LIST_LIST_H
#define CPP2_S21_CONTAINERS_SRC_LIST_LIST_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include <iostream>

namespace s21 {

template <class T>

class List {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  template <class value_type>
  struct Node {
    value_type value_;
    Node<value_type> *next_;
    Node<value_type> *prev_;
  };

  class ListIterator {
    friend class List;
    friend class ListConstIterator;
   public:
    ListIterator(typename List<value_type>::Node<value_type> *node) : cur_node_(node){};
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int);
    iterator operator--(int);
    reference operator*();
    bool operator==(ListIterator);
    bool operator!=(ListIterator);
    operator typename List<value_type>::const_iterator();
   private:
    Node<value_type> *cur_node_ = 0;
  };
  class ListConstIterator {
    friend class List;
    friend class ListIterator;
   public:
    ListConstIterator(typename List<value_type>::Node<value_type> *node) : cur_node_(node){};
    const_iterator &operator++();
    const_iterator &operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);
    const_reference operator*() const;
    bool operator==(ListConstIterator) const;
    bool operator!=(ListConstIterator) const;
    operator typename List<value_type>::iterator();
   private:
    Node<value_type> *cur_node_ = 0;
  };

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  const_reference Front() const; 
  const_reference Back() const;

  iterator Begin();
  iterator End();
  const_iterator Begin() const;
  const_iterator End() const;

  bool Empty() const;
  size_type Size();
  size_type MaxSize() const;
  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PushFront(const_reference value);
  void PopBack();
  void PopFront();
  void Swap(List &other);
  void Merge(List &other);
  void Splice(const_iterator pos, List &other);
  void Reverse();
  void Unique();
  void Sort();
  List<value_type>& operator=(List<value_type>&& l);
  List<value_type>& operator=(const List<value_type>& l);
  
 private:
  Node<value_type> last_;
  Node<value_type> *head_;
  Node<value_type> *tail_;
  void CopyList(const List<value_type> &);
  void ResetNode(Node<value_type> *);
  void SwapingProc(List<value_type> &);
  void ResetUnite();
  void PointerNewWay();
  void BubbleSwap(iterator);
  void TransferElem(List &other);
  
};
}  // namespace s21

#include "s21_list.tpp"
#endif  // CPP2_S21_CONTAINERS_SRC_LIST_LIST_H