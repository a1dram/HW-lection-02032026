#include <iostream>

template< class T >
struct BiList
{
  T val;
  BiList< T >* next;
  BiList< T >* prev;
};

template< class T >
struct BiLoopList
{
  BiList< T >* head;
  BiList< T >* tail;

  BiLoopList();
  ~BiLoopList();

  bool empty() const;
  size_t size() const;

  T* front();
  const T* front() const;
  T* back();
  const T* back() const;

  void push_front(const T& x);
  void push_back(const T& x);
  void pop_front();
  void pop_back();

  void clear();
  void convert_to_list(const T* a, size_t n);
};

template< class T >
BiLoopList< T >::BiLoopList():
  head(nullptr),
  tail(nullptr)
{}

template< class T >
BiLoopList< T >::~BiLoopList()
{
  clear();
}

template< class T >
bool BiLoopList< T >::empty() const
{
  return head == nullptr;
}

template< class T >
size_t BiLoopList< T >::size() const
{
  if (empty()) {
    return 0;
  }

  size_t n = 0;
  BiList< T >* p = head;
  while (p != head)
  {
    ++n;
    p = p->next;
  }

  return n;
}

template< class T >
T* BiLoopList< T >::front()
{
  return head ? &head->val : nullptr;
}

template< class T >
const T* BiLoopList< T >::front() const
{
  return head ? &head->val : nullptr;
}

template< class T >
T* BiLoopList< T >::back()
{
  return tail ? &tail->val : nullptr;
}

template< class T >
const T* BiLoopList< T >::back() const
{
  return tail ? &tail->val : nullptr;
}

template< class T >
void BiLoopList< T >::push_front(const T& x)
{
  BiList< T >* node = new BiList< T >{x, nullptr, nullptr};

  if (empty())
  {
    node->next = node;
    node->prev = node;
    head = node;
    tail = node;
    return;
  }

  node->next = head;
  node->prev = tail;

  head->prev = node;
  tail->next = node;
  head = node;
}

template< class T >
void BiLoopList< T >::push_back(const T& x)
{
  BiList< T >* node = new BiList< T >{x, nullptr, nullptr};

  if (empty())
  {
    node->next = node;
    node->prev = node;
    head = node;
    tail = node;
    return;
  }

  node->prev = tail;
  node->next = head;

  tail->next = node;
  head->prev = node;
  tail = node;
}

template< class T >
void BiLoopList< T >::pop_front()
{
  if (empty()) {
    return;
  }

  if (head == tail)
  {
    delete head;
    head = nullptr;
    tail = nullptr;
    return;
  }

  BiList< T >* old = head;
  BiList< T >* nh = head->next;

  tail->next = nh;
  nh->prev = tail;
  head = nh;

  delete old;
}

template< class T >
void BiLoopList< T >::pop_back()
{
  if (empty()) {
    return;
  }

  if (head == tail)
  {
    delete tail;
    head = nullptr;
    tail = nullptr;
    return;
  }

  BiList< T >* old = tail;
  BiList< T >* nt = tail->prev;

  nt->next = head;
  head->prev = nt;
  tail = nt;

  delete old;
}

template< class T >
void BiLoopList< T >::clear()
{
  while (!empty()) {
    pop_front();
  }
}

template< class T >
void BiLoopList< T >::convert_to_list(const T* a, size_t n)
{
  clear();
  for (size_t i = 0; i < n; ++i) {
    push_back(a[i]);
  }
}
