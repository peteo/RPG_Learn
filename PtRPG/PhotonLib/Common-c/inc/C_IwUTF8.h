/* Exit Games Common - C Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __C_IWUTF8_H
#define __C_IWUTF8_H

#include "Constants.h"

#ifdef _EG_MARMALADE_PLATFORM

#include <IwUTF8.h>

#ifdef __cplusplus
	extern "C"
	{
#endif

int C_IwWideCharToUTF8(const ucs2char* wideString, int wideStringLength,  char* utf8Buffer,  unsigned int utf8BufferSize);
int	C_IwUTF8ToWideChar(const char* utf8String, int utf8StringSize, ucs2char* wideBuffer, unsigned int wideBufferSize);

#ifdef __cplusplus
	}
#endif

#endif

#endif