#ifndef SRC_STACK_S21_STACK_H_
#define SRC_STACK_S21_STACK_H_

#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  list<T> data_;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack &s);
  stack &operator=(stack &&s);

  const_reference top() const;
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void emplace_front(Args &&...args);
};

template <typename T>
stack<T>::stack() : data_{} {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : data_{items} {}

template <typename T>
stack<T>::stack(const stack &s) : data_(s.data_) {}

template <typename T>
stack<T>::stack(stack &&s) : data_(s.data_) {}

template <typename T>
stack<T>::~stack() {}

template <typename T>
stack<T> &stack<T>::operator=(stack &s) {
  if (this != &s) {
    this->data_ = s.data_;
  }
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) {
  if (this != &s) {
    this->data_ = s.data_;
  }
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  return data_.back();
}

template <typename T>
void stack<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
bool stack<T>::empty() {
  return data_.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return data_.size();
}

template <typename T>
void stack<T>::pop() {
  data_.pop_back();
}

template <typename T>
void stack<T>::swap(stack &other) {
  data_.swap(other.data_);
}

template <typename T>
template <typename... Args>
void stack<T>::emplace_front(Args &&...args) {
  data_.emplace_back(args...);
}

}  // namespace s21
#endif  // SRC_STACK_S21_STACK_H_