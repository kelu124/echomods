/*******************
 *
 * Copyright 1998-2010 IAR Systems AB. 
 *
 * This is a template implementation of the "__close" function used by
 * the standard library.  Replace it with a system-specific
 * implementation.
 *
 * The "__close" function should close the file corresponding to
 * "handle".  It should return 0 on success and nonzero on failure.
 *
 ********************/

#include <yfuns.h>

_STD_BEGIN

#pragma module_name = "?__close"

#pragma diag_suppress = Pe826

int __close(int handle)
{
  return 0;
}

_STD_END
