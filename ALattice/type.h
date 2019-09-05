using Complex = std::complex<double>;

template<typename T>
struct isNumber{
  static const bool value = std::is_arithmetic<T>::value; // integral or float-point number
};

template<typename T>
struct isNumber<std::complex<T>>{
  static const bool value = true;
};


template<typename T, int N> class Matrix; //declaration

template<typename T>
struct isMatrix{
  static const bool value = false;
};

template<typename T>
struct isMatrix<Matrix<T, 2>>{
  static const bool value = true;
};

template<typename T>
struct isMatrix<Matrix<T, 3>>{
  static const bool value = true;
};


template<typename T>
struct MPI_Type{
  static constexpr MPI_Datatype value = MPI_DATATYPE_NULL;
};

template<>
struct MPI_Type<double>{
  static constexpr MPI_Datatype value = MPI_DOUBLE;
};

template<>
struct MPI_Type<float>{
  static constexpr MPI_Datatype value = MPI_FLOAT;
};

template<>
struct MPI_Type<int>{
  static constexpr MPI_Datatype value = MPI_INT;
};

template<>
struct MPI_Type<std::complex<float>>{
  static constexpr MPI_Datatype value = MPI_C_FLOAT_COMPLEX;
};

template<>
struct MPI_Type<std::complex<double>>{
  static constexpr MPI_Datatype value = MPI_C_DOUBLE_COMPLEX;
};
