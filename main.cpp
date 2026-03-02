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
