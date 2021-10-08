#### ft_containers

- https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
- https://web.stanford.edu/class/cs107l/handouts/04-Custom-Iterators.pdf
- https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html
- https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/SFINAE.html
- https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/
- https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/
- https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
- https://www.fluentcpp.com/2018/04/27/tag-dispatching/
- https://tfetimes.com/wp-content/uploads/2015/11/Accelerated_C-_Practical_Programming_by_Example_-_Andrew_Koenig_Barbara_E._Moo_-_Addison-Wesley_-_2000.pdf (chapter 11 for memory and vector example)
- https://cs.lmu.edu/~ray/notes/redblacktrees/
- https://www.programiz.com/dsa/red-black-tree
- https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

- Best ressource ever ? : http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2011/n3242.pdf#page=731&zoom=100,96,712
 

- The size type seem to depend on the implementation (23.4.4.1 Class template map overview) :
```c++
public:
// types:
typedef Key key_type;
typedef T mapped_type;
typedef pair<const Key, T> value_type;
typedef Compare key_compare;
typedef Allocator allocator_type;
typedef value_type& reference;
typedef const value_type& const_reference;
typedef implementation-defined iterator; // see 23.2
typedef implementation-defined const_iterator; // see 23.2
typedef implementation-defined size_type; // see 23.2
typedef implementation-defined difference_type;// see 23.2
typedef typename allocator_traits<Allocator>::pointer pointer;
typedef typename allocator_traits<Allocator>::const_pointer const_pointer;
typedef std::reverse_iterator<iterator> reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
```

- http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2011/n3242.pdf#page=789&zoom=100,96,712 (the size type depend on the implementation)


- https://stackoverflow.com/questions/2127612/is-there-a-readable-implementation-of-the-stl
- http://stepanovpapers.com/butler.hpl.hp/stl/stl/
- https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_set.h
