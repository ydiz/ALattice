#ifndef XLATTICE_misc_H
#define XLATTICE_misc_H

Lattice<Vector<int, 4>> coordinate(const std::vector<int> &grid)
{
  Lattice<Vector<int, 4>> ret(grid);
  std::vector<int> gcoor(4);
  for(int i=0; i<ret.grid.volLocal; ++i)
  {
    gcoor = ret.grid.localIndexToGlobalCoor(i);
    std::copy(gcoor.begin(), gcoor.end(), ret[i].begin());
  }
  return ret;
}


#endif
