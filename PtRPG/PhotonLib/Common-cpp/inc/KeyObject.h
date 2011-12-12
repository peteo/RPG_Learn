/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __KEY_OBJECT_H
#define __KEY_OBJECT_H

#include "ConfirmAllowedKey.h"

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
	template <typename Etype>
	class KeyObject : public Object
	{
	public:
		KeyObject(const KeyObject<Etype> &toCopy);
		KeyObject(const Object& obj);
		KeyObject(const Object* const obj);
		KeyObject(typename ConfirmAllowedKey<Etype>::type data);
		~KeyObject(void);

		KeyObject<Etype>& operator=(const KeyObject<Etype>& toCopy);
		KeyObject<Etype>& operator=(const Object& toCopy);

		Etype getDataCopy(void);
		Etype* getDataAddress(void);

	private:
		typedef Object super;

		void convert(const Object* const obj, nByte type);
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
	template<typename Etype>
	KeyObject<Etype>::KeyObject(const KeyObject<Etype>& toCopy) : Object(toCopy)
	{
	}



	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link Object>&.
	   
	   If the type of the content of the passed object does not
	   match the template overload of the object to create, an empty
	   \object is created instead of a copy of the passed object,
	   which leads to <link KeyObject::getDataCopy, getDataCopy()>
	   and <link KeyObject::getDataAddress, getDataAddress()> return
	   0.
	   Parameters
	   obj :  The <link Object>& to copy.                                 */
	template <typename Etype>
	KeyObject<Etype>::KeyObject(const Object& obj)
	{
		convert(&obj, ConfirmAllowedKey<Etype>::typeName);
	}



	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link Object>*.
	   
	   If the type of the content of the passed object does not
	   match the template overload of the object to create, an empty
	   \object is created instead of a copy of the passed object,
	   which leads to <link KeyObject::getDataCopy, getDataCopy()>
	   and <link KeyObject::getDataAddress, getDataAddress()> return
	   0.
	   Parameters
	   obj :  The <link Object>* to copy.                                 */
	template <typename Etype>
	KeyObject<Etype>::KeyObject(const Object* const obj)
	{
		convert(obj, ConfirmAllowedKey<Etype>::typeName);
	}



	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed Etype.
	   
	   Parameters
	   data :  The value to copy. Has to be of a supported type.         */
	template <typename Etype>
	KeyObject<Etype>::KeyObject(typename ConfirmAllowedKey<Etype>::type data)
	{
		set(&data, ConfirmAllowedKey<Etype>::typeName, 0, true);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DESTRUCTOR                                                                                                 //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   Destructor. */
	template <typename Etype>
	KeyObject<Etype>::~KeyObject(void)
	{
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// OPERATORS                                                                                                   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   Operator = : Makes a deep copy of its right operand into its
	   left operand. This overwrites old data in the left operand.  */
	template<typename Etype>
	KeyObject<Etype>& KeyObject<Etype>::operator=(const KeyObject<Etype>& toCopy)
	{
		return super::operator=(toCopy);
	}

	/* Summary
	   Operator = : Makes a deep copy of its right operand into its
	   left operand. This overwrites old data in the left operand.

	   If the type of the content of the right operand does not
	   match the template overload of the left operand, then the left
	   operand stays unchanged.  */
	template<typename Etype>
	KeyObject<Etype>& KeyObject<Etype>::operator=(const Object& toCopy)
	{
		if(ConfirmAllowedKey<Etype>::typeName == toCopy.getType())
			*this = super::operator=(toCopy);
		return *this;
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
	template <typename Etype>
	inline Etype KeyObject<Etype>::getDataCopy(void)
	{
		if(_type == ConfirmAllowedKey<Etype>::typeName)
			return *(Etype*)_data;
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
	template <typename Etype>
	inline Etype* KeyObject<Etype>::getDataAddress(void)
	{
		if(_type == ConfirmAllowedKey<Etype>::typeName)
			return (Etype*)_data;
		else
			return 0;
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// INTERNALS                                                                                                   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Etype>
	void KeyObject<Etype>::convert(const Object* const obj, nByte type)
	{
		if(obj && type == obj->getType())
			*this = *obj;
		else
		{
			_type = 0;
			_size = NULL;
			_dimensions = 0;
			_data = NULL;
		}
	}

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif