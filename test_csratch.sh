#!/bin/bash

for j in 128 256
do
for i in 4 5 1
do
 filei='/global/cscratch1/sd/cjh1//scan_0000000308/stem4d_0000000308_00000001'${i}'0.dat'
 echo "proc-"$j"-file:"$filei
 srun -n $j ./mpi_read $filei
 wait
done
done
