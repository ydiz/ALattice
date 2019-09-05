#ifndef XLATTICE_VECTOR_H
#define XLATTICE_VECTOR_H

//TBD: need to define *, / , *=, /= in overload.h
template<typename T, int N>
class Vector{
public:
  T v[N];
  //construtors
  Vector();
  template<typename U> Vector(const U&); //any "number"; isNumber

  T& operator[](int i);
  const T& operator[](int i) const;

  Vector<T, N>& operator+=(const Vector<T, N> &rhs);
  Vector<T, N>& operator-=(const Vector<T, N> &rhs);
  Vector<T, N>& operator*=(const Vector<T, N> &rhs);
  template<typename U>
  typename std::enable_if<isNumber<U>::value, Vector<T, N>&>::type operator*=(const T &rhs);
  template<typename U>
  typename std::enable_if<isNumber<U>::value, Vector<T, N>&>::type operator/=(const T &rhs);

  T* begin() {return v;}
  const T* begin() const {return v;}
  T* end() {return v+N;}
  const T* end() const {return v+N;}

};


template<typename T, int N>
Vector<T, N>::Vector() {}

template<typename T, int N>
template<typename U>
Vector<T, N>::Vector(const U& x)
{
  static_assert(isNumber<T>::value, "Must be a number");
  for(int i=0; i<N; ++i) v[i] = x;
}


using Vector4 = Vector<Complex, 4>;
using VectorInt4 = Vector<int, 4>;

#endif
