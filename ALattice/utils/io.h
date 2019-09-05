#ifndef XLATTICE_IO_H
#define XLATTICE_IO_H

inline uint64_t byte_reverse64(uint64_t f) {
uint64_t g;
g = ((f&0xFF)<<24) | ((f&0xFF00)<<8) | ((f&0xFF0000)>>8) | ((f&0xFF000000UL)>>24) ;
g = g << 32;
f = f >> 32;
g|= ((f&0xFF)<<24) | ((f&0xFF00)<<8) | ((f&0xFF0000)>>8) | ((f&0xFF000000UL)>>24) ;
return g;
}

// ?_dims may not be 4
Cartesian readHeader(const std::string &header)
{
  std::vector<int> gcoor(4);

  std::regex re(R"(DIMENSION_(\d) = (\d)+)");
  std::sregex_iterator match_begin(header.begin(), header.end(), re);
  std::sregex_iterator match_end;
  for(auto i=match_begin; i!=match_end; ++i)
  {
    gcoor[std::stoi((*i)[1])-1] = std::stoi((*i)[2]);
  }
  // std::cout << gcoor << std::endl;
  return Cartesian{gcoor};
}

// read IEEE64BIG; only for double(not float)!
// make U depends on grid!! or check is the grid read from file is identical to default grid
// ?? check if saved field has lorentz index. if not, size_per_site_bytes and loop over mu need to be changed.
GaugeField readField(const std::string& filename, bool verbose=0) // verbose: print out header
{
  std::ifstream f(filename);
  std::string line;
  std::string header;
  while(line != "END_HEADER") {
    getline(f, line);
    header += line + '\n';
  }
  if(verbose) std::cout << header << std::endl;

  Cartesian grid = readHeader(header); // read grid from hdeader.

  // get the size of the data section of the input file
  int data_begin = f.tellg();
  f.seekg(0, f.end);
  int data_end = f.tellg();

  f.seekg(0, f.beg);
  int header_size = data_begin;
  int data_size = data_end - data_begin;
  int size_per_site_bytes = data_size / grid.volGlobal; //size per site in bytes

  int node_size = data_size / grid.worldSize;
  int node_size_in_double = node_size / sizeof(uint64_t);
  int node_size_in_complex = node_size_in_double / 2;
  int node_size_in_matrix = node_size_in_complex / 9;
  int node_size_in_site = node_size_in_matrix / grid._ndims;
  assert(node_size_in_site == grid.volLocal);

  // read sites that belong to my node to fdata
  uint64_t* fdata = new uint64_t[node_size_in_double];
  uint64_t* cur_position;
  for(int i=0; i<node_size_in_site; ++i)
  {
    cur_position = fdata + i * size_per_site_bytes / sizeof(uint64_t);
    f.seekg(data_begin + grid.localIndexToGlobalIndex(i) * size_per_site_bytes, f.beg);
    f.read((char *)cur_position, size_per_site_bytes);//read only accept char *
  }
  f.close();

  // big endian to little endian
  for(int i=0; i<node_size_in_double; ++i) *(fdata+i) = byte_reverse64(*(fdata+i));
  // uint64_t -> double
  double* pd = (double*)fdata;
  // double -> Complex
  std::vector<Complex> cc(node_size_in_complex);
  for(int i=0; i<node_size_in_double-1; i+=2) cc[i/2] = Complex(*(pd+i), *(pd+i+1));
  // Complex vector -> GaugeField
  GaugeField U(grid);
  for(int i=0; i<node_size_in_complex; ){
    for(int mu=0; mu<4; ++mu){
      std::copy(&cc[i], &cc[i+9], *(U[mu][i/36].m));
      i+=9;
    }
  }

  delete[] fdata;
  return U;
}


#endif
