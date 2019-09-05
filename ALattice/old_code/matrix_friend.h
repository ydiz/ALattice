#ifndef MATRIX_H
#define MATRIX_H

// declare friend functions of tempalte class
template<int N> class Matrix;
template<int N> Matrix<N> operator+(const Matrix<N> &m1, const Matrix<N> &m2);
template<int N> Matrix<N> operator-(const Matrix<N> &m1, const Matrix<N> &m2);
template<int N> Matrix<N> operator*(const Matrix<N> &m1, const Matrix<N> &m2);
template<typename T, int N> typename std::enable_if< isNumber<T>::value, Matrix<N> >::type operator*(const Matrix<N> &m1, const T &m2);
template<typename T, int N> typename std::enable_if< isNumber<T>::value, Matrix<N> >::type operator*(const T &m2, const Matrix<N> &m1);

template<int N> std::ostream& operator<<(std::ostream &out, const Matrix<N> M);

//  it's cleaner to make m[][] public and do not use friend functions
template<int N>
class Matrix{
    Complex m[N][N];
public:

  Complex& operator()(int i, int j);
  const Complex& operator()(int i, int j) const;

  template<typename T>
  typename std::enable_if<isNumber<T>::value, Matrix<N>&>::type operator=(const T &rhs);

  Matrix<N>& operator+=(const Matrix<N> &rhs);
  Matrix<N>& operator-=(const Matrix<N> &rhs);
  Matrix<N>& operator*=(const Matrix<N> &rhs);
  // template<typename T>
  // typename std::enable_if<isNumber<T>::value, Matrix<N>&>::type operator*=(const T &rhs);

  friend Matrix<N> operator+ <>(const Matrix<N> &m1, const Matrix<N> &m2);
  friend Matrix<N> operator- <>(const Matrix<N> &m1, const Matrix<N> &m2);
  // friend Matrix<N> operator* <>(const Matrix<N> &m1, const Matrix<N> &m2);

  template<typename T, int M>  friend typename std::enable_if< isNumber<T>::value, Matrix<M> >::type
  operator* (const Matrix<M> &m1, const T &m2);

  friend std::ostream& operator<< <>(std::ostream &out, const Matrix<N> M);
};


template<int N>
inline Complex& Matrix<N>::operator()(int i, int j)
{
  assert(i>=0 && i<=N); //comment this after testing period
  assert(j>=0 && j<=N);
  return m[i][j];
}

template<int N>
inline const Complex& Matrix<N>::operator()(int i, int j) const
{
  assert(i>=0 && i<=N);  //comment this after testing period
  assert(j>=0 && j<=N);
  return m[i][j];
}

template<int N>
template<typename T>
inline typename std::enable_if< isNumber<T>::value, Matrix<N>& >::type Matrix<N>::operator=(const T &rhs)
{
  for(int i=0; i<N; ++i) m[i][i] = rhs;
}


template<int N>
inline Matrix<N>& Matrix<N>::operator+=(const Matrix<N> &rhs)
{
  *this = *this + rhs;
  return *this;
}

template<int N>
inline Matrix<N>& Matrix<N>::operator-=(const Matrix<N> &rhs)
{
  *this = *this - rhs;
  return *this;
}

template<int N>
inline Matrix<N>& Matrix<N>::operator*=(const Matrix<N> &rhs)
{
  *this = *this * rhs;
  return *this;
}


template<int N>
inline Matrix<N> operator+(const Matrix<N> &m1, const Matrix<N> &m2)
{
  Matrix<N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret(i,j) = m1(i,j) + m2(i,j);
  return ret;
}

template<int N>
inline Matrix<N> operator-(const Matrix<N> &m1, const Matrix<N> &m2)
{
  Matrix<N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret(i,j) = m1(i,j) - m2(i,j);
  return ret;
}

// template<int N>
// inline Matrix<N> operator*(const Matrix<N> &m1, const Matrix<N> &m2)
// {
//   Matrix<N> ret;
//   ret = 0;
//   for(int i=0; i<N; ++i)
//     for(int j=0; j<N; ++j)
//       for(int k=0; k<N; ++k)
//         ret(i,j) += m1(i,k) * m2(k,j);
//   return ret;
// }

template<typename T, int N>
inline typename std::enable_if< isNumber<T>::value, Matrix<N> >::type
operator*(const Matrix<N> &m1, const T &m2)
{
  Matrix<N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret(i,j) = m1(i,j) * m2;
  return ret;
}


template<int N>
std::ostream& operator<<(std::ostream &out, const Matrix<N> M)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
      out << M(i,j) << " ";
    out << std::endl;
  }
  return out;
}

#endif
