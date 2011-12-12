/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __CUSTOM_TYPE_H
#define __CUSTOM_TYPE_H

#include "CustomTypeBase.h"
#include "CustomTypeFactory.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	template<nByte typeCode>
	class CustomType : public CustomTypeBase
	{
	public:
		static const nByte TypeCode = typeCode;
	protected:
		static void constructClass(const CustomTypeFactory<typeCode>& factory);
		static void deconstructClass(void);
		CustomType(void);
		CustomType(const CustomType& toCopy);
		~CustomType(void);
	private:
		typedef CustomTypeBase super;

		static void* ccalloc(short count, nByte customTypeCode);
		static void cfree(void* pData, nByte customTypeCode);
		static unsigned int csizeOf(nByte customTypeCode);

		static CustomTypeFactory<typeCode>* mFactory;
	};

	template<nByte typeCode>
	CustomTypeFactory<typeCode>* CustomType<typeCode>::mFactory = NULL;



	template<nByte typeCode>
	void CustomType<typeCode>::constructClass(const CustomTypeFactory<typeCode>& factory)
	{
		super::constructClass(typeCode, &ccalloc, &cfree, &csizeOf);
		mFactory = factory.copyFactory();
	}

	template<nByte typeCode>
	void CustomType<typeCode>::deconstructClass(void)
	{
		super::deconstructClass();
		mFactory->destroyFactory(); // not just deleting it, as subclasses could potentially implement copyFactory() by using something else then new
	}

	template<nByte typeCode>
	CustomType<typeCode>::CustomType(void)
	{
	}

	template<nByte typeCode>
	CustomType<typeCode>::CustomType(const CustomType& toCopy)
	{
	}

	template<nByte typeCode>
	CustomType<typeCode>::~CustomType(void)
	{
	}

	template<nByte typeCode>
	void* CustomType<typeCode>::ccalloc(short count, nByte customTypeCode)
	{
		return mFactory->create(count);
	}

	template<nByte typeCode>
	void CustomType<typeCode>::cfree(void* pData, nByte customTypeCode)
	{
		mFactory->destroy(static_cast<CustomType<typeCode>*>(pData));
	}

	template<nByte typeCode>
	unsigned int CustomType<typeCode>::csizeOf(nByte customTypeCode)
	{
		return mFactory->sizeOf();
	}

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif