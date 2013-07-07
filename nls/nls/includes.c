//
//  includes.c
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


#include <stdio.h>
#include <strings.h>    /* required for strrchr and strcpy functions */
#include <stdlib.h>     /* Declare data types such as char,int e.t.c. */
#include <libgen.h>     /* required for the basename functions. */
#include <stdbool.h>    /* required for the bool functions. */
#include <unistd.h>     /* required for the basename functions. */
#include <sys/types.h>  /* Defines data types such as ino_t,off_t e.t.c. */
#include <sys/stat.h>   /* Defines the structure of the data returned from stat*/
#include <dirent.h>     /* required for directory functions */
#include <time.h>       /* required for time functions */
#include <grp.h>        /* required for Group Details */
#include <pwd.h>        /* required for User Details */
