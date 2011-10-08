/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __KEY_OBJECT_H
#define __KEY_OBJECT_H

#include "Object.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	/* Summary
	   Container class template for objects to be stored as keys in
	   a Hashtable.
	   Description
	   Please refer to <link Hashtable> for more information and an
	   \example.                                                    */
	template <class Etype>
	class KeyObject:public Object
	{
	public:
		KeyObject(const KeyObject<Etype> &toCopy);

		KeyObject(const Object* const obj);

		KeyObject(nByte data);
		KeyObject(short data);
		KeyObject(int data);
		KeyObject(int64 data);
		KeyObject(const JString& data);
		KeyObject(const char* data);
		KeyObject(const wchar_t* data);

		~KeyObject(void);

		Etype getDataCopy(void);
		Etype* getDataAddress(void);

	private:
		void convert(const Object* const obj, nByte type);

		KeyObject<Etype>& operator=(const KeyObject<Etype>& notToUse);
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS                                                                                                //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   Copy-Constructor.

	   Creates an object out of a deep copy of its parameter.

	   The parameter has to be of the same template overload as the
	   \object, you want to create.
	   Parameters
	   toCopy :  The object to copy.                                */
	template<class Etype>
	KeyObject<Etype>::KeyObject(const KeyObject<Etype>& toCopy) : Object(toCopy)
	{
	}



	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link Object>.
	   
	   If the type of the content of the passed object does not
	   match the template overload of the object to create, an empty
	   \object is created instead of a copy of the passed object,
	   which leads to <link KeyObject::getDataCopy, getDataCopy()>
	   and <link KeyObject::getDataAddress, getDataAddress()> return
	   0.
	   Parameters
	   obj :  The <link Object> to copy.                                 */
	template<>
	inline KeyObject<nByte>::KeyObject(const Object* const obj)
	{
		convert(obj, EG_BYTE);
	}

	template<>
	inline KeyObject<short>::KeyObject(const Object* const obj)
	{
		convert(obj, EG_SHORT);
	}

	template<>
	inline KeyObject<int>::KeyObject(const Object* const obj)
	{
		convert(obj, EG_INTEGER);
	}

	template<>
	inline KeyObject<int64>::KeyObject(const Object* const obj)
	{
		convert(obj, EG_LONG);
	}

	template<>
	inline KeyObject<JString>::KeyObject(const Object* const obj)
	{
		convert(obj, EG_STRING);
	}



	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed nByte.
	   
	   Exists only for the nByte template overload of this class.
	   Parameters
	   data :  The nByte to copy.                                 */
	template <>
	inline KeyObject<nByte>::KeyObject(nByte data)
	{
		set((void*)&data, EG_BYTE, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed short.
	   
	   Exists only for the short template overload of this class.
	   Parameters
	   data :  The short to copy.                                 */
	template <>
	inline KeyObject<short>::KeyObject(short data)
	{
		set((void*)&data, EG_SHORT, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed int.
	   
	   Exists only for the int template overload of this class.
	   Parameters
	   data :  The int to copy.                                 */
	template <>
	inline KeyObject<int>::KeyObject(int data)
	{
		set((void*)&data, EG_INTEGER, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed int64.
	   
	   Exists only for the int64 template overload of this class.
	   Parameters
	   data :  The int64 to copy.                                 */
	template <>
	inline KeyObject<int64>::KeyObject(int64 data)
	{
		set((void*)&data, EG_LONG, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link JString>.
	   
	   Exists only for the <link JString> template overload of this
	   class.
	   Parameters
	   data :  The <link JString> to copy.                                */
	template <>
	inline KeyObject<JString>::KeyObject(const JString& data)
	{
		set((void*)&data, EG_STRING, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed char*, which is implicitly converted into a <link JString>.
	   
	   Exists only for the <link JString> template overload of this
	   class.
	   Parameters
	   data :  The <link JString> to copy.                                */
	template <>
	inline KeyObject<JString>::KeyObject(const char* data)
	{
		JString temp = data;
		set((void*)&temp, EG_STRING, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed wchar_t*, which is implicitly converted into a <link JString>.
	   
	   Exists only for the <link JString> template overload of this
	   class.
	   Parameters
	   data :  The <link JString> to copy.                                */
	template <>
	inline KeyObject<JString>::KeyObject(const wchar_t* data)
	{
		JString temp = data;
		set((void*)&temp, EG_STRING, true);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DESTRUCTOR                                                                                                 //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   Destructor. */
	template <class Etype>
	KeyObject<Etype>::~KeyObject(void)
	{
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// getDataCopy                                                                                                 //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   \Returns a deep copy of the content of the object. If you
	   \only need access to the content, while the object still
	   exists, you can use <link KeyObject::getDataAddress, getDataAddress()>
	   instead to avoid the deep copy. That is especially
	   interesting for large content, of course.
	   
	   If successful, the template overloads for array types of this
	   method allocate the data for the copy, so you have to free
	   (for arrays of primitive types) or delete (for arrays of
	   class objects) it, as soon, as you do not need the array
	   anymore. All non-array copies free there memory
	   automatically, as soon as they leave their scope, same as the
	   single indices of the array, as soon, as the array is freed.
	   
	   In case of an error this function returns 0 for primitive
	   return types and empty objects for classes.
	   Returns
	   a deep copy of the content of the object if successful, 0 or
	   an empty object otherwise.                                             */
	template <>
	inline nByte KeyObject<nByte>::getDataCopy(void)
	{
		if(_type == EG_BYTE)
			return *(nByte*)_data;
		else
			return 0;
	}

	template <>
	inline short KeyObject<short>::getDataCopy(void)
	{
		if(_type == EG_SHORT)
			return *(short*)_data;
		else
			return 0;
	}

	template <>
	inline int KeyObject<int>::getDataCopy(void)
	{
		if(_type == EG_INTEGER)
			return *(int*)_data;
		else
			return 0;
	}

	template <>
	inline int64 KeyObject<int64>::getDataCopy(void)
	{
		if(_type == EG_LONG)
			return *(int64*)_data;
		else
			return 0;
	}

	template <>
	inline JString KeyObject<JString>::getDataCopy(void)
	{
		if(_type == EG_STRING)
			return *(JString*)_data;
		else
			return JString("");
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// getDataAddress                                                                                              //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   \Returns the address of the original content of the object.
	   If you need access to the data above lifetime of the object,
	   call <link KeyObject::getDataCopy, getDataCopy()>.
	   
	   The return type is a pointer to the data, so it is a
	   double-pointer, of course, for template overloads, which data
	   already is a pointer.
	   
	   In case of an error, this method returns 0.
	   Returns
	   the address of the original content of the object, if
	   successful, 0 otherwise.                                      */
	template <>
	inline nByte* KeyObject<nByte>::getDataAddress(void)
	{
		if(_type == EG_BYTE)
			return (nByte*)_data;
		else
			return 0;
	}

	template <>
	inline short* KeyObject<short>::getDataAddress(void)
	{
		if(_type == EG_SHORT)
			return (short*)_data;
		else
			return 0;
	}

	template <>
	inline int* KeyObject<int>::getDataAddress(void)
	{
		if(_type == EG_INTEGER)
			return (int*)_data;
		else
			return 0;
	}

	template <>
	inline int64* KeyObject<int64>::getDataAddress(void)
	{
		if(_type == EG_LONG)
			return (int64*)_data;
		else
			return 0;
	}

	template <>
	inline JString* KeyObject<JString>::getDataAddress(void)
	{
		if(_type == EG_STRING)
			return (JString*)_data;
		else
			return 0;
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// INTERNALS                                                                                                   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class Etype>
	void KeyObject<Etype>::convert(const Object* const obj, nByte type)
	{
		if(obj)
		{
			if(type == obj->getType())
			{
				_type = 0;
				Object* temp = this;
				*temp = *obj;
			}
			else
			{
				_type = 0;
				_size = 0;
				_dimensions = 0;
				_data = 0;
			}
		}
		else
		{
			_type = 0;
			_size = 0;
			_dimensions = 0;
			_data = 0;
		}
	}

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif