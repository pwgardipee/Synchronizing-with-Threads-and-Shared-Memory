#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "queueModule.h"
#include "constants.h"

void *munch1(void *pairStruct){
    char *asterix;
    char *wr;
    while(1){
        
        wr = DequeueString((Queue*)((queuePair*)pairStruct)->dQ);

        while((asterix = index(wr, ' '))  != NULL)
        {
            *asterix = '*';
        }
         
        EnqueueString((Queue*)((queuePair*)pairStruct)->enQ, wr);

        if(strncmp(wr, "STOP\0", 5) == 0){
            pthread_exit(0);
        }
    }
    

}
