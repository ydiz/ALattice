#include <ALattice/alattice.h>

static std::vector<int> _defaultMPI;
// static std::vector<int> _defaultLat {8,8,8,8};
static std::vector<int> _defaultLat {4,4,4,4};

std::vector<int> defaultMPI(){
  return _defaultMPI;
}

std::vector<int> defaultLat(){
  return _defaultLat;
}


static void quiesce_node()
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank!=0) std::cout.clear(std::ios_base::badbit);
}

static void unquiesce_node()
{
  std::cout.clear();
}

static void set_default_mpi() {
  int nodes;
  MPI_Comm_size(MPI_COMM_WORLD, &nodes);
  _defaultMPI = {1,1,1,1};

  int i=3;
  while(nodes!=1) {
    nodes /= 2;
    _defaultMPI[i] *= 2;
    i--;
    if(i==-1) i = 3;   
  }
 
}

void init(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  quiesce_node();
  set_default_mpi();

  std::cout << "Lattice size: " << defaultLat() << std::endl;
  std::cout << "MPI decomposition: " << defaultMPI() << std::endl;
  std::cout << "Number of threads: " << omp_get_thread_num() << std::endl;
  std::cout << std::string(30, '=') << std::endl;
}

void finalize() {
  MPI_Finalize();
}

