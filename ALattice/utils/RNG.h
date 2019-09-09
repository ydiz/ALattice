#pragma once

//two ways to call RNG: 1. rng(); 2. rng.rand()
template<typename DIST>
class RNG {
  std::default_random_engine eng;
  DIST dist;
public:
  using result_type = typename DIST::result_type;

  std::function<result_type()> rand; // not necessary; identical to operator()

  template<class... T> RNG(T... args);
  result_type operator()();

  void fill(Lattice<result_type> &lat);
};

// constructor
template<typename DIST>
template<class... T>
RNG<DIST>::RNG(T... args) : dist(args...)
{
  // auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  // eng.seed(seed);
  eng.seed(0);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  eng.discard(rank * 10e8);

  rand = [this]{return dist(eng);};  //"this" can only be captured by copy, i.e. [this] or [=]
}

// operator()
template<typename DIST>
inline typename DIST::result_type RNG<DIST>::operator()()
{
  return dist(eng);
}

template<typename DIST>
void RNG<DIST>::fill(Lattice<result_type> &lat)
{
  std::generate(lat._data.begin(), lat._data.end(), rand);
}



void gaussian(LatticeMatrix &ret);
void gaussian(GaugeField &ret);


