/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __OBJECT_H
#define __OBJECT_H

#include "WrapperDefines.h"
#include "data_structures.h"
#include "Base.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class Utils;
	/* Summary
	   Container class designed to hold all types of objects that
	   can be transmitted over both Neutron and Photon. This class
	   substitutes <link _EG_Object, EG_Object>.
	   Description
	   Object is the common base for the template classes <link KeyObject>
	   and <link ValueObject>, that provide a more convenient
	   interface for handling Objects.
	   
	   <i>We do not recommend to use the class Object
	   directly, as the class templates KeyObject and ValueObject
	   provide a more type-safe and more convenient interface for
	   dealing with Objects !</i>
	   See Also
	   <link _EG_Object, EG_Object> , <link KeyObject> , <link ValueObject>     */
	class Object : protected Base
	{
	public:
		Object(void);
		Object(void* data, nByte type, nByte customType, bool makeCopy);
		Object(void* data, nByte type, nByte customType, short size, bool makeCopy);
		Object(void* data, nByte type, nByte customType, unsigned int dimensions, const short* const size, bool makeCopy);
		~Object(void);

		Object(const Object& toCopy);
		Object& operator=(const Object& toCopy);

		bool operator==(const Object& toCompare) const;
		bool operator!=(const Object& toCompare) const;

		const void* getData(void) const;
		nByte getType(void) const;
		nByte getCustomType(void) const;
		const short* getSize(void) const;
		unsigned int getDimensions(void) const;
		void set(void* data, nByte type, nByte customType, bool makeCopy);
		void set(void* data, nByte type, nByte customType, short size, bool makeCopy);
		void set(void* data, nByte type, nByte customType, unsigned int dimensions, const short* const size, bool makeCopy);

	protected:
		void setWithoutCleanup(void* data, nByte type, nByte customType, bool makeCopy);
		void setWithoutCleanup(void* data, nByte type, nByte customType, short size, bool makeCopy);
		void setWithoutCleanup(void* data, nByte type, nByte customType, unsigned int dimensions, const short* const sizes, bool makeCopy);

		void* _data;
		short* _size;
		nByte _type;
		nByte _customType;
		unsigned int _dimensions;

	private:
		void setSize(short size);
		void setSizes(const short* const sizes, unsigned int dimensions=1);
		void setData(void* data);
		void setDataNoCopy(void* data);
		void setType(nByte type);
		void setCustomType(nByte customType);
		void cleanup(void* pData = 0, unsigned int recursionDepth=0);
		void copyArray(void* pDataIn, void** pDataOut, unsigned int recursionDepth=0) const;
		bool equalsArray(const void* const pData1, const void* const pData2, unsigned int recursionDepth=0) const;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif