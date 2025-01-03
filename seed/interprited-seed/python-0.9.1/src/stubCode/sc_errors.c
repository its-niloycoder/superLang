#include <stdio.h>

#include "object.h"
#include "errors.h"
#include "sc_errors.h"
#include "stringobject.h"
#include "tupleobject.h"

object *
err_scerr(sc_errno)
	int sc_errno;
{
	switch(sc_errno) {
	
	case NoBufSize:
		err_setstr(StubcodeError, "Stubcode didn't start with BufSize");
		break;
	
	case TwoBufSize:
		err_setstr(StubcodeError, "Stubcode can't have more then one BufSize");
		break;

	case ElementIsNull:
		err_setstr(StubcodeError, "Trying to access an NIL object");
		break;
	
	case StackOverflow:
		err_setstr(StubcodeError, "Stack overflow");
		return NULL;
	
	case StackUnderflow:
		err_setstr(StubcodeError, "Stack underflow");
		return NULL;
	
	case NoEndLoop:
		err_setstr(StubcodeError, "LoopXXX with no EndLoop");
		return NULL;
	
	case BufferOverflow:
		err_setstr(StubcodeError, "Buffer overflow");
		return NULL;
	
	}
	return NULL;
}

err_scerrset(sc_errno, value, instr)
	int sc_errno;
	object *value;
	char *instr;
{
	object *str, *str1, *t;

	if ((t = newtupleobject(3)) == NULL) {
		return -1;
	}
	if ((str = newstringobject(instr)) == NULL) {
		return -1;
	}
	if (settupleitem(t, 2, str) != 0) {
		return -1;
	}
	INCREF(value);
	if (settupleitem(t, 1, value) != 0) {
		DECREF(t);
		return -1;
	}
	switch(sc_errno) {
	
	case TypeFailure:
		if ((str1 = newstringobject("Unexpected type")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;
	
	case RangeError:
		if ((str1 = newstringobject("Value out of range")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;
	
	case SizeError:
		if ((str1 = newstringobject("Value doesn't have the right size")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;
	
	case FlagError:
		if ((str1 = newstringobject("Illegal flag value")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;

	case TransError:
		if ((str1 = newstringobject("hdr.h_status != 0")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;

	default:
		if ((str1 = newstringobject("sc_errno not found")) == NULL) {
			DECREF(t);
			return -1;
		}
		break;
	}
	if (settupleitem(t, 0, str1) != 0) {
		DECREF(t);
		return -1;
	}
	err_setval(StubcodeError, t);
	DECREF(t);
	return -1;
}
