// usually use cartComm
class Communicator{
public:
  static int rank_;
  static int worldSize; // this one is needed, should not be deleted.
  static int isWorldLeader;

  static std::string node;


  static MPI_Comm cartComm;
  static int _ndims;
  static std::vector<int> _processes_grid;
  static std::vector<int> _process_coor;

  Communicator(const std::vector<int> &processes_grid);

  int Rank() const;
  int rankFromProcessCoor(const std::vector<int> &process_coor) const;
  std::vector<int> processCoorFromRank(int rank) const;

  template<typename T>
  typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type Bcast(int root, T &data) const; // Broadcast an object
  template<typename T> void Bcast(int root, std::vector<T> &data) const;  //Broadcast a vector

  template<typename T> T sumMPI(T x) const;
};

template<typename T>
T Communicator::sumMPI(T x) const
{
  T ret;
  MPI_Allreduce(&x, &ret, 1, MPI_Type<T>::value, MPI_SUM, cartComm);
  return ret;
}


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

inline int Communicator::rankFromProcessCoor(const std::vector<int> &process_coor) const
{
  int rank;
  MPI_Cart_rank(cartComm, process_coor.data(), &rank);
  return rank;
}

inline std::vector<int> Communicator::processCoorFromRank(int rank) const
{
  std::vector<int> process_coor(_ndims);
  MPI_Cart_coords(cartComm, rank, _ndims, process_coor.data());
  return process_coor;
}

template<typename T>
typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
Communicator::Bcast(int root, T &data) const {
  MPI_Bcast(&data, sizeof(data), MPI_BYTE, root, cartComm); // ? (void *)&data is unnecessary
}

template<typename T>
inline void Communicator::Bcast(int root, std::vector<T> &data) const {
  MPI_Bcast(data.data(), data.size() * sizeof(T), MPI_BYTE, root, cartComm);
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
