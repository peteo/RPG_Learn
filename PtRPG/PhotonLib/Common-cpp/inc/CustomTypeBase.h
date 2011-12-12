/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __CUSTOM_TYPE_BASE_H
#define __CUSTOM_TYPE_BASE_H

#include "Base.h"
#include "data_structures.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	class CustomTypeBase : protected Base
	{
	public:
		virtual void cleanup(void) = 0;
		virtual bool compare(const CustomTypeBase& other) const = 0;
		virtual void duplicate(CustomTypeBase* const retVal) const = 0;
		virtual void deserialize(const nByte* const pData, short length) = 0;
		virtual short serialize(nByte* const retVal) const = 0;
		JString toString(void) const;
		virtual JString& toString(JString& retStr) const = 0;
	private:
		template<nByte typeCode> friend class CustomType;

		static void constructClass(nByte typeCode, CB_CALLOC cbCalloc, CB_FREE cbFree, CB_SIZEOF cbSizeOf);
		static void deconstructClass(void);
		CustomTypeBase(void);
		CustomTypeBase(const CustomTypeBase& toCopy);
		~CustomTypeBase();

		static void ccleanup(void* pData);
		static bool ccompare(void* pData1, void* pData2);
		static void cduplicate(void* pData, void* retVal);
		static void cdeserialize(nByte* pData, short length, void* retVal);
		static short cserialize(void* pData, nByte* retVal);
		static int ctoString(void* pData, EG_CHAR* buffer);
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif