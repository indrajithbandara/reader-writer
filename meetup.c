/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "meetup.h"
#include "resource.h"

/*
 * Declarations for barrier shared variables -- plus concurrency-control
 * variables -- must START here.
 */

static resource_t data;

int hipCount = 0;
int meetFirst = 0;
int numOfHipstersArrived = -1;
pthread_mutex_t threadHipsterMutex[MAX_THREADS];
pthread_mutex_t lock;
pthread_t threadHipster[MAX_THREADS];

void *Barrier(void *arg)
{
    int threadNumber = *(int *)arg;
    printf("Thread number is %d and hipsCount is%d\n", threadNumber, hipCount);
    pthread_mutex_unlock(&threadHipsterMutex[threadNumber]);
    while (threadNumber < hipCount)
    {
    }
}

void initialize_meetup(int n, int mf)
{
    char label[100];
    int i;

    if (n < 1)
    {
        fprintf(stderr, "Who are you kidding?\n");
        fprintf(stderr, "A meetup size of %d??\n", n);
        exit(1);
    }

    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
    hipCount = n;
    meetFirst = mf;

    for (i = 0; i < hipCount; i++)
    {

        int status = pthread_mutex_init(&threadHipsterMutex[i], NULL);
        if (status != 0)
        {
            fprintf(stderr, "Error creating Hipster Mutex\n");
            exit(1);
        }
    }
    pthread_mutex_init(&lock, NULL);
    //Locking all the threads
    for (i = 0; i < hipCount; i++)
    {
        pthread_mutex_lock(&threadHipsterMutex[i]);
    }
}

void join_meetup(char *value, int len)
{
    // printf("NOTHING IMPLEMENTED YET FOR join_meetup\n");
    if (pthread_create(&threadHipster[numOfHipstersArrived], 0, Barrier, (void *)&numOfHipstersArrived) < 0)
    {
        fprintf(stderr, "Could not create %d thread\n", numOfHipstersArrived);
        return;
    }
    // printf("In main thread is %d\n", numOfHipstersArrived);
    numOfHipstersArrived++;
}
