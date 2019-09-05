unique_ptr v.s. share_ptr

cannot assign the result of new directly to unique_ptr

three ways:

1.2.3.

-----

string normal_str="First line.\nSecond line.\nEnd of message.\n";
string raw_str=R"(First line.\nSecond line.\nEnd of message.\n)";

------------------
Formally static_assert is a declaration. It is allowed wherever declarations are allowed.(https://stackoverflow.com/questions/25904145/static-assert-inside-outside-class-definition)


A static assert declaration may appear at namespace and block scope (as a block declaration) and **inside a class body** (as a member declaration) (https://en.cppreference.com/w/cpp/language/static_assert)

----

Even for template class, constructor can turn a variable to this class implicitly. But `operator T()` to convert this class to another class implicitly may not work.
----

e.g. For vector<vector<int>> v, v.data() is also not trivially copyable
-----

declare member function as const. Otherwise if `const T& lat`, then lat cannot call that member function
-------

```
T* begin() {return *m;} //don't make the function const; otherwise *m is const Complex *
const T* begin() const {return *m;}
T* end() {return *(m+2)+3;}
const T* end() const {return *(m+2)+3;}
```
-----

## trivially copyable
trivially copyable:
```
class Foo{
  int * c;
public:
  Foo() : c(new int[5]) {}
  // ~Foo() {delete[] c;}
};
```

not trivially copyable:
```
class Foo{
  int * c;
public:
  Foo() : c(new int[5]) {}
  ~Foo() {delete[] c;}  // non trivial destructor makes it not trivially copyable.
};
```

not trivially copyable:
```
class Foo{
  unique_ptr<int> c; // has members that are not trivially copyable
public:
  Foo() {}
};
```

---


vector doesn't have its element stored in the object. only a pointer to its elements. (sizeof(v)==24)


if object contains dynamic allocation (new and delete), it cannot be copied directly.
```
class Foo{
  int *c;
public:
  Foo() {c = new int[5];}
  ~Foo() {delete[] c;}
};

Foo foo;
MPI_Bcast(&foo, sizeof(foo), MPI_BYTE, 0, MPI_COMM_WORLD); // error Address not mapped

```

error:
```
[zyd:16436] Signal: Segmentation fault (11)
[zyd:16436] Signal code: Address not mapped (1)
```

`MPI_Bcast(&foo, sizeof(foo), MPI_BYTE, 0, MPI_COMM_WORLD);` only works for objects that are trivially copyable. (MPI communication works similarly to memcpy)




-----

Don't use object generated by constructor directly as parentheses initialization arguments.

Myclass x(Class1(xx), Class2()); // wrong! will be interpreted as function declaration.

C++'s most vexing parse:

anything that can be interpreted by the compiler as a function declaration will be interpreted as a function declaration.

Myclass x and Myclass x will call default constructor. But Myclass x() will not. This is will be interpreted as function declaration


Another instance of the same problem:

std::ifstream ifs("file.txt");
std::vector<T> v(std::istream_iterator<T>(ifs), std::istream_iterator<T>());

v is interpreted as a declaration of function with 2 parameters.

The workaround is to add another pair of parentheses:

std::vector<T> v((std::istream_iterator<T>(ifs)), std::istream_iterator<T>());

Or, if you have C++11 and list-initialization (also known as uniform initialization) available:

std::vector<T> v{std::istream_iterator<T>{ifs}, std::istream_iterator<T>{}};

With this, there is no way it could be interpreted as a function declaration.



How can that be interpreted as a function? – Casebash Oct 29 '10 at 1:00

std::vector is return type; v is function name; ( opens formal argument list; std::istream_iterator is type of first argument; ifs is name of first argument, () around ifs are effectively ignored; second std::istream_iterator is type of second argument, which is unnamed, () around it are also ignored; ');' closes argument list and function declaration. – Constantin Oct


@Constantin, the parentheses after the second argument are not ignored. The second parameter is not a std::istream_iterator but a pointer/reference to a function that takes no arguments and returns an istream_iterator. – CTMacUser

------

int nodeNameLen=0;
char nodeName[MPI_MAX_PROCESSOR_NAME];
MPI_Get_processor_name(nodeName, &nodeNameLen);

Even if nodeNameLen is only three, length of nodeName needs to be very large. (don't know why)

-----

type.h:18:29: error: ‘constexpr’ needed for in-class initialization of static data member ‘ompi_datatype_t* const MPI_Type<T>::value’ of non-integral type [-fpermissive]
   static const MPI_Datatype value = MPI_DATATYPE_NULL;


struct xxx{
  static constexpr MPI_Datatype value = MPI_DATATYPE_NULL;
};
-----

resize vector before passing v.data() as `int *`

std::string(start, end);
-----
**Static variables of class must be defined outside of class definition.** When creating an instance of class, static variables are not allocated memory because they don't belong to specific objects.

```
class Communicator{
public:
  static MPI_Comm worldComm;
  static int worldRank;
  static int worldSize;

  Communicator();
};

MPI_Comm Communicator::worldComm;
int Communicator::worldRank;
int Communicator::worldSize;

```

----

constructors will not be inherited. But it can be inherited explicitely using `using Base::Base`

```
struct Base {
    Base(int a) : i(a) {}
    int i;
};

struct Derived : Base {
    Derived(int a, std::string s) : Base(a), m(s) {}

    using Base::Base; // Inherit Base's constructors.
    // Equivalent to:
    //Derived(int a) : Base(a), m() {}

    std::string m;
};
```


------------

mpicxx == mpic++

mpicc --showme

-----

**When compiling xxx.cc to xxx.o, don't forget to add "-c" option**. Otherwise, `g++ -o xxx.o xxx.cc` will produce an executable `xxx.o`. Then when linking `xxx.o` to `xxx` (`g++ -o xxx xxx.o`), there will be errors that say `multiple definition of blahblah`. This is because g++ implicitly links system libraries.  So forgetting "-c" makes `xxx.o` has all the system function defined. Thus we are linking `xxx.o` and implicitly system libraries, in both of which system functions are defined.


p.s. **you cannot link a thing twice.** e.g. `g++ main.o -o main main.o ` will result in "multiple definition" error. But multiple "-lxxx" will be ignored.


-----

suppress specific warnings in g++: -Wno-xxx

e.g. for warning:
```
warning: ignoring attributes on template argument ‘__m128 {aka __vector(4) float}’ [-Wignored-attributes]
```
add `-Wno-ignored-attributes`

-------------

The library order pass to gcc/g++ does actually matter. If A depends on B, A must be listed first. The reason is that it optimizes out symbols that aren't referenced, so if it sees library B first, and no one has referenced it at that point then it won't link in anything from it at all.

-----

## enum

* use of enum without name:
```
enum {aa, bb, cc};
cout << aa;
```
you can define such enum in a class, which gives it a scope, and helps expose class's capabilities:
```
class Encryption {
  enum { DEFAUTL_KEYLEN=16, SHORT_KEYLEN=8, LONG_KEYLEN=32 };
};
key[Encryption::DEFAUTL_KEYLEN];
```

*


----

# map

* map doesn't have `operator[] const` method. This because `a[xx]` will insert a new item if "xx" doesn't exist. `at()` has const version.  
Thus const map obeject cannot call []. You can only use `.at()`

# initialize static member in class

only `int` static member can be initialized in class. Other types need to be initialized outside.

```
class A{
private:
 static const int a = 4; // valid
 static const std::string t ; // can't be initialized here
};
// in a cpp file where the static variable will exist; don't add `static`
const std::string A::t = "this way it works";
```

# A class can have

*  class can not have data members of its own type. A class can have data members that are pointers/reference to its own type."
* class can have static data members of its own type

The reason for class can't have data members of its own type is the compiler must know the size of class object. For example, one class is a local variable in function, the compiler can handle the stack only it knows the class size.

The static class member doesn't reside in class object, so has no impact to size of class object. It's OK.





-----------------
```
std::vector<Complex> cc(size_in_double/2);
std::copy(&cc[0], &cc[9], *m.m);
```
1. m is 2d pointer, so must first dereference!
2. end is one-beyond-last element
----------------

uint64_t a;
(double) a == (float) a; //it's not the behavior we want.

use
```
double *pd = (double *) &a;
```
---------------------

static global variable

when you define static globals, you are telling the compiler to keep the variable only for that file and don't let the linker know about it.

https://stackoverflow.com/questions/7837190/c-c-global-vs-static-global
-----------------

## delegating constructors
https://stackoverflow.com/questions/308276/can-i-call-a-constructor-from-another-constructor-do-constructor-chaining-in-c

After c++11, you can call one constructor from another constructor.

```
class Foo {
public:
  Foo(char x, int y) {}
  Foo(int y) : Foo('a', y) {}
};
```

------

operator= must be a member function; must have only one parameter

----

return type of a STL function object is defined in the class definition
e.g.
```
template<typename DIST>
class RNG {
  using result_type = typename DIST::result_type();
```
------------

1. lambda expression in a class member function: if use class members, capture `this`.
2. "this" can only be captured by copy, i.e. [this] or [=]

e.g.`std::function<result_type()> rand = [this]{return dist(eng);};`
------------

## do not initialize data member with () at the point of declaration;
You can initialize the data members at the point of declaration, but not with () brackets:

e.g.
```
class RNG {
  A dist(10); //error!
  A dist{10}; //correct
  A dist = A(10); //correct

  RNG() : dist(10) {}  //before c++11, this is the only way
};
```

-----
```
Complex* begin() {return *m;} //don't make the function const; otherwise *m is const Complex *
Complex* end() {return *(m+2)+3;}
```
--------------
template function argument deduction does not consider implicit conversions.  
https://en.cppreference.com/w/cpp/language/template_argument_deduction#Implicit_conversions

---------------------

for(auto value: a)  
for(auto const& value: a)

---

operator<< :
1. do not forget return out
2. std::ostream  std::endl;


do not forget return for ordinary functions

---

write type-checking "function": like "isMatrix<>()"

First write general case, then special case

-------

assert and static_assert are not in std namescope

-----------

implicit type conversion:

1. From another class to my class: constructor

2. From my class to another class: (note the `const`)

```
class MyClass{
  operator Another() const;
};

Myclass::operator Another() const
{
  xxx
  return another_class;
}

```