//
//  pathHelper.c
//  nls
//
//  Created by Patrick Chamelo on 7/7/13.
//  Copyright (c) 2013 Patrick Chamelo. All rights reserved.
//


#include "includes.c"


// ------------------------------------------------------------------------------------------
#pragma mark - Path helpers
// ------------------------------------------------------------------------------------------

char *getFileNameForPath(char *path)
{
	return basename(path);
	//return strrchr(path, '/');
}

bool pathEndsWithSlash(char *path)
{
	size_t size = strlen(path);
	bool hasSlash = (path[size - 1] == '/');
    
	return hasSlash;
}


char *getWorkingDirectoryPath()
{
	char *path;
	// nls [ -hinsto ]
	long size;
	char *buffer = NULL;
	size = pathconf(".", _PC_PATH_MAX);
	path = getcwd(buffer, (size_t)size);
    
	if (path == NULL)
	{
		printf("Path could not be determined\n");
		exit(0);
	}
    
	return path;
}

