//
//  main.c
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


#include <stdbool.h>
#include "fileHelper.c"
#include "printHelper.c"


int main(int argc, const char * argv[])
{
	DIR *directory;
	int status;
	struct stat st;
    
	if (argc > 1)
	{
        if ((strcmp(argv[1],"--help") == 0)||
            (strcmp(argv[1],"-h") == 0)    ||
            (strcmp(argv[1],"-i") == 0)    ||
            (strcmp(argv[1],"-s") == 0)    ||
            (strcmp(argv[1],"-t") == 0)    ||
            (strcmp(argv[1],"-n") == 0)    ||
            (strcmp(argv[1],"-o") == 0))
		{
			if (strcmp(argv[1], "--help") == 0)
			{
                printSynopsis();
                exit(0);
			}
            
			if (argc == 3)
			{
				char *option = strdup(argv[1]);
				char *path = strdup(argv[2]);
                
				directory = opendir(path);
				status = stat(path, &st);
                
				if (status == -1)
				{
					printf("%s does not exist\n", argv[2]);
					exit(2);
				}
				else if (!S_ISDIR(st.st_mode))
				{
					printForOptionPathStat(option, path, st);
				}
				else
				{
					struct dirent *entry;
					unsigned char done = 0;
					struct stat st;
					int access (const char *filename, int how);
					char string[1024];
                    
					while (!done)
					{
						entry = readdir(directory);
						if (entry != 0)
						{
							if ((strncmp(entry->d_name, ".",1) != 0) ||
								strcmp(option, "-h") == 0)
							{
								size_t size = strlen(path);
								bool hasSlash = (path[size - 1] == '/');
								if (hasSlash)
								{
									sprintf(string, "%s%s", path, entry->d_name);
								}
								else
								{
									sprintf(string, "%s/%s", path, entry->d_name);
								}
                                
								stat(string, &st);
								printForOptionPathStat(option, string, st);
							}
						}
						else
						{
							done = 1;
						}
					}
				}
                
				closedir(directory);
			}
		}
        else
        {
            printf("nls: '%s' is not a nls command. See 'nsl --help", argv[1]);
            exit(0);
        }

	}
    else
    {
        printSynopsis();
        exit(0);
    }
    
	return 0;
}

