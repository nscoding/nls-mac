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


#include "fileHelper.c"
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

int main(int argc, const char * argv[])
{
    if (argc > 1)
    {
        if (strcmp (argv[1], "--help") == 0)
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

                   exit(0);
        }
    }
    
    return 0;
}

