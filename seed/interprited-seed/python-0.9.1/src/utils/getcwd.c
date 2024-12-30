/* Two PD getcwd() implementations.
   Author: Guido van Rossum, CWI Amsterdam, Jan 1991, <guido@cwi.nl>. */

/* #define NO_GETWD /* Turn this on to popen pwd instead of calling getwd() */

#include <stdio.h>
#include <errno.h>

extern int errno;

#ifndef NO_GETWD

/* Default: Version for BSD systems -- use getwd() */

#include "sys/param.h"

extern char *getwd();

char *
getcwd(buf, size)
	char *buf;
	int size;
{
	char localbuf[MAXPATHLEN+1];
	char *ret;
	
	if (size <= 0) {
		errno = EINVAL;
		return NULL;
	}
	ret = getwd(localbuf);
	if (ret != NULL && strlen(localbuf) >= size) {
		errno = ERANGE;
		return NULL;
	}
	if (ret == NULL) {
		errno = EACCES; /* Most likely error */
		return NULL;
	}
	strncpy(buf, localbuf, size);
	return buf;
}

#endif
