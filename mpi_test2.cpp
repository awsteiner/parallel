#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

  int mpi_rank, mpi_size;
  
  // Init MPI
  MPI_Init(&argc,&argv);

    // Get MPI rank, etc.
  MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
  MPI_Status status;
  
  static const int buf_size=1;

  if (mpi_rank==0) {

    cout << "MPI size: " << mpi_size << endl;
  
    // Allocate memory
    vector<double> input_buffer(buf_size);
    vector<double> output_buffers[mpi_size-1];
    for(size_t j=0;j<mpi_size-1;j++) {
      output_buffers[j].resize(buf_size);
    }

    // Request array
    MPI_Request blank_request;
    vector<MPI_Request> request(mpi_size-1);
    
    for(size_t i=0;i<mpi_size-1;i++) {
      
      // Somehow choose which rank to send the task to
      int proc_index=i+1;

      std::cout << "Non-blocking send task " << i << " to rank "
                << proc_index << "." << std::endl;
      input_buffer[0]=i+1;
      
      // Prepare the non-blocking request to send a message
      MPI_Isend(&(input_buffer[0]),buf_size,
                MPI_DOUBLE,proc_index,0,
                MPI_COMM_WORLD,&blank_request);
      
      std::cout << "Non-blocking receive task " << i << " from rank "
                << proc_index << "." << std::endl;
      // Prepare the non-blocking request to receive a message
      MPI_Irecv(&(output_buffers[i][0]),buf_size,
                MPI_DOUBLE,proc_index,1,
                MPI_COMM_WORLD,&(request[i]));
      
    }
    
    for(size_t i=0;i<mpi_size-1;i++) {

      int req_index;
      
      std::cout << "Waiting for completion of a task." << std::endl;
      
      // Wait until one of the workers is prepared to send and
      // receive
      MPI_Waitany(mpi_size-1,&request[0],&req_index,&status);
      
      cout << "Found result: " << output_buffers[req_index][0]
           << " computed by request with index " << req_index << "." << endl;
    }
    
    // Do something with the result
    
  } else {

    vector<double> input_buffer(buf_size), output_buffer(buf_size);

    // Obtain instruction
    MPI_Recv(&input_buffer[0],buf_size,MPI_DOUBLE,0,0,
	     MPI_COMM_WORLD,&status);
    cout << "Rank " << mpi_rank << " received." << endl;

    // Perform some calculation
    output_buffer[0]=input_buffer[0]*2;
    cout << "Rank " << mpi_rank << " computing: " << input_buffer[0]
         << " " << output_buffer[0] << endl;

    // Send results
    MPI_Send(&output_buffer[0],buf_size,MPI_DOUBLE,0,1,
             MPI_COMM_WORLD);
    cout << "Rank " << mpi_rank << " sending result back." << endl;
      
  }
    
  MPI_Finalize();

  return 0;
}
