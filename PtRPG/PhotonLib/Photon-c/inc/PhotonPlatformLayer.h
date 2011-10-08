/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_PLATFORM_LAYER_H
#define __PHOTON_PLATFORM_LAYER_H

#include "defines.h"

#ifdef _EG_BREW_PLATFORM
	#include "brew/BrewPlatformLayer.h"
#endif

#ifdef _EG_UNIX_PLATFORM
	#include "arpa/inet.h"
	#ifdef _EG_MARMALADE_PLATFORM
		#define INADDR_NONE -1 // should be defined by platform's BSD-socket implementation, but for some reason it isn't for Marmalade-platform
	#endif
#endif

#ifdef _EG_APPLE_PLATFORM
	#include "iPhone/Encryption_iPhone.h"
#else
	#include "encryption/Encryption_general.h"
#endif

// encryption functions
#ifdef __cplusplus
extern "C"
{
#endif

	void PhotonPlatformLayer_calculateSHA256Hash(unsigned char* inputData, int length, unsigned char* hashedChars);
	int PhotonPlatformLayer_encrypt(unsigned char* plainData, int plainDataSize, unsigned char* key, unsigned char** encodedData, int* encodedDataSize);
	int PhotonPlatformLayer_decrypt(unsigned char* encodedData, int encodedDataSize, unsigned char* key, unsigned char** plainData, int* plainDataSize);

#ifdef __cplusplus
}
#endif

#endif  // _PHOTON_PLATFORM_LAYER_H_
