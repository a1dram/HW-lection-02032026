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
  return head == nullptr; // T::operator==()
}

template< class T >
size_t BiLoopList< T >::size() const
{
  if (empty()) {
    return 0;
  }

  size_t n = 0;
  BiList< T >* p = head; // T::operator=()
  while (p != head) // T::operator!=()
  {
    ++n;
    p = p->next; // T::operator=()
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
  BiList< T >* node = new BiList< T >{x, nullptr, nullptr}; // T::T()

  if (empty())
  {
    // тут везде T::operator=()
    node->next = node;
    node->prev = node;
    head = node;
    tail = node;
    return;
  }

  // тут везде T::operator=()
  node->next = head;
  node->prev = tail;

  head->prev = node;
  tail->next = node;
  head = node;
}

template< class T >
void BiLoopList< T >::push_back(const T& x)
{
  BiList< T >* node = new BiList< T >{x, nullptr, nullptr}; // T::T()

  if (empty())
  {
    // тут везде T::operator=()
    node->next = node;
    node->prev = node;
    head = node;
    tail = node;
    return;
  }

  // тут везде T::operator=()
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

  if (head == tail) // T::operator==()
  {
    delete head;
    head = nullptr;
    tail = nullptr;
    return;
  }

  BiList< T >* old = head; // T::operator=()
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

  if (head == tail) // T::operator==()
  {
    delete tail;
    head = nullptr;
    tail = nullptr;
    return;
  }

  BiList< T >* old = tail; // T::operator=()
  BiList< T >* nt = tail->prev;

  nt->next = head; // T::operator=()
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

int main()
{
  char a[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
  size_t n = sizeof(a) / sizeof(a[0]);

  BiLoopList< char > lst;
  lst.convert_to_list(a, n);

  if (!lst.empty())
  {
    BiList< char >* p = lst.head;
    for (size_t i = 0; i < n; ++i)
    {
      std::cout << p->val << (i + 1 == n ? '\n' : ' ');
      p = p->next;
    }
  }

  if (!lst.empty())
  {
    BiList< char >* p = lst.tail;
    for (size_t i = 0; i < n; ++i)
    {
      std::cout << p->val << (i + 1 == n ? '\n' : ' ');
      p = p->prev;
    }
  }

  lst.clear();
  return 0;
}
