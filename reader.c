#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "queueModule.h"
#include "constants.h"
#include <string.h>

void *reader( void *readerQueue){

	char *ch = (char*)calloc(1,sizeof(char));
	char *buffer = (char*)calloc(BUFF_SIZE,sizeof(char));
	char *temp;
	int index, i;
	index = 0;

	// Read the stdin
	while((*ch = fgetc(stdin)) != EOF){

		/*
		if(index > BUFF_SIZE) {
			fprintf(stderr,"LINE TOOOOO BIGG");
			exit(EXIT_FAILURE);
		}
		else if(*ch == '\n' && index <= BUFF_SIZE)
		{
			temp = (char*)calloc(BUFF_SIZE,sizeof(char));
	
			for(i = 0; i < BUFF_SIZE; i++)
			{
				temp[i] = buffer[i];
			}
			temp[i] = '\0';
						+
			EnqueueString((Queue*)readerQueue, temp);
			index = 0;
		}
		else if(index > BUFF_SIZE)
		{
			index
		}
		else{
			buffer[index] = *ch;
            index++;	
		}




		if(*ch == '\n' && index >= BUFF_SIZE)
		{
			memset((void*)buffer, 0, BUFF_SIZE );
			index = 0;
		}
		else if(*ch == '\n' && index < BUFF_SIZE)
		{
			temp = (char*)calloc(BUFF_SIZE,sizeof(char));
			if (temp == NULL) {
				fprintf(stderr,"temp malloc in reader.c failed");
			}
	
			for(i = 0; i < BUFF_SIZE; i++)
			{
				temp[i] = buffer[i];
			}
			temp[i] = '\0';
			
			EnqueueString((Queue*)readerQueue, temp);
			memset((void*)buffer, 0, BUFF_SIZE);
			index = 0;
		}
		else if(index < BUFF_SIZE)
		{
            buffer[index] = *ch;
            index++;
		}
		else
		{
			index++;
		}
		
*/



		if(*ch == '\n')
		{
			if(index < buffsize - 1) //figure it out later
			{
				//enqueue
			}
			else
			{
				//ignore i
			}
		}
		else
		{
			if(index <= buffsize)
			{
				buffer[index] = *ch;
			}
			index++;
		}

	}

	char *endString = (char*)malloc(5*sizeof(char));
	if (endString == NULL) {
		fprintf(stderr,"malloc in reader.c failed");
	}
	strncpy(endString, "STOP\0", 5);

	EnqueueString((Queue*)readerQueue, endString);
	fprintf(stdout,"in reader before free");
	//free(ch);
	pthread_exit(0);
}

