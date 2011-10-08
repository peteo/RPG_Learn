/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2010 by Exit Games. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __GP_OPERATION_H
	#define __GP_OPERATION_H

	#include "data_structures.h"

	#ifdef __cplusplus
		extern "C"
		{
	#endif

		void EG_writeShort(EG_GpOperation* op, short val);
		void EG_writeInt(EG_GpOperation* op, int val);
		void EG_writeByte(EG_GpOperation* op, nByte val);
		void EG_writeBoolean(EG_GpOperation* op, bool bol);
		void EG_writeLong(EG_GpOperation* op, int64 lng);
		void EG_writeFloat(EG_GpOperation* op, float val);
		void EG_writeDouble(EG_GpOperation* op, double val);
		bool EG_serialize(EG_GpOperation* op, EG_Object* serObject, bool setType, bool protocolOneFive);
		void EG_serializeString(EG_GpOperation* op, EG_CHAR** str, bool setType);
		void EG_serializeStringArray(EG_GpOperation* op, EG_CHAR** strArr, short length, bool setType);
		void EG_serializeByteArray(EG_GpOperation* op, nByte* byteArr, short length, bool setType);
		void EG_serializeIntArray(EG_GpOperation* op, int* intArr, short length, bool setType);
		bool EG_serializeHashTable(EG_GpOperation* op, EG_HashTable* hash, bool setType, bool protocolOneFive);
		void EG_serializeVector(EG_GpOperation* op, EG_Vector* vect, bool setType);
		void EG_serializeBoolean(EG_GpOperation* op, bool* bol, bool setType);
		void EG_serializeByte(EG_GpOperation* op, nByte* bt, bool setType);
		void EG_serializeShort(EG_GpOperation* op, short* srt, bool setType);
		void EG_serializeInteger(EG_GpOperation* op, int* in, bool setType);
		void EG_serializeLong(EG_GpOperation* op, int64* lng, bool setType);
		void EG_serializeFloat(EG_GpOperation* op, float* flt, bool setType);
		void EG_serializeDouble(EG_GpOperation* op, double* dbl, bool setType);
		bool EG_serializeArrayObject_15(EG_GpOperation* op, EG_Object* obj);
		bool EG_serializeArrayObject_15Helper(EG_GpOperation* op, void* pData, nByte type, unsigned int dimensions, short* arraySizes, unsigned int recursionDepth);

		bool EG_ReadBoolean(EG_GpOperation* op);
		short EG_ReadShort(EG_GpOperation* op);
		int EG_ReadInt(EG_GpOperation* op);
		int64 EG_ReadLong(EG_GpOperation* op);
		nByte EG_ReadByte(EG_GpOperation* op);
		float EG_ReadFloat(EG_GpOperation* op);
		double EG_ReadDouble(EG_GpOperation* op);

		EG_Object* EG_Deserialize(EG_GpOperation* op);
		EG_Object* EG_DeserializeType(EG_GpOperation* op, nByte param);
		EG_Object* EG_DeserializeVector(EG_GpOperation* op);
		EG_Object* EG_DeserializeHashTable(EG_GpOperation* op);
		EG_HashTable EG_DeserializeHashTableHelper(EG_GpOperation* op);
		EG_Object* EG_DeserializeString(EG_GpOperation* op);
		EG_Object* EG_DeserializeInteger(EG_GpOperation* op);
		EG_Object* EG_DeserializeByte(EG_GpOperation* op);
		EG_Object* EG_DeserializeByteArray(EG_GpOperation* op);
		EG_Object* EG_DeserializeBoolean(EG_GpOperation* op);
		EG_Object* EG_DeserializeShort(EG_GpOperation* op);
		EG_Object* EG_DeserializeIntArray(EG_GpOperation* op);
		EG_Object* EG_DeserializeStringArray(EG_GpOperation* op);
		EG_CHAR* EG_DeserializeStringHelper(EG_GpOperation* op);
		EG_Object* EG_DeserializeLong(EG_GpOperation* op);
		EG_Object* EG_DeserializeArray_15(EG_GpOperation* op);
		EG_Object* EG_DeserializeFloat(EG_GpOperation* op);
		EG_Object* EG_DeserializeDouble(EG_GpOperation* op);



		bool EG_GpserializeData(EG_GpOperation* op, bool protocolOneFive);
		void EG_GpdeserializeData(EG_GpOperation* op);

		void EG_setUrl(EG_GpOperation* op, char* url);
		void EG_setOpType(EG_GpOperation* op, nByte opType);
		void EG_setDoDeserialize(EG_GpOperation* op, bool doDeserialize);
		void EG_setOperation(EG_GpOperation* op, nByte operation);
		nByte EG_getOperation(EG_GpOperation* op);
		void EG_addParameter(EG_GpOperation* op, nByte param, EG_Object* serObject);
		void EG_ReleaseGpOperation(EG_GpOperation* gp);

		EG_Object* EG_getRetVal(EG_GpOperation* op, nByte retVal);
		EG_HashTable* EG_getRetVals(EG_GpOperation* op);
		EG_HashTable* EG_getParameters(EG_GpOperation* op);

		
	#ifdef __cplusplus
		}
	#endif 

#endif