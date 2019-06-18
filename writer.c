#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "queueModule.h"
#include "constants.h"


void *writer( void *writerQueue){
	char *wr;
	while(1){
		wr = DequeueString((Queue*)writerQueue);

		if(!(strncmp(wr, "STOP\0", 5) == 0)){
			fprintf(stdout,"%s\n",wr);
			//free(wr);
		}
		else{
			//fprintf(stdout,"in writer before free");
			//free(wr);
			pthread_exit(0);
		}
	}
}

