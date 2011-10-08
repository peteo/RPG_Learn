/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __WRAPPER_DEFINES_H
#define __WRAPPER_DEFINES_H

#include "porting.h"

#undef false
#undef true

#define DELETE_SETNULL_ARRAY(p){delete[](p);p=NULL;}
#define DELETE_SETNULL(p){delete (p);p=NULL;}

#define MEMSET2(p, val, num) for(int xyz=0; xyz<num; xyz++)p[xyz] = val;							 

// Mimicks Java arrayCopy()
#define ARRAYCOPY(__SRC, __SRC_POS, __DST, __DST_POS, __LEN)		\
				{													\
					int pos = __DST_POS;							\
					for(int i=__SRC_POS; i-__SRC_POS<__LEN; i++)	\
						__DST[__DST_POS++] = __SRC[i];				\
				}

#if defined(_EG_BREW_PLATFORM)

// brew 1 doesnt have this
#ifndef ABS
#define ABS(x) ((x)>=0?(x):-(x))
#endif

// in case we don't have this defined
#ifndef AVK_TXPGDOWN
#define AVK_TXPGDOWN 57442
#endif

// not defined in brew currently
#ifndef MAX_INT64
#define MAX_INT64	(0x7fffffffffffffff)
#endif
#ifndef MAX_UINT64
#define MAX_UINT64	(0xffffffffffffffff)
#endif
#ifndef MIN_INT64
#define MIN_INT64 (0x8000000000000000)
#endif

#ifdef AEE_SIMULATOR
	#define CLIENT1
	//#define CLIENT2
#endif

#define BSMIDLET_LOADING1  0
#define BSMIDLET_LOADING2  1
//#define BSMIDLET_SPLASH_SCREEN  4	//new - "Press key" afer loading
#define BSMIDLET_TRY_TO_EXIT  3011
#define BSMIDLET_LOGIN  120
#define BSMIDLET_LOGIN_WAIT  121
#define BSMIDLET_LOGIN_FORM  125
#define BSMIDLET_REGISTER  130
#define BSMIDLET_TRY_TO_LOGIN  3001
#define BSMIDLET_TRY_TO_REGISTER  3002
#define BSMIDLET_WRONG_PASSWORD  1000
#define BSMIDLET_PASSWORD_INCORRECT  1001
#define BSMIDLET_USER_NOT_REGISTERED  1010
#define BSMIDLET_USERNAME_INCORRECT  1005
#define BSMIDLET_ALREADY_REGISTERED  1020
#define BSMIDLET_REGISTRATION_SUCCESSFUL  160
#define BSMIDLET_GUEST_OR_REGISTER 470
#define BSMIDLET_NETWORK_SETUP_ERR  1051

#endif

#endif