#pragma once

inline std::vector<int> indexToCoor(int index, const std::vector<int> &coor)
{
  std::vector<int> lcoor(coor.size());
  for(int mu=0; mu<coor.size(); ++mu){
    lcoor[mu] = index % coor[mu];
    index = index / coor[mu];
  }
  return lcoor;
}

inline int coorToIndex(const std::vector<int> &coor_value, const std::vector<int> &coor)
{
  int index = 0;
  int stride = 1;
  for (int mu=0; mu<coor.size(); ++mu)
  {
    index += coor_value[mu] * stride;
    stride *= coor[mu];
  }
  return index;
}

