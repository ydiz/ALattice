#pragma once

template<typename T>
class Lattice{
public:
  static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");

  Cartesian grid;
  std::vector<T> _data;

  Lattice();
  Lattice(std::vector<int> _grid);
  Lattice(const Cartesian &_grid);

  template<typename U, std::enable_if_t<isNumber<U>::value, int> = 0> 
  Lattice(const U& x);

  T& operator[](int i);
  const T& operator[](int i) const;

  typename std::vector<T>::iterator begin();
  typename std::vector<T>::const_iterator begin() const;
  typename std::vector<T>::iterator end();
  typename std::vector<T>::const_iterator end() const;

  template<typename U> typename std::enable_if<isNumber<U>::value, Lattice<T>&>::type
  operator=(const U &rhs);

  template<typename U>  Lattice<T>& operator+=(const U& x);
  template<typename U>  Lattice<T>& operator-=(const U& x);
  template<typename U>  Lattice<T>& operator*=(const U& x);
  template<typename U>  Lattice<T>& operator/=(const U& x);

  std::vector<T> getSlice(int dim, int coor_value) const; // coor_value in local coordinate!!
  void insertSlice(const std::vector<T> &slice, int dim, int coor_value);

  // conversion to Grid
  #ifdef WITH_GRID
  operator Grid_LatticeReal() const;
  operator Grid_LatticeColourMatrix() const;
  #endif
};

// Field is implemented with vector. In vector's operator+, generally you'll need "grid" make a field object.
template<typename T>
Lattice<T>::Lattice() : Lattice(defaultLat()) {}

template<typename T>
Lattice<T>::Lattice(std::vector<int> _grid) : Lattice(Cartesian(_grid)) {}

template<typename T>
Lattice<T>::Lattice(const Cartesian & _grid) : grid(_grid), _data(grid.volLocal) {}

template<typename T>
template<typename U, std::enable_if_t<isNumber<U>::value, int>>
Lattice<T>::Lattice(const U &x) : Lattice(defaultLat()) {
  for(int i=0; i<grid.volLocal; ++i) _data[i] = x;
}




template<typename T>
typename std::vector<T>::iterator Lattice<T>::begin() {return _data.begin();}

template<typename T>
typename std::vector<T>::const_iterator Lattice<T>::begin() const {return _data.begin();}

template<typename T>
typename std::vector<T>::iterator Lattice<T>::end() {return _data.end();}

template<typename T>
typename std::vector<T>::const_iterator Lattice<T>::end() const {return _data.end();}




template<typename T>
std::vector<T> Lattice<T>::getSlice(int dim, int coor_value) const
{
  std::vector<T> ret(grid.volSlice[dim]);
  int ret_index;
  int offset = coor_value * grid._stride[dim];

  int p2_upper = (dim==grid._ndims-1) ? 1 : (grid.volLocal / grid._stride[dim+1]); // p2_upper; L[dim+1] * L[dim+2]  * ... * L[N-1]
  int p2_step = grid._stride[dim+1];

  for(int p2=0; p2<p2_upper; ++p2) // p2 run over index [dim+1, dim+2, .., N-1]
    for(int p1=0; p1<grid._stride[dim]; ++p1) //p1 run over index [0,1, .. , dim-1]
    {
      ret_index = p1 + p2 * grid._stride[dim];
      ret[ret_index] = _data[offset + p1 + p2 * p2_step];
    }
  return ret;
}

  template<typename T>
void Lattice<T>::insertSlice(const std::vector<T> &slice, int dim, int coor_value)
{
  int slice_index;
  int offset = coor_value * grid._stride[dim];

  int p2_upper = (dim==grid._ndims-1) ? 1 : (grid.volLocal / grid._stride[dim+1]); // p2_upper; L[dim+1] * L[dim+2]  * ... * L[N-1]
  int p2_step = grid._stride[dim+1];

  for(int p2=0; p2<p2_upper; ++p2) // p2 run over index [dim+1, dim+2, .., N-1]
    for(int p1=0; p1<grid._stride[dim]; ++p1) //p1 run over index [0,1, .. , dim-1]
    {
      slice_index = p1 + p2 * grid._stride[dim];
      _data[offset + p1 + p2 * p2_step] = slice[slice_index];
    }
}



template<typename T>
T peekSite(const Lattice<T> &lat, const std::vector<int> &gcoor)
{
  T ret;
  int rank = lat.grid.globalCoorToRank(gcoor);
  int lIndex = lat.grid.localCoorToIndex(lat.grid.globalCoorToLocalCoor(gcoor));

  ret = lat[lIndex];
  lat.grid.Bcast(rank, ret);
  return ret;
}

using LatticeReal = Lattice<double>;
using LatticeComplex = Lattice<Complex>;
using LatticeMatrix = Lattice<Matrix<Complex, 3>>;

