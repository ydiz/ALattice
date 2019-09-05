#pragma once

////////////////////////////////////////////////////
//Matrix
///////////////////////////////////////////////////

template<typename T, int N>
inline T& Matrix<T, N>::operator()(int i, int j)
{
  return m[i][j];
}

template<typename T, int N>
inline const T& Matrix<T, N>::operator()(int i, int j) const
{
  return m[i][j];
}

// =, +=, -=, *=, /=

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator+=(const Matrix<T, N> &rhs)
{
  *this = *this + rhs;
  return *this;
}

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator-=(const Matrix<T, N> &rhs)
{
  *this = *this - rhs;
  return *this;
}

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator*=(const Matrix<T, N> &rhs)
{
  *this = *this * rhs;
  return *this;
}


template<typename T, int N>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type Matrix<T, N>::operator*=(const U& rhs)
{
  *this = *this * rhs;
  return *this;
}

template<typename T, int N>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type Matrix<T, N>::operator/=(const U& rhs)
{
  *this = *this / rhs;
  return *this;
}

// unary -
template<typename T, int N>
inline Matrix<T, N> operator-(const Matrix<T, N> &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = -x.m[i][j];
  return ret;
}

// +, -, *, /
template<typename T, int N>
inline Matrix<T, N> operator+(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] + m2.m[i][j];
  return ret;
}

template<typename T, int N>
inline Matrix<T, N> operator-(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] - m2.m[i][j];
  return ret;
}

template<typename T, int N>
inline Matrix<T, N> operator*(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  ret = 0;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      for(int k=0; k<N; ++k)
        ret.m[i][j] += m1.m[i][k] * m2.m[k][j];
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator*(const Matrix<T, N> &m1, const U &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] * x;
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator*(const U &x, const Matrix<T, N> &m1)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] * x;
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator/(const Matrix<T, N> &m1, const U &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] / x;
  return ret;
}

template<typename T, int N>
std::ostream& operator<<(std::ostream &out, const Matrix<T, N> M)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
      out << M.m[i][j] << " ";
    out << std::endl;
  }
  return out;
}

////////////////////////////////////////////////////
//Vector
///////////////////////////////////////////////////

template<typename T, int N>
inline T& Vector<T, N>::operator[](int i)
{
  return v[i];
}

template<typename T, int N>
inline const T& Vector<T, N>::operator[](int i) const
{
  return v[i];
}

// =, +=, -=, *=, /=

template<typename T, int N>
inline Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N> &rhs)
{
  *this = *this + rhs;
  return *this;
}

template<typename T, int N>
inline Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N> &rhs)
{
  *this = *this - rhs;
  return *this;
}


// unary -
template<typename T, int N>
inline Vector<T, N> operator-(const Vector<T, N> &x)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = -x.v[i];
  return ret;
}

// +, -, *, /
template<typename T, int N>
inline Vector<T, N> operator+(const Vector<T, N> &m1, const Vector<T, N> &m2)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = m1.v[i] + m2.v[i];
  return ret;
}

template<typename T, int N>
inline Vector<T, N> operator-(const Vector<T, N> &m1, const Vector<T, N> &m2)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = m1.v[i] - m2.v[i];
  return ret;
}

template<typename T, int N>
std::ostream& operator<<(std::ostream &out, const Vector<T, N> v)
{
  out << "[";
  for(const auto &x: v)
  {
    if(&x == v.end()-1)
      out << x << "]";
    else
      out << x << ", ";
  }
  return out;
}





