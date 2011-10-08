/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

/* Summary
This file contains the helper methods for
creating/initializing
 * EG_Vector,
 * EG_Object and
 * EG_Hashtable.
See Also
see section <link Topic1, Neutron Data Structures> for
details.                                               */

#ifndef __DATASTRUCTURES_H
	#define __DATASTRUCTURES_H

	#include "platformLayer.h"


	/* <title EG_Object structure>
	   <toctitle EG_Object structure>
	   
	   Summary
	   EG_Object is a structure that encapsulates objects of all
	   common data types, so that they can be transmitted over the
	   Neutron platform.
	   Description
	   <c>typedef struct _EG_Object</c>
	   
	   <c>{</c>
	   
	   <c> void *obj_data;</c>
	   
	   <c> nByte type;</c>
	   
	   <c> int size;</c>
	   
	   <c>} EG_Object;</c>
	   
	   
	   
	   The first property is a generic pointer(void*) that points to
	   the data payload. The payload data can be of any supported
	   data type as shown below. The second property is an id that
	   describes the type of data, like #defined in constants.h and
	   listed below:
	   
	   <table noborder>
	   basic type Exitgames ID
	   \
	   nByte EG_BYTE
	   short EG_SHORT
	   int EG_INTEGER
	   int64 EG_LONG
	   float EG_FLOAT
	   double EG_DOUBLE
	   bool EG_BOOLEAN
	   EG_CHAR* EG_STRING
	   EG_Vector EG_VECTOR
	   EG_HashTable EG_HASHTABLE
	   </table>
	   * ------------- --------------- *
	   
	   
	   
	   
	   
	   The last property is 'size' which defines the total number of
	   elements present in that Object (only needed for arrays).
	   
	   To create EG_Objects there are three different functions:
	   
	   \1. Use <link EG_Object_create@void*@nByte@bool, EG_Object_create()>
	   to create EG_Objects holding non-array data.
	   
	   \2. Use <link EG_Object_createFromArray@void*@nByte@short@bool, EG_Object_createFromArray()>
	   for creating objects holding single-dimensional arrays
	   
	   \2. Use <link EG_Object_createFromMultiDimensionalArray@void*@nByte@int@short*@bool, EG_Object_createFromMultiDimensionalArray()>
	   for creating objects holding multi-dimensional arrays.
	   
	   
	   
	   \Note: Exit Games structures are not packed using the
	   __packed and #pragma commands.
	   Example
	   These examples create and delete an EG_Object for 'String':
	   In first example the object gets a full copy of your data. In
	   second example the object only gets a pointer to your data.
	   We recommend to use the second way carefully and only if size
	   \of data allows no full copy.
	   
	   <code lang="c++">
	   EG_CHAR* data = L"fifteen cans of Stella !";
	   EG_Object* sample = EG_Object_create(&data, EG_STRING, true); // creates an object with its own copy of the data
	     // ...
	     // usage of the object
	     // ...
	   EG_Object_delete(sample); // this frees the object and releases the memory allocated for the internal copy
	   
	   EG_CHAR* data = (EG_CHAR*)MALLOC(sizeof(EG_CHAR)*((WCSLEN(L"fifteen cans of Stella !"))+1));
	   WCSCPY(data, L"fifteen cans of Stella !");
	   EG_Object* sample = EG_Object_create(&data, EG_STRING, false);  // false = no copy! we store the pointer to the original data instead
	   // ...
	   // usage of the object
	   // ...
	   // EG_Object_delete(sample); // you MUST NOT free 'data', it is done in EG_Object_delete() here!
	   </code>
	   See Also
	   <link MemoryManagement, Sending and receiving data> , <link EG_Object_create@void*@nByte@bool, EG_Object_create()>
	   , <link EG_Object_createFromArray@void*@nByte@short@bool, EG_Object_createFromArray()>
	   , <link EG_Object_createFromMultiDimensionalArray@void*@nByte@int@short*@bool, EG_Object_createFromMultiDimensionalArray()>,
	   <link EG_Object_delete@EG_Object*, EG_Object_delete()> , <link EG_Object_compare@EG_Object*@EG_Object*, EG_Object_compare()>                */
	typedef struct _EG_Object
	{
		void* obj_data; //  The data to be hold by the object.
		nByte type; //  The data type of the data
		unsigned int dimensions; // number of array dimensions for multidimensional arrays; this is always 1 for 1-dimensional arrays and 0 for non-array types
		short* size; //  Nr. of elements of the type 'type' contained in obj_data. If 'dimensions' is 0, this is a pointer to 1, otherwise it is an array of 'dimensions' length, holding the size of the array in every dimension
	} EG_Object;

	#ifdef __cplusplus
		extern "C"
		{
	#endif

			nByte EG_Object_getType(EG_Object* obj);
			int EG_Object_getDimensions(EG_Object* obj);
			short* EG_Object_getSize(EG_Object* obj);
			EG_Object* EG_Object_create(void* obj_data, nByte type, bool cloneData);
			EG_Object* EG_Object_createFromArray(void* obj_data, nByte type, short arraySize, bool cloneData);
			EG_Object* EG_Object_createFromMultiDimensionalArray(void* obj_data, nByte type, unsigned int dimensions, short* arraySizes, bool cloneData);
			void EG_Object_delete(EG_Object* obj);
			void EG_Object_internal_deleteHelper(void* pData, nByte type, unsigned int dimensions, short* arraySizes, unsigned int recursionDepth);
			bool EG_Object_compare(EG_Object* obj1, EG_Object* obj2);
			bool EG_Object_internal_compareHelper(void* pData1, void* pData2, nByte type, unsigned int dimensions, short* arraySizes, unsigned int recursionDepth);
			void* EG_duplicateData(void* pData, nByte type);
			void* EG_duplicateDataArray(void* pData, nByte type, short arraySize);
			void* EG_duplicateMultiDimensionalDataArray(void* pData, nByte type, unsigned int dimensions, short* arraySizes);
			void* EG_internal_duplicateMultiDimensionalDataArray_Helper(void* pArrayOut, void* pArrayIn, nByte type, unsigned int dimensions, short* arraySizes, unsigned int recursionDepth);
			// internal
			typedef struct _SPhotonCommand IPhotonCommand;
			extern unsigned int PhotonCommand_Release(IPhotonCommand* pCommand);

	#ifdef __cplusplus
		}
	#endif
	#define CREATE_OBJECT(obj_data, type) EG_Object_create(obj_data, type, false)
	#define CREATE_OBJECT_FROM_ARRAY(obj_data, type, arraySize) EG_Object_createFromArray(obj_data, type, arraySize, false)

	#define addHashTableEntry					 EG_HashTable_addEntry
	#define addVectorElement                     EG_Vector_addElement
	#define clearHashTable                       EG_HashTable_clear
	#define compareEGObjects                     EG_Object_compare 
	#define createObject                         EG_Object_create
	#define createObjectFromArray                EG_Object_createFromArray
	#define deleteObject                         EG_Object_delete
	#define duplicateDataArray                   EG_duplicateDataArray
	#define duplicateData                        EG_duplicateData
	#define getLastVectorElement                 EG_Vector_getLastElement
	#define getLastVectorIndex                   EG_Vector_getLastIndex
	#define getObjectType                        EG_Object_getType
	#define getValFromKey                        EG_HashTable_getValFromKey
	#define initializeHashTable                  EG_HashTable_initialize
	#define initializeVector                     EG_Vector_initialize
	#define releaseVector                        EG_Vector_release
	#define removeHashTableEntry                 EG_HashTable_removeEntry
	#define removeVectorElement                  EG_Vector_removeElement
	#define toString                             EG_HashTable_toString

	/* <title EG_Vector structure>
	   <toctitle EG_Vector structure>
	   
	   Summary
	   Implements an automatically re-sizing array of objects.
	   
	   Only supported by Neutron, not by Photon!
	   Description
	   Like an array, it contains components that can be accessed
	   using an integer index. The size of a Vector can grow or
	   shrink as needed to accommodate adding and removing items
	   after the Vector has been created.
	   
	   It contains 2 properties. The first property is elements
	   which contains the address of array of
	   EG-Objects(EG_Object**). Object May be any type either it can
	   be hashtable ,EG-objects or vector itself. Second Property is
	   the total number of elements present in that vector.
	   
	   \Note: Exit Games Neutron structures are not packed using the
	   __packed and #pragma commands.
	   
	   
	   
	   <b><i>Please note that although it's possible to store data
	   \of different types in the same Vector, this is not conform
	   to the Neutron Server's protocol. To comply with the
	   protocol, all EG_Objects in the EG_Vector have to contain the
	   same data type, e.g. EG_STRING.</i></b>
	   Example
	   This example creates a EG_Vector and add a data as string.
	   
	   <code>
	   //Create and initialize the vector.
	   EG_Vector* sv = NULL;
	   EG_Vector_initialize(&amp;sv);
	   
	   EG_CHAR* data = L"TEST";
	   
	   EG_Object* sample = EG_Object_create((void*)data, EG_STRING, true);
	   EG_Vector_addElement(&amp;sv, sample);
	   </code>
	   See Also
	   <link EG_Object> , <link EG_Vector_getLastIndex@EG_Vector**, EG_Vector_getLastIndex()>
	   , <link EG_Vector_getLastElement@EG_Vector**, EG_Vector_getLastElement()>
	   , <link EG_Vector_release@EG_Vector**, EG_Vector_release()> ,
	   <link EG_Vector_initialize@EG_Vector**, EG_Vector_initialize()>                        */
	typedef struct _EG_Vector
	{
		EG_Object** elements; // Elements contained in the vector. Implemented as a dynamic array.
		uint16 totalElements; // Total number of elements in the elements array.

	} EG_Vector;

	#ifdef __cplusplus
		extern "C"
		{
	#endif 

		bool EG_Vector_initialize(EG_Vector** sv);
		void EG_Vector_release(EG_Vector** sv);
		int EG_Vector_getLastIndex(EG_Vector** sv);
		void *EG_Vector_getLastElement(EG_Vector** sv);
		bool EG_Vector_addElement(EG_Vector** sv, EG_Object* wstr);
		void EG_Vector_removeElement(EG_Vector** sv, int indx);

	#ifdef __cplusplus
		}
	#endif 

	/* <title EG_HashTable structure>
	   <toctitle EG_HashTable structure>
	   
	   Summary
	   The EG_HashTable structure implements a the well-known
	   "Hashtable" (or "Hashmap") container structure, used for
	   mapping keys to values.
	   Description
	   Both keys and values of an EG_HashTable have to be data
	   strucures of type EG_Object. The EG_Objects used as values
	   can contain any basic type supported by EG_Object, whereas
	   the EG_Objects used as keys can only contain one if the
	   following types:
	   
	   <table noborder>
	   nByte    EG_BYTE
	   short    EG_SHORT
	   int      EG_INTEGER
	   int64    EG_LONG
	   EG_CHAR* EG_STRING
	   </table>
	   
	   Internally the EG_HashTable struct consists of three
	   properties that affect its efficiency: If many entries are to
	   be inserted into a Hashtable, creating it with a sufficiently
	   large capacity may allow the entries to be inserted more
	   efficiently than letting it perform automatic rehashing as
	   needed to grow the table.
	   
	   The 1st and 2nd properties are the EG_Vectors containing the
	   keys and values. The third property contains the total number
	   \of elements included in the hashtable.
	   
	   
	   
	   \Note: Exit Games Neutron structures are not packed using the
	   __packed and #pragma commands.
	   Example
	   This example creates an EG_Hashtable and adds a 'key' and
	   'value' in that:
	   
	   <code>
	   //Creating Hash Table
	   EG_Hashtable hash;
	   EG_HashTable_initialize(&amp;hash);
	   
	   //Creating Key
	   EG_CHAR* key = L"USERID";
	   
	   //Creating Value
	   EG_CHAR* val = L"Exit-GB";
	   
	   //Creating key and value Object
	   EG_Object* keyObj = EG_Object_create((void*)key, EG_STRING, true);
	   EG_Object* valObj = EG_Object_create((void*)val, EG_STRING, true);
	   
	   //Add Entry in Hashtable
	   EG_HashTable_addEntry(&amp;hash, keyObj, valObj);
	   </code>
	   See Also
	   <link EG_Object> , <link EG_HashTable_initialize@EG_HashTable*, EG_HashTable_initialize()>
	   , <link EG_HashTable_addEntry@EG_HashTable*@EG_Object*@EG_Object*, EG_HashTable_addEntry()>
	   , <link EG_HashTable_removeEntry@EG_HashTable*@EG_Object*, EG_HashTable_removeEntry()>
	   , <link EG_HashTable_clear@EG_HashTable*, EG_HashTable_clear()>
	   , <link EG_HashTable_toString@EG_HashTable*, EG_HashTable_toString()>                       */
	typedef struct _EG_HashTable
	{
		EG_Vector* Key; // EG_Vector specifying the key of the hash table
		EG_Vector* Val; // EG_Vector specifying the  value corresponding to above key.
		short numElements; // Number of elements (key-value pairs) holded by the hash table.

	} EG_HashTable;

	#ifdef __cplusplus
		extern "C"
		{
	#endif

		void EG_HashTable_addEntry(EG_HashTable* hashtable, EG_Object* Key, EG_Object* Val);
		void EG_HashTable_removeEntry(EG_HashTable* hashtable, EG_Object* Key);
		void EG_HashTable_initialize(EG_HashTable* hashtable);
		void EG_HashTable_clear(EG_HashTable* hashtable);
		EG_Object* EG_HashTable_getValFromKey(EG_HashTable* hashtable, void* key, nByte type, int* hashIndex);
		EG_CHAR* EG_HashTable_toString(EG_HashTable* hashtable);
		EG_CHAR* EG_HashTable_toStringWithTypes(EG_HashTable* hashtable, bool withTypes);
		EG_CHAR* EG_HashTable_internal_appendData(EG_CHAR* data, bool withTypes, void* pData, nByte type, unsigned int dimensions, short* arraySizes, unsigned int recursionDepth);

	#ifdef __cplusplus
		}
	#endif



	#ifdef __cplusplus
		extern "C"
		{
	#endif 
		bool EG_Time_Less(unsigned int firstTime, unsigned int secondTime);
		bool EG_Time_Greater(unsigned int firstTime, unsigned int secondTime);
		bool EG_Time_LessOrEqual(unsigned int firstTime, unsigned int secondTime);
		bool EG_Time_GreaterOrEqual(unsigned int firstTime, unsigned int secondTime);
		int EG_Time_Difference(unsigned int firstTime, unsigned int secondTime);
		bool EG_Time_Overflowed(unsigned int firstTime, unsigned int secondTime);
	#ifdef __cplusplus
		}
	#endif


	typedef struct _EG_GpOperation
	{
		nByte opType; // The type of the operation.
		nByte opCode; // The operation code.
		short invocID; // Invocation Id
		bool doDeserialize; // Flag for Deserialization
		int returnCode; // return code of the operation.
		int debugOpCount;
		int debugSerCount;
		int bytesWritten;
		int bytePointer;
		char* url;
		nByte* pszPostData; // Data in sending Buffer..
		nByte* pszResponseData; // Data in Receiving Buffer..
		int currLenRead; //Used to make sure all of data is read in.
		EG_HashTable* parameters;
		EG_HashTable* returnValues;
		short roundtripTime; // v3.0 starts before actually sending the data and ends when receiving the answer from the server (without de-serialisation)
	} EG_GpOperation;

#endif
