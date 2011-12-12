/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __CONFIRM_ALLOWED_KEY_H
#define __CONFIRM_ALLOWED_KEY_H

#include "Object.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	template<typename CType> struct ConfirmAllowedKey;
	template<> struct ConfirmAllowedKey<nByte>
	{
		typedef nByte type;
		static const nByte typeName = EG_BYTE;
	};
	template<> struct ConfirmAllowedKey<short>
	{
		typedef short type;
		static const nByte typeName = EG_SHORT;
	};
	template<> struct ConfirmAllowedKey<int>
	{
		typedef int type;
		static const nByte typeName = EG_INTEGER;
	};
	template<> struct ConfirmAllowedKey<int64>
	{
		typedef int64 type;
		static const nByte typeName = EG_LONG;
	};
	template<> struct ConfirmAllowedKey<JString>
	{
		typedef JString type;
		static const nByte typeName = EG_STRING;
	};
	template<> struct ConfirmAllowedKey<char*>
	{
		typedef char* type;
		static const nByte typeName = EG_STRING;
	};
	template<> struct ConfirmAllowedKey<EG_CHAR*>
	{
		typedef EG_CHAR* type;
		static const nByte typeName = EG_STRING;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif