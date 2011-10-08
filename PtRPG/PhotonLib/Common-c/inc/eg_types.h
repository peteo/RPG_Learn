/* Exit Games Common - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __EG_TYPES_H
#define __EG_TYPES_H

#include "porting.h"

#ifndef _EG_BREW_PLATFORM

#include <assert.h>

typedef struct _EG_Callback   EG_Callback;

typedef void (*PFNNOTIFY)(void* pUser);
typedef void (*PFNCBCANCEL)(EG_Callback* pcb);

#if defined(_EG_WINDOWS_PLATFORM)
#include <windows.h>

typedef struct _ThreadResponse ThreadResponse;

typedef void (*PFN_TIMER_NOTIFY)(void* pData);

//Descriptor structure for memory stream. For internal using only
typedef struct _MemoryStream
{
	char*		_pBuffer;      //Pointer to data buffer
	unsigned	_iSize;         //Buffer size in bytes
	unsigned	_iCurrPosition; //Current offset in buffer
} MemoryStream;

//Structure is used for data exchange between main and other threads. For internal using only
struct _ThreadResponse
{
	PFNNOTIFY		_callback_func; //Pointer to callback function which called when data from server received
	void*			_pNotifyData;	// User defined data for _callback_func 
	MemoryStream*	_mStream;		//Data received from server
	bool			_bProcessed;    //Status flag. If set to false, call still in progress, true response from server received and handled.
};
#endif

//Structure specifies the data and functions for a callback context. For internal using only
struct _EG_Callback
{
	PFNCBCANCEL	pfnCancel;      // Filled by callback handler
	void*		pCancelData;    // Filled by callback handler
	PFNNOTIFY	pfnNotify;      // Filled by caller
	void*		pNotifyData;    // Filled by caller
};

#else // !_EG_BREW_PLATFORM

typedef struct _PlatformSpecific	PlatformSpecific;

#include "AEE.h"
#include "AEEModGen.h"
#include "AEEAppGen.h"
#include "AEESource.h"
#include "AEEWeb.h"

typedef AECHAR EG_CHAR;
typedef AEECallback EG_Callback;
typedef PFNNOTIFY PFN_TIMER_NOTIFY;

#ifndef AEE_SIMULATOR
// __FUNCTION__ is apparently not known on ARM
#define __FUNCTION__ 0
#endif

//Wrapper for Brew platform specific interfaces. For internal using only
struct _PlatformSpecific
{
	AEEDeviceInfo	_DeviceInfo;		//Structure contains mobile device information 
	IShell*			_pIShell;			//Pointer to IShell interface
	IModule*		_pIModule;			//Pointer to IModule interface
	IApplet*		_pApp;				//Pointer to applet
	IFileMgr*		_pFileMgr;			//Pointer to IFileMgr interface
	IWeb*			web_conn;			//Pointer to IWeb interface
	EG_Callback		_callback_func;		//Structure specifies the data and functions for a callback context
};

#endif // !_EG_BREW_PLATFORM

#endif// __EG_TYPES_H__
