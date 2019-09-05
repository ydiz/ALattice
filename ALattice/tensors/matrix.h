#ifndef XLATTICE_MATRIX_H
#define XLATTICE_MATRIX_H

template<typename T, int N>
class Matrix{
public:
  T m[N][N];

  //construtors
  Matrix();
  template<typename U> Matrix(const U&); //any "number"; isNumber

  T& operator()(int i, int j);
  const T& operator()(int i, int j) const;

  T* begin() {return *m;} //don't make the function const; otherwise *m is const Complex *
  const T* begin() const {return *m;}
  T* end() {return *(m+N-1)+N;}
  const T* end() const {return *(m+N-1)+N;}

  Matrix<T, N>& operator+=(const Matrix<T, N> &rhs);
  Matrix<T, N>& operator-=(const Matrix<T, N> &rhs);
  Matrix<T, N>& operator*=(const Matrix<T, N> &rhs);
  template<typename U>
  typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type operator*=(const U &rhs);
  template<typename U>
  typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type operator/=(const U &rhs);

  // conversion to Grid tensor
  #ifdef WITH_GRID
  operator Grid::iMatrix<T, N>() const;
  #endif
};


template<typename T, int N>
Matrix<T, N>::Matrix() {}

template<typename T, int N>
template<typename U>
Matrix<T, N>::Matrix(const U& x)
{
  static_assert(isNumber<T>::value, "Must be a number");
  for(int i=0; i<N; ++i) m[i][i] = x;
}

// inteface to grid
//FIXME: change Grid::iMatrix<Complex, N> to Grid::iMatrix<T, N>
#ifdef WITH_GRID
template<typename T, int N>
inline Matrix<T, N>::operator Grid::iMatrix<T, N>() const
{
  Grid::iMatrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret._internal[i][j] = m[i][j];
  return ret;
}
#endif


using Matrix3 = Matrix<Complex, 3>;

#endif
