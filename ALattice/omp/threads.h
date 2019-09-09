#pragma once

#include <omp.h>
#define parallel_for      _Pragma("omp parallel for for ") // _Pragma("argument") is equivalent to #pragma argument

