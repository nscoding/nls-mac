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

