#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include "queueModule.h"
#include "constants.h"

void *munch2( void *pairStruct){
    char *wr;
    char* temp;
    int index;
    while(1){
        
        //puts("INDEX RESET!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

        wr = DequeueString( (Queue*) ( (queuePair*)pairStruct)->dQ);
        
        
        index = 0;
        while(wr[index] != '\0')        
        {
            if(islower(wr[index]))
            {
                //printf("INDEX: %d\n", index);
                wr[index] = toupper((unsigned char)wr[index]);
                //wr[index] = wr[index] - 32;
            }
            
            index++;
            
        }
        
        EnqueueString((Queue*)((queuePair*)pairStruct)->enQ, wr);

        if(strncmp(wr, "STOP\0", 5) == 0){
            pthread_exit(0);
        }
    }
}

