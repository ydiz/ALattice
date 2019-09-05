#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <type_traits>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <fstream>
#include <utility>
#include <array>
#include <regex>

#define WITH_MPI3

#ifdef WITH_MPI3
#include <mpi.h>
#endif

// #define WITH_GRID

#ifdef WITH_GRID
#include <Grid/Grid.h>
#include "./Grid/xlattice_grid.h"
#endif

// std::vector<int> default_grid;
// int default_grid_vol;

#include "utils/vector.h"
#include "init.h"
#include "utils/util.h"

#include "type.h"

#ifdef WITH_MPI3
#include "mpi/communicator.h"
#include "cartesian.h"
#endif

#include "tensors/matrix.h"
#include "tensors/vector.h"
#include "tensors/overload.h"

#include "field/lattice.h"
#include "field/field.h"
#include "field/overload.h"
#include "math_operations/math_operations.h"
#include "cshift.h"

#include "utils/misc.h"
#include "utils/read_write.h"
#include "utils/su3.h"
#include "utils/io.h"
#include "utils/observables.h"

#include "RNG.h"

#include "HMC/actions.h"
#include "HMC/WilsonAction.h"
#include "HMC/integrator.h"
#include "HMC/hmc.h"

// using Complex = std::complex<double>;
// using Matrix3 = Matrix<Complex, 3> ;
// using Vector4 = Vector<Complex, 4>;
// using VectorInt4 = Vector<int, 4>;
// using LatticeReal = Lattice<double>;
// using LatticeComplex = Lattice<Complex>;
// using LatticeMatrix = Lattice<Matrix<Complex, 3> >;
// using GaugeField = Field< Matrix<Complex, 3>  >;
// using RealField = Field< double >;
// using ComplexField = Field< Complex >;
