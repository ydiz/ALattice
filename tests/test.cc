#include <ALattice/alattice.h>

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);
  RealField rf = -1;
  // std::cout << rf << std::endl;
  cout << sum(rf) << endl;

  // GaugeField gf = 1.0;
  // cout << gf;
  GaugeField P;
  P = 1.0;
  std::cout << plaq(P) << std::endl;
  gaussian(P);
  // std::cout << P << std::endl;

  return 0;
}
