#ifndef IO_H
#define IO_H

#ifdef IO
#include "io/write.h"
#include "io/read.h"
#endif

#ifdef SYSIO
#include "io/putmsg.h"
#include "io/echo.h"
#endif

#endif
