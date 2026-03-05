#include <iostream>

template< class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};

template< class T >
BiList< T >* add(BiList< T >* h, const T& d)
{
  // конструктор копирования T::T(const T&)
  BiList< T >* node = new BiList< T >{ d, nullptr, nullptr };

  if (h == nullptr)
  {
    node->next = node;
    node->prev = node;
    return node;
  }

  BiList< T >* tail = h->prev;

  node->next = h;
  node->prev = tail;

  tail->next = node;
  h->prev = node;

  return node;
}

template< class T >
BiList< T >* insert(BiList< T >* h, const T& d)
{
  // конструктор копирования T::T(const T&)
  BiList< T >* node = new BiList< T >{ d, nullptr, nullptr };

  if (h == nullptr)
  {
    node->next = node;
    node->prev = node;
    return node;
  }

  BiList< T >* after = h->next;

  node->prev = h;
  node->next = after;

  h->next = node;
  after->prev = node;

  return node;
}
