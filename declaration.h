/*
	Anno Accademico 2012/2013
	Informatica
	Progetto 2 : Threads
	Mattia Santangelo		151776
	Luca Amadori			151103
*/

// Libraries included in this program 
#include <stdio.h>		/* for printf */
#include <stdlib.h>		/* for exit */
#include <pthread.h>	/* for pthread_create, pthread_join */
#include <unistd.h>		/* for getopt, access */
#include <string.h>		/* for strcmp */
#include <errno.h>		/* for perror */
#include <fcntl.h>
#include <semaphore.h>	/* for sem_init, sem_post, sem_wait */
#include <malloc.h>		/* for malloc */
#include <sys/stat.h>	/* for read/write permissions */
#include <time.h>		/* for date and time */ 


// definition of the boolean type 
#define TRUE 1
#define FALSE 0
typedef int BOOL;


// list of functions used in this program
// Thread functions
void *thread1_process(void * arg);
void *thread2_process(void * arg);
void *thread3_process(void * arg);
void *thread4_process(void * arg);
// Auxiliary Functions
void print_string_ctrl(char* elem);
void usage();
int try_catch(FILE *f1_log, FILE *f2_log, FILE *f3_log, FILE *f4_log, char *f1, char* f2, char* f3, char* f4);
void printError(int err);
// Log Functions
void printEx(FILE *f, char * elem, int errnum);
void printDate(char *elem, int size);
void printOp(FILE *f, char * elem , int op);




/* LOG CODES */
/*

		Function : printEX()

	0 :		Execution terminated by typing 'quit' string.
	-1 :	Error while creating a thread.
	-2 :	Error while joining first thread with main.
	-3 :	Error while opening device /dev/random.
	-4 :	Error while reading from device /dev/random.

	1 :		The creation of 4 threads has completed.
	2 :		'pthread_join' properly done.



		Function : printOp()
	
	1 :		The first thread successfully reads the string from command line.
	2 :		The second thread encrypts the string.
	3 :		The third thread decrpyts the input string with the key.
	4 :		The fourth thread prints the decryption's result.


*/