//
//  printHelper.c
//  nls
//
//  Created by Patrick Chamelo on 7/7/13.
//  Copyright (c) 2013 Patrick Chamelo. All rights reserved.
//


#include "fileHelper.c"

// ------------------------------------------------------------------------------------------
#pragma mark - Logging methods
// ------------------------------------------------------------------------------------------


void printSynopsis()
{
    printf("SYNOPSIS \n"
           "nls [ -hinsto ] [ pathname ] \n\n"
           "OPTIONS: \n\n"
           "-i, --Inode\n"
           "Display the name and the inode of a file or directory\n"
           "-h, --Hidden files\n"
           "Display the hidden files also of a file or directory\n"
           "-n, --Current user permissions\n"
           "Display the permissions of the current user for a file or directory\n"
           "-s, --Access permissions\n"
           "Display the access permissions of a file or directory\n"
           "-t, --Total size and items\n"
           "Display the tolal size and the number of items of a file or directory\n"
           "-o, --User and Group\n"
           "Display the user and the group members of file or directory\n\n");
}


// Method to print all the fine names including the hidden ones.
void printFilesForPath(char *filename)
{
    struct stat file;
	if (stat(filename, &file) == 0)
    {
        printf("%-45s \n", getFileNameForPath(filename));
    }
}


// Method to get the size of the file.
void printSizeForFile(char *filename, struct stat file)
{
	if (stat(filename, &file) == 0)
    {
        if (S_ISDIR(file.st_mode))
        {
            int value = 0;
            int sizeofdir = getDirectorySizeForPath(filename, value);
            printf("%-45s \t Size kb:%-15i \n", getFileNameForPath(filename), sizeofdir);
        }
        else
        {
            int filesize = getFileSizeForPath(filename);
            printf("%-45s \t Size kb:%-15i \n", getFileNameForPath(filename), filesize);
        }
        
    }
}


// Method to print the name and the st number of a file.
void printInodeForFile(char *filename, struct stat file)
{
	if (stat(filename, &file) == 0)
	{
		printf("%-10lli %s \t\n", file.st_ino, getFileNameForPath(filename));
	}
}


// Method to print the permissions of the Owner , Group and Others.
void printPermissionsForFile(char *filename, struct stat file)
{
	if (stat(filename, &file) == 0)
	{
        mode_t mode = getModeForFile(filename);
        
        printf("%s\n", getFileNameForPath(filename));
        printf("Owner ");
        
        printf(((mode & 0400) == 0) ? "-" : "r");
        printf(((mode & 0200) == 0) ? "-" : "w");
        printf(((mode & 0100) == 0) ? "-" : "x");
        printf("\n");
        
        printf("Group ");
        
        printf(((mode & 0040) == 0) ? "-" : "r");
        printf(((mode & 0020) == 0) ? "-" : "w");
        printf(((mode & 0010) == 0) ? "-" : "x");
        printf("\n");
        
        
        printf("Others ");
        printf(((mode & 0004) == 0) ? "-" : "r");
        printf(((mode & 0002) == 0) ? "-" : "w");
        printf(((mode & 0001) == 0) ? "-" : "x");
        printf("\n\n");
	}
}


// Method to print the permissions of the current user.
void printPermissionsOfCurrentUserForFile(char *filename, struct stat file)
{
	int access (const char *filename, int how);
	access(filename, file.st_mode);
    
	if (stat(filename, &file) == 0)
	{
        printf((access(filename, R_OK) == -1) ? "-" : "r");
        printf((access(filename, W_OK) == -1) ? "-" : "w");
        printf((access(filename, X_OK) == -1) ? "-" : "x");
        printf(" -> %s\n", getFileNameForPath(filename));
	}
}


// Method to get the user name with and the group members.
void printUsernameAndGroupMembersForFile(char *filename, struct stat file)
{
	if (stat(filename, &file) == 0)
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
			printf("%-45s Owner: %s \t Group id: %i || ",
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


void printForOptionPathStat(char *option, char *path, struct stat st)
{
	if (strcmp(option, "-h") == 0)
	{
		printFilesForPath(path);
	}
	else if (strcmp(option, "-i") == 0)
	{
		printInodeForFile(path, st);
	}
	else if (strcmp(option, "-s") == 0)
	{
		printPermissionsForFile(path, st);
	}
	else if (strcmp(option, "-n") == 0)
	{
		printPermissionsOfCurrentUserForFile(path, st);
	}
	else if (strcmp(option, "-t") == 0)
	{
		printSizeForFile(path, st);
	}
	else if (strcmp(option, "-o") == 0)
	{
		printUsernameAndGroupMembersForFile(path, st);
	}
}


