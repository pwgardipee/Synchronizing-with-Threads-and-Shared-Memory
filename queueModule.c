#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "queueModule.h"


Queue *CreateStringQueue(int size)
{
    Queue *strQueue = (Queue*)calloc(1,sizeof(Queue));
    if(strQueue == NULL){
        puts("Queue calloc failed");
        exit(EXIT_FAILURE);
    }

    strQueue->charArr = (char**)calloc(1,size * sizeof(char *));
    if(strQueue->charArr == NULL){
        puts("Queue char array calloc failed");
        exit(EXIT_FAILURE);
    }

    strQueue->start = 0;
    strQueue->end = 0;
    strQueue->runningSize = 0;
    strQueue->size = size;
    pthread_mutex_init(&strQueue->mutex, NULL);
    pthread_cond_init(&strQueue->q_full, NULL);
    pthread_cond_init(&strQueue->q_empty, NULL);
    return strQueue;

}


void EnqueueString(Queue *q, char *string)
{
    pthread_mutex_lock(&q->mutex);

    while((q->start == q->end) && (q->runningSize == q->size))
    {
        pthread_cond_wait(&q->q_full, &q->mutex);
        q->enqueueBlockCount++;
    }
    
    q->charArr[q->end] = string;
    q->end = (q->end + 1)%(q->size);
    q->runningSize++; 
    q->enqueueCount++;
    pthread_cond_signal(&q->q_empty);   // signal when queue is not empty anymore
    pthread_mutex_unlock(&q->mutex);
    return;
}

char *DequeueString(Queue *q)
{
    pthread_mutex_lock(&q->mutex);
    while(q->runningSize == 0)
    {
        q->dequeueBlockCount++;
        pthread_cond_wait(&q->q_empty, &q->mutex);
    }
    
    int tempIndex = q->start;
    q->runningSize--;
    q->start = (q->start + 1)%(q->size);
    q->dequeueCount++;
    pthread_cond_signal(&q->q_full);  // signal when queue is not full anymore
    pthread_mutex_unlock(&q->mutex);
    return q->charArr[tempIndex];

}

void PrintQueueStats(Queue *q)
{
    fprintf(stdout, "EnqueueCount: %d \nDequeueCount: %d \nEnqueueBlockCount: %d \nDequeueBlockCount: %d\n\n", q->enqueueCount, q->dequeueCount, q->enqueueBlockCount, q->dequeueBlockCount);

}
