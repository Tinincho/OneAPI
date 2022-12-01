#include <stdio.h>
#include "mpi.h"
#include <omp.h>

//Martín Salvador Sosa.
int main()
{
    
    int world_size, world_rank, name_length;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Get_processor_name(processor_name, &name_length);
    
    int thread_count = 0, thread_number = 1;
    
    #pragma omp parallel default(shared) private(thread_count, thread_number)
    {
        thread_count = omp_get_num_threads();
        thread_number = omp_get_thread_num();
        
        printf("Hello from thread %d out of %d from process %d out of %d on %s\n",
           thread_number, thread_count, world_rank, world_size, processor_name);
    }
    
    MPI_Finalize();
}