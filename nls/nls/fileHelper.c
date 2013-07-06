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


#include <stdlib.h>					/* Declare data types such as char,int e.t.c. */
#include <stdio.h>					/* Input / Output */
#include <sys/types.h>				/* Defines data types such as ino_t,off_t e.t.c. */
#include <sys/stat.h>				/* Defines the structure of the data returned from stat*/
#include <dirent.h> 				/* required for directory functions */
#include <strings.h>				/* required for strrchr and strcpy functions */
#include <time.h>		  			/* required for time functions */
#include <unistd.h>					/* required for R_OK W_OK X_OK functions */
#include <grp.h>					/* required for Group Details */
#include <pwd.h>					/* required for User Details */



// ------------------------------------------------------------------------------------------
#pragma mark - Size methods
// ------------------------------------------------------------------------------------------

// Method to get the size of the file.
int getFileSizeForPath(char *filename)
{
    //This structure will be used to query file status
	struct stat file;
    
    // validate if it can retrieve the size or not
	if (stat(filename, &file) != 0)
    {
        return (int)(file.st_size / 1024);
    }
    
	printf("Cannot retrive size for %s \n", filename);
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
	
	if (stat(filename, &file) != 0)
    {
        return file.st_mtime;
    }
	
    printf("Cannot retrieve time for %s \n", filename);
	return 0;
}


// Method to get the mode of a file.
mode_t getModeForFile(char *filename)
{
	struct stat file;
	if (stat(filename, &file) != 0)
    {
        return file.st_mode;
    }
    
	printf("Cannot retrieve mode for %s \n", filename);
	return 0;
}


// Method to get the user id of a file.
uid_t getUserIDForFile(char *filename)
{
	struct stat file;
    if (stat(filename, &file) != 0)
    {
        return file.st_uid;
    }
	
    printf("Cannot retrieve user id for %s \n", filename);
	return 0;
}


// Method to get the group id of a file.
gid_t getUserGroupForFile(char *filename)
{
	struct stat file;
	if (stat(filename, &file) != 0)
    {
        return file.st_gid;
    }
	
    printf("Cannot retrieve group id for %s \n", filename);
	return 0;
}


// ------------------------------------------------------------------------------------------
#pragma mark - Logging methods
// ------------------------------------------------------------------------------------------


// Method to print the name and the st number of a file.
void printInodeForFile(char *filename, struct stat file)
{
	if (stat(filename, &file) != 0)
    {
		printf("Inode no: %-10lli file :%s \t\n", file.st_ino, filename);
	}
}


// Method to print the permissions of the Owner , Group and Others.
void printPermissionsForFile(char *filename, struct stat file)
{
    if (stat(filename, &file) != 0)
	{
		mode_t mode = getModeForFile(filename);
		if ((mode & 0400) == 0)
        {
            printf("Owner cannot read ,");
        }
		else
        {
            printf("Owner can read ,");
        }
		
        if ((mode & 0200) == 0)
        {
            printf(" cannot write ,");
        }
		else
        {
            printf(" can write ,");
        }
        
		if ((mode & 0100) == 0)
        {
            printf(" cannot execute || %s\n", filename);
        }
		else
        {
            printf(" can execute || %s\n", filename);
        }
		
        if ((mode & 0040) == 0)
        {
            printf("Group cannot read ,");
        }
		else
        {
            printf("Group can read ,");
        }
		
        if ((mode & 0020) == 0)
        {
            printf(" cannot write ,");
        }
		else
        {
            printf(" can write ,");
        }
		
        if ((mode & 0010) == 0)
        {
            printf(" cannot execute || %s\n", filename);
        }
		else
        {
            printf(" can execute || %s\n", filename);
        }
		
        if ((mode & 0004) == 0)
        {
            printf("Others cannot read ,");
        }
		else
        {
            printf("Others can read ,");
        }
		
        if ((mode & 0002) == 0)
        {
            printf(" cannot write ,");
        }
		else
        {
            printf(" can write ,");
        }
        
		if ((mode & 0001) == 0)
        {
            printf(" cannot execute || %s\n", filename);
        }
		else
        {
            printf(" can execute || %s\n", filename);
        }
	}
}


// Method to print the permissions of the current user.
void printPermissionsOfCurrentUserForFile(char *filename, struct stat file)
{
	int access (const char *filename, int how);
	access(filename, file.st_mode);
    
    if (stat(filename, &file) != 0)
	{
		if (access(filename,R_OK) == -1)
		{
            printf ("You can not read ||") ;
        }
		else
        {
            printf ("You can read ||") ;
        }
        
		if (access(filename,W_OK) == -1)
		{
            printf (" You can not write ||");
        }
		else
        {
            printf (" You can write ||") ;
        }
        
		if (access(filename,X_OK) == -1)
		{
            printf (" You can not execute || %s \n", filename);
        }
		else
        {
            printf (" You can execute || %s \n", filename);
        }
	}
}

// Method to get the user name with and the group members.
void printUsernameAndGroupMembersForFile(char *filename, struct stat file)
{
    if (stat(filename, &file) != 0)
	{
		uid_t uid = getUserIDForFile(filename);
		gid_t gid = getUserGroupForFile(filename);
        
        /* get the information about the user. */
		struct passwd* upwd = getpwuid(uid);
        
        /* get the information about the group. */
		struct group* gpwd = getgrgid(gid);
		
        /* make sure this user actually exists. */
		if (!upwd)
        {
            printf("User %i does not exist.\n", uid);
        }
		else
        {
            printf("file: %-45s Owner: %s \t Group id: %i || ",
                   filename, upwd->pw_name, getUserGroupForFile(filename));
        }
        
		/* make sure this group actually exists. */
        if (!gpwd)
        {
            printf("group %i does not exist.\n", gid);
        }
		else
        {
			char** p_member;
			printf("Members of group: ");
			for (p_member = gpwd->gr_mem; *p_member; p_member++)
            {
                printf(" (%s) ", *p_member);
            }
			
            printf("\n");
		}
	}
}

