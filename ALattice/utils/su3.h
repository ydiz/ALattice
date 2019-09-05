#ifndef XLATTICE_SU3_H
#define XLATTICE_SU3_H

//FIXME: how to do this at compile time??
struct su3_generator{
  std::vector<Matrix<Complex, 3>> ti;

  su3_generator() : ti(8)
  {
    std::vector<Complex> t(9);
    const Complex j(0.0, 1.0);

    t = {0,j,0, -j,0,0, 0,0,0};
    std::copy(t.begin(), t.end(), ti[0].begin());
    t = {0,1,0, 1,0,0, 0,0,0};
    std::copy(t.begin(), t.end(), ti[1].begin());
    t = {0,0,j, 0,0,0, -j,0,0};
    std::copy(t.begin(), t.end(), ti[2].begin());
    t = {0,0,1, 0,0,0, 1,0,0};
    std::copy(t.begin(), t.end(), ti[3].begin());
    t = {0,0,0, 0,0,j, 0,-j,0};
    std::copy(t.begin(), t.end(), ti[4].begin());
    t = {0,0,0, 0,0,1, 0,1,0};
    std::copy(t.begin(), t.end(), ti[5].begin());
    t = {1,0,0, 0,-1,0, 0,0,0};
    std::copy(t.begin(), t.end(), ti[6].begin());
    t = {1,0,0, 0,1,0, 0,0,-2};
    std::copy(t.begin(), t.end(), ti[7].begin());


    for(int i=0; i<7; ++i) ti[i] /= 2.;
    ti[7] /= 2. * std::sqrt(3.);
  }
};

#endif

/*
ta[0] = np.array([[0,1j,0],[-1j,0,0],[0,0,0]])
ta[1] = np.array([[0,1,0],[1,0,0],[0,0,0]])
ta[2] = np.array([[0,0,1j],[0,0,0],[-1j,0,0]])
ta[3] = np.array([[0,0,1],[0,0,0],[1,0,0]])

ta[4] = np.array([[0,0,0],[0,0,1j],[0,-1j,0]])
ta[5] = np.array([[0,0,0],[0,0,1],[0,1,0]])
ta[6] = np.array([[1,0,0],[0,-1,0],[0,0,0]])
ta[7] = np.array([[1,0,0],[0,1,0],[0,0,-2]])
*/
