#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "main.h"
#include "queueModule.h"
#include "reader.h"
#include "writer.h"
#include "munch1.h"
#include "munch2.h"
#include "constants.h"

int th0 = 55;
int th1 = 66;
int th2 = 77;
int th3 = 88;

int main() {

	//Declare your queues
	Queue *readerToMunch = CreateStringQueue(BUFF_SIZE); // Reader to Munch 1
	Queue *munchToMunch2 = CreateStringQueue(BUFF_SIZE); // Munch 1 to Munch 2
	Queue *munch2ToWriter = CreateStringQueue(BUFF_SIZE); // Munch 2 to Writer


	//Declare your 4 threads
	// 0 -> reader, 1---> munch1, 2--> munch2, 3 --> writer
	pthread_t thread_id[4];  

	queuePair *readerToMunch1 = (queuePair*)malloc(sizeof(queuePair));
	if(readerToMunch1 == NULL)
	{
		fprintf(stderr, "malloc failed for reader to munch1 queue pair.");
        exit(EXIT_FAILURE);
	}
	readerToMunch1->dQ = readerToMunch;
	readerToMunch1->enQ = munchToMunch2;


	queuePair *munch1ToMunch2 = (queuePair*)malloc(sizeof(queuePair));
	if(readerToMunch1 == NULL)
	{
		fprintf(stderr, "malloc failed for munch1 to munch2 queue pair.");
        exit(EXIT_FAILURE);
	}
	munch1ToMunch2->dQ = munchToMunch2;
	munch1ToMunch2->enQ = munch2ToWriter;

	 pthread_create(&thread_id[0],NULL, reader, (void*)readerToMunch);
	 pthread_create(&thread_id[1],NULL, munch1, (void*)readerToMunch1);
	 pthread_create(&thread_id[2],NULL, munch2, (void*)munch1ToMunch2);
	 pthread_create(&thread_id[3],NULL, writer, (void*)(munch1ToMunch2->enQ));

	// pthread_create(&thread_id[0],NULL, reader, (void*)readerToMunch);
	// pthread_create(&thread_id[1],NULL, munch1, (void*)readerToMunch1);
	// pthread_create(&thread_id[3],NULL, writer, (void*)readerToMunch1->enQ);

	th0 = pthread_join(thread_id[0], NULL);
	th1 = pthread_join(thread_id[1], NULL);
	th2 = pthread_join(thread_id[2], NULL);
	th3 = pthread_join(thread_id[3], NULL);

	fprintf(stdout, "READER TO MUNCH1 QUEUE STATS: \n");
	PrintQueueStats(readerToMunch);

	fprintf(stdout, "MUNCH1 TO MUNCH2 QUEUE STATS: \n");
	PrintQueueStats(munchToMunch2);

	fprintf(stdout, "MUNCH2 TO WRITER QUEUE STATS: \n");
	PrintQueueStats(munch2ToWriter);

	return 0;
}
