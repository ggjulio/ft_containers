#ifndef ITERATOR
#define ITERATOR

namespace ft {



///  Marking input iterators.
struct input_iterator_tag { };

///  Marking output iterators.
struct output_iterator_tag { };

/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag { };

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag { };

/// Random-access iterators support a superset of bidirectional
/// iterator operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

// template <class Iterator>
// 	class iterator_traits;
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
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef random_access_iterator_tag iterator_category;
        typedef T*                         pointer;
        typedef T&                         reference;
    };

template <class T>
    struct iterator_traits<const T*> {
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef random_access_iterator_tag iterator_category;
        typedef T*                         pointer;
        typedef T&                         reference;
    };



} /* namespace ft */

#endif /* ITERATOR */