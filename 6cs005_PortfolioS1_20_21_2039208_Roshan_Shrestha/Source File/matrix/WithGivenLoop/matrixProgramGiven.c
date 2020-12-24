#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAT_SIZE 10
//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
{
    long long int ds = finish->tv_sec - start->tv_sec;
    long long int dn = finish->tv_nsec - start->tv_nsec;

    if (dn < 0)
    {
        ds--;
        dn += 1000000000;
    }
    *difference = ds *1000000000 + dn;
    return !(*difference > 0);
}

int main()
{
	int i,j,k;           //Parameters For Rows And Columns
	int matrix1[MAT_SIZE][MAT_SIZE]; //First Matrix
	int matrix2[MAT_SIZE][MAT_SIZE]; //Second Matrix
	int result [MAT_SIZE][MAT_SIZE]; //Multiplied Matrix
	
	//Initializing All Defined Matrices By Zero - - - - - - - - - - - - - - -//
	    for(int x=0;x<10;x++){
		for(int y=0;y<10;y++){
		    matrix1[x][y] = 0;
		    matrix2[x][y] = 0;
		}
	    }
	
	//Getting Matrix1 And Matrix2 Info from User - - - - - - - - - - - - - - -//
	    printf(" --- Defining Matrix 1 ---\n\n");
	    
	    // Getting Row And Column(Same As Row In Matrix2) Number For Matrix1
	    printf("Enter number of rows for matrix 1: ");
	    scanf("%d",&i);
	    printf("Enter number of columns for matrix 1: ");
	    scanf("%d",&j);
	    
	    printf("\n --- Initializing Matrix 1 ---\n\n");
	    for(int x=0;x<i;x++){
		for(int y=0;y<j;y++){
		    printf("Enter variable [%d,%d]: ",x+1,y+1);
		    scanf("%d",&matrix1[x][y]);
		}
	    }
	    
	    printf("\n --- Defining Matrix 2 ---\n\n");

	    // Getting Column Number For Matrix2
	    printf("Number of rows for matrix 2 : %d\n",j);
	    printf("Enter number of columns for matrix 2: ");
	    scanf("%d",&k);
	    
	    printf("\n --- Initializing Matrix 2 ---\n\n");
	    for(int x=0;x<j;x++){
		for(int y=0;y<k;y++){
		    printf("Enter variable [%d,%d]: ",x+1,y+1);
		    scanf("%d",&matrix2[x][y]);
		}
	    }
	    
	    
	    //Printing Matrices - - - - - - - - - - - - - - - - - - - - - - - - - - -//
	    
	    printf("\n --- Matrix 1 ---\n\n");
	    for(int x=0;x<i;x++){
		for(int y=0;y<j;y++){
		    printf("%5d",matrix1[x][y]);
		}
		printf("\n\n");
	    }
	    
	    printf(" --- Matrix 2 ---\n\n");
	    for(int x=0;x<j;x++){
		for(int y=0;y<k;y++){
		    printf("%5d",matrix2[x][y]);
		}
		printf("\n\n");
	    }
	    
	struct timespec start, finish;
    	long long int time_elapsed;
    	clock_gettime(CLOCK_MONOTONIC, &start);
    	
	//resulting matrices
	for(int x=0; x<i; x++) {
	 for(int y=0; y<j; y++) {
	  result[x][y]=0;
	  for(int k=0; k<i; k++) {
		result[x][y]=result[x][y] +matrix1[x][k] * matrix2[k][y];
	   }
	  }
	}
	printf("\nThe results is…\n");
	for(int x=0; x<i; x++) {
	 for(int y=0; y<j; y++) {
	   printf("%d  ", result[x][y]); 
	  }
	printf("\n");
	}
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
	(time_elapsed / 1.0e9));

	return 0;
}

