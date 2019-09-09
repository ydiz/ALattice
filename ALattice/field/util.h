#pragma once

// generate a lattice whose value on each site is the coordinate of that site
Lattice<Vector<int, 4>> coordinate(const std::vector<int> &grid);
