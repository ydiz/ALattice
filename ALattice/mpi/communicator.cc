#include <ALattice/alattice.h>


Communicator::Communicator(const std::vector<int> &processes_grid)
{
  MPI_Comm_rank(MPI_COMM_WORLD, &rank_);
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

  isWorldLeader = (rank_ == 0);

  // node; name of node
  int nodeNameLen=0;
  char nodeName[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(nodeName, &nodeNameLen);
  node = std::string(nodeName, nodeName+nodeNameLen);

  // Cartesian layout
  _ndims = processes_grid.size();
  _processes_grid = processes_grid;
  MPI_Cart_create(MPI_COMM_WORLD, _ndims, _processes_grid.data(), std::vector<int>(_ndims,1).data(), 0, &cartComm); // "0" indicates no re-ordering

  _process_coor.resize(_ndims);
  MPI_Cart_coords(cartComm, rank_, _ndims, _process_coor.data());
}

int Communicator::Rank() const {
  return rank_;
}

int Communicator::rankFromProcessCoor(const std::vector<int> &process_coor) const
{
  int rank;
  MPI_Cart_rank(cartComm, process_coor.data(), &rank);
  return rank;
}

std::vector<int> Communicator::processCoorFromRank(int rank) const
{
  std::vector<int> process_coor(_ndims);
  MPI_Cart_coords(cartComm, rank, _ndims, process_coor.data());
  return process_coor;
}


std::ostream& operator<<(std::ostream& out, const Communicator &comm)
{
  std::cout << "worldRank " << comm.rank_ << " of " << comm.worldSize << " running on " << comm.node
       << "; coor " << comm._process_coor << std::endl;
  return out;
}


// static variables
int Communicator::rank_;
int Communicator::worldSize;
int Communicator::isWorldLeader;

// int Communicator::Nnodes;
std::string Communicator::node;

MPI_Comm Communicator::cartComm;
int Communicator::_ndims;
std::vector<int> Communicator::_processes_grid;
std::vector<int> Communicator::_process_coor;
