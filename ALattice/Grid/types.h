#pragma once

using Grid_LatticeReal = Grid::Lattice< Grid::iScalar<Grid::iScalar<Grid::iScalar<double>> > >;
using Grid_LatticeColourMatrix = Grid::Lattice< Grid::iScalar<Grid::iScalar<Grid::iMatrix<std::complex<double>, 3>> > >;
using Grid_LatticeGaugeField = Grid::Lattice< Grid::iVector<Grid::iScalar<Grid::iMatrix<std::complex<double>, 3>>, 4> >;

