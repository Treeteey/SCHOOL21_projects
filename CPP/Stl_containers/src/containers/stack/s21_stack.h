#ifndef CPP2_S21_CONTAINERS_SRC_STACK_STACK_H
#define CPP2_S21_CONTAINERS_SRC_STACK_STACK_H

#include "../vector/s21_vector.h"
#include <utility>

namespace s21 {

template<class T, class Container = s21::Vector<T>>
class Stack {
public:

  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  Stack() : container_() {}
  Stack(std::initializer_list<value_type> const &items)  : container_{items} {}
  Stack(const Stack &s) : container_(s.container_) {}
  Stack(Stack &&s) : container_(std::move(s.container_)) {}

  ~Stack() {}
        
  Stack &operator=(Stack &&s) {
    if (this != &s) {
        container_ = std::move(s.container_);
    }
    return *this;
  }

  const_reference Top() const {
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
    container_.PopBack();
  }

  void Swap(Stack& other) {
    container_.Swap(other.container_);
  }

private:
  Container container_;
};
} // namespace s21

#endif // CPP2_S21_CONTAINERS_SRC_STACK_STACK_H