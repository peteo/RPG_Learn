#ifndef _PLATFORM_LAYER_IPHONE_INCLUDED_
#define _PLATFORM_LAYER_IPHONE_INCLUDED_

#import "arpa/inet.h"
#include <CommonCrypto/CommonDigest.h>
#include <CommonCrypto/CommonCryptor.h>

#ifdef __cplusplus
extern "C"
{
#endif

	int PhotonPlatformLayer_internal_doCipher(CCOperation encryptOrDecrypt, unsigned char* sourceData, int sourceDataSize, unsigned char* key, unsigned char** resultData, int* resultDataSize);
	
#ifdef __cplusplus
}
#endif 

#endif // _PLATFORM_LAYER_IPHONE_INCLUDED_