#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAT_SIZE 1024

//pre-assigned the size of the thread to be 1024X1024 accrding to the question
int X = 1024, F = 1024, Y = 1024, rows, cloumns, count = 0;
int MAX_THREADS;
int matrix1[MAT_SIZE][MAT_SIZE]; //First Matrix
int matrix2[MAT_SIZE][MAT_SIZE]; //Second Matrix
int result[MAT_SIZE][MAT_SIZE]; //Multiplied Matrix


//Function For Calculate Each Element in Result Matrix Used By Threads - - -//
void* matrix(void* arg) {

	int counts = count++;
	
	// Each thread computes 1/number of thread of max matrix multiplication 
	for (int a = counts * MAT_SIZE / MAX_THREADS; a < (counts + 1) * MAT_SIZE / MAX_THREADS; a++) {
		for (int b = 0; b < MAT_SIZE; b++) {
			for (int c = 0; c < MAT_SIZE; c++) {
				result[a][b] += matrix1[a][c] * matrix2[c][b];
			}
		}
	}
	sleep(3);
	//End Of Thread
	pthread_exit(0);
}

//to initiallize inputs of Matrix
int inputmultiply() {
	printf("Enter number of threads: \n");
	scanf("%d", &MAX_THREADS);


	//initializing matrix 1
	for (int x = 0; x < X; x++) {

		for (int y = 0; y < F; y++) {

			matrix1[x][y] = rand() % 20; //random numbers are assgned
		}
	}


	//initializing matrix 2
	for (int x = 0; x < F; x++) {

		for (int y = 0; y < Y; y++) {

			matrix2[x][y] = rand() % 20; //random number are assigned
		}
	}


}

//Calculate Time
int time_difference(struct timespec *start, struct timespec *finish,
	long long int *difference)
{
	long long int ds = finish->tv_sec - start->tv_sec;
	long long int dn = finish->tv_nsec - start->tv_nsec;

	if (dn < 0)
	{
		ds--;
		dn += 1000000000;
	}
	*difference = ds * 1000000000 + dn;
	return !(*difference > 0);
}


void main(int argc, char *argv[]) {

	inputmultiply();

	//Defining Threads

	pthread_t thread[MAX_THREADS];

	//Counter For Thread Index
	int thread_number = 0;



	//Start Timer
	struct timespec start, finish;
	long long int time_elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (int x = 0; x < MAX_THREADS; x++) {


		//Initializing Parameters For Passing To Function
		int *p;
		
		//Status For Checking Errors
		int status;

		//Create thread 
		status = pthread_create(&thread[thread_number], NULL, matrix, (void *)&p[thread_number]);

		//Check For Error
		if (status != 0) {
			printf("Error In Threads");

			exit(0);
		}

		thread_number++;
	}



	//Wait For All Threads Done

	for (int z = 0; z < MAX_THREADS; z++)
	{
		pthread_join(thread[z], NULL);
	}

  	//Calculate Total Time Including 3 Soconds Sleep In Each Thread
  	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lld ns or %0.2lf sec\n", time_elapsed, (time_elapsed / 1.0e9));


	//Display total number of thread used and its id
	printf(" Total Thread used -> %d \n\n", thread_number);
	/*for (int z = 0; z < thread_number; z++) {
		printf(" Thread %d ID : %d\n", z + 1, (int)thread[z]);
	}*/
}
