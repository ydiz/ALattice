#include <ALattice/alattice.h>

void WilsonAction::describe() const {
  std::cout << "Wilson Action beta = " + std::to_string(beta_) << std::endl;
}

double WilsonAction::S(const GaugeField &U) const {
  double avgPlaq = plaq(U);
  return beta_ * (1.0 - avgPlaq) * 6 * U.grid.volGlobal;
}

GaugeField WilsonAction::deriv(const GaugeField &U) const {
  GaugeField rst;

  for(size_t mu=0; mu<4; ++mu) {
    LatticeMatrix staple_mu {}; // this will set every element to 0

    for(size_t nu=0; nu<4; ++nu) {
      if(nu==mu) continue;
      staple_mu += shiftF(U[nu], mu) * adj(shiftF(U[mu], nu)) * adj(U[nu]) 
        + adj(shiftB(shiftF(U[nu], mu), nu)) * adj(shiftB(U[mu], nu)) * shiftB(U[nu], nu); 
    }
    rst[mu] = Ta(U[mu] * staple_mu);
  }

  return (beta_ / 6.0  * 0.5) * rst; // 0.5 comes from Ta
}
