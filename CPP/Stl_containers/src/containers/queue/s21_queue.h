#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_QUEUE_H
#define CPP2_S21_CONTAINERS_SRC_QUEUE_QUEUE_H

#include "../vector/s21_vector.h"

namespace s21 {

template<class T, class Container = s21::Vector<T>>
class Queue {
public:

  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  Queue() : container_() {}
  Queue(std::initializer_list<value_type> const &items)  : container_{items} {}
  Queue(const Queue &q) : container_(q.container_) {}
  Queue(Queue &&q) : container_(std::move(q.container_)) {}

  ~Queue() {}
        
  Queue &operator=(Queue &&q) {
    if (this != &q) {
        container_ = std::move(q.container_);
    }
    return *this;
  }

  const_reference Front() const {
    return container_.Front();
  }

  const_reference Back() const {
    return container_.Back();
  }

  bool Empty() const {
    return container_.Empty();
  }

  size_type Size() const {
    return container_.Size();
  }
  
  void Push(const_reference value) {
    container_.PushBack(value);
  }

  void Pop() {
    if (!container_.Empty()) {
        for (size_type i = 0; i < container_.Size() - 1; i++) {
            container_[i] = container_[i + 1];
        }
        container_.PopBack();
    }
  }

  void Swap(Queue& other) {
    container_.Swap(other.container_);
  }

private:
  Container container_;
};

} // namespace s21

#endif // CPP2_S21_CONTAINERS_SRC_QUEUE_QUEUE_H