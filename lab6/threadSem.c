/*
* Parth Patel
* 500893723
* CPS590 Lab06
*
* 2) The variable myglobal is usually not 40 because when the thread is run,
*   j is set to myglobal and then incremented by 1. In the main myglobal is then
*   set to myglobal + 1. Then myglobal is set to j, since the thread does not
*   increment myglobal before myglobal is set to myglobal = myglobal + 1, the operation
*   myglobal = myglobal + 1 is essentially overwritten.
*
* 3) The variable myglobal will be 40 in the special case that the main function adds 1
*   to myglobal, then the thead function does j = j + 1 and myglobal = j before the main
*   does myglobal = myglobal + 1. This would have to occur every iteration for myglobal
*   to be 40.
*/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
/*
Purpose: Use 2 threads to increment myglobal exactly 40 times in total.
Compile: using -pthread option
 */

int myglobal = 0;
sem_t sem;
 void *thread_function(void *arg)
 {
	sem_wait(&sem);
	int i,j;

	for (i = 0; i < 20; i++)
	{
		j = myglobal;
		j = j + 1;
		printf(".");
		fflush(stdout);
		sleep(0.2);
		myglobal = j;
	}
	sem_post(&sem);
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	int i;
	sem_init(&sem, 0, 1);
	if (pthread_create(&mythread, NULL, thread_function, NULL)) {
		printf("error creating thread.");
		abort();
	}

	sem_wait(&sem);
	for (i = 0; i < 20; i++)
	{
		myglobal = myglobal + 1;
		printf("o");
		fflush(stdout);
		sleep(0.21);
	}
	sem_post(&sem);
	if (pthread_join(mythread, NULL)) {
		printf("error joining thread.");
		abort();
	}

	printf("\nmyglobal equals %d\n", myglobal);
	sem_destroy(&sem);
	exit(0);
}


