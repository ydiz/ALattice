#include <ALattice/alattice.h>

using namespace std;

int main(int argc, char **argv)
{
  init(argc, argv);

  Lattice<Vector<int, 4>> coor;
  coor = coordinate(defaultLat());
  cout << shiftF(coor, 2);

  return 0;
}
