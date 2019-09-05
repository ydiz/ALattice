
// zyd: try to make Cartesian global, and all lattice objects depends on a single grid.
class Cartesian : public Communicator{
public:
  std::vector<int> _gdimensions;
  std::vector<int> _ldimensions;
  std::vector<int> _stride;

  int volGlobal;
  int volLocal;
  std::vector<int> volSlice; // volume when mu'th coordinate is fixed

  std::vector<std::vector<int>> indexMap; // local index after local shift one unit in mu direction

  Cartesian();
  Cartesian(const std::vector<int> &gdimensions);
  Cartesian(const std::vector<int> &gdimensions, const std::vector<int> &processes);

  //global
  std::vector<int> globalCoorToProcessorCoor(const std::vector<int> &gcoor) const;
  int globalCoorToRank(const std::vector<int> &gcoor) const;
  std::vector<int> globalIndexToGlobalCoor(int index) const; // local coordinate
  int globalCoorToGlobalIndex(const std::vector<int> &gcoor) const; // local coordinate

  // local <--> global
  std::vector<int> globalCoorToLocalCoor(const std::vector<int> &gcoor) const;
  std::vector<int> localCoorToGlobalCoor(const std::vector<int> &lcoor) const;
  int globalCoorToLocalIndex(const std::vector<int> &gcoor) const;
  std::vector<int> localIndexToGlobalCoor(int lIndex) const;
  int localIndexToGlobalIndex(int lIndex) const;

  // local
  std::vector<int> localIndexToLocalCoor(int index) const; // local coordinate
  int localCoorToIndex(const std::vector<int> &lcoor) const; // local coordinate


};

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

inline std::vector<int> Cartesian::globalCoorToProcessorCoor(const std::vector<int> &gcoor) const {
  std::vector<int> pcoor(_ndims);
  for(int mu=0; mu<_ndims; ++mu)  pcoor[mu] = gcoor[mu] / _ldimensions[mu];
  return pcoor;
}

inline int Cartesian::globalCoorToRank(const std::vector<int> &gcoor) const {
  return rankFromProcessCoor(globalCoorToProcessorCoor(gcoor));
}

inline std::vector<int> Cartesian::globalCoorToLocalCoor(const std::vector<int> &gcoor) const {
  return gcoor % _ldimensions;
}

inline std::vector<int> Cartesian::localCoorToGlobalCoor(const std::vector<int> &lcoor) const {
  return lcoor + _process_coor * _ldimensions;
}

inline int Cartesian::globalCoorToLocalIndex(const std::vector<int> &gcoor) const {
  return localCoorToIndex(globalCoorToLocalCoor(gcoor));
}

inline std::vector<int> Cartesian::localIndexToLocalCoor(int index) const {
  return indexToCoor(index, _ldimensions);
}

// can be improved by using _stride instead of call function coorToIndex
inline int Cartesian::localCoorToIndex(const std::vector<int> &lcoor) const {
  return coorToIndex(lcoor, _ldimensions);
}

inline std::vector<int> Cartesian::globalIndexToGlobalCoor(int index) const {
  return indexToCoor(index, _gdimensions);
}

inline std::vector<int> Cartesian::localIndexToGlobalCoor(int lIndex) const {
  return localCoorToGlobalCoor(localIndexToLocalCoor(lIndex));
}

inline int Cartesian::localIndexToGlobalIndex(int lIndex) const {
  return globalCoorToGlobalIndex(localIndexToGlobalCoor(lIndex));
}

inline int Cartesian::globalCoorToGlobalIndex(const std::vector<int> &gcoor) const {
  return coorToIndex(gcoor, _gdimensions);
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
