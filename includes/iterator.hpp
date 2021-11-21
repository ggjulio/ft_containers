#ifndef ITERATOR
#define ITERATOR

namespace ft {

template <class Iterator>
  struct iterator_traits {
		typedef typename Iterator::value_type            value_type;
		typedef typename Iterator::difference_type       difference_type;
		typedef typename Iterator::iterator_category     iterator_category;
		typedef typename Iterator::pointer               pointer;
		typedef typename Iterator::reference             reference;
	};
template <class T>
	struct iterator_traits<T*> {
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
	};

template <class T>
	struct iterator_traits<const T*> {
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
	};

template<class _Category, class _Tp, class _Distance = std::ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

template <typename _Iter>
class reverse_iterator
	: public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{
	template<typename _Iter1> friend class reverse_iterator;
protected:
	_Iter current;

public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;

	reverse_iterator(): current() {}
	reverse_iterator(iterator_type x): current(x) {}
	reverse_iterator(const reverse_iterator& other): current(other.current) {}

	template <class _Iter1>
	reverse_iterator(const reverse_iterator<_Iter1>& other)
		: current(other.current) {}

	template< class _Iter1>
	 reverse_iterator& operator=( const reverse_iterator<_Iter1>& other)
	 {
		current = other.current;
		return *this;
	 }

	iterator_type base() const { return current; }

    reference operator*() const				{ _Iter tmp = current; return *--tmp;}
    pointer  operator->() const				{ return &(operator*());}
    reverse_iterator& operator++()			{ --current; return *this;}
    reverse_iterator  operator++(int) 		{ reverse_iterator tmp(*this); --current; return tmp;}
    reverse_iterator& operator--() 			{ ++current; return *this;}
    reverse_iterator  operator--(int)		{ reverse_iterator tmp(*this); ++current; return tmp;}
    reverse_iterator  operator+ (difference_type n) const	{ return reverse_iterator(current - n);}
    reverse_iterator& operator+=(difference_type n)			{ current -= n; return *this;}
    reverse_iterator  operator- (difference_type n) const	{ return reverse_iterator(current + n);}
    reverse_iterator& operator-=(difference_type n) 		{ current += n; return *this;}
    reference         operator[](difference_type n) const	{ return *(*this + n);}

}; /* class reverse_iterator */

template <class Iterator>
  bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() == rhs.base();}

template <class IterL, class IterR>
  bool operator== (const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
  { return lhs.base() == rhs.base();}


template <class Iterator>
  bool operator!= (const reverse_iterator<Iterator>& lhs,  const reverse_iterator<Iterator>& rhs)
  { return lhs.base() != rhs.base();}

template <class IterL, class IterR>
  bool operator!= (const reverse_iterator<IterL>& lhs,  const reverse_iterator<IterR>& rhs)
  { return lhs.base() != rhs.base();}


template <class Iterator>
  bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() > rhs.base();}

template <class IterL, class IterR>
  bool operator<  (const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
  { return lhs.base() > rhs.base();}


template <class Iterator>
  bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() >= rhs.base();}

template <class IterL, class IterR>
  bool operator<= (const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
  { return lhs.base() >= rhs.base();}


template <class Iterator>
  bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() < rhs.base();}

template <class IterL, class IterR>
  bool operator>  (const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
  { return lhs.base() < rhs.base();}


template <class Iterator>
  bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() <= rhs.base();}

template <class IterL, class IterR>
  bool operator>= (const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs)
  { return lhs.base() <= rhs.base();}


template< class Iterator >
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& it )
	{ return reverse_iterator<Iterator>(it.base() - n); }

template <class IterL, class IterR>
	reverse_iterator<IterL> operator+(
		typename reverse_iterator<IterL>::difference_type n,
        const reverse_iterator<IterR>& it )
	{ return reverse_iterator<IterL>(it.base() - n); }


template <class Iterator>
  typename reverse_iterator<Iterator>::difference_type operator- (
    	const reverse_iterator<Iterator>& lhs,
    	const reverse_iterator<Iterator>& rhs)
	{ return rhs.base() - lhs.base(); }

template <class IterL, class IterR>
  typename reverse_iterator<IterL>::difference_type operator- (
    	const reverse_iterator<IterL>& lhs,
    	const reverse_iterator<IterR>& rhs)
	{ return rhs.base() - lhs.base(); }



} /* namespace ft */

#endif /* ITERATOR */