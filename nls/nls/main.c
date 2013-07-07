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


#include "printHelper.c"

int main(int argc, const char * argv[])
{
	DIR *directory;
	int status;
	struct stat st;
    
	if (argc > 1)
	{
        // check the first argument
        // if is any of the supported options
        if ((strcmp(argv[1],"--help") == 0)||
            (strcmp(argv[1],"-h") == 0)    ||
            (strcmp(argv[1],"-i") == 0)    ||
            (strcmp(argv[1],"-s") == 0)    ||
            (strcmp(argv[1],"-t") == 0)    ||
            (strcmp(argv[1],"-n") == 0)    ||
            (strcmp(argv[1],"-o") == 0))
		{
            // if is help print the synopsis of the app
            if (strcmp(argv[1], "--help") == 0)
            {
                printSynopsis();
                exit(0);
            }
            
            char *option = strdup(argv[1]);
            char *path;
            
            if (argc == 3)
            {
                // nls [ -hinsto ] [ pathname ]
                path = strdup(argv[2]);
            }
            else
            {
                // nls [ -hinsto ]
                path = getWorkingDirectoryPath();
            }
            
            directory = opendir(path);
            status = stat(path, &st);
            size_t size = strlen(path);
            
            if (size > 0)
            {
                if (status == -1)
                {
                    printf("%s does not exist\n", path);
                    exit(0);
                }
                else if (!S_ISDIR(st.st_mode))
                {
                    printForOptionPathStat(option, path, st);
                }
                else
                {
                    struct dirent *entry;
                    struct stat st;
                    int access (const char *filename, int how);
                    char string[1024];
                    
                    while (true)
                    {
                        entry = readdir(directory);
                        if (entry != 0)
                        {
                            if ((strncmp(entry->d_name, ".", 1) != 0) ||
                                strcmp(option, "-h") == 0)
                            {
                                if (pathEndsWithSlash(path))
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
                            break;
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

