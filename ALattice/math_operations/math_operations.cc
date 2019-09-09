#include <ALattice/alattice.h>

GaugeField Exponentiate(const GaugeField &U, double alpha, int Nexp) {
  GaugeField rst;
  for(int mu=0; mu<4; ++mu)
    for(int i=0; i<U.grid.volLocal; ++i) 
      rst[mu]._data[i] = Exponentiate(U[mu]._data[i], alpha, Nexp);

  return rst;
}

