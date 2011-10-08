/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __VALUE_OBJECT_H
#define __VALUE_OBJECT_H

#include "Object.h"
#include "Hashtable.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	template<typename CType> struct ConfirmAllowed;
	template<> struct ConfirmAllowed<nByte>
	{
		typedef nByte type;
		typedef nByte scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_BYTE;
	};
	template<> struct ConfirmAllowed<short>
	{
		typedef short type;
		typedef short scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_SHORT;
	};
	template<> struct ConfirmAllowed<int>
	{
		typedef int type;
		typedef int scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_INTEGER;
	};
	template<> struct ConfirmAllowed<int64>
	{
		typedef int64 type;
		typedef int64 scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_LONG;
	};
	template<> struct ConfirmAllowed<float>
	{
		typedef float type;
		typedef float scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_FLOAT;
	};
	template<> struct ConfirmAllowed<double>
	{
		typedef double type;
		typedef double scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_DOUBLE;
	};
	template<> struct ConfirmAllowed<bool>
	{
		typedef bool type;
		typedef bool scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_BOOLEAN;
	};
	template<> struct ConfirmAllowed<JString>
	{
		typedef JString type;
		typedef JString scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
	};
	template<> struct ConfirmAllowed<char*>
	{
		typedef char* type;
		typedef char* scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
	};
	template<> struct ConfirmAllowed<wchar_t*>
	{
		typedef wchar_t* type;
		typedef wchar_t* scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
	};
	template<> struct ConfirmAllowed<JVector<Object> >
	{
		typedef JVector<Object> type;
		typedef JVector<Object> scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_VECTOR;
	};
	template<> struct ConfirmAllowed<Hashtable>
	{
		typedef Hashtable type;
		typedef Hashtable scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_HASHTABLE;
	};
	template<class CType> struct ConfirmAllowed<const CType>
	{
		typedef typename ConfirmAllowed<CType>::type type;
		typedef typename ConfirmAllowed<CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<CType>::dimensions;
		static const nByte typeName = ConfirmAllowed<CType>::typeName;
	};
	template<class CType> struct ConfirmAllowed<CType*>
	{
		typedef typename ConfirmAllowed<CType>::type* type;
		typedef typename ConfirmAllowed<CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<CType>::dimensions+1;
		static const nByte typeName = ConfirmAllowed<CType>::typeName;
	};
	template<class CType> struct ConfirmAllowed<const CType* const>
	{
		typedef typename ConfirmAllowed<const CType>::type* const type;
		typedef typename ConfirmAllowed<const CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<const CType>::dimensions+1;
		static const nByte typeName = ConfirmAllowed<const CType>::typeName;
	};



	/* Summary
	   Container class template for objects to be stored as values
	   in a Hashtable.
	   Description
	   Please refer to <link Hashtable> for more information and an
	   \example.                                                    */
	template<class Etype>
	class ValueObject:public Object
	{
	public:
		ValueObject(const ValueObject<Etype>& toCopy);

		ValueObject(const Object* const obj);

		ValueObject(nByte data);
		ValueObject(short data);
		ValueObject(int data);
		ValueObject(int64 data);
		ValueObject(float data);
		ValueObject(double data);
		ValueObject(bool data);
		ValueObject(const JString& data);
		ValueObject(const char* data);
		ValueObject(const wchar_t* data);
		ValueObject(const JVector<Object>& data);
		ValueObject(const Hashtable& data);

		ValueObject(typename ConfirmAllowed<Etype>::type data, short size);
		ValueObject(typename ConfirmAllowed<Etype>::type data, const short* const sizes);

		~ValueObject(void);

		Etype getDataCopy(void);
		Etype* getDataAddress(void);

	private:
		void convert(const Object* const obj, nByte type, unsigned int dimensions);
		ValueObject<Etype>& operator=(const ValueObject<Etype>& notToUse);
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
	ValueObject<Etype>::ValueObject(const ValueObject<Etype> &toCopy) : Object(toCopy)
	{
	}



	/* Summary
	   Constructor.

	   Creates an object out of a deep copy of the passed <link ExitGames::Object, Object>.

	   If the type of the content of the passed object does not
	   match the template overload of the object to create, an empty
	   \object is created instead of a copy of the passed object,
	   which leads to <link ExitGames::KeyObject::getDataCopy, getDataCopy()>
	   and <link ExitGames::KeyObject::getDataAddress, getDataAddress()>
	   return 0.
	   Parameters
	   obj :  The <link ExitGames::Object, Object> to copy.                                 */
	template <class Etype>
	ValueObject<Etype>::ValueObject(const Object* const obj)
	{
		convert(obj, ConfirmAllowed<Etype>::typeName, ConfirmAllowed<Etype>::dimensions);
	}



	/* Summary
	   Constructor.

	   Creates an object out of a deep copy of the passed nByte.

	   Exists only for the nByte template overload of this class.
	   Parameters
	   data : The nByte to copy.                                 */
	template <>
	inline ValueObject<nByte>::ValueObject(nByte data)
	{
		set(&data, EG_BYTE, true);
	}

	/* Summary
	   Constructor.

	   Creates an object out of a deep copy of the passed short.

	   Exists only for the short template overload of this class.
	   Parameters
	   data : The short to copy.                                 */
	template <>
	inline ValueObject<short>::ValueObject(short data)
	{
		set(&data, EG_SHORT, true);
	}

	/* Summary
	   Constructor.

	   Creates an object out of a deep copy of the passed int.

	   Exists only for the int template overload of this class.
	   Parameters
	   data : The int to copy.                                 */
	template <>
	inline ValueObject<int>::ValueObject(int data)
	{
		set(&data, EG_INTEGER, true);
	}

	/* Summary
	   Constructor.

	   Creates an object out of a deep copy of the passed int64.

	   Exists only for the int64 template overload of this class.
	   Parameters
	   data : The int64 to copy.                                 */
	template <>
	inline ValueObject<int64>::ValueObject(int64 data)
	{
		set(&data, EG_LONG, true);
	}

	/* Summary
	   Constructor.

	   Creates an object out of a copy of the passed float.

	   Exists only for the float template overload of this class.
	   Parameters
	   data : The float to copy.                                 */
	template <>
	inline ValueObject<float>::ValueObject(float data)
	{
		set(&data, EG_FLOAT, true);
	}

	/* Summary
	   Constructor.

	   Creates an object out of a copy of the passed double.

	   Exists only for the double template overload of this class.
	   Parameters
	   data : The double to copy.                                 */
	template <>
	inline ValueObject<double>::ValueObject(double data)
	{
		set(&data, EG_DOUBLE, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed bool.
	   
	   Exists only for the bool template overload of this class.
	   Parameters
	   data : The bool to copy.                                 */
	template <>
	inline ValueObject<bool>::ValueObject(bool data)
	{
		set(&data, EG_BOOLEAN, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link JString>.
	   
	   Exists only for the <link JString> template overload of this
	   class.
	   Parameters
	   data : The <link JString> to copy.                                */
	template <>
	inline ValueObject<JString>::ValueObject(const JString& data)
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
	inline ValueObject<JString>::ValueObject(const char* data)
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
	inline ValueObject<JString>::ValueObject(const wchar_t* data)
	{
		JString temp = data;
		set((void*)&temp, EG_STRING, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link JVector>\<<link Object>\>.
	   
	   Exists only for the <link JVector>\<<link Object>\>
	   template overload of this class.
	   Parameters
	   data : The <link JVector>\<<link Object>\> to copy.                                */
	template <>
	inline ValueObject<JVector<Object> >::ValueObject(const JVector<Object>& data)
	{
		set((void*)&data, EG_VECTOR, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed <link Hashtable>.
	   
	   Exists only for the <link Hashtable> template overload of
	   this class.
	   Parameters
	   data : The <link Hashtable> to copy.                                */
	template <>
	inline ValueObject<Hashtable>::ValueObject(const Hashtable& data)
	{
		set((void*)&data, EG_HASHTABLE, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed single-dimensional Etype-array.
	   
	   Parameters
	   data : The array to copy.
	   size : The element count of data.                               */
	template <class Etype>
	ValueObject<Etype>::ValueObject(typename ConfirmAllowed<Etype>::type data, short size)
	{
		set(data, ConfirmAllowed<Etype>::typeName, size, true);
	}

	/* Summary
	   Constructor.
	   
	   Creates an object out of a deep copy of the passed multi-dimensional Etype-array.
	   
	   Parameters
	   data  : The array to copy.
	   sizes : The array of element counts for the different dimensions of data.                               */
	template <class Etype>
	ValueObject<Etype>::ValueObject(typename ConfirmAllowed<Etype>::type data, const short* const sizes)
	{
		set(data, ConfirmAllowed<Etype>::typeName, ConfirmAllowed<Etype>::dimensions, sizes, true);
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DESTRUCTOR                                                                                                  //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   Destructor.*/
	template <class Etype>
	ValueObject<Etype>::~ValueObject(void)
	{
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// getDataCopy                                                                                                 //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Summary
	   \Returns a deep copy of the content of the object. If you
	   \only need access to the content, while the object still
	   exists, you can use <link ValueObject::getDataAddress, getDataAddress()>
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
	   return types and for arrays and empty objects for classes.
	   Returns
	   a deep copy of the content of the object if successful, 0 or
	   an empty object otherwise.                                               */
	template <>
	inline nByte ValueObject<nByte>::getDataCopy(void)
	{
		return (_type == EG_BYTE && !_dimensions)?*(nByte*)_data:0;
	}

	template <>
	inline short ValueObject<short>::getDataCopy(void)
	{
		return (_type == EG_SHORT && !_dimensions)?*(short*)_data:0;
	}

	template <>
	inline int ValueObject<int>::getDataCopy(void)
	{
		return (_type == EG_INTEGER && !_dimensions)?*(int*)_data:0;
	}

	template <>
	inline int64 ValueObject<int64>::getDataCopy(void)
	{
		return (_type == EG_LONG && !_dimensions)?*(int64*)_data:0;
	}

	template <>
	inline float ValueObject<float>::getDataCopy(void)
	{
		return (_type == EG_FLOAT && !_dimensions)?*(float*)_data:0;
	}

	template <>
	inline double ValueObject<double>::getDataCopy(void)
	{
		return (_type == EG_DOUBLE && !_dimensions)?*(double*)_data:0;
	}

	template <>
	inline bool ValueObject<bool>::getDataCopy(void)
	{
		return (_type == EG_BOOLEAN && !_dimensions)?*(bool*)_data:false;
	}

	template <>
	inline JString ValueObject<JString>::getDataCopy(void)
	{
		return (_type == EG_STRING && !_dimensions)?*(JString*)_data:JString("");
	}

	template <>
	inline JVector<Object> ValueObject<JVector<Object> >::getDataCopy(void)
	{
		return (_type == EG_VECTOR && !_dimensions)?JVector<Object>(*(JVector<Object>*)_data):JVector<Object>();
	}

	template <>
	inline Hashtable ValueObject<Hashtable>::getDataCopy(void)
	{
		return (_type == EG_HASHTABLE && !_dimensions)?Hashtable(*(Hashtable*)_data):Hashtable();
	}

	template <>
	inline nByte* ValueObject<nByte*>::getDataCopy(void)
	{
		return (_type == EG_BYTE && _dimensions == 1)?(nByte*)EG_duplicateDataArray(_data, EG_BYTE, *_size):0;
	}

	template <>
	inline short* ValueObject<short*>::getDataCopy(void)
	{
		return (_type == EG_SHORT && _dimensions == 1)?(short*)EG_duplicateDataArray(_data, EG_SHORT, *_size):0;
	}

	template <>
	inline int* ValueObject<int*>::getDataCopy(void)
	{
		return (_type == EG_INTEGER && _dimensions == 1)?(int*)EG_duplicateDataArray(_data, EG_INTEGER, *_size):0;
	}

	template <>
	inline int64* ValueObject<int64*>::getDataCopy(void)
	{
		return (_type == EG_LONG && _dimensions == 1)?(int64*)EG_duplicateDataArray(_data, EG_LONG, *_size):0;
	}

	template <>
	inline float* ValueObject<float*>::getDataCopy(void)
	{
		return (_type == EG_FLOAT && _dimensions == 1)?(float*)EG_duplicateDataArray(_data, EG_FLOAT, *_size):0;
	}

	template <>
	inline double* ValueObject<double*>::getDataCopy(void)
	{
		return (_type == EG_DOUBLE && _dimensions == 1)?(double*)EG_duplicateDataArray(_data, EG_DOUBLE, *_size):0;
	}

	template <>
	inline bool* ValueObject<bool*>::getDataCopy(void)
	{
		return (_type == EG_BOOLEAN && _dimensions == 1)?(bool*)EG_duplicateDataArray(_data, EG_BOOLEAN, *_size):0;
	}

	template <>
	inline JString* ValueObject<JString*>::getDataCopy(void)
	{
		if(_type == EG_STRING && _dimensions == 1)
		{
			JString* temp = new JString[*_size];
			for(short i=0; i<*_size; i++)
				temp[i] = (((JString*)(_data))[i]);
			return temp;
		}
		else
			return 0;
	}

	template <>
	inline Hashtable* ValueObject<Hashtable*>::getDataCopy(void)
	{
		if(_type == EG_HASHTABLE && _dimensions == 1)
		{
			Hashtable* temp = new Hashtable[*_size];
			for(short i=0; i<*_size; i++)
				temp[i] = (((Hashtable*)(_data))[i]);
			return temp;
		}
		else
			return 0;
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
	inline nByte* ValueObject<nByte>::getDataAddress(void)
	{
		return (_type == EG_BYTE && !_dimensions)?(nByte*)_data:0;
	}

	template <>
	inline short* ValueObject<short>::getDataAddress(void)
	{
		return (_type == EG_SHORT && !_dimensions)?(short*)_data:0;
	}

	template <>
	inline int* ValueObject<int>::getDataAddress(void)
	{
		return (_type == EG_INTEGER && !_dimensions)?(int*)_data:0;
	}

	template <>
	inline int64* ValueObject<int64>::getDataAddress(void)
	{
		return (_type == EG_LONG && !_dimensions)?(int64*)_data:0;
	}

	template <>
	inline float* ValueObject<float>::getDataAddress(void)
	{
		return (_type == EG_FLOAT && !_dimensions)?(float*)_data:0;
	}

	template <>
	inline double* ValueObject<double>::getDataAddress(void)
	{
		return (_type == EG_DOUBLE && !_dimensions)?(double*)_data:0;
	}

	template <>
	inline bool* ValueObject<bool>::getDataAddress(void)
	{
		return (_type == EG_BOOLEAN && !_dimensions)?(bool*)_data:0;
	}

	template <>
	inline JString* ValueObject<JString>::getDataAddress(void)
	{
		return (_type == EG_STRING && !_dimensions)?(JString*)_data:0;
	}

	template <>
	inline JVector<Object>* ValueObject<JVector<Object> >::getDataAddress(void)
	{
		return (_type == EG_VECTOR && !_dimensions)?(JVector<Object>*)_data:0;
	}

	template <>
	inline Hashtable* ValueObject<Hashtable>::getDataAddress(void)
	{
		return (_type == EG_HASHTABLE && !_dimensions)?(Hashtable*)_data:0;
	}

	template <>
	inline nByte** ValueObject<nByte*>::getDataAddress(void)
	{
		return (_type == EG_BYTE && _dimensions == 1)?(nByte**)&_data:0;
	}
	template <>
	inline short** ValueObject<short*>::getDataAddress(void)
	{
		return (_type == EG_SHORT && _dimensions == 1)?(short**)&_data:0;
	}

	template <>
	inline int** ValueObject<int*>::getDataAddress(void)
	{
		return (_type == EG_INTEGER && _dimensions == 1)?(int**)&_data:0;
	}

	template <>
	inline int64** ValueObject<int64*>::getDataAddress(void)
	{
		return (_type == EG_LONG && _dimensions == 1)?(int64**)&_data:0;
	}

	template <>
	inline float** ValueObject<float*>::getDataAddress(void)
	{
		return (_type == EG_FLOAT && _dimensions == 1)?(float**)&_data:0;
	}

	template <>
	inline double** ValueObject<double*>::getDataAddress(void)
	{
		return (_type == EG_DOUBLE && _dimensions == 1)?(double**)&_data:0;
	}

	template <>
	inline bool** ValueObject<bool*>::getDataAddress(void)
	{
		return (_type == EG_BOOLEAN && _dimensions == 1)?(bool**)&_data:0;
	}

	template <>
	inline JString** ValueObject<JString*>::getDataAddress(void)
	{
		return (_type == EG_STRING && _dimensions == 1)?(JString**)&_data:0;
	}

	template <>
	inline Hashtable** ValueObject<Hashtable*>::getDataAddress(void)
	{
		return (_type == EG_HASHTABLE && _dimensions == 1)?(Hashtable**)&_data:0;
	}

	template <class Etype>
	Etype* ValueObject<Etype>::getDataAddress(void)
	{
		return (_type == ConfirmAllowed<Etype>::typeName && _dimensions == ConfirmAllowed<Etype>::dimensions)?(Etype*)&_data:0;
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// INTERNALS                                                                                                   //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<class Etype>
	void ValueObject<Etype>::convert(const Object* const obj, nByte type, unsigned int dimensions)
	{
		if(obj)
		{
			if(type == obj->getType() && dimensions == obj->getDimensions())
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