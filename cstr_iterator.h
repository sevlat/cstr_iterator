
#include <iterator>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
template<typename CH, bool WITH_ZERO>
struct basic_cstr_iterator_engine;

template<typename CH>
struct basic_cstr_iterator_engine<CH, false>
{
  static CH* Check(CH* sz)
  {
    if (!sz)  return 0;
    if (!*sz) return 0;
    return sz;
  }

  static void Inc(CH* &sz)
  {
    assert(!sz || *sz);
    ++sz;
    if (!*sz) sz=0;
  }
};

template<typename CH>
struct basic_cstr_iterator_engine<CH, true>
{
  static CH* Check(CH* sz)
  {
    return sz;
  }

  static void Inc(CH* &sz)
  {
    assert(*sz);
    if (!*sz) sz=0;
    else ++sz;
  }
};

////////////////////////////////////////////////////////////////////////////////
template<typename CH, bool WITH_ZERO=false>
class basic_cstr_iterator: public std::iterator<std::input_iterator_tag, CH>
{
 public:
  basic_cstr_iterator()
   : m_sz(0)  {}

  explicit basic_cstr_iterator(CH *sz)
   : m_sz(basic_cstr_iterator_engine<CH, WITH_ZERO>::Check(sz))  {}

 public:
  basic_cstr_iterator& operator++()
  {
    basic_cstr_iterator_engine<CH, WITH_ZERO>::Inc(m_sz);
    return *this;
  }

  basic_cstr_iterator operator++(int)
  {
    basic_cstr_iterator it(*this);
    operator++();
    return it;
  }

 public:
  bool operator==(const basic_cstr_iterator &it) { return m_sz==it.m_sz; }
  bool operator!=(const basic_cstr_iterator &it) { return !operator==(it); }

  CH& operator*() { return *m_sz; }

 private:
  CH *m_sz;
};

typedef basic_cstr_iterator<char>                cstr_iterator;
typedef basic_cstr_iterator<const char>          cstr_citerator;
typedef basic_cstr_iterator<char, true>          cstrz_iterator;
typedef basic_cstr_iterator<const char, true>    cstrz_citerator;

typedef basic_cstr_iterator<wchar_t>             cwstr_iterator;
typedef basic_cstr_iterator<const wchar_t>       cwstr_citerator;
typedef basic_cstr_iterator<wchar_t, true>       cwstrz_iterator;
typedef basic_cstr_iterator<const wchar_t, true> cwstrz_citerator;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename IT>
class Test {
 public:
  void Do(const char *sz)
  {
     IT ib(sz);
     IT ie;

     bool b0=(ib==ie);
     bool b1=(ie==ib);
     bool b2=(ib!=ie);
     bool b3=(ie!=ib);

     string s;
     copy(ib, ie, back_inserter(s));

     if (sz && *sz) {
       assert(!b0);
       assert(!b1);
       assert(b2);
       assert(b3);
       assert(s.compare(sz)==0);
     } else {
       assert(b0);
       assert(b1);
       assert(!b2);
       assert(!b3);
       assert(s.empty());
     }
  }

  void Do()
  {
    Do(0);
    Do("");
    Do("qwertyuiop");
    Do("hgiw uituhg witu hgw4oitu ghoirhg o4ti hgor htoeruhg eriuhg er94287t5yt 4587fy4 w5 5o47 ");
  }
};

inline void Test_cstr_iterator()
{
  Test <basic_cstr_iterator<const char, false> > test2;
  test2.Do();
}

