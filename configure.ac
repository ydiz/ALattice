# ==============================
# Names, Sanity Check, and other basic things 

AC_PREREQ([2.69])
AC_INIT([ALattice], [0.4])
AC_CONFIG_SRCDIR([ALattice/alattice.h])

AM_INIT_AUTOMAKE([foreign]) # must add this line to use automake. why?

# =============================

AC_PROG_CXX
AC_PROG_RANLIB # a must for building libraries

# /home/ydzhao/cuth/install/openmpi-3.1.0
AC_ARG_ENABLE([mpi],
    [AC_HELP_STRING([--enable-mpi=prefix], [enable MPI])],
    [echo "Compile with MPI $enable_mpi"], [echo "Compile without MPI"; exit])

if test ! -z "$enable_mpi"; then
  AC_DEFINE([WITH_MPI],[1],[with MIP])
  AM_CXXFLAGS="-I$enable_mpi/include $AM_CXXFLAGS"
  AM_LDFLAGS="-L$enable_mpi/lib $AM_LDFLAGS"
  LIBS="-lmpi_cxx -lmpi $LIBS"
fi

############### Grid

AC_ARG_ENABLE([grid],
    [AC_HELP_STRING([--enable-grid=prefix], [enable LAPACK])],
    [echo "Compile with Grid" $enable_grid], [echo "Compile without Grid"])

if test ! -z "$enable_grid"; then
  AC_DEFINE([WITH_GRID],[1],[with grid])
  AM_CXXFLAGS="-I$enable_grid/include $AM_CXXFLAGS"
  AM_LDFLAGS="-L$enable_grid/lib $AM_LDFLAGS"
  # AC_SEARCH_LIBS([Grid_init], [Grid], [echo "Grid was found"], [echo AC_MSG_ERROR(["Grid was not found"])]) # ? error
fi

############### OpenMP
AC_LANG([C++])
AC_OPENMP # check openmp and set OPENMP_CXXFLAGS
if test "${ac_cv_prog_cxx_openmp}X" != "noX"; then
  AM_CXXFLAGS="$OPENMP_CXXFLAGS $AM_CXXFLAGS" # need to have AC_LANG([C++]); otherwise OPENMP_CXXFLAGS will not be set by AC_OPENMP
  AM_LDFLAGS="$OPENMP_CXXFLAGS $AM_LDFLAGS"
else
  AC_MSG_ERROR(["Checking OpenMP Failed"])
fi

# =============================


AM_CXXFLAGS="-I${srcdir} $AM_CXXFLAGS"
AM_LDFLAGS="-L$PWD/ALattice $AM_LDFLAGS"

# echo "AM_:CXXFLAGS $AM_CXXFLAGS"
# echo "AM_LDFLAGS $AM_LDFLAGS"


# ==============================
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# =============================
# Write the output   

AC_CONFIG_FILES([Makefile ALattice/Makefile tests/Makefile])
AC_CONFIG_HEADERS([include/Config.h])
AC_OUTPUT


# ==============================

echo "CXXFLAGS:
`echo ${AM_CXXFLAGS} ${CXXFLAGS} | tr ' ' '\n' | sed 's/^-/    -/g'`
LDFLAGS:
`echo ${AM_LDFLAGS} ${LDFLAGS} | tr ' ' '\n' | sed 's/^-/    -/g'`
LIBS:
`echo ${LIBS} | tr ' ' '\n' | sed 's/^-/    -/g'`"
