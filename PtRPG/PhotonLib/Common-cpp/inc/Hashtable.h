/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "Object.h"
#include "JVector.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	/* Summary
	   The Hashtable class is the main container class for objects
	   to be transmitted over Neutron or Photon when using the C++
	   Wrapper.
	   Description
	   This class implements the well-known concept of a container
	   structure storing an arbitrary number of key/value-pairs.
	   
	   The Hashtable class substitutes the <link _EG_HashTable, EG_HashTable>
	   data structure when using the Neutron /Photon C++ Wrapper.
	   All data that is about to be transmitted over Neutron /
	   Photon needs to be stored in a Hashtable, and all
	   events/operations received are instances of the Hashtable
	   class.
	   
	   Before you can store your data in a Hashtable, you need to
	   wrap the values in another container of either type KeyObject
	   for keys or ValueObject for values.
	   
	   These two templates will only accept types usable as a key
	   resp. value in a Hashtable.
	   
	   
	   
	   <b>datatypes, which are supported as keys:</b>
	   
	   nByte, short, int, int64 and <link JString>
	   
	   
	   
	   <b>datatypes, which are supported as values:</b>
	   
	   nByte, short, int, int64, bool, <link JString>, <link JVector>,
	   Hashtable and arrays of types nByte, int and JString
	   
	   
	   
	   Please refer to the documentation for <link Hashtable::put@Object &amp;@Object &amp;, put()>
	   and <link Hashtable::getValue@Object &amp;@const, getValue()>
	   to see how to store and access data in a Hashtable.
	   See Also
	   <link Hashtable::put@Object &amp;@Object &amp;, put()> , <link Hashtable::getValue@Object &amp;@const, getValue()>
	   , <link KeyObject> , <link ValueObject>                                                                            */
	class Hashtable : protected Base
	{
	public:
		Hashtable(void);
		~Hashtable(void);

		Hashtable(const Hashtable& toCopy);
		Hashtable& operator=(const Hashtable& toCopy);

		bool operator==(const Hashtable &toCompare) const;
		bool operator!=(const Hashtable &toCompare) const;
		const Object& operator[](unsigned int index) const;
		Object& operator[](unsigned int index);

		void put(const Object& key, const Object& value);
		const Object* getValue(const Object& key) const;
		unsigned int size(void) const;
		JVector<Object> keys(void) const;
		void remove(const Object& key);
		bool contains(const Object& key) const;
		void removeAllElements(void);
		JString toString(bool withTypes=false) const;
		JString& toString(JString& retStr, bool withTypes=false) const;
	private:
		static bool haveSameKey(const Object& one, const Object& two);
		static JString toStringHelper(const Object& object, JString& retStr, bool withTypes=false, unsigned int recursionDepth=0);
		JVector<Object>* _keytable;
		JVector<Object>* _valtable;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif