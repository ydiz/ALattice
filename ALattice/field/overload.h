#pragma once

////////////////////////////////////////////////////
//Lattice
///////////////////////////////////////////////////

template<typename T>
inline T& Lattice<T>::operator[](int i)
{
  return _data[i];
}

template<typename T>
inline const T& Lattice<T>::operator[](int i) const
{
  return _data[i];
}

// =, +=, -=, *=, /=
template<typename T>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Lattice<T>&>::type
Lattice<T>::operator=(const U &rhs)
{
  for(int i=0; i<grid.volLocal; ++i) _data[i] = rhs;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator+=(const U &x)
{
  *this = *this + x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator-=(const U &x)
{
  *this = *this - x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator*=(const U &x)
{
  *this = *this * x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator/=(const U &x)
{
  *this = *this / x;
  return *this;
}

// unary -
template<typename T>
inline Lattice<T> operator-(const Lattice<T> &x)
{
  Lattice<T> ret(x.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = - x._data[i];
  return ret;
}

// +, -, *, /
template<typename T, typename U>
inline auto operator+(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] + l2._data[0])>
{
  Lattice<decltype(l1._data[0] + l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] + l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator+(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] + x)>
{
  Lattice<decltype(l._data[0] + x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] + x;
  return ret;
}

template<typename T, typename U>
inline auto operator+(const U &x, const Lattice<T> &l) -> Lattice<decltype(l._data[0] + x)>
{
  Lattice<decltype(l._data[0] + x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x + l._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator-(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] - l2._data[0])>
{
  Lattice<decltype(l1._data[0] - l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] - l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator-(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] - x)>
{
  Lattice<decltype(l._data[0] - x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] - x;
  return ret;
}

template<typename T, typename U>
inline auto operator-(const U &x, const Lattice<T> &l) -> Lattice<decltype(l._data[0] - x)>
{
  Lattice<decltype(l._data[0] - x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x - l._data[i];
  return ret;
}


template<typename T, typename U>
inline auto operator*(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] * l2._data[0])>
{
  Lattice<decltype(l1._data[0] * l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] * l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator*(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] * x)>
{
  Lattice<decltype(l._data[0] * x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] * x;
  return ret;
}

template<typename T, typename U>
inline auto operator*(const U &x, const Lattice<T> &l) -> Lattice<decltype(x * l._data[0])>
{
  Lattice<decltype(x * l._data[0])> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x * l._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] / l2._data[0])>
{
  Lattice<decltype(l1._data[0] / l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] / l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] / x)>
{
  Lattice<decltype(l._data[0] / x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] / x;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const U &x, const Lattice<T> &l) -> Lattice<decltype(x / l._data[0])>
{
  Lattice<decltype(x / l._data[0])> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x / l._data[i];
  return ret;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Lattice<T> &latt)
{
  const std::string delimiter = (isMatrix<T>::value) ? "\n": "\t";
  std::vector<int> gcoor(latt.grid._ndims);
  for(int i=0; i<latt.grid.volGlobal; ++i)
  {
    gcoor = latt.grid.globalIndexToGlobalCoor(i);
    out << gcoor << delimiter << peekSite(latt, gcoor) << std::endl;
  }
  return out;
}


//////////////////////////////////////
// Field
/////////////////////////////////////

template<typename T, int N>
inline Lattice<T>& Field<T, N>::operator[](int i)
{
  return _data[i];
}

template<typename T, int N>
inline const Lattice<T>& Field<T, N>::operator[](int i) const
{
  return _data[i];
}

// +=, -=, *=, /=
template<typename T, int N>
template<typename U>
inline Field<T, N>& Field<T, N>::operator+=(const U &x)
{
  *this = *this + x;
  return *this;
}

template<typename T, int N>
template<typename U>
inline Field<T, N>& Field<T, N>::operator-=(const U &x)
{
  *this = *this - x;
  return *this;
}

template<typename T, int N>
template<typename U>
inline Field<T, N>& Field<T, N>::operator*=(const U &x)
{
  *this = *this * x;
  return *this;
}

template<typename T, int N>
template<typename U>
inline Field<T, N>& Field<T, N>::operator/=(const U &x)
{
  *this = *this / x;
  return *this;
}

// unary -
template<typename T, int N>
inline Field<T, N> operator-(const Field<T, N> &x)
{
  Field<T, N> ret;
  ret._data = - x._data;
  return ret;
}


template<typename T, int N, typename U>
inline auto operator+(const Field<T, N> &l1, const Field<U, N> &l2) -> Field<decltype(l1._data[0][0] + l2._data[0][0]), N>
{
  Field<decltype(l1._data[0][0] + l2._data[0][0]), N> ret;
  ret._data = l1._data + l2._data;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator-(const Field<T, N> &l1, const Field<U, N> &l2) -> Field<decltype(l1._data[0][0] - l2._data[0][0]), N>
{
  Field<decltype(l1._data[0][0] - l2._data[0][0]), N> ret;
  ret._data = l1._data - l2._data;
  return ret;
}


template<typename T, int N, typename U>
inline auto operator*(const Field<T, N> &l1, const Field<U, N> &l2) -> Field<decltype(l1._data[0][0] * l2._data[0][0]), N>
{
  Field<decltype(l1._data[0][0] * l2._data[0][0]), N> ret;
  ret._data = l1._data * l2._data;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator*(const Field<T, N> &l, const U &x) -> Field<decltype(l._data[0][0] * x), N>
{
  Field<decltype(l._data[0][0] * x), N> ret;
  ret._data = l._data * x;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator*(const U &x, const Field<T, N> &l) -> Field<decltype(x * l._data[0][0]), N>
{
  Field<decltype(x * l._data[0][0]), N> ret;
  ret._data = x * l._data;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator/(const Field<T, N> &l1, const Field<U, N> &l2) -> Field<decltype(l1._data[0][0] / l2._data[0][0]), N>
{
  Field<decltype(l1._data[0][0] / l2._data[0][0]), N> ret;
  ret._data = l1._data / l2._data;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator/(const Field<T, N> &l, const U &x) -> Field<decltype(l._data[0][0] / x), N>
{
  Field<decltype(l._data[0][0] / x), N> ret;
  ret._data = l._data / x;
  return ret;
}

template<typename T, int N, typename U>
inline auto operator/(const U &x, const Field<T, N> &l) -> Field<decltype(x / l._data[0][0]), N>
{
  Field<decltype(l._data[0][0] / x), N> ret;
  ret._data = x / l._data;
  return ret;
}


template<typename  T, int N>
std::ostream& operator<<(std::ostream& out, Field<T, N> field)
{
  for(int i=0; i<N; ++i)
  {
    std::cout << "===================== " << "mu = " << i << "  =====================" << std::endl << '\n';
    std::cout << field._data[i];
  }
  return out;
}
