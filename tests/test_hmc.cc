#include <ALattice/alattice.h>

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);

  // GaugeField U = 1.0;
  // GaugeField U = readField("U_softly_fixed_4");
  // std::cout << action.S(U) << std::endl;
  // std::cout << action.deriv(U) << std::endl;

  WilsonAction action(6.0);

  HMC_para para;
  para.trajs = 50;

  HMC hmc(para, action);
  hmc.run();
  return 0;
}
