#ifndef XLATTICE_THREADS_H
#define XLATTICE_THREADS_H

 // #include <omp.h>
 #define PARALLEL_FOR_LOOP        _Pragma("omp parallel for schedule(static)")
  #define parallel_for       PARALLEL_FOR_LOOP for

parallel_for

#endif
