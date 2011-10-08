/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_PEER_H
#define __PHOTON_PEER_H

#include "Photon.h"
#include "PhotonListener.h"
#include "Utils.h"
#include "Hashtable.h"
#include "JVector.h"
#include "UTF8String.h"
#include "ANSIString.h"

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
	class PhotonPeer
	{
	public:
		#ifdef _EG_BREW_PLATFORM
		PhotonPeer(PhotonListener* listener, PlatformSpecific* pPlatform);
		#else
		PhotonPeer(PhotonListener* listener);
		#endif
		~PhotonPeer(void);

		bool Connect(const JString& ipAddr, const nByte appID[32] = (nByte*)"");
		void Disconnect(void);
		void service(bool dispatchIncomingCommands = true);
		void serviceBasic(void);
		short opCustom(nByte customOpCode, const Hashtable& customOpParameters, bool sendReliable, nByte channelID=0, bool encrypt=false);
		void sendOutgoingCommands(void);
		bool dispatchIncomingCommands(void);
		short opExchangeKeysForEncryption(void);
		void deriveSharedKey(nByte* serverPublicKey);
		void fetchServerTimestamp(void);

		PhotonListener* getListener(void);
		int getServerTimeOffset(void);
		int getServerTime(void);
		int getBytesOut(void);
		int getBytesIn(void);
		PeerState getPeerState(void);
		int getSentCountAllowance(void);
		void setSentCountAllowance(int setSentCountAllowance);
		int getTimePingInterval(void);
		void setTimePingInterval(int setTimePingInterval);
		int getRoundTripTime(void);
		int getRoundTripTimeVariance(void);
		bool setDebugOutputLevel(PhotonPeer_DebugLevel debugLevel);
		PhotonPeer_DebugLevel getDebugOutputLevel(void);
		int getIncomingReliableCommandsCount(void);
		short getPeerId(void);
		int getSentTimeAllowance(void);
		void setSentTimeAllowance(int setSentTimeAllowance);
		unsigned int getQueuedIncomingCommands(void);
		unsigned int getQueuedOutgoingCommands(void);
		JString getServerAddress(void);
		bool getIsEncryptionAvailable(void);
	protected:
		SPhotonPeer* m_pPhotonPeer;
	private:
		PhotonListener* m_pListener;

		static void OnOperationResult(PhotonPeer* pPeer, nByte opCode, int returnCode, EG_HashTable* returnValues, short invocID);
		static void OnPeerStatus(PhotonPeer* pPeer, int statusCode);
		static void OnEventAction(PhotonPeer* pPeer, nByte eventCode, EG_HashTable* returnValues);
		static void OnDebugReturn(PhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel, EG_CHAR* szDebugString);
	};
#ifndef _EG_BREW_PLATFORM
}
#endif
#endif // _PHOTON_PEER_H