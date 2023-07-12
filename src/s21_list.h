#ifndef SRC_LIST_S21_LIST_H_
#define SRC_LIST_S21_LIST_H_

#include <climits>
#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T>
class list {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
    value_type value;
    Node *next;
    Node *prev;
    Node(const_reference value, Node *next, Node *prev)
        : value(value), next(next), prev(prev) {}
  };
  size_type size_ = 0;
  Node *head_ = nullptr;
  Node *tail_ = nullptr;

  void SwapT(reference x, reference y);
  void DelNode(Node *element);

 public:
  class ListIterator {
   public:
    Node *ptr_;

    ListIterator(Node *p = nullptr) : ptr_(p) {}

    reference operator*() const { return ptr_->value; }

    ListIterator &operator++() {
      ptr_ = ptr_->next;
      return *this;
    }

    ListIterator &operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }

    bool operator==(const ListIterator &other) const {
      return (ptr_ == other.ptr_);
    }

    bool operator!=(const ListIterator &other) const {
      return (ptr_ != other.ptr_);
    }
  };

  class ConstListIterator {
   public:
    const Node *ptr_;

    ConstListIterator(const Node *p = nullptr) : ptr_(p) {}

    const_reference operator*() const { return ptr_->value; }

    ConstListIterator &operator++() {
      ptr_ = ptr_->next;
      return *this;
    }

    ConstListIterator &operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }

    bool operator==(const ConstListIterator &other) const {
      return (ptr_ == other.ptr_);
    }

    bool operator!=(const ConstListIterator &other) const {
      return (ptr_ != other.ptr_);
    }
  };

 public:
  explicit list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();

  list &operator=(list &&l);
  list &operator=(list const &l);

  const_reference front() const;
  const_reference back() const;

  ListIterator begin();
  ListIterator end();

  ConstListIterator cbegin() const;
  ConstListIterator cend() const;

  bool empty() const;
  size_type size();
  size_type max_size();
  void clear();
  ListIterator insert(ListIterator pos, const_reference value);
  void erase(ListIterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(ConstListIterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  void emplace(ConstListIterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);
};

template <typename T>
list<T>::list() : size_(0) {
  head_ = new Node({}, nullptr, nullptr);
  tail_ = new Node({}, nullptr, nullptr);
  head_->next = tail_;
  tail_->prev = head_;
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_t i = 0; i != n; ++i) {
    push_back(head_->value);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto &element : items) {
    push_back(element);
  }
}

template <typename T>
list<T>::list(const list &l) : list() {
  Node *cur_el = l.head_->next;
  for (size_t i = 0; i != l.size_; ++i) {
    push_back(cur_el->value);
    cur_el = cur_el->next;
  }
}

template <typename T>
list<T>::list(list &&l) {
  size_ = l.size_;
  head_ = l.head_;
  l.head_ = nullptr;
  tail_ = l.tail_;
  l.tail_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  if (!empty()) clear();
  delete head_;
  delete tail_;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&l) {
  if (this != &l) {
    list(l).swap(*this);
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> const &l) {
  if (this != &l) {
    list(l).swap(*this);
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (empty()) throw "Conteiner is empty";
  return head_->next->value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (empty()) throw "Conteiner is empty";
  return tail_->prev->value;
}

template <typename T>
typename list<T>::ListIterator list<T>::begin() {
  return ListIterator(head_->next);
}

template <typename T>
typename list<T>::ListIterator list<T>::end() {
  return list<T>::ListIterator(tail_);
}

template <typename T>
typename list<T>::ConstListIterator list<T>::cbegin() const {
  return ConstListIterator(head_->next);
}

template <typename T>
typename list<T>::ConstListIterator list<T>::cend() const {
  return list<T>::ConstListIterator(tail_);
}

//
//--------------------------------------------------------------------------------//

template <typename T>
bool list<T>::empty() const {
  return (size_ == 0);
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return LLONG_MAX / (sizeof(Node));
}

template <typename T>
void list<T>::clear() {
  while (size_ != 0) {
    pop_front();
  }
}

template <typename T>
void list<T>::erase(ListIterator pos) {
  DelNode(pos.ptr_);
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *temp = new Node({}, tail_, tail_->prev);
  temp->value = value;
  tail_->prev->next = temp;
  tail_->prev = temp;
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  DelNode(tail_->prev);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *temp = new Node({}, head_->next, head_);
  temp->value = value;
  head_->next->prev = temp;
  head_->next = temp;
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  DelNode(head_->next);
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(size_, other.size_);
  Node *temp = head_;
  head_ = other.head_;
  other.head_ = temp;
  temp = tail_;
  tail_ = other.tail_;
  other.tail_ = temp;
}

template <typename T>
void list<T>::merge(list &other) {
  size_type n = other.size();
  for (size_t i = 0; i != n; ++i) {
    push_back(other.front());
    other.pop_front();
  }
  sort();
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListIterator pos,
                                               const_reference value) {
  Node *temp = new Node({}, pos.ptr_, pos.ptr_->prev);
  temp->value = value;
  pos.ptr_->prev->next = temp;
  pos.ptr_->prev = temp;
  ++size_;
  return ListIterator(pos.ptr_->prev);
}

template <typename T>
void list<T>::splice(ConstListIterator pos, list &other) {
  Node *position = head_;
  for (auto i = cbegin(); i != cend() && i != pos; ++i) {
    position = position->next;
  }
  if (other.size_ != 0 && position != nullptr) {
    size_ += other.size_;
    Node *temp = position->next;
    position->next = other.head_->next;
    position->next->prev = position;
    temp->prev = other.tail_->prev;
    temp->prev->next = temp;

    other.size_ = 0;
    other.head_->next = other.tail_;
    other.tail_->prev = other.head_;
  }
}

template <typename T>
void list<T>::reverse() {
  Node *temp_front = head_->next;
  Node *temp_back = tail_->prev;
  for (size_t i = 0; i < size() / 2; ++i) {
    value_type temp = temp_front->value;
    temp_front->value = temp_back->value;
    temp_back->value = temp;
    temp_front = temp_front->next;
    temp_back = temp_back->prev;
  }
}

template <typename T>
void list<T>::unique() {
  Node *cur_el = head_;
  if (size_ > 1) {
    while (cur_el != tail_) {
      if (cur_el->value == cur_el->next->value) {
        DelNode(cur_el->next);
      } else {
        cur_el = cur_el->next;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  Node *left = head_->next;
  Node *right = left->next;
  value_type *temp = new value_type;
  for (size_t i = 0; i < size_ - 1; ++i) {
    for (size_t j = 0; j < size_ - i - 1; ++j) {
      if (left->value > right->value) {
        *temp = left->value;
        left->value = right->value;
        right->value = *temp;
      }
      right = right->next;
    }
    left = left->next;
    right = left->next;
  }
  delete temp;
}

template <typename T>
template <typename... Args>
void list<T>::emplace(ConstListIterator pos, Args &&...args) {
  std::initializer_list<value_type> init_list = {args...};
  if (init_list.size() != 0) {
    list<T> new_list(init_list);
    splice(pos, new_list);
  } else {
    list<T> new_list(1);
    splice(pos, new_list);
  }
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
  emplace(cend(), args...);
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
  emplace(cbegin(), args...);
}

template <typename T>
void list<T>::DelNode(Node *element) {
  element->prev->next = element->next;
  element->next->prev = element->prev;
  delete element;
  --size_;
}

}  // namespace s21
#endif  // SRC_LIST_S21_LIST_H_