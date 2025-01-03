/*
**	strtol
**		This is a general purpose routine for converting
**		an ascii string to an integer in an arbitrary base.
**		Leading white space is ignored, if 'base' is zero
**		it looks for a leading 0, 0x or 0X to tell which
**		base.  If these are absent it defaults to 10.
**		Base must be between 0 and 36.
**		If 'ptr' is non-NULL it will contain a pointer to
**		the end of the scan.
**		Errors due to bad pointers will probably result in
**		exceptions - we don't check for them.
*/

#include "ctype.h"

long
strtol(str, ptr, base)
register char *	str;
char **		ptr;
int		base;
{
    register long	result;	/* return value of the function */
    register int	c;	/* current input character */
    int			minus;	/* true if a leading minus was found */

    result = 0;
    minus = 0;

/* catch silly bases */
    if (base < 0 || base > 36)
    {
	if (ptr)
	    *ptr = str;
	return result;
    }

/* skip leading white space */
    while (*str && isspace(*str))
	str++;

/* check for optional leading minus sign */
    if (*str == '-')
    {
	minus = 1;
	str++;
    }

/* check for leading 0 or 0x for auto-base or base 16 */
    switch (base)
    {
    case 0:		/* look for leading 0, 0x or 0X */
	if (*str == '0')
	{
	    str++;
	    if (*str == 'x' || *str == 'X')
	    {
		str++;
		base = 16;
	    }
	    else
		base = 8;
	}
	else
	    base = 10;
	break;

    case 16:	/* skip leading 0x or 0X */
	if (*str == '0' && (*(str+1) == 'x' || *(str+1) == 'X'))
	    str += 2;
	break;
    }

/* do the conversion */
    while (c = *str)
    {
	if (isdigit(c) && c - '0' < base)
	    c -= '0';
	else
	{
	    if (isupper(c))
		c = tolower(c);
	    if (c >= 'a' && c <= 'z')
		c -= 'a' - 10;
	    else	/* non-"digit" character */
		break;
	    if (c >= base)	/* non-"digit" character */
		break;
	}
	result = result * base + c;
	str++;
    }

/* set pointer to point to the last character scanned */
    if (ptr)
	*ptr = str;
    return minus ? -result : result;
}
