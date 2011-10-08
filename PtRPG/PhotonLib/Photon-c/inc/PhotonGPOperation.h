/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_GP_OPERATION_H
#define __PHOTON_GP_OPERATION_H

#include "GPOperation.h"

	#ifdef __cplusplus
		extern "C"
		{
	#endif 

		bool EG_CreatePhotonGPOperation(EG_GpOperation** op, char* url, nByte opcode);

	#ifdef __cplusplus
		}
	#endif 

#endif //__PHOTON_GP_OPERATION_H__