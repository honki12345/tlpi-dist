/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 31-1 */

/* strerror.c

   An implementation of strerror() that is not thread-safe.
*/
#define _GNU_SOURCE                 /* Get '_sys_nerr' and '_sys_errlist'
                                       declarations from <stdio.h> */
#include <stdio.h>
#include <string.h>                 /* Get declaration of strerror() */

#define MAX_ERROR_LEN 256           /* Maximum length of string
                                       returned by strerror() */

static char buf[MAX_ERROR_LEN];     /* Statically allocated return buffer */

char *
strerror(int err)
{
    if (err < 0) {
        snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err);
    } else {
        /* Use the system's strerror function to get the error message */
        char *sys_msg = strerror_r(err, buf, MAX_ERROR_LEN);
        if (sys_msg != buf) {
            /* strerror_r returned a pointer to a static string */
            strncpy(buf, sys_msg, MAX_ERROR_LEN - 1);
            buf[MAX_ERROR_LEN - 1] = '\0';
        }
    }
    return buf;
}
