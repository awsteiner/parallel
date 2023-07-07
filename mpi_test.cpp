#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]) {

  int mpi_rank, mpi_size;
  
  // Init MPI
  MPI_Init(&argc,&argv);

    // Get MPI rank, etc.
  MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);

  // Wait for the previous MPI rank
  int tag=0, buffer=0;
  if (mpi_size>1 && mpi_rank>=1) {
    MPI_Recv(&buffer,1,MPI_INT,mpi_rank-1,
             tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  }

  cout << mpi_rank << "/" << mpi_size << endl;

  // Send a message to the next MPI rank
  if (mpi_size>1 && mpi_rank<mpi_size-1) {
    MPI_Send(&buffer,1,MPI_INT,mpi_rank+1,
             tag,MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return 0;
}
