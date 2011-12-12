/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __M95_TYPES_H
#define __M95_TYPES_H

#include "WrapperDefines.h"

/*
The Brew-version of the Common C++ client library implements it's own global new, new[], delete and delete[] operator-overloads,
because they are not predefined on brew arm and not overloading them leads to crashes on device.
The operators are implemented as inline, to avoid "linkage disagreement" errors on ARM-compiler.

If you or any Non Exit Games library, included by you, has implemented it's own global new/delete operator overloads, you will get
"multiple definition" linker errors, so you have to disable all global implementations of these operators, but one.
You can disable Exit Games' implementations by defining _EG_DEACTIVATE_NEW_OVERLOADS in your application's .vcproj-files for Visual Studio and
in it's .mak-files for ARM. You do NOT need a new build of the client library therefore, because our libraries do not define these operators before you compile your application.

You can find further information about this topic on:
http://www.developer.com/ws/brew/article.php/10943_3355691_2 (scroll down to paragraph "EverLoad")
http://www.developer.com/ws/brew/article.php/2216471 (first paragraph "linkage disagreement")
*/
#if defined(_EG_BREW_PLATFORM) && !defined(_EG_DEACTIVATE_NEW_OVERLOADS)

#include "AEEStdLib.h"  // AEE stdlib stuff

inline void* operator new(unsigned int size)
{
	return MALLOC(size);
}

inline void operator delete(void *ptr)
{
	FREE(ptr);
}

inline void* operator new[](unsigned int size)
{
	return MALLOC(size);
}

inline void operator delete[](void *ptr)
{
	FREE(ptr);
}
#endif

#endif