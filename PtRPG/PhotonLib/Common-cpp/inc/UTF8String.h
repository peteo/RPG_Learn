/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __UTF8_STRING_H
#define __UTF8_STRING_H

#include "BaseCharString.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	/* Summary
	   The UTF8String class is a container class for char* strings, encoded with UTF8.
	   Description
	   This is the UTF8 implementation of <link BaseCharString>.
	   Please look at the doc of the abstract base class for more information.*/
	class UTF8String : protected BaseCharString
	{
	public:
		UTF8String(void);
		UTF8String(const UTF8String& wstr);
		UTF8String(const JString& wstr);
		UTF8String(const char* str);
		UTF8String(const EG_CHAR* wstr);
		~UTF8String(void);

		UTF8String& operator=(const UTF8String& Rhs);
		UTF8String& operator=(const JString& Rhs);
		UTF8String& operator=(const char* Rhs);
		UTF8String& operator=(const EG_CHAR* Rhs);

		operator const char* (void) const;
		operator const EG_CHAR* (void) const;
		operator JString (void) const;

		const char*	cstr(void) const;
		JString JStringRepresentation(void) const;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif
