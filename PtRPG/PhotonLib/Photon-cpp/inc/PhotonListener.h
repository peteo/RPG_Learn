/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_LISTENER_H
#define __PHOTON_LISTENER_H

#include "Photon.h"
#include "OperationResponse.h"
#include "EventData.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	/* <title Photon: PhotonListener class>
	   <toctitle Photon: PhotonListener class>
	   
	   Summary
	   The PhotonListener class defines the callback interface to
	   allow your application to communicate with the Photon Server
	   via the <link PhotonPeer> class.
	   Description
	   The interface defines the following callback methods:
	   <table noborder>
	   <link PhotonListener::onEvent@nByte@Hashtable&amp;, onEvent()>
	    is called every time an event is received.
	   <link PhotonListener::onOperationResponse@nByte@int@Hashtable&amp;@short, onOperationResponse()>
	    is called in response to every operation you sent to the
		Photon server, carrying the Photon servers result code.
	   <link PhotonListener::onStatusChanged@int, onStatusChanged()>
		is called on errors and connection-state changes.
	   <link PhotonListener::debugReturn@PhotonPeer_DebugLevel@JString&amp;, debugReturn()>
	    is called if a Photon related error occurs,
	    passing an error message. This will happen e.g. if you call
	    a PhotonPeer method with invalid parameters.
	   </table>
	   Please note that Photon will free any data passed as
	   \arguments as soon as the callback function returns, so make
	   sure to create copies within the callback function of all
	   data needed by your application beyond the scope of the
	   callback function.                                                                                       */
	class PhotonListener
	{
	public:

	/* Summary
	   called by the library as callback to operations. See <link CB_ON_OPERATION_RESPONSE>.
	   Parameters
	   operationResponse : operationResponse
	   Returns
	   Nothing.                                                                                                  */
		virtual void onOperationResponse(const OperationResponse& operationResponse) = 0;

	/* Summary
	   called by the library as callback for peer
	   state-changes and errors. See <link CB_ON_STATUS_CHANGED>.
	   Parameters
	   statusCode :    the status code
	   Returns
	   Nothing.                                                                                                  */
		virtual void onStatusChanged(int statusCode) = 0;

	/* Summary
	   called by the library as callback for events coming in. See <link CB_ON_EVENT>.
	   Parameters
	   event data : the event.
	   Returns
	   Nothing.                                                                                              */
		virtual void onEvent(const EventData& eventData) = 0;

    /* Summary
       called by the library as callback for debug messages in error
       case.
       Parameters
       debugLevel: the debug level, the message was created with
       string : the debug message
       Returns
       Nothing.                                                      */
		virtual void debugReturn(PhotonPeer_DebugLevel debugLevel, const JString& string) = 0;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif