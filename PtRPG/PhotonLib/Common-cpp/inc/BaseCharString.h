/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __BASE_CHAR_STRING_H
#define __BASE_CHAR_STRING_H

#include "Base.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class JString;

	/* Summary
	   The BaseCharString class is the abstract base class for container classes,
	   holding char* strings.
	   Description
	   Subclasses of this class act as convenience classes for conversions between
	   instances of class <link JString> and char*'s.
	   The encoding of the char*'s is defines by the subclass. There should be one
	   subclass for every supported encoding.
	   Subclasses of this class should only be used to hold or pass strings and for
	   conversions between string encodings.
	   Please use class <link JString> for common string operations and modifications.*/
	class BaseCharString : protected Base
	{
	public:
		virtual operator const char* (void) const = 0;
		virtual operator JString (void) const = 0;

		virtual const char*	cstr(void) const = 0;
		virtual JString JStringRepresentation(void) const = 0;
	protected:
		char* mBuffer;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif