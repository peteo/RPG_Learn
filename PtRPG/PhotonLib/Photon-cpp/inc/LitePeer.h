/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __LITE_PEER_H
#define __LITE_PEER_H

#include "PhotonPeer.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	/* <title Photon: PhotonPeer class>
	   <toctitle Photon: PhotonPeer class>
	   
	   Summary
	   The PhotonPeer class provides a channel for reliable or
	   unreliable communication based on UDP.
	   Description
	   This class encapsulates Photon-related functions of the
	   public API as described in section <link UDP based functions, Photon functions>.
	   
	   PhotonPeer uses the callback interface <link PhotonListener>
	   that needs to be implemented by your application, to receive
	   results and events from the Photon Server.
	   
	   
	   
	   <b>How to establish a connection and to send data using the
	   PhotonPeer class:</b>
	   
	   
	   
	   \1. create an PhotonPeer instance.
	   
	   \2. PhotonPeer::Connect() to connect to the server;
	   
	   \3. regularly call PhotonPeer::service() to get new events
	   and to send commands. (best called within the game loop!)
	   
	   \4. wait for a callback to PhotonListener::PhotonPeerReturn()
	   with returnCode: SC_CONNECT;
	   
	   \5. call PhotonPeer::opJoin() to get into a game
	   
	   6 wait for "joined" return in
	   PhotonListener::PhotonPeerReturn() with opCode: OPC_RT_JOIN;
	   
	   \7. send in-game data by calling PhotonPeer::opRaiseEvent()
	   See <link MemoryManagement, Sending and receiving data> for
	   more information about Photon's serializable data structures
	   
	   \8. receive events by the
	   PhotonListener::PhotonPeerEventAction() callback
	   
	   \9. call PhotonPeer::opLeave() to quit/leave the game.
	   
	   \10. wait for callback PhotonListener::PhotonPeerReturn()
	   with opCode: OPC_RT_LEAVE;
	   
	   \11. disconnect by calling PhotonPeer::Disconnect()
	   
	   \12. check "disconnect" return in
	   PhotonListener::PhotonPeerReturn() with returnCode:
	   SC_DISCONNECT                                                                 */
	class LitePeer : public PhotonPeer
	{
	public:
		#ifdef _EG_BREW_PLATFORM
		LitePeer(PhotonListener* listener, PlatformSpecific* pPlatform);
		#else
		LitePeer(PhotonListener* listener, bool useTcp = false);
		#endif
		~LitePeer(void);
		bool opRaiseEvent(bool sendReliable, const Hashtable& evData, nByte eventCode, nByte channelID=0, int* targetActors=NULL, short numTargetActors=0);
		bool opJoin(const JString& gameId, const Hashtable& gameProperties=Hashtable(), const Hashtable& actorProperties=Hashtable(), bool broadcastActorProperties=false);
		bool opLeave(const JString& gameId);
		bool opSetPropertiesOfActor(int actorNr, const Hashtable& properties, bool broadcast, nByte channelID=0);
		bool opSetPropertiesOfGame(const Hashtable& properties, bool broadcast, nByte channelID=0);
		bool opGetProperties(nByte channelID=0);
		bool opGetPropertiesOfActor(const JString* const properties, short numProperties, const int* const actorNrList=NULL, short numActors=0, nByte channelID=0);
		bool opGetPropertiesOfActor(const nByte* const properties, short numProperties, const int* const actorNrList=NULL, short numActors=0, nByte channelID=0);
		bool opGetPropertiesOfGame(const JString* const properties, short numProperties, nByte channelID=0);
		bool opGetPropertiesOfGame(const nByte* const properties, short numProperties, nByte channelID=0);
	};
#ifndef _EG_BREW_PLATFORM
}
#endif
#endif