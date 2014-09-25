/*
	Anno Accademico 2012/2013
	Informatica
	Progetto 2 : Threads
	Mattia Santangelo		151776
	Luca Amadori			151103
*/

#include "declaration.h"



int try_catch(FILE *f1_log, FILE *f2_log, FILE *f3_log, FILE *f4_log, char *f1, char* f2, char* f3, char* f4)
{
	// This variabile is the returned parameter of this function. It controls if files are correctly created.
	int file_control=0;

	// The string passed to the mkdir function 
	char path[] = "/var/log/threads";

	/*
		If access() returns '-1', it means that the folder doesn't exist and the program will create it.
		Otherwise it proceeds with the creation of four files.
	*/	
	if ((access(path,F_OK))== -1)
	{
		if((mkdir(path, S_IRWXO))<0)
				{
					printError(2);
					exit(1);
				}

				if((f1_log=fopen(f1, "wt"))==NULL)
				{
					perror(f1);
					printError(1);
					file_control--;
				}
				if((f2_log=fopen(f2, "wt"))==NULL)
				{
					perror(f2);
					printError(1);
					file_control--;
				}
				if((f3_log=fopen(f3, "wt"))==NULL)
				{
					perror(f3);
					printError(1);
					file_control--;
				}
				if((f4_log=fopen(f4, "wt"))==NULL)
				{
					perror(f4);
					printError(1);
					file_control--;
				}
		
	} else 	{
				if((f1_log=fopen(f1, "wt"))==NULL)
				{
					perror(f1);
					printError(1);
					file_control--;
				}
				if((f2_log=fopen(f2, "wt"))==NULL)
				{
					perror(f2);
					printError(1);
					file_control--;
				}
				if((f3_log=fopen(f3, "wt"))==NULL)
				{
					perror(f3);
					printError(1);
					file_control--;
				}
				if((f4_log=fopen(f4, "wt"))==NULL)
				{
					perror(f4);
					printError(1);
					file_control--;
				}
			}

	fclose(f1_log);
	fclose(f2_log);
	fclose(f3_log);
	fclose(f4_log);
	

return file_control;
}

// Function used to print errors
void printError(int err)
{
	switch(err)
	{
		case 1:
			printf("Unable to write into folder /var/log/threads. Permission Denied. \n");
		break;
		case 2:
			printf("Unable to create folder /var/log/threads. Permission Denied. \n");
		break;
	}
}