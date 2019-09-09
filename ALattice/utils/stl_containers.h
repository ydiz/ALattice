#pragma once

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> &v)
{
  out << "[";
  for(const auto &x: v)
  {
    if(&x == &v.back())
      out << x << "]";
    else
      out << x << ", ";
  }
  return out;
}


// unary -
template<typename T>
inline std::vector<T> operator-(const std::vector<T>& v1)
{
  std::vector<T> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = - v1[i];
  return ret;
}

// +, -, *, /
template<typename T, typename U>
inline auto operator+(const std::vector<T>& v1, const std::vector<U> &v2) -> std::vector<decltype(v1[0]+v2[0])>
{
  std::vector<decltype(v1[0]+v2[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] + v2[i];
  return ret;
}


template<typename T, typename U>
inline auto operator-(const std::vector<T>& v1, const std::vector<U> &v2) -> std::vector<decltype(v1[0]-v2[0])>
{
  std::vector<decltype(v1[0]-v2[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] - v2[i];
  return ret;
}

template<typename T, typename U>
inline auto operator*(const std::vector<T>& v1, const std::vector<U> &v2) -> std::vector<decltype(v1[0]*v2[0])>
{
  std::vector<decltype(v1[0]*v2[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] * v2[i];
  return ret;
}


template<typename T, typename U>
inline auto operator*(const std::vector<T>& v1, const U &x) -> std::vector<decltype(v1[0]*x)>
{
  std::vector<decltype(v1[0]*x)> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] * x;
  return ret;
}

template<typename T, typename U>
inline auto operator*(const T& x, const std::vector<U>& v1) -> std::vector<decltype(x * v1[0])>
{
  std::vector<decltype(x*v1[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = x * v1[i];
  return ret;
}



template<typename T, typename U>
inline auto operator/(const std::vector<T>& v1, const std::vector<U> &v2) -> std::vector<decltype(v1[0]/v2[0])>
{
  std::vector<decltype(v1[0]/v2[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] / v2[i];
  return ret;
}

template<typename T, typename U>
inline auto operator/(const std::vector<T>& v1, const U &x) -> std::vector<decltype(v1[0] /x)>
{
  std::vector<decltype(v1[0]*x)> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] / x;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const T& x, const std::vector<U>& v1) -> std::vector<decltype(x / v1[0])>
{
  std::vector<decltype(x*v1[0])> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = x / v1[i];
  return ret;
}

inline std::vector<int> operator%(const std::vector<int> &v1, const std::vector<int> &v2)
{
  std::vector<int> ret(v1.size());
  for(int i=0; i<v1.size(); ++i) ret[i] = v1[i] % v2[i];
  return ret;
}




// not convenient for openmp
// unary: sum
// template<typename T>
// inline T sum(const std::vector<T>& v)
// {
//   T ret;
//   ret = 0;
//   for(int i=0; i<v.size(); ++i) ret += v[i];
//   return ret;
// }
//
// template<typename T>
// inline auto real(const std::vector<T>& v) -> std::vector< decltype(real(v[0])) >
// {
//   std::vector<decltype(real(v[0]))> ret;
//   for(int i=0; i<v.size(); ++i) ret[i] = real(v[i]);
//   return ret;
// }




inline std::complex<double> operator+(const std::complex<double> &c, int x)
{
  return std::complex<double>(c.real() + x, c.imag());
}

inline std::complex<double> operator*(const std::complex<double> &c, int x)
{
  return std::complex<double>(c.real() * x, c.imag() * x);
}


template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, std::pair<T, U> p)
{
  out << "(" << p.first << ", " << p.second << ")";
}

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, std::array<T, N> a)
{
  out << "[";
  for(int i=0; i<N; ++i)
  {
    if(i==N-1)
      out << a[i] << "]";
    else
      out << a[i] << ", ";
  }
  return out;
}
