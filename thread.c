/*
	Anno Accademico 2012/2013
	Informatica
	Progetto 2 : Threads
	Mattia Santangelo		151776
	Luca Amadori			151103
*/

#include "declaration.h"


// The getline function is controlled by these two integers 
int bytes_read;
size_t nbytes = 1024;
// Input string given by the user and exit String
char *s;
char quit[] = "quit\n"; 
// Key String
char *r;
// String Se=XOR(R,S)
char *Se;
// String Sd=XOR(R,Se)
char *Sd;
// String length
int lungS = -1; 

// declaration of four files in which the programm will write the log
FILE *t1_log;
FILE *t2_log;
FILE *t3_log;
FILE *t4_log;
// array of char used to define the path of log files into system folders.
char t1[]= "/var/log/threads/t1.log";
char t2[]= "/var/log/threads/t2.log";
char t3[]= "/var/log/threads/t3.log";
char t4[]= "/var/log/threads/t4.log";


// semaphore variables
sem_t sem1,sem2,sem3, sem4;

BOOL control=TRUE;

int main (int argc, char** argv)
{ 
        
    // getOpt option used to show the program usage
    // In this case, only '-h' option is available. When another char is used next to '-' the program will terminate 
    // returning an error.
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "h")) != -1)
    {
        switch (c)
        {
            case 'h':
                usage();
                exit(0);
                break;

            default:
                printf("Invalid Char \n \t Only available option -h \n");
                abort();

        }
    }
    /*
        Creation of four files into the declared folder /var/log/threads. This method will create the folder if it doesn't exist.
        Otherwise it creates four files into it.
        If this operation doesn't proceed successfully the program will terminate returning an error.
    */
    if(try_catch(t1_log,t2_log,t3_log,t4_log, t1,t2,t3,t4)<0)
    	exit(1);

    //thread local variables
    pthread_t th1, th2, th3, th4;
    // sem_init is the initialization of the semaphores, which control the access to data stored in memory.
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,0);  
    sem_init(&sem4,0,1);  

    // Thread creation with the pthread_create function. If one of this 4 threads is not correctly created, the program returns an error and get killed by exit(1);
    if (pthread_create(&th1, NULL, thread1_process, NULL) < 0)
    { 
                fprintf (stderr, "pthread_create error for thread 1 \n");
                printEx(t1_log, t1,-1);
                exit (1);
    }
    // prints if this operation is done.
    printEx(t1_log, t1,1);
    if (pthread_create(&th2, NULL, thread2_process, NULL) < 0)
    { 
                fprintf (stderr, "pthread_create error for thread 2 \n");
                printEx(t2_log, t2,-1);
                exit (1);
    }
    // prints if this operation is done.
    printEx(t2_log, t2,1);
    if (pthread_create(&th3, NULL, thread3_process, NULL) < 0)
    { 
                fprintf (stderr, "pthread_create error for thread 3 \n");
                printEx(t3_log, t3,-1);
                exit (1);
    }
    // prints if this operation is done.
    printEx(t3_log, t3,1);
    if (pthread_create(&th4, NULL, thread4_process, NULL) < 0)
    { 
                fprintf (stderr, "pthread_create error for thread 4 \n");
                printEx(t4_log, t4,-1);
                exit (1);
    }
    // prints if this operation is done.
    printEx(t4_log, t4,1);
   

    // Join of the first thread with the main process. This operation returns an error when the join_function is not correctly executed.
    if (pthread_join(th1, NULL) != 0)
    {
        fprintf(stderr, "pthread_join error for thread 1 \n");
        printEx(t1_log, t1,-2);
        exit(1);        
    } 

    	printEx(t1_log, t1,2);

    // The program prints into the 4 log files that the execution is terminated without errors.
   	printEx(t1_log, t1,0);
    printEx(t2_log, t2,0);
    printEx(t3_log, t3,0);
    printEx(t4_log, t4,0);

return 0;
}





void *thread1_process(void * arg)
{
    int k=1;
    while(k)
    {    
        do
        {       
            // sem4 it's initialized to 1 and with sem_wait it returns 0 and only this thread can
            // write/read data stored in global memory.
            sem_wait(&sem4);
                     
            printf("Inserisci il testo \n");
            // dynamic allocation of memory for a string
            s=(char *)malloc(nbytes + 1);
            // getline() reads a line of text from the command line as input string
            bytes_read = getline(&s, &nbytes, stdin);
  			printOp(t1_log,t1,1);

            /* 
                If-else statement that controls if the given string is equal to "quit" or not.
                In the first case the program will quit, while in the second grants access to the data to
                the second thread with sem_post()
            */
            if (strcmp(s,quit)==0)
            {
                free(s);
                pthread_exit(0);
            }
                else { sem_post(&sem1); }
                        
        } while(control);     
                
    }
    pthread_exit(0);
}


void *thread2_process(void * arg)
{
    int k=1;
    while(k)
    {
        sem_wait(&sem1);
        // dimension of the input string is saved in this variable
        lungS = strlen(s);
        s[lungS]='\0';
        
        // dynamic allocation of a new string that will contain the key
        r=(char *)malloc(sizeof(char)*lungS);
        r[lungS]='\0';

        // The program opens /dev/random in read-only mode
        int retval;
        FILE *fp;
        if ((fp=fopen("/dev/urandom", "r"))==NULL)
        {
            perror("/dev/urandom");
            printEx(t2_log, t2,-3);
            exit(1);
        }
        // a string of lungS dimension is read from /dev/urandom
        if (retval = fread(r, 1, lungS, fp) < 0)
        {
            fprintf(stderr, "Error Reading from /dev/urandom" );
            printEx(t2_log, t2,-4);
            exit(1);
        }

        fclose(fp);
        printOp(t2_log,t2,2);
        // Prints encryption key 'R'
        printf("R: ");
        // cleaning of the string from non-printable char
        print_string_ctrl(r);

        Se = (char *)malloc(sizeof(char)*lungS);
        Se[lungS]='\0';

        
        // XOR of Input string and key saved into Se
        int k;
        for(k=0; k<lungS; k++)
            Se[k] = r[k] ^ s[k];
         
        printf("Se: ");    
        print_string_ctrl(Se);

        sem_post(&sem2);
        }

        pthread_exit(0);
}

void *thread3_process(void *arg)
{
    int k=1;
    while(k)
    {
        sem_wait(&sem2);

        Sd = (char *)malloc(sizeof(char)*lungS);
        Sd[lungS]='\0';
        // XOR of the key and the crypted string
        int j;
        for(j=0; j<lungS; j++)
            Sd[j] = r[j] ^ Se[j];
        printOp(t3_log,t3,3);

        sem_post(&sem3);
    }

    pthread_exit(0);
}

void *thread4_process(void *arg)
{
    int k=1;
   	while(k)
    {
        sem_wait(&sem3);

        // It prints the final string, equal to the given string, as result from the XOR of the key with the crypted string.
        printf("Sd: %s \n", Sd);
        printOp(t4_log,t4,4);

        // deallocation of memory for the four strings.
        free(s);
    	free(r);
    	free(Se);
    	free(Sd);
    	
    	sem_post(&sem4);
    }
    

    pthread_exit(0);

}



void print_string_ctrl(char* elem)
{
    int l = strlen(elem);
    int m;
    char rescue = '#';
    for (m=0; m<l; m++)
    {
        if (isprint(elem[m])!=0 && (iscntrl(elem[m])==0))
        {
            printf("%c", elem[m]);
        } else (printf("%c", rescue));
    }

    printf("\n");
}

// Function used to print into the terminal the usage of this program, called in the getOpt() method.
void usage()
{
    printf("Usage:\n \t ./executable_file -> Normal execution \n \t Run me As Root Please ;) \n");
}