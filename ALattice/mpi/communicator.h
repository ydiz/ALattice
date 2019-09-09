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


template<typename T>
typename std::enable_if<std::is_trivially_copyable<T>::value, void>::type
Communicator::Bcast(int root, T &data) const {
  MPI_Bcast(&data, sizeof(data), MPI_BYTE, root, cartComm); // ? (void *)&data is unnecessary
}

template<typename T>
inline void Communicator::Bcast(int root, std::vector<T> &data) const {
  MPI_Bcast(data.data(), data.size() * sizeof(T), MPI_BYTE, root, cartComm);
}


