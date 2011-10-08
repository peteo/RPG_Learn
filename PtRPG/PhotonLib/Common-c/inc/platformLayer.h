/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PLATFORM_LAYER_H
#define __PLATFORM_LAYER_H

#include "misc.h"

unsigned short IPL_GetCurrentTimeUint16(void);

#ifdef  __cplusplus
extern "C"
{
#endif

#ifdef _EG_UNIX_PLATFORM
	int EG_wtoi(EG_CHAR* wstr);
	int EG_strnicmp(const char* str1, const char* str2, unsigned int count);
	int getTimeUnix(void);
#endif

#ifdef  __cplusplus
}
#endif

#ifdef _EG_APPLE_PLATFORM
	void clientCB(CFReadStreamRef stream, CFStreamEventType eventType, void* clientCallBackInfo);
#endif

#endif  // _PLATFORM_LAYER_
