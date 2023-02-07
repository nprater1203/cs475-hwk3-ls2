/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 2/6/23
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	
	if(argc == 2 || argc == 3){
		

		if(argc == 2){
			//printf("%s",argv[1]);

			// if(strcmp(argv[1],".") == 0){
			char cwd[256];
			getcwd(cwd,sizeof(cwd));
			//printf("CWD: %s\n",cwd);
			char recurseDir[4096];
			strcpy(recurseDir,cwd);
			if(strcmp(argv[1],".") != 0){
				strcat(recurseDir,"/");
				strcat(recurseDir,argv[1]);
				//printf("%s\n",recurseDir);
			}
			mode1(recurseDir);
		}
		else
		{
			printf("Mode 2\n");
		}
		// stack_t *s = initstack();

		// push(s, "Hello1");
		// push(s, "Hello2");
		// push(s, "Hello3");

		// // print stack
		// printstack(s);

		// // free up stack
		// freestack(s);


	}
	else
	{
		printf("Usage: ./ls2 <path> [optional-file]\n");
	}
	return 0;
}
