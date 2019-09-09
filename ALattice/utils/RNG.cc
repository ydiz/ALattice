#include <ALattice/alattice.h>

void gaussian(LatticeMatrix &ret)
{
  su3_generator ss;
  static RNG<std::normal_distribution<>> rng; // if not static, will reset seed every time this function is called
  LatticeReal lat(ret.grid);
  ret = 0.0;
  for(int i=0; i<8; ++i)
  {
    rng.fill(lat);
    ret += lat * ss.ti[i]; 
  }
}

void gaussian(GaugeField &ret)
{
  for(auto &x: ret._data) gaussian(x);
}

