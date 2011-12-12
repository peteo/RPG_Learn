/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __CUSTOM_TYPE_FACTORY_H
#define __CUSTOM_TYPE_FACTORY_H

#include "Base.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	
	template<nByte typeCode> class CustomType;

	template<nByte typeCode> class CustomTypeFactory : public Base
	{
	public:
		virtual ~CustomTypeFactory(void) {};
		virtual CustomTypeFactory<typeCode>* copyFactory(void) const = 0;
		virtual void destroyFactory(void) = 0;

		virtual CustomType<typeCode>* create(short amount) const = 0;
		virtual CustomType<typeCode>* copy(CustomType<typeCode>* toCopy) const = 0;
		virtual void destroy(CustomType<typeCode>* toDestroy) const = 0;
		virtual unsigned int sizeOf(void) const = 0;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif