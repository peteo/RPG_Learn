/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTONLISTENER_H
#define __PHOTONLISTENER_H

#include "Hashtable.h"

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
	   <link PhotonListener::PhotonPeerEventAction@nByte@Hashtable&amp;, PhotonPeerEventAction()>
	    is called every time an event is received.
	   <link PhotonListener::PhotonPeerOperationResult@nByte@int@Hashtable&amp;@short, PhotonPeerOperationResult()>
	    is called in response to every operation you sent to the
		Photon server, carrying the Photon servers result code.
	   <link PhotonListener::PhotonPeerStatus@int, PhotonPeerStatus()>
		is called on errors and connection-state changes.
	   <link PhotonListener::PhotonPeerDebugReturn@PhotonPeer_DebugLevel@JString&amp;, PhotonPeerDebugReturn()>
	    is called if a Photon related error occurs,
	    passing an error message. This will happen e.g. if you call
	    a PhotonPeer method with invalid parameters.
	   </table>
	   Please note that Photon will free any data passed as
	   \arguments as soon as the callback function returns, so make
	   sure to create copies within the callback funrction of all
	   data needed by your application beyond the scope of the
	   callback function.                                                                                       */
	class PhotonListener
	{
	public:

	/* Summary
	   called by the library as callback to operations. See <link OPERATIONRESULT_CB>.
	   Parameters
	   opCode :        opCode of operation
	   returnCode :    The result code of the operation.
	   returnValues :  any returned values for the operation
	   invocID :       index number of operation
	   Returns
	   Nothing.                                                                                                  */
		virtual void PhotonPeerOperationResult(nByte opCode, int returnCode, const Hashtable& returnValues, short invocID) = 0;

	/* Summary
	   called by the library as callback for peer
	   state-changes and errors. See <link PEERSTATUS_CB>.
	   Parameters
	   statusCode :    the status code
	   Returns
	   Nothing.                                                                                                  */
		virtual void PhotonPeerStatus(int statusCode) = 0;

	/* Summary
	   called by the library as callback for events coming in. See <link PHOTONEVENTACTION_CB>.
	   Parameters
	   opCode :        Code of event
	   returnValues :  event data.
	   Returns
	   Nothing.                                                                                              */
		virtual void PhotonPeerEventAction(nByte eventCode, const Hashtable& returnValues) = 0;

    /* Summary
       called by the library as callback for debug messages in error
       case.
       Parameters
       debugLevel: the debug level, the message was created with
       string :  the debug message
       Returns
       Nothing.                                                      */
		virtual void PhotonPeerDebugReturn(PhotonPeer_DebugLevel debugLevel, const JString& string) = 0;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif //__PHOTONLISTENER_H__
