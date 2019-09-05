#ifndef XField_FIELD_H
#define XField_FIELD_H

// static const int Nd = 4;
// fermion field, put color index to Field, spin index to vector
template<typename T, int N>
class Field{
public:
  std::vector<Lattice<T>> _data;
  Cartesian grid;

  Field();
  Field(const Cartesian& grid);
  template<typename U> Field(const U& x);

  template<typename U>  Field& operator+=(const U& x);
  template<typename U>  Field& operator-=(const U& x);
  template<typename U>  Field& operator*=(const U& x);
  template<typename U>  Field& operator/=(const U& x);

  Lattice<T>& operator[](int i);
  const Lattice<T>& operator[](int i) const;
};

// constructors
template<typename T, int N>
Field<T, N>::Field() : _data(N) { grid = _data[0].grid; }

template<typename T, int N>
Field<T, N>::Field(const Cartesian &_grid) : _data(N, Lattice<T>{_grid}) { grid = _data[0].grid; }

template<typename T, int N>
template<typename U>
Field<T, N>::Field(const U& x) : _data(N)
{
  for(auto &data_i:  _data) data_i = x;
  grid = _data[0].grid;
}


using GaugeField = Field<Matrix<Complex, 3>, 4>;
using ColorMatrixField = Field<Matrix<Complex, 3>, 1>;
using RealField = Field<double, 1 >;
using ComplexField = Field<Complex, 1 >;

#endif
