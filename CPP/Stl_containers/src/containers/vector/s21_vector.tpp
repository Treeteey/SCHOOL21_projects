#include "s21_vector.h"

namespace s21 {

template <class value_type>
Vector<value_type>::Vector() {
  ResetVector();
}

template <class value_type>
Vector<value_type>::Vector(size_type n)
    : elements_(new value_type[n]), size_(n), capacity_(n) {}

template <class value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items)
    : elements_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  for (size_type i = 0; i < size_; i++) {
    elements_[i] = *(items.begin() + i);
  }
}

template <class value_type>
Vector<value_type>::Vector(const Vector &v)
    : elements_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  for (size_type i = 0; i < size_; i++) {
    elements_[i] = v.elements_[i];
  }
}

template <class value_type>
Vector<value_type>::Vector(Vector &&v) {
  TransferData(v);
}

template <class value_type>
Vector<value_type>::~Vector() {
  delete[] elements_;
  ResetVector();
}

template <class value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector &&v) {
  if (this != &v) {
    delete[] elements_;
    TransferData(v);
  }
  return *this;
}

template <class value_type>
typename Vector<value_type>::reference Vector<value_type>::At(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Вне диапазона");
  }
  return elements_[pos];
}

template <class value_type>
typename Vector<value_type>::reference Vector<value_type>::operator[](
    size_type pos) {
  return elements_[pos];
}

template <class value_type>
typename Vector<value_type>::const_reference Vector<value_type>::Front() const {
  if (size_ == 0) {
    throw std::out_of_range("Вне диапазона");
  }
  return elements_[0];
}

template <class value_type>
typename Vector<value_type>::const_reference Vector<value_type>::Back() const {
  if (size_ == 0) {
    throw std::out_of_range("Вне диапазона");
  }
  return elements_[size_ - 1];
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::Data() {
  return elements_;
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::Begin() const {
  return elements_;
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::End() const {
  return elements_ + size_;
}

template <class value_type>
bool Vector<value_type>::Empty() const {
  return size_ == 0;
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::Size() const {
  return size_;
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::MaxSize() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class value_type>
void Vector<value_type>::Reserve(size_type size) {
  if (size > capacity_) {
    Reallocate(size);
  }
}

template <class value_type>
typename Vector<value_type>::size_type Vector<value_type>::Capacity() const {
  return capacity_;
}

template <class value_type>
void Vector<value_type>::ShrinkToFit() {
  if (size_ == capacity_) {
    return;
  }
  Reallocate(size_);
}

template <class value_type>
void Vector<value_type>::Clear() {
  delete[] elements_;
  ResetVector();
}

template <class value_type>
typename Vector<value_type>::iterator Vector<value_type>::Insert(
    iterator pos, const_reference value) {
  if (pos < Begin() || pos > End()) {
    throw std::out_of_range("Вне диапазона");
  }
  size_t index = pos - Begin();
  for (size_t i = size_; i > index; i--) {
    elements_[i] = elements_[i - 1];
  }
  elements_[index] = value;
  size_++;
  return Begin() + index;
}

template <class value_type>
void Vector<value_type>::Erase(iterator pos) {
  if (pos < Begin() || pos > End()) {
    throw std::out_of_range("Вне диапазона");
  }
  size_t index = pos - Begin();
  for (size_t i = index; i < size_ - 1; i++) {
    elements_[i] = elements_[i + 1];
  }
  size_--;
}

template <class value_type>
void Vector<value_type>::PushBack(const_reference value) {
  if (size_ < capacity_) {
    elements_[size_] = value;
  } else {
    size_type new_capacity = capacity_ > 0 ? capacity_ * 2 : 1;
    value_type *new_elements = new value_type[new_capacity];
    for (size_type i = 0; i < size_; i++) {
      new_elements[i] = elements_[i];
    }
    delete[] elements_;
    elements_ = new_elements;
    capacity_ = new_capacity;
    elements_[size_] = value;
  }
  size_++;
}

template <class value_type>
void Vector<value_type>::PopBack() {
  if (size_ > 0) {
    size_--;
  }
}

template <class value_type>
void Vector<value_type>::Swap(Vector &other) {
  if (this != &other) {
    std::swap(elements_, other.elements_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
}

template <class value_type>
void Vector<value_type>::ResetVector() {
  elements_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class value_type>
void Vector<value_type>::TransferData(Vector<value_type> &v) {
  elements_ = v.elements_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  v.ResetVector();
}

template <class value_type>
void Vector<value_type>::Reallocate(size_type new_capacity) {
  value_type *new_data = new value_type[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    new_data[i] = elements_[i];
  }
  delete[] elements_;
  elements_ = new_data;
  capacity_ = new_capacity;
}

}  // namespace s21
