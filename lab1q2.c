#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <sys/wait.h>
#include <mqueue.h>
#include <string.h>
#include <sys/stat.h>

#define MQ_NAME "/mq_msg_name"
#define SIZE 1024
typedef struct
		{
    		char msg[100];
		} message;
typedef struct
		{
    		char msg[100];
		} messageR;
void error_handler(char* msg)
{
    fprintf(stderr, msg, strlen(msg));
    exit(1);
}

int
main(int argc, char *argv[])
{
    
       struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(message)};
        
    char buff[SIZE]; 
    FILE *f;
    mqd_t queue;
        
 switch (fork()) {
 	case -1:
 		printf("There is wrong with fork");
 	case 0:
 		
    f = fopen("text.txt", "r");
    fgets(buff, SIZE, f);
    message msg;
    strcpy(msg.msg, buff);
    fclose(f);
    queue = mq_open(MQ_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes);
    // To test the error remove , &attributes
    if(queue == -1)
    	error_handler("message queue can not be opened\n");	

    if(mq_send(queue, (char *)&msg, sizeof(msg), 1) == -1)
     	error_handler("The message ca not be sent\n");
     else
	mq_send(queue, (char *)&msg, sizeof(msg), 1);
	
 
    mq_close(queue);
    
    int unlinkk = mq_unlink(MQ_NAME);
    
 	break;
 	default:
 		
 	break;
 	  }
 	  
 	  struct mq_attr attributesR = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(messageR)};
    
    	int count = 0;
    	mqd_t queueR;
 	  
 	switch (fork()) {
 	case -1:
 		printf("There is wrong with fork");
 	case 0:
 		queue = mq_open(MQ_NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attributesR);
    	if(queue == -1)
			error_handler("can not open queue\n");
	
    	messageR msg;
	
    	mq_receive(queueR, (char *)&msg, sizeof(msg), NULL);
    	
    	for(int i = 0; i < strlen(msg.msg); i++) {  
        	if(msg.msg[i] == ' ')  
            	count++;
            
    	}
    	if (count != 0)
    		printf("Total number of words: %d\n", count+1);  
   		
    	getchar();
    	mq_close(queueR);
    	exit(EXIT_SUCCESS);
	
 	break;
 	default:
 	
 	break;
 	  }
 	    
        	
 }