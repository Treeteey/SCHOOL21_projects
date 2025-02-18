#include <cstddef>
#ifndef CPP2_S21_CONTAINERS_SRC_VECTOR_VECTOR_H
#define CPP2_S21_CONTAINERS_SRC_VECTOR_VECTOR_H

namespace s21 {

template<class T>
class Vector {
public:

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
        
  ~Vector();

  Vector &operator=(Vector &&v);

  reference At(size_type pos);
  reference operator[](size_type pos);
  const_reference Front() const;
  const_reference Back() const;
  iterator Data();

  iterator Begin() const;
  iterator End() const;

  bool Empty() const;
  size_type Size() const;
  size_type MaxSize() const;
  void Reserve(size_type size);
  size_type Capacity() const;
  void ShrinkToFit();

  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void Swap(Vector& other);

private:
  value_type *elements_;
  size_type size_;
  size_type capacity_;

  void ResetVector();
  void TransferData(Vector<T> &v);
  void Reallocate(size_type new_capacity);
};
} // namespace s21

#include "s21_vector.tpp"
#endif // CPP2_S21_CONTAINERS_SRC_VECTOR_VECTOR_H