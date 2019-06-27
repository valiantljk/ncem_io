//https://kb.iu.edu/d/aqpe
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void ErrorMessage(int error, int rank, char* string)
{
        fprintf(stderr, "Process %d: Error %d in %s\n", rank, error, string);
        MPI_Finalize();
        exit(-1);
}

void main(int argc, char *argv[]){

int myrank,nprocs,start,end,length,error;
char * buffer;
double t1, t2; 
MPI_File fh;
MPI_Offset filesize;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
MPI_Barrier(MPI_COMM_WORLD);
t1 = MPI_Wtime(); 
MPI_File_open(MPI_COMM_WORLD, argv[1], MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
MPI_File_get_size(fh, &filesize);
length = filesize / nprocs;
start = length * myrank;
if (myrank == nprocs-1)
	end = filesize;
else
	end = start + length;
buffer = (char *)malloc((end - start) * sizeof(char));
MPI_File_seek(fh, start, MPI_SEEK_SET);
MPI_File_read(fh, buffer, end-start, MPI_BYTE, &status);
if(error != MPI_SUCCESS) ErrorMessage(error, myrank, "MPI_File_read");
MPI_File_close(&fh);
MPI_Barrier(MPI_COMM_WORLD);
t2 = MPI_Wtime(); 
if(myrank==0)
printf("World size:%d,Total time is:%f\n",nprocs,t2-t1);
MPI_Finalize();
}
