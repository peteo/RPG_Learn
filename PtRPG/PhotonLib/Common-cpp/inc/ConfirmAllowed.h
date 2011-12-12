/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __CONFIRM_ALLOWED_H
#define __CONFIRM_ALLOWED_H

#include "CompileTimeAssertTrue.h"
#include "IsDerivedFrom.h"
#include "Object.h"
#include "Hashtable.h"
#include "CustomType.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	template<typename CType> struct ConfirmAllowed
	{
		CompileTimeAssertTrue<IsDerivedFrom<CType, CustomType<CType::TypeCode> >::Is> failCompilingIfFalse;
		typedef CType type;
		typedef CType scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_CUSTOM;
		static const nByte customTypeName = CType::TypeCode;
	};
	template<> struct ConfirmAllowed<nByte>
	{
		typedef nByte type;
		typedef nByte scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_BYTE;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<short>
	{
		typedef short type;
		typedef short scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_SHORT;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<int>
	{
		typedef int type;
		typedef int scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_INTEGER;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<int64>
	{
		typedef int64 type;
		typedef int64 scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_LONG;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<float>
	{
		typedef float type;
		typedef float scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_FLOAT;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<double>
	{
		typedef double type;
		typedef double scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_DOUBLE;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<bool>
	{
		typedef bool type;
		typedef bool scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_BOOLEAN;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<JString>
	{
		typedef JString type;
		typedef JString scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<char*>
	{
		typedef char* type;
		typedef char* scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<EG_CHAR*>
	{
		typedef EG_CHAR* type;
		typedef EG_CHAR* scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_STRING;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<JVector<Object> >
	{
		typedef JVector<Object> type;
		typedef JVector<Object> scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_VECTOR;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<Hashtable>
	{
		typedef Hashtable type;
		typedef Hashtable scalarType;
		static const unsigned int dimensions = 0;
		static const nByte typeName = EG_HASHTABLE;
		static const nByte customTypeName = 0;
	};
	template<> struct ConfirmAllowed<Object*>
	{
		typedef Object* type;
		typedef Object scalarType;
		static const unsigned int dimensions = 1; // only supported as array!
		static const nByte typeName = EG_OBJECT;
		static const nByte customTypeName = 0;
	};
	template<typename CType> struct ConfirmAllowed<const CType>
	{
		typedef typename ConfirmAllowed<CType>::type type;
		typedef typename ConfirmAllowed<CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<CType>::dimensions;
		static const nByte typeName = ConfirmAllowed<CType>::typeName;
		static const nByte customTypeName = ConfirmAllowed<CType>::customTypeName;
	};
	template<typename CType> struct ConfirmAllowed<CType*>
	{
		typedef typename ConfirmAllowed<CType>::type* type;
		typedef typename ConfirmAllowed<CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<CType>::dimensions+1;
		static const nByte typeName = ConfirmAllowed<CType>::typeName;
		static const nByte customTypeName = ConfirmAllowed<CType>::customTypeName;
	};
	template<typename CType> struct ConfirmAllowed<const CType* const>
	{
		typedef typename ConfirmAllowed<const CType>::type* const type;
		typedef typename ConfirmAllowed<const CType>::scalarType scalarType;
		static const unsigned int dimensions = ConfirmAllowed<const CType>::dimensions+1;
		static const nByte typeName = ConfirmAllowed<const CType>::typeName;
		static const nByte customTypeName = ConfirmAllowed<CType>::customTypeName;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif