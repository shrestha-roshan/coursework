#include <pthread.h>
#include <stdio.h>
#include <time.h>

int counter;
static void *thread_func(void *_tn) {
	int i;
	for (i=0; i<100000; i++){
		counter++;
	}
	return NULL;
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


int main() {
	//Start Timer
	struct timespec start, finish;
	long long int time_elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);
	int i, N=5;
	pthread_t t[N];
	for (i = 0;i<N;i++){
		pthread_create(&t[i], NULL,thread_func, NULL);
	}		
	for (i = 0; i<N; i++){
		pthread_join(t[i],NULL);
	}
	printf("%d\n", counter);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lld ns or %0.2lf sec\n", time_elapsed, (time_elapsed / 1.0e9));
	return 0;
}
