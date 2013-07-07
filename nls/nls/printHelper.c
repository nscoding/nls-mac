//
//  printHelper.c
//  nls
//
//  Created by Patrick Chamelo on 7/7/13.
//  Copyright (c) 2013 Patrick Chamelo. All rights reserved.
//


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


void printSynopsis()
{
    printf("SYNOPSIS \n"
           "explore [ -hinsto ] [ pathname ] \n\n"
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

