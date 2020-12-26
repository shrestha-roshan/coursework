#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int main()
{

	int Value;
	printf("\nEnter size of Matrix\n");
	scanf("%d", &Value);
	//int SizeOfArray = *Value;
	int a[Value][Value], b[Value][Value], c[Value][Value];
	int i, j, k;
	//printf("\nEnter Firt Matrix\n");
	for (i = 0; i < Value; i++)
	{
		for (j = 0; j < Value; j++)
		{
			a[i][j] = rand() % 50;
		}
	}

	//printf("Enter the Second Matrix\n");
	for (i = 0; i < Value; i++)
	{
		for (j = 0; j < Value; j++)
		{
			b[i][j] = rand() % 50;
		}
	}
	//Start Timer
	struct timespec start, finish;
	long long int time_elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (i = 0; i < Value; i++)
	{
		for (k = 0; k < Value; k++)
		{
			c[i][j] = 0;
			{
				for (j = 0; j < Value; j++)
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lld ns or %0.2lf sec\n", time_elapsed, (time_elapsed / 1.0e9));
	
	
	return 0;
}
