#include <ALattice/alattice.h>

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);
  RealField rf = -1;
  cout << sum(rf);

  // GaugeField gf = 1.0;
  // cout << gf;
  GaugeField P;
  gaussian(P);
  std::cout << P << std::endl;

  // string file= "U_softly_fixed_4";
  // GaugeField U;
  // U = readField(file);
  //
  // cout << linkTrace(U);
  // cout << plaq(U);

  // test cshift
  // Lattice<Vector<int, 4>> coor;
  // coor = coordinate(defaultLat());
  // cout << shiftF(coor, 2);

  return 0;

}
