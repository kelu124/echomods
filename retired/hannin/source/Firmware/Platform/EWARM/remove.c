/*******************
 *
 * Copyright 1998-2010 IAR Systems AB. 
 *
 * This is a template implementation of the "remove" function of the
 * standard library.  Replace it with a system-specific
 * implementation.
 *
 * The "remove" function should remove the file named "filename".  It
 * should return 0 on success and nonzero on failure.
 *
 ********************/

#include <stdio.h>

_STD_BEGIN

#pragma module_name = "?remove"

#pragma diag_suppress = Pe826

int remove(const char * filename)
{
  return 0;
}

_STD_END
