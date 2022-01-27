//Philosopher with deadlocks

#include<stdio.h>    
#include <unistd.h>
#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5
#define R 6
#define TRUE 1
#define LEFT(i)	i
#define RIGHT(i) (i+1)%N
#define up(sem) sem_post(sem)
#define down(sem) sem_wait(sem)
#define DELAY	sleep(rand() % R);

sem_t chopstick[N]; // chopstic[i] represents for the ith philosopher's availability

void* philosopher(void *pNo) { // pNo points to a philosopher ID
	int i= *((int*)pNo);  // i is the ID number of the philosopher
	
	while (TRUE) {
		// Think
		printf("Philosopher %d is thinking\n", i);
		DELAY;
		// Hungry
		printf("Philosopher %d is hungry\n", i);
		DELAY;
		// Take left chopstick
		down(&chopstick[i]);
		// Take right chopstick
		down(&chopstick[(i+1)%N]);
		DELAY;
		// Eat
		printf("Philosopher %d is eating\n", i);
		DELAY;
		// Drop left chopstick
		up(&chopstick[i]);
		// Drop right chopstick
		up(&chopstick[(i+1)%N]);
	}
}


int main() {
	pthread_t tid[N];
	int philosopherID[N], i;

	// Initiate semaphores
	for (i=0; i<N; i++) sem_init(&chopstick[i],0,1);
	
	// Create philosopher threads
	for (i=0; i<N; i++) {
		philosopherID[i]=i;
		pthread_create(&tid[i],NULL,philosopher,&philosopherID[i]);
	}
	
	// Wait till all philosophers terminate
	for (i=0; i<N; i++) 
		pthread_join(tid[i],NULL);
}

