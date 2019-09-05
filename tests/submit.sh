#!/bin/bash
#SBATCH -N 4
#SBATCH -J GFFA_cuth
###SBATCH --mail-user=yz3210@columbia.edu
#SBATCH --mail-type=ALL
#SBATCH -t 72:00:00
#SBATCH -o output-%j.txt

#OpenMP settings:
export OMP_NUM_THREADS=32
export OMP_PLACES=threads
export OMP_PROC_BIND=spread

#run the application:
srun -n 4 -c 32 --cpu_bind=cores ./test
# srun -n 4 -c 32 --cpu_bind=cores ./test_hmc
# srun -n 4 -c 32 --cpu_bind=cores ./test_cshift

