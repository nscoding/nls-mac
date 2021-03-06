//
//  pathHelper.c
//  nls
//
//  Created by Patrick Chamelo on 7/7/13.
//  Copyright (c) 2013 Patrick Chamelo. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.



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

