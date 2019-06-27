#!/bin/bash

for i in 1 2 3
do
for j in 1 2 4 8 16 32 64
do
 filei='$DW_JOB_STRIPED/scan_0000000308/stem4d_0000000308_000000002'${i}'.dat'
 echo "proc-"$j"-file:"$filei
 srun -n $j ./mpi_read $filei
 wait
done
done
