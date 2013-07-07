//
//  includes.c
//  nls
//
//  Created by Patrick Chamelo on 7/7/13.
//  Copyright (c) 2013 Patrick Chamelo. All rights reserved.
//

#include <stdio.h>
#include <strings.h>				/* required for strrchr and strcpy functions */
#include <stdlib.h>					/* Declare data types such as char,int e.t.c. */
#include <libgen.h>					/* required for the basename functions. */
#include <stdbool.h>				/* required for the bool functions. */
#include <unistd.h>					/* required for the basename functions. */
#include <sys/types.h>				/* Defines data types such as ino_t,off_t e.t.c. */
#include <sys/stat.h>				/* Defines the structure of the data returned from stat*/
#include <dirent.h>					/* required for directory functions */
#include <time.h>					/* required for time functions */
#include <grp.h>					/* required for Group Details */
#include <pwd.h>					/* required for User Details */
