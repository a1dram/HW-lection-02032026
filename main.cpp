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

template< class T >
BiList< T >* cut(BiList< T >* h) noexcept
{
  if (h == nullptr)
    return nullptr;

  if (h->next == h)
  {
    // деструктор T::~T()
    delete h;
    return nullptr;
  }

  BiList< T >* tail = h->prev;
  BiList< T >* nh = h->next;

  tail->next = nh;
  nh->prev = tail;

  // деструктор T::~T()
  delete h;
  return nh;
}

template< class T >
BiList< T >* erase(BiList< T >* h) noexcept
{
  if (h == nullptr)
    return nullptr;

  if (h->next == h)
    return h;

  BiList< T >* del = h->next;
  BiList< T >* after = del->next;

  h->next = after;
  after->prev = h;

  // деструктор T::~T()
  delete del;
  return h;
}

template< class T >
BiList< T >* clear(BiList< T >* h, BiList< T >* e) noexcept
{
  if (h == nullptr)
    return e;

  if (e == nullptr)
  {
    BiList< T >* tail = h->prev;
    tail->next = nullptr;
    h->prev = nullptr;
  }

  while (h != e)
  {
    BiList< T >* old = h;
    h = h->next;

    // деструктор T::~T()
    delete old;
  }

  return e;
}
