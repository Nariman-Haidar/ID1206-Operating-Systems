#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int pfd[2];               /* Pipe file descriptors */

    if (pipe(pfd) == -1)  
        printf("Pipe was not create");
        
        /* fork make a child process. Then, the child process executes ls /, passing the result through a pipe to the parent process.*/
        
        
 switch (fork()) {
 	case -1:
 		printf("There is wrong with fork");
 	case 0:
 	 	if (close(pfd[0]) == -1)                    
            printf("Read is not used");

        /* Duplicate stdout on write end of pipe; close duplicated descriptor */

        if (pfd[1] != STDOUT_FILENO) {              /* check */
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                printf("Error");
            if (close(pfd[1]) == -1)
                printf("Error");
        }

        execlp("ls", "ls", "/", (char *) NULL);          /* Writes to pipe */

 	break;
 	default:
 		printf("Default");
 	break;
 	  }
 	  
 	  /* The parent executes wc -l to print out the number of lines for the list passed by the child */
 	  
 	if (close(pfd[1]) == -1)                    
            printf("Error with write");

        /* Duplicate stdin on read end of pipe; close duplicated descriptor */

        if (pfd[0] != STDIN_FILENO) {               /*check */
            if (dup2(pfd[0], STDIN_FILENO) == -1)
                printf("Error");
            if (close(pfd[0]) == -1)
                printf("Error");
        }

        execlp("wc", "wc", "-l", (char *) NULL);
        
        /* Parent closes unused file descriptors for pipe, and waits for children */

    	if (close(pfd[0]) == -1)
        	printf("Error!");
    	if (close(pfd[1]) == -1)
        	printf("Error!");
    	if (wait(NULL) == -1)
        	printf("Error!");
    	if (wait(NULL) == -1)
        	printf("Error!");
	
    	exit(EXIT_SUCCESS);
 }

