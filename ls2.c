#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"
#include "stack.h"


// TODO: function definitions here for ls2

void mode1(char* path){
    DIR* dir;
	struct dirent* dirent;
	struct stat fileInfo;

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
		dirent = readdir(dir);
		while(dirent != NULL){
		    lstat(path, &fileInfo);
		    if(strcmp(dirent->d_name,".") != 0 && strcmp(dirent->d_name,"..") != 0)
		    {
				//printf("%s ...\n", dirent->d_name);
				if(S_ISDIR(fileInfo.st_mode))
			    {
					printf("%s/ (directory)\n%s", dirent->d_name,INDENT);
					
					//printf("Before: %s\n", abPath);
					strcat(path,"/");
					strcat(path,dirent->d_name);
					//printf("chdir: %s\n", path);
					chdir(dirent->d_name);
                    mode1(path);

			    }
				else if(S_ISREG(fileInfo.st_mode))
			    {
				    printf("%s (%ld bytes)\n", dirent->d_name, fileInfo.st_size);
			    }

		    }
			dirent = readdir(dir);
	    }
				
	}
    closedir(dir);
}
