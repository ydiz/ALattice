#include <ALattice/alattice.h>

Cartesian::Cartesian() : Cartesian(defaultLat(), defaultMPI()) {}

Cartesian::Cartesian(const std::vector<int> &gdimensions) : Cartesian(gdimensions, defaultMPI()) {}

Cartesian::Cartesian(const std::vector<int> &gdimensions, const std::vector<int> &processes) : Communicator(processes)
{
  _gdimensions = gdimensions;
  _ldimensions = _gdimensions / processes;

  _stride.resize(_ndims); _stride[0] = 1;
  for(int mu=1; mu<_ndims; ++mu) _stride[mu] = _stride[mu-1] * _ldimensions[mu-1];

  volLocal = 1;
  for(auto x: _ldimensions) volLocal *= x;

  volGlobal = 1;
  for(auto x: _gdimensions) volGlobal *= x;

  volSlice = std::vector<int>(_ndims, 1);
  for(int mu=0; mu<_ndims; ++mu)
  {
    for(int nu=0; nu<_ndims; ++nu){
      if(mu!=nu) volSlice[mu] *= _ldimensions[nu];
    }
  }

  indexMap = std::vector<std::vector<int>>(_ndims, std::vector<int>(volLocal));
  std::vector<int> lcoor(_ndims);
  std::vector<int> newCoor(_ndims);
  for(int i=0; i<volLocal; ++i)
  {
    lcoor = localIndexToLocalCoor(i);
    for(int mu=0; mu<_ndims; ++mu)
    {
      newCoor = lcoor;
      newCoor[mu] = (lcoor[mu] + 1) % _ldimensions[mu];
      indexMap[mu][i] = localCoorToIndex(newCoor);
    }
  }
}


std::ostream& operator<<(std::ostream& out, const Cartesian& grid)
{
  out << "_ndims: " << grid._ndims << std::endl;
  out << "_gdimensions: " << grid._gdimensions << std::endl;
  out << "_ldimensions: " << grid._ldimensions << std::endl;
  out << "_stride: " << grid._stride << std::endl;
  out << "volLocal: " << grid.volLocal << std::endl;
  out << "volSlice" << grid.volSlice << std::endl;
}
