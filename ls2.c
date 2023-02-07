#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
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
 * @param	*A	Pointer to the path
 */

void mode1(char* path){
    DIR* dir;
	struct dirent* dirent;
	struct stat fileInfo;
	char* temp = malloc(4096);	

	//printf("Recurse with directiory: %s\n", path);
	// if(strcmp(path,"." != 0))
	// {
	// 	strcat(abPath,path);
	// }
	
	//printf("DIR PATH: %s\n", path);
	//chdir(path);
    dir = opendir(path);

	if(dir != NULL)
	{
		//Get the name of the next file/directory
		dirent = readdir(dir);
		while(dirent != NULL){

		    if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0)
		    {
				strcpy(temp,path);
				strcat(temp,"/");
				strcat(temp,dirent->d_name);
				//printf("Temp = %s ...\n", temp);

				//Get file information
				lstat(temp, &fileInfo);
				//Directories
				if(S_ISDIR(fileInfo.st_mode))
			    {
					printf("%s/ (directory)\n%s", dirent->d_name,INDENT);
					
					//temp = path;
					//printf("Before: %s\n", abPath);
					
					//printf("chdir: %s\n", path);
					//chdir(dirent->d_name);
                    mode1(temp);
					//chdir("..");
					
			    }
				//Regular files
				else //if(S_ISREG(fileInfo.st_mode))
			    {
				    printf("%s (%ld bytes)\n", dirent->d_name, fileInfo.st_size);
			    }

		    }
			dirent = readdir(dir);
	    }
				
	}
	//free(temp);
    closedir(dir);
}
