#include <ALattice/alattice.h>

double plaq(const GaugeField &U)
{
  double plaq_sum = 0.0;
  for(int mu=0; mu<4; ++mu)
    for(int nu=mu+1; nu<4; ++nu)
    {
      plaq_sum += sum(trace(real( U[mu] * shiftF(U[nu], mu) * adj(shiftF(U[mu], nu)) * adj(U[nu]) )));
    }
  return plaq_sum / (U.grid.volGlobal * 6.0 * 3.0);
}


double linkTrace(const GaugeField& U)
{
  return sum(trace(real(U))) / (U.grid.volGlobal * 4.0 * 3.0);
}

