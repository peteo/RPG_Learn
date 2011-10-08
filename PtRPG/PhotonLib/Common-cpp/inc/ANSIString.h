/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __ANSI_STRING_H
#define __ANSI_STRING_H

#include "BaseCharString.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	/* Summary
	   The ANSIString class is a container class for char* strings, encoded with the current locale.
	   Description
	   This is the current locale implementation of <link BaseCharString>.
	   Please look at the doc of the abstract base class for more information.*/
	class ANSIString : public BaseCharString
	{
	public:
		ANSIString(void);
		ANSIString(const ANSIString& wstr);
		ANSIString(const JString& wstr);
		ANSIString(const char* str);
		ANSIString(const EG_CHAR* wstr);
		ANSIString& operator=(const ANSIString& Rhs);
		ANSIString& operator=(const JString& Rhs);
		ANSIString& operator=(const char* Rhs);
		ANSIString& operator=(const EG_CHAR* Rhs);
		operator const char* (void) const;
		operator const EG_CHAR* (void) const;
		operator JString (void) const;
		const char*	cstr(void) const;
		JString JStringRepresentation(void) const;
		~ANSIString(void);
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif