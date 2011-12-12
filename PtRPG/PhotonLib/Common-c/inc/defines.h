/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __DEFINES_H
#define __DEFINES_H
#include "Constants.h"

#ifndef _INT64
#define _INT64
#if (BREW_MAJ_VER < 3)
#ifndef _EG_WIN32_PLATFORM
/* Non Windows Targets 
 */
typedef  signed long long   int64;       /* Signed 64 bit value */
typedef  unsigned long long uint64;      /* Unsigned 64 bit value */
#else
/* Windows based targets
 */
typedef  __int64            int64;       /* Signed 64 bit value */
typedef  unsigned __int64   uint64;      /* Unsigned 64 bit value */  
#endif 
#endif
#endif

// UTF8
#define UTF8LEN(str) utf8len(str)

#ifndef _EG_BREW_PLATFORM

// Definitions for memory allocation /////////////////////////////////////
#if defined(_EG_APPLE_PLATFORM)
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#define MALLOC(size)			memset(malloc(size), 0, size)
#define FREE(p)					(p?(free(p), p=NULL):((void*)0))
#define REALLOC					realloc

// Definitions for memory management //////////////////////////////////////
#include <memory.h>
#define MEMCPY(dst, src, size)	memcpy(dst, src, size)
#define MEMSET(dst, c, size)	memset(dst, c, size)
#define ZEROAT(ptr)				(void)MEMSET(ptr, 0, sizeof(*ptr))

// Definitions for string operations /////////////////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/* ATTENTION:
wchar_t is UTF16 on Windows, but UTF32 on UNIX and it's inheritors OSX/iOS, although OSX/iOS-NSString/CFString uses UTF16,
so you have to convert EG_CHAR to/from NSString/CFString, but redefining wchar_t to be 16bit on UNIX or defining EG_CHAR to be always
16bit would have meant reimplementing standard wchar_t library on UNIX */
typedef wchar_t EG_CHAR;

#ifndef _EG_BREW_PLATFORM
#ifdef  __cplusplus
extern "C"
{
#endif
	EG_CHAR* ANSI2Unicode(const char* _str, EG_CHAR* _wstr, int _wstrLen);
	char* Unicode2ANSI(const EG_CHAR* _wstr, char* _str, int _strSize);
	char* Unicode2UTF8(const EG_CHAR* wstr, int src_len, unsigned char* dst, int dst_size);
	EG_CHAR* UTF82Unicode(const unsigned char* str, int src_size, EG_CHAR* dst, int dst_len);
	int SizeOfWStrAsUTF8(const EG_CHAR* str, int len);
	int LengthOfUTF8AsWStr(const unsigned char* str, int size);
#ifdef  __cplusplus
}
#endif
#endif

// Unicode string support and conversion
#define WSTRTOSTR(src, dst, size) Unicode2ANSI(src, dst, size)
#define STRTOWSTR(src, dst, size) ANSI2Unicode(src, dst, size)
#define WSTRTOUTF8(src, src_len, dst, dst_size) Unicode2UTF8(src, src_len, dst, dst_size)
#define UTF8TOWSTR(src, src_size, dst, dst_len) UTF82Unicode(src, src_size,  dst, dst_len)

// ASCII
#ifndef _EG_BREW_PLATFORM
	#define STRCMP(str1, str2)			strcmp(str1, str2)
	#define STRCAT(dst, src)			strcat(dst, src)
	#define STRSTR(str1, str2)			strstr(str1, str2)
	#define STRLEN(str)					strlen(str)
	#define STRNLEN(str,n)				strnlen(str,n)
	#define STRCPY(dst, src)			strcpy(dst, src)
	#define STRCHR(str, c)				strchr(str, c)
	#define STRRCHR(str, c)				strrchr(str, c)
	#define STRNCMP(str1, str2, c)		strncmp(str1, str2,
	#if defined(_EG_WINDOWS_PLATFORM)
		#define STRLOWER(str)			_strlwr(str)
		#define STRDUP(str)				_strdup(str)c)
		#define STRNICMP(str1, str2, c)	_strnicmp(str1, str2, c)
		#define VSNPRINTF				_vsnprintf
		#define SNPRINTF				_snprintf
	#else
		#define STRLOWER(str)			strlwr(str)
		#define STRDUP(str)				strdup(str)
		#define STRNICMP(str1, str2, c)	EG_strnicmp(str1, str2, c)
		#define VSNPRINTF				vsnprintf
		#define SNPRINTF				snprintf
	#endif
	#define SPRINTF						sprintf
#endif

// UTF16 / UTF32
#define WCSCMP(str1, str2)			wcscmp(str1, str2)
#define WCSCAT(dst, src)			wcscat(dst, src)
#define WCSSTR(str1, str2)			wcsstr(str1, str2)
#define WCSLEN(str)					wcslen(str)
#define WCSNLEN(str,n)				wcsnlen(str,n)
#define WCSCPY(dst, src)			wcscpy(dst, src)
#define WCSLOWER(str)				_wcslwr(str)
#define WCSCHR(str, c)				wcschr(str, c)
#define WCSRCHR(str, c)				wcsrchr(str, c)
#define WCSNCMP(str1, str2, c)		wcsncmp(str1, str2, c)
#define WCSNICMP(str1, str2, c)		_wcsnicmp(str1, str2, c)
#define WCSDUP(str)					_wcsdup(str)
#define VWSCPRINTF					_vwscprintf
#if defined(_EG_WINDOWS_PLATFORM)
	#define VSNWPRINTF				_vsnwprintf
#elif defined(_EG_MARMALADE_PLATFORM) && defined(I3D_ARCH_ARM)
	#define VSNWPRINTF				EG_vswprintf // very expensive, use with care!
#else
	#define VSNWPRINTF				vswprintf
#endif
#define VSCWPRINTF					_vscwprintf
#if defined(_EG_WINDOWS_PLATFORM)
	#define SNWPRINTF				_snwprintf
#elif defined(_EG_MARMALADE_PLATFORM) && defined(I3D_ARCH_ARM)
	#define SNWPRINTF				EG_swprintf
#else
	#define SNWPRINTF				swprintf
#endif

#define ATOI(str)					atoi(str)
#if defined(_EG_WINDOWS_PLATFORM)
	#define WTOI(str)				_wtoi(str)
#else
	#define WTOI(str)				EG_wtoi(str)
#endif

// widestring versions of predefined macros
// __WFILE__ and __WFUNCTION__ instead of __FILEW__ and __FUNCTIONW__, to avoid conflicts with MS sytem libs, which do not #ifdef their defines
#ifndef WIDEN
	#define WIDEN2(str) (L ## str)
	#define WIDEN(str) WIDEN2(str)
#endif
#ifndef __WFILE__
	#define __WFILE__ WIDEN(__FILE__)
#endif
#ifndef __WFUNCTION__
	#if defined _MSC_VER
		#define __WFUNCTION__ WIDEN(__FUNCTION__)
	#else
		extern EG_CHAR __EGGlobalwstr[1024];
		#define __WFUNCTION__ STRTOWSTR(__FUNCTION__, __EGGlobalwstr, STRLEN(__FUNCTION__)) // we can't use preprocessor token pasting here, as on GCC __FUNCTION__ is not a macro like in VS
	#endif
#endif

// Time access and control functions //////////////////////////////////////

// Attention: Do not use these macros, if you need the absolute time on different platforms, because they have completely different base dates
// on different platforms and are only to be used for time intervals between two calls

// Brew:
// GETTIMEMS: returns the number of milliseconds that have elapsed since the last occurrence of 00:00:00 local time.
// GETUPTIMEMS: returns the number milliseconds for which the device was powered on. In simulator, it takes the PC time for calculation.


#if defined(_EG_WINDOWS_PLATFORM)
#	if defined(_EG_WIN32_PLATFORM)
#		define WIN32_LEAN_AND_MEAN
#		define _WIN32_WINNT 0x0500
#		include <Windows.h>
#		include <Mmsystem.h>
#	endif
#   define GETTIMEMS	timeGetTime // returns the number of milliseconds for which the PC was powered on - accuracy: 1ms - overhead: medium
#   define GETUPTIMEMS	GetTickCount // returns the number of milliseconds for which the PC was powered on - accuracy: 50ms - overhead. small
#elif defined(_EG_UNIX_PLATFORM)
#	include <time.h>
#   define GETTIMEMS	getTimeUnix // returns the number of milliseconds passed since 1970
#   define GETUPTIMEMS	getTimeUnix // returns the number of milliseconds passed since 1970
#endif

// Debug output functions ////////////////////////////////////////////////
#ifdef _EG_MEEGO_PLATFORM
	#include "stdarg.h" // not in ifdefs below, as it is also needed for debugCallbacks
#endif
#if(DBGPRINTF_LEVEL || DBGPRINTF_MEMORY_ACTIVE || DBGPRINTF_PERFORMANCE_ACTIVE)

#if(defined(_EG_WINDOWS_PLATFORM)) && defined(__cplusplus)
	#pragma managed(push, off)
#endif
#ifdef __cplusplus
	extern "C"
	{
#endif
		static __inline void __DBGPRINTF(const char* message, ...)
		{
			va_list argptr;
			va_start(argptr, message);
			vfprintf(stderr, message, argptr);
			va_end(argptr);
			fprintf(stderr, "\n");
		}
#ifdef  __cplusplus
	}
#endif
#if(defined(_EG_WINDOWS_PLATFORM)) && defined(__cplusplus)
	#pragma managed(pop)
#endif

#define DBGPRINTF_LEVEL_DEBUG_VERBOSE	6
#define DBGPRINTF_LEVEL_DEBUG			5
#define DBGPRINTF_LEVEL_INFO			4
#define DBGPRINTF_LEVEL_WARNING			3
#define DBGPRINTF_LEVEL_ERROR			2
#define DBGPRINTF_LEVEL_FATAL			1
#define DBGPRINTF_LEVEL_OFF				0

#define DBGPRINTF_EX_FORMAT		"*dbgprintf-%d* %-80s line:%10d  "
#define DBGPRINTF_EXSTR_FORMAT	"*dbgprintf-%s* %-80s line:%10d  "

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_DEBUG_VERBOSE)
#define DBGPRINTF_DEBUG_VERBOSE			fprintf(stderr, DBGPRINTF_EX_FORMAT, DBGPRINTF_LEVEL_DEBUG_VERBOSE, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_DEBUG_VERBOSE(...)	((void)0)
#endif

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_DEBUG)
#define DBGPRINTF_DEBUG					fprintf(stderr, DBGPRINTF_EX_FORMAT, DBGPRINTF_LEVEL_DEBUG, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_DEBUG(...)			((void)0)
#endif

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_INFO)
#define DBGPRINTF_INFO					fprintf(stderr, DBGPRINTF_EX_FORMAT, DBGPRINTF_LEVEL_INFO, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_INFO(...)				((void)0)
#endif

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_WARNING)
#define DBGPRINTF_WARNING				fprintf(stderr, DBGPRINTF_EX_FORMAT,DBGPRINTF_LEVEL_WARNING, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_WARNING(...)			((void)0)
#endif

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_ERROR)
#define DBGPRINTF_ERROR					fprintf(stderr, DBGPRINTF_EX_FORMAT, DBGPRINTF_LEVEL_ERROR, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_ERROR(...)			((void)0)
#endif

#if(DBGPRINTF_LEVEL >= DBGPRINTF_LEVEL_FATAL)
#define DBGPRINTF_FATAL					fprintf(stderr, DBGPRINTF_EX_FORMAT, DBGPRINTF_LEVEL_FATAL, __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_FATAL(...)			((void)0)
#endif

#if(DBGPRINTF_MEMORY_ACTIVE)
#define DBGPRINTF_MEMORY				fprintf(stderr, DBGPRINTF_EX_FORMAT, "memory", __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_MEMORY(...)			((void)0)
#endif

#if (DBGPRINTF_PERFORMANCE_ACTIVE)
#define DBGPRINTF_PERFORMANCE			fprintf(stderr, DBGPRINTF_EX_FORMAT, "performance", __FILE__, __LINE__), __DBGPRINTF
#else
#define DBGPRINTF_PERFORMANCE(...)		((void)0)
#endif

#define DBGPRINTF						DBGPRINTF_ERROR

#else
#define DBGPRINTF_DEBUG_VERBOSE(...)	((void)0)
#define DBGPRINTF_DEBUG(...)			((void)0)
#define DBGPRINTF_INFO(...)				((void)0)
#define DBGPRINTF_WARNING(...)			((void)0)
#define DBGPRINTF_ERROR(...)			((void)0)
#define DBGPRINTF_FATAL(...)			((void)0)
#define DBGPRINTF_MEMORY(...)			((void)0)
#define DBGPRINTF_PERFORMANCE(...)		((void)0)
#define DBGPRINTF(...)					((void)0)
#endif

// debugging helpers
#ifdef EG_DEBUGGER
#define DEBUG_ONLY(arg) arg
#define RELEASE_ONLY(arg) ((void)0)
#define DEBUG_RELEASE(dbgarg, relarg) dbgarg
#else
#define DEBUG_ONLY(arg) ((void)0)
#define RELEASE_ONLY(arg) arg
#define DEBUG_RELEASE(dbgarg, relarg) relarg
#endif

// Error codes ///////////////////////////////////////////////////////////
#define SUCCESS              0        // No error
#define EFAILED              1        // General failure
#define ENOMEMORY            2        // Out of memory
#define ECLASSNOTSUPPORT     3        // Class not supported

#ifndef _BOOLEAN
// This has to be defined for C to be an unsigned type of the same size as the C++ builtin type bool.
// That is 1 on all currently supported platforms.
// The C++ wrapper is not compatible to platforms, which define bool to a different size in C99 than in C++
#if !defined(__cplusplus) && !defined(bool) // bool is already defined in C99 (which is used in our xcode-projects), but not in the older C version used in VS (which is not conforming to any official standard, but more like C89 + parts of C99)
typedef unsigned char       bool;	// Boolean value type.
#endif
#define _BOOLEAN
#endif

#ifndef _UINT32
typedef unsigned int		uint32;	// Unsigned 32 bit value
#define _UINT32
#endif

#ifndef _UINT16
typedef unsigned short		uint16;	// Unsigned 16 bit value
#define _UINT16
#endif

#ifndef _UINT8
#ifndef _EG_MARMALADE_PLATFORM
typedef unsigned char		uint8;	// Unsigned 8  bit value
#define _UINT8
#endif
#endif

#ifndef _INT32
typedef signed int			int32;	// Signed 32 bit value
#define _INT32
#endif

#ifndef _INT16
typedef signed short		int16;	// Signed 16 bit value
#define _INT16
#endif

#ifndef _INT8
#ifndef _EG_MARMALADE_PLATFORM
typedef signed char			 int8;	// Signed 8  bit value
#define _INT8
#endif
#endif

//Necessary Brew defines
#define CALLBACK_Cancel(pcb)    if (0 != (pcb)->pfnCancel) (pcb)->pfnCancel(pcb)
#define CALLBACK_Init(pcb,pcf,pcx) {(pcb)->pfnNotify = (PFNNOTIFY)(pcf); \
											(pcb)->pNotifyData = (pcx);}

#define CALLBACK_IsQueued(pcb)  (0 != (pcb)->pfnCancel)

#define VTBL(iname)       iname##Vtbl

#define QINTERFACE(iname) \
struct _##iname {\
  struct VTBL(iname)  *pvt;\
};\
typedef struct VTBL(iname) VTBL(iname);\
struct VTBL(iname)

#define DECLARE_IBASE(iname) \
  unsigned int  (*AddRef)         (iname*); \
  unsigned int  (*Release)        (iname*);

#define INHERIT_IBase(iname) \
  unsigned int  (*AddRef)         (iname*); \
  unsigned int  (*Release)        (iname*)

#define DECLARE_VTBL(iname)      iname   vt##iname; 
#define GET_PVTBL(p,iname)       ((iname*)p)->pvt

#ifdef BREW_MODULE
#define INIT_VTBL(p,iname,vt) \
{ \
   static void *glueVtbl; \
   if (!glueVtbl) \
      glueVtbl=(*gftbl->gfGlueVtbl)(&vt,sizeof(vt)>>2); \
   else \
      (*gftbl->gfGlueAddRef)(glueVtbl); \
   GET_PVTBL(p,iname) = (VTBL(iname) *) glueVtbl; \
}
#define FREE_VTBL(p,iname) (*gftbl->gfGlueDelRef)(GET_PVTBL(p,iname))
#else
#define INIT_VTBL(p,iname,vt)    (GET_PVTBL(p,iname) = (VTBL(iname) *)&vt)
#define FREE_VTBL(p,iname)
#endif

/*#define INHERIT_IModule(iname) \
   INHERIT_IBase(iname); \
   int         (*CreateInstance)(iname * po,IShell * pIShell,AEECLSID ClsId,void ** ppObj); \
   void        (*FreeResources)(iname * po, IHeap * ph, IFileMgr * pfm)*/
#ifndef __IMODULE_DEFINED___
#define __IMODULE_DEFINED___
typedef struct _IModule         IModule;
QINTERFACE(IModule)
{
	INHERIT_IBase(IModule);
};
#endif //__IMODULE_DEFINED___

#endif // _EG_BREW_PLATFORM

#endif