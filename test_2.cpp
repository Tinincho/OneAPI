#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <omp.h>

using namespace std;

//Martín Salvador Sosa.
int main ()
{
	ofstream my_file("test_2_results.txt");

    double start_time;
    double end_time;
	
	int arrays_length = 2000;
	int array_1[arrays_length];
	int array_2[arrays_length];
	int array_3[arrays_length];
	
	#pragma omp parallel shared(my_file, start_time, end_time, array_1, array_2, array_3)
	{
        start_time = omp_get_wtime();
		
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				for (int iterator = 0; iterator < arrays_length / 2; iterator++)
				{
					array_1[iterator] = iterator;
					array_2[iterator] = iterator;
					array_3[iterator] = array_1[iterator] + array_2[iterator];
				}
			}
			
			#pragma omp section
			{
				for (int iterator = arrays_length / 2; iterator < arrays_length; iterator++)
				{
					array_1[iterator] = iterator;
					array_2[iterator] = iterator;
					array_3[iterator] = array_1[iterator] + array_2[iterator];
				}
			}
		}
		
		#pragma omp barrier
		{
			#pragma omp master
			{
				for (int iterator = 0; iterator < arrays_length; iterator++)
				{
					my_file << array_1[iterator] << " + " << array_2[iterator] << " = " << array_3[iterator] << "\n";
				}
				
				my_file.close();
			}
		}
	}
	
	end_time = omp_get_wtime();
	
	printf("Work took %f seconds.\n", end_time - start_time);
	
    return 0;
}