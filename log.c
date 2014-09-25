/*
	Anno Accademico 2012/2013
	Informatica
	Progetto 2 : Threads
	Mattia Santangelo		151776
	Luca Amadori			151103
*/

#include "declaration.h"

void printEx(FILE *f, char * elem , int errcode)
{
	// String for the date
	char buff[30];	

	/* 
		The program opens the files passed to f with path elem.
		If this operation is done no errors are reported, else the program will quit immediatly.
	*/
	if((f=fopen(elem, "at"))==NULL)
	{
		perror(elem);
		exit(1);
	}
	// function that prints the date and time into the selected file.
	printDate(buff, sizeof(buff));
	fprintf (f, "%s ", buff);

	/*
		This switch loop looks up at the variable errcode passed to the function.
	*/
	switch(errcode)
	{
		// Correct execution of the program
		case 0:
			fprintf(f,"EXECUTION TERMINATED BY TYPING 'quit' STRING \n");
			fclose(f);
		break;
		// Error while creating a thread
		case -1:
			fprintf(f, "Error while creating the thread! \n");
			fclose(f);
		break;
		// Error while joining a thread with the main process
		case -2:
			fprintf(f, "Error while joining the first thread with the main process \n");
			fclose(f);
		break;
		// Error while opening /dev/random
		case -3:
			fprintf(f, "Error while opening device /dev/random");
			fclose(f);
		break;
		// Error while reading from /dev/random
		case -4:
			fprintf(f, "Error while reading device /dev/random\n" );
			fclose(f);
		break;
		// Creation of 4 threads has completed.
		case 1:
			fprintf(f, "Thread created successfully! \n" );
			fclose(f);
		break;
		// Join operation properly done.
		case 2:
			fprintf(f, "Join of the first thread is done. It's job is completed ! \n" );
			fclose(f);
		break;
	}	
}

/*
	Function that prints the correct operation done by the threads into the relative log file.
	The switch loop looks up at the variabile op passed to the function that specify the number/code of
	the operation done by a thread.
*/
void printOp(FILE *f, char * elem , int op)
{
	char buff[30];	

	if((f=fopen(elem, "at"))==NULL)
	{
		perror(elem);
		exit(1);
	}
	printDate(buff, sizeof(buff));
	fprintf (f, "%s ", buff);

	switch(op)
	{
		case 1:
			fprintf(f, "String Saved \n");
			fclose(f);
		break;
		case 2:
			fprintf(f, "Encrypt Completed \n");
			fclose(f);
		break;
		case 3:
			fprintf(f, "Decrypt Completed \n");
			fclose(f);
		break;
		case 4:
			fprintf(f, "String Printed \n");
			fclose(f);
		break;
	}
}



// Function that prints out the current date and time.
void printDate(char *elem, int size)
{
    struct tm *sTm;
    time_t now = time (0);
    sTm = gmtime (&now);
    strftime (elem, size, "%Y-%m-%d %H:%M:%S", sTm);
}