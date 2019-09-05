#include <ALattice/alattice.h>

using namespace std;


int main(int argc, char** argv)
{
  init(argc, argv);

  RealField rf = -1;
  cout << sum(rf);

  MPI_Finalize();

  return 0;
}
