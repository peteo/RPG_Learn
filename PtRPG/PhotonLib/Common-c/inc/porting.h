/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PORTING_H
#define __PORTING_H

#include "defines.h"

// Compile time messages /////////////////////////////////////////////////
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "

#if defined(_EG_BREW_PLATFORM)
#   include <AEE.h>
#   include <AEEShell.h>	
#   include <AEEAppgen.h>	
#   include <AEEModgen.h>	
#   include <AEEStdlib.h>
#   include <AEEWeb.h>
#   include <AEENet.h>
//# include "AEEClassIDs.h"
#   include <AEEHeap.h>
#   include <AEETAPI.h>
#   include <AEEFile.h>		//	AEEFile Services
#   include <AEESSL.h>
#   include <BREWVersion.h>
//# include "brew_defines.h"
//wrapper additional includes
//# include "AEEMenu.h"
//# include "AEEDisp.h"		// AEE Display Services
//# include "AEEGraphics.h"
#elif defined(_EG_WINDOWS_PLATFORM)
#   if defined(_EG_WIN32_PLATFORM)
#       define WIN32_LEAN_AND_MEAN
#       define _WIN32_WINNT 0x0500
#       include <process.h>
#       include <mbstring.h>
#   endif
#   include <tchar.h>
#   include <assert.h>
#   include <winsock2.h>
#   include <windows.h>
#   include <time.h>
#   include <ws2tcpip.h>
#   include <wininet.h>
#   include <urlmon.h>
#   include <string.h>
#elif defined(_EG_UNIX_PLATFORM)
#	if defined(_EG_APPLE_PLATFORM)
#		include <AvailabilityMacros.h>
#		import <CoreFoundation/CFString.h>
#		import <CoreFoundation/CoreFoundation.h>
#		include <sys/time.h>
#	elif defined(_EG_MEEGO_PLATFORM)
#		include <iconv.h>
#		include <sys/time.h>
#		include <limits.h>
#	elif defined(_EG_MARMALADE_PLATFORM)
#		include "C_IwUTF8.h"
#		include <limits.h>
#	endif
#endif

#endif