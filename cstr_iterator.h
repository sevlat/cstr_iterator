#ifndef cstr_iterator_h_already_included__29_05_2014__2C8AB6C0
#define cstr_iterator_h_already_included__29_05_2014__2C8AB6C0
//
// SeVlaT, 29.05.2014
//

////////////////////////////////////////////////////////////////////////////////
template<typename CH, bool WITH_ZERO>
struct basic_cstr_iterator_engine;

template<typename CH>
struct basic_cstr_iterator_engine<CH, false>
{
  static CH* Check(CH *sz)
  {
    if (!sz)  return 0;
    if (!*sz) return 0;
    return sz;
  }

  static void Inc(CH* &sz)
  {
    assert(sz);
    assert(*sz);
    ++sz;
    if (!*sz) sz=0;
  }
};

template<typename CH>
struct basic_cstr_iterator_engine<CH, true>
{
  static CH* Check(CH *sz)
  {
    static CH s_chZero=0;
    if (!sz) return &s_chZero;
    return sz;
  }

  static void Inc(CH* &sz)
  {
    assert(sz);
    if (!*sz) sz=0;
    else ++sz;
  }
};

////////////////////////////////////////////////////////////////////////////////
template<typename CH, bool WITH_ZERO=false>
class basic_cstr_iterator: public std::iterator<std::input_iterator_tag, CH>
{
  typedef basic_cstr_iterator_engine<CH, WITH_ZERO> Engine;

 public:
  const bool WithZero=WITH_ZERO;

 public:
  basic_cstr_iterator()
   : m_sz(0)  {}

  explicit basic_cstr_iterator(CH *sz)
   : m_sz(Engine::Check(sz))  {}

 public:
  basic_cstr_iterator& operator++()
  {
    Engine::Inc(m_sz);
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

////////////////////////////////////////////////////////////////////////////////
typedef basic_cstr_iterator<char>                cstr_iterator;
typedef basic_cstr_iterator<const char>          cstr_citerator;
typedef basic_cstr_iterator<char, true>          cstrz_iterator;
typedef basic_cstr_iterator<const char, true>    cstrz_citerator;

typedef basic_cstr_iterator<wchar_t>             cwstr_iterator;
typedef basic_cstr_iterator<const wchar_t>       cwstr_citerator;
typedef basic_cstr_iterator<wchar_t, true>       cwstrz_iterator;
typedef basic_cstr_iterator<const wchar_t, true> cwstrz_citerator;

#endif
