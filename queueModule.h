#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h> 

typedef struct Queue {
    char** charArr;
    int size;
    int runningSize;
    int start;
    int end;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    pthread_mutex_t mutex;
    pthread_cond_t q_full; 
    pthread_cond_t q_empty;

} Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char *DequeueString(Queue *q);

void PrintQueueStats(Queue *q);



#endif
