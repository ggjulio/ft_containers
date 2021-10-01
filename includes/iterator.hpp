#ifndef ITERATOR
#define ITERATOR

namespace ft {

template <class Iterator>
	class iterator_traits;

template <class T>
	class iterator_traits<T*>;

template <class T>
	class iterator_traits<const T*>;

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


} /* namespace ft */

#endif /* ITERATOR */