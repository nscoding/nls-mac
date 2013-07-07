//
//  fileHelper.c
//  nls
//
//  Created by Patrick Chamelo on 7/6/13.
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


#include "pathHelper.c"


// ------------------------------------------------------------------------------------------
#pragma mark - Size methods
// ------------------------------------------------------------------------------------------

// Method to get the size of the file.
int getFileSizeForPath(char *filename)
{
	//This structure will be used to query file status
	struct stat file;
    
	// validate if it can retrieve the size or not
	if (stat(filename, &file) == 0)
	{
		return (int)(file.st_size / 1024);
	}
    
	printf("Cannot retrive size for %s \n", getFileNameForPath(filename));
	return 0;
}


// Method to get the size of a directory
int getDirectorySizeForPath(char *pathname, int value)
{
	char newpath[1024];
	
	DIR *directory;
	struct dirent *entry;
	unsigned char done = 0;
	struct stat file;
	
	directory = opendir(pathname);
    
	while (done != 1)
	{
		entry = readdir(directory);
		if (entry == 0)
		{
			done = 1;
		}
		else
		{
			if ((strncmp(entry->d_name, ".", 1) != 0))
			{
				sprintf(newpath,"%s/%s", pathname,entry->d_name);
				stat(newpath,&file);
				
				if (S_ISREG(file.st_mode))
				{
					value = value + getFileSizeForPath(newpath);
				}
				else if (S_ISDIR(file.st_mode))
				{
					getDirectorySizeForPath(newpath, value);
				}
			}
		}
	}
    
	closedir(directory);
    
	return value;
}


// ------------------------------------------------------------------------------------------
#pragma mark - Information methods
// ------------------------------------------------------------------------------------------

// Method to get modification time in seconds since 1970 of a file.
time_t getModificationTimeForFile(char *filename)
{
	struct stat file;
	
	if (stat(filename, &file) == 0)
	{
		return file.st_mtime;
	}
	
	printf("Cannot retrieve time for %s \n", getFileNameForPath(filename));
	return 0;
}


// Method to get the mode of a file.
mode_t getModeForFile(char *filename)
{
	struct stat file;
	if (stat(filename, &file) == 0)
	{
		return file.st_mode;
	}
    
	printf("Cannot retrieve mode for %s \n", getFileNameForPath(filename));
	return 0;
}


// Method to get the user id of a file.
uid_t getUserIDForFile(char *filename)
{
	struct stat file;
	if (stat(filename, &file) == 0)
	{
		return file.st_uid;
	}
	
	printf("Cannot retrieve user id for %s \n", getFileNameForPath(filename));
	return 0;
}


// Method to get the group id of a file.
gid_t getUserGroupForFile(char *filename)
{
	struct stat file;
	if (stat(filename, &file) == 0)
	{
		return file.st_gid;
	}
	
	printf("Cannot retrieve group id for %s \n", getFileNameForPath(filename));
	return 0;
}


