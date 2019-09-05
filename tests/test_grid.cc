// #include <Grid/Grid.h>
#define WITH_GRID
#include <ALattice/alattice.h>

using namespace std;

int main(int argc, char **argv)
{
  Grid::Grid_init(&argc, &argv);
  std::vector<int> latt({4,4,4,4});
  std::vector<int> mpi({1,1,1,1});

  Grid::GridCartesian * grid =  Grid::QCD::SpaceTimeGrid::makeFourDimGrid(latt,
                                    Grid::GridDefaultSimd(4,Grid::vComplex::Nsimd()),
                                    mpi);

  Grid::QCD::LatticeGaugeField  U(grid);
  Grid::QCD::LatticeGaugeField  dSdU(grid);
  //
  //
  Grid::FieldMetaData header;
  std::string file("./U_softly_fixed_4");
  Grid::QCD::NerscIO::readConfiguration(U, header,file);
  // cout << U ;
  Grid::QCD::WilsonGaugeActionR action(6.0);
  action.deriv(U, dSdU);
  cout << dSdU;

  std::cout << action.S(U) << std::endl;

  // std::vector<int> v;
  // grid.Broadcast(0, v);
  // Lattice<Matrix3> latm(grid);
  // latm = 3.0;
  // cout << Grid_LatticeColourMatrix(latm) << endl;



}
