/* Exit Games Photon - C Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#include "data_structures.h"

#ifndef __C_EVENT_DATA_H
#define __C_EVENT_DATA_H

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct _CEventData
	{
		nByte code;
		EG_HashTable parameters;
	} CEventData;

	// public API functions
	EG_CHAR* EventData_toString(CEventData* pEventData, bool withParameters, bool withParameterTypes);
	EG_Object* EventData_getParameterForCode(CEventData* pEventData, nByte parameterCode);

	// public API getter/setter functions
	nByte EventData_getCode(CEventData* pEventData);
	EG_HashTable* EventData_getParameters(CEventData* pEventData);
#ifdef __cplusplus
}
#endif 

#endif