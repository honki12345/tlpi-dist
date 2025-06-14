/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter 10 */

/* t_stime.c

   Demonstrate the use of stime() to set the system time.

   Requires superuser privileges.
*/
#define _SVID_SOURCE            /* For stime() */
#if ! defined(__sun)
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE           /* For strptime() */
#endif
#endif
#include <time.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    struct tm tm;
    time_t t;
    struct timespec ts;         /* clock_settime()을 위해 추가 */

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s \"DD MMM YYYY HH:MM:SS\"\n", argv[0]);

    if (strptime(argv[1], "%d %b %Y %H:%M:%S", &tm) == NULL)
        fatal("strptime failed");

    t = mktime(&tm);

    /* stime() 대신 clock_settime() 사용 */
    ts.tv_sec = t;
    ts.tv_nsec = 0;
    if (clock_settime(CLOCK_REALTIME, &ts) == -1)
        errExit("clock_settime");

    exit(EXIT_SUCCESS);
}
