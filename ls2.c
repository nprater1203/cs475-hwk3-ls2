#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "ls2.h"
#include "stack.h"
/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 2/6/23
*/

/**
 * Prints all the files and directories in the given path
 *
 * @param	char*	Pointer to the path
 * @param   int*	Keeps the count for indents
 */

void mode1(char* path, int* indentCount){
    DIR* dir;
	struct dirent* dirent;
	struct stat fileInfo;
	char* temp = malloc(4096);	

    dir = opendir(path);

	if(dir != NULL)
	{
		
		//Get the name of the next file/directory
		dirent = readdir(dir);
		while(dirent != NULL){
		    if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0)
		    {
				for(int i = 0; i < *indentCount; i++)
				{
					printf("%s",INDENT);
				}
				strcpy(temp,path);
				strcat(temp,"/");
				strcat(temp,dirent->d_name);

				//Get file information
				lstat(temp, &fileInfo);
				//Directories
				if(S_ISDIR(fileInfo.st_mode))
			    {
					(*indentCount)++;
					printf("%s/ (directory)\n", dirent->d_name);
                    mode1(temp,indentCount);					
			    }
				//Regular files
				else if(S_ISREG(fileInfo.st_mode))
			    {
				    printf("%s (%ld bytes)\n", dirent->d_name, fileInfo.st_size);
			    }

		    }
			dirent = readdir(dir);
	    }
		
				
	}
	free(temp);
    closedir(dir);
	(*indentCount)--;

}

/**
 * Prints all directories and its path to the target file
 *
 * @param	char*	    Pointer to the path
 * @param   int*	    Keeps the count for indents
 * @param	char*	    Target file
 * @param   stack_t*	The stakc
 */

void mode2(char* path, int* indentCount, char* targetFile, stack_t* stack){
	    DIR* dir;
	struct dirent* dirent;
	struct stat fileInfo;
	char* temp = malloc(4096);
	bool fileFound = false;	

    dir = opendir(path);

	if(dir != NULL)
	{
		
		//Get the name of the next file/directory
		dirent = readdir(dir);
		while(dirent != NULL){
		    if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0)
		    {
				// for(int i = 0; i < *indentCount; i++)
				// {
				// 	printf("%s",INDENT);
				// }
				strcpy(temp,path);
				strcat(temp,"/");
				strcat(temp,dirent->d_name);

				//Get file information
				lstat(temp, &fileInfo);
				//Directories
				if(S_ISDIR(fileInfo.st_mode))
			    {
					
					(*indentCount)++;
                    mode2(temp,indentCount,targetFile,stack);	
					if(fileFound){
						push(stack,dirent->d_name);	
					}			
			    }
				//Regular files
				else if(S_ISREG(fileInfo.st_mode))
			    {
					if(strcmp(dirent->d_name,targetFile) == 0)
					{
						fileFound = true;
					}
					
			    }

		    }
			dirent = readdir(dir);
	    }
		
				
	}
	free(temp);
    closedir(dir);
	(*indentCount)--;

}
