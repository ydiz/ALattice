#ifndef XLATTICE_CSHIFT_H
#define XLATTICE_CSHIFT_H

template<typename T>
Lattice<T> shiftF(const Lattice<T> &lat, int dim)
{
  std::vector<T> slice = lat.getSlice(dim, 0);
  std::vector<T> newSlice(lat.grid.volSlice[dim]);

  // send/receive slice to/from other nodes.
  int bytes = slice.size() * sizeof(T);
  int rank_source, rank_dest;
  int err1 = MPI_Cart_shift(lat.grid.cartComm, dim, -1, &rank_source, &rank_dest);
  assert(err1==0);
  MPI_Request recv_request, send_request, requests_array[2];
  MPI_Irecv(newSlice.data(), bytes, MPI_BYTE, rank_source, 0, lat.grid.cartComm, &recv_request);
  MPI_Isend(slice.data(), bytes, MPI_BYTE, rank_dest, 0, lat.grid.cartComm, &send_request);
  requests_array[0] = recv_request;  requests_array[1] = send_request;
  MPI_Waitall(2, requests_array, MPI_STATUSES_IGNORE);
  MPI_Barrier(lat.grid.cartComm);

  // Lat after mpi communication
  Lattice<T> newLat = lat;
  newLat.insertSlice(newSlice, dim, 0);

  // local cshift
  Lattice<T> ret(lat.grid);
  for(int i=0; i<lat.grid.volLocal; ++i) ret[i] = newLat[lat.grid.indexMap[dim][i]];
  return ret;
}

template<typename T>
Lattice<T> shiftB(const Lattice<T> &lat, int dim)
{
  std::vector<T> slice = lat.getSlice(dim, lat.grid._ldimensions[dim]-1);
  std::vector<T> newSlice(lat.grid.volSlice[dim]);

  // send/receive slice to/from other nodes.
  int bytes = slice.size() * sizeof(T);
  int rank_source, rank_dest;
  MPI_Cart_shift(lat.grid.cartComm, dim, 1, &rank_source, &rank_dest);
  MPI_Request recv_request, send_request, requests_array[2];
  MPI_Irecv(newSlice.data(), bytes, MPI_BYTE, rank_source, 0, lat.grid.cartComm, &recv_request);
  MPI_Isend(slice.data(), bytes, MPI_BYTE, rank_dest, 0, lat.grid.cartComm, &send_request);
  requests_array[0] = recv_request;  requests_array[1] = send_request;
  MPI_Waitall(2, requests_array, MPI_STATUSES_IGNORE);
  MPI_Barrier(lat.grid.cartComm);

  // Lat after mpi communication
  Lattice<T> newLat = lat;
  newLat.insertSlice(newSlice, dim, lat.grid._ldimensions[dim]-1);

  // local cshift
  Lattice<T> ret(lat.grid);
  for(int i=0; i<lat.grid.volLocal; ++i) ret[lat.grid.indexMap[dim][i]] = newLat[i];
  return ret;
}

// test cshift
// Lattice<Vector<int, 4>> coor;
// coor = coordinate(defaultLat());
// cout << shiftF(coor, 2);


template<typename T, int N>
Field<T, N> shiftF(const Field<T, N> &fld, int dim)
{
  Field<T, N> ret;
  for(int i=0; i<N; ++i) ret._data[i] = shiftF(fld._data[i], dim);
  return ret;
}

template<typename T, int N>
Field<T, N> shiftB(const Field<T, N> &fld, int dim)
{
  Field<T, N> ret;
  for(int i=0; i<N; ++i) ret._data[i] = shiftB(fld._data[i], dim);
  return ret;
}


#endif
