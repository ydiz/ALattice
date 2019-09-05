#ifdef WITH_GRID
template<typename T>
Lattice<T>::operator Grid_LatticeReal() const
{
  static_assert(isNumber<T>::value, "Must be a number");
  std::vector<int> mpi {1,1,1,1};
  std::vector<int> simd {1,1,1,1};
  Grid::GridCartesian *Grid_grid = Grid::QCD::SpaceTimeGrid::makeFourDimGrid(grid, simd, mpi);
  Grid_LatticeReal ret(Grid_grid);
  for(int i=0; i<grid.volLocal; ++i) ret._odata[i] = _data[i];
  return ret;
}

template<typename T>
Lattice<T>::operator Grid_LatticeColourMatrix() const
{
  static_assert(isMatrix<T>::value && T::dim==3, "Must be a 3x3 matrix");
  std::vector<int> mpi {1,1,1,1};
  std::vector<int> simd {1,1,1,1};
  Grid::GridCartesian *Grid_grid = Grid::QCD::SpaceTimeGrid::makeFourDimGrid(grid, simd, mpi);
  Grid_LatticeColourMatrix ret(Grid_grid);
  for(int i=0; i<grid.volLocal; ++i) ret._odata[i]()() = Grid::iMatrix<Complex, 3>(_data[i]);
  return ret;
}
#endif
