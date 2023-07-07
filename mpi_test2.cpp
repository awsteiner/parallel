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
  MPI_Status status;
  
  static const int buf_size=1;

  if (mpi_rank==0) {

    // Allocate memory
    vector<double> input_buffer(buf_size);
    vector<double> output_buffers[mpi_size-1];
    for(size_t j=0;j<mpi_size-1;j++) {
      output_buffers.resize(buf_size);
    }
    
    for(size_t i=0;i<mpi_size-1;i++) {
      MPI_Request blank_request;
      vector<MPI_Request> request(mpi_size-1);
      
      // Somehow choose which rank to send the task to
      int proc_index=i+1;

      std::cout << "Isend: " << i << std::endl;
      // Prepare the non-blocking request to send a message
      MPI_Isend(&(input_buffers[0]),buf_size,
                MPI_DOUBLE,proc_index+1,0,
                MPI_COMM_WORLD,&blank_request);
      
      std::cout << "Irecv: " << i << std::endl;
      // Prepare the non-blocking request to receive a message
      MPI_Irecv(&(output_buffers[proc_index][0]),buf_size,
                MPI_DOUBLE,proc_index+1,1,
                MPI_COMM_WORLD,&(request[i]));
      
    }
    
    for(size_t i=0;i<mpi_size-1;i++) {
      // Wait until one of the workers is prepared to send and
      // receive
      MPI_Waitany(mpi_size,&request[i],&proc_index,&status);
      
      std::cout << "Waitany: " << i << std::endl;
      cout << "Found result: " << output_buffers[i][0] << endl;
    }
    
    // Do something with the result
    
  } else {

    static const size_t buf_size;
    vector<double> input_buffer(buf_size), output_buffer(buf_size);

    // Obtain instruction
    cout << "Recv" << endl;
    MPI_Recv(&input_buffer[0],buf_size,MPI_DOUBLE,0,0,
	     MPI_COMM_WORLD,&status);

    // Perform some calculation
    output_buffer[0]=input_buffer[0]*2;

    // Send results
    cout << "Send" << endl;
    MPI_Send(&output_buffer[0],buf_size,MPI_DOUBLE,0,1,
             MPI_COMM_WORLD);
      
  }
      
    
  MPI_Finalize();

  return 0;
}
