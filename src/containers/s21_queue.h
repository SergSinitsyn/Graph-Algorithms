#ifndef SRC_QUEUE_S21_QUEUE_H_
#define SRC_QUEUE_S21_QUEUE_H_

#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  list<T> data_;

 public:
  queue();
  explicit queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &q);
  queue &operator=(queue &&q);

  const_reference front() const;
  const_reference back() const;
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);
};

template <typename T>
queue<T>::queue() : data_{} {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : data_(items) {}

template <typename T>
queue<T>::queue(const queue &q) : data_(q.data_) {}

template <typename T>
queue<T>::queue(queue &&q) : data_(q.data_) {}

template <typename T>
queue<T>::~queue() {}

template <typename T>
queue<T> &queue<T>::operator=(queue &q) {
  if (this != &q) {
    this->data_ = q.data_;
  }
  return *this;
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  if (this != &q) {
    this->data_ = q.data_;
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  return data_.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  return data_.back();
}

template <typename T>
bool queue<T>::empty() {
  return data_.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return data_.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  data_.pop_front();
}

template <typename T>
void queue<T>::swap(queue &other) {
  data_.swap(other.data_);
}

template <typename T>
template <typename... Args>
void queue<T>::emplace_back(Args &&...args) {
  data_.emplace_back(args...);
}

}  // namespace s21
#endif  // SRC_QUEUE_S21_QUEUE_H_