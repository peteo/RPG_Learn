/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_PHOTON_PEER_H
#define __C_PHOTON_PEER_H

#include "CEventData.h"
#include "COperationResponse.h"

//********************************************************************************************************************************
// Callback typedef functions
//********************************************************************************************************************************

/* Summary
   Typedef for the call back function to be invoked in response
   to basic operations sent to the Photon Server providing the result values from the server.
   Description
   This CB is used as general callback for all operations. The type of an operation is
   identified by an opCode.

   An operation's result is summarized by the returnCode: an int typed code, 0 for OK or
   some error code defined by the application, which is defining the operation itself.
   The opCode defines the type of operation called on Photon and in turn also the returnValues. They are
   provided as Hashtable which contains the complete answer of Photon, including keys for
   opCode and returnCode. Each operation returns its opCode and returnCode but anything else can be
   defined serverside.

   Parameters
   pUser             : user data
   operationResponse : the operationResponse                       */
typedef void(*CB_ON_OPERATION_RESPONSE)(void* pUser, COperationResponse* operationResponse);

/* Summary 
   CB_ON_STATUS_CHANGED is used to denote errors or simply state-changes of the respective PhotonPeer.
   Description
   State change callback

   When this method is used to signalize a state-change, the opCode and other values will be 0 (or null)
   with the following statusCode values:
    * SC_CONNECT the connection to the Photon Server was established
    * SC_DISCONNECT the connection was closed (due to an API-call or a timeout)
    * SC_EXCEPTION/SC_EXCEPTION_CONNECT some system or network error closed the connection

   Possible errors
   When developing with the Photon API, hundreds of events might reach a client each minute. If they are
   not processed in time, they might cause issues. As result of this, there are warnings and errors,
   which should help getting the timing right. Check PhotonConstants for a list (they start with SC_).

   Parameters
   pUser :         user data
   statusCode :    see description                        */
typedef void(*CB_ON_STATUS_CHANGED)(void* pUser, int statusCode);

/* Summary
   Typedef for the event handler function for all Neutron Events
   transmitted by PhotonPeer (UDP).
   Description
   Whenever a Photon event is sent and received via UDP, the
   local peer will be notified via this method. So this is the
   corresponding callback function to Neutron's EVENTACTION_CB
   for HTTP transmissions. Please refer to "sending and
   receiving data" for more information. When a new PhotonPeer is
   created, a pointer to a callback function must be set using
   the function:
   
   <link PhotonPeer_SetCBOnEvent@SPhotonPeer*@CB_ON_EVENT@void*, IPHOTONPEER_SetCBEventAction()>
   
   This way, an application can react on any event, based on its
   eventCode.
   
   The following Neutron events are reported by default:
   
   EV_RT_JOIN
   
   EV_RT_LEAVE
   
   These events are predefined and will be triggered as soon as
   a player has joined or has left the room the local player is
   currently active in. To transmit in-room data, define your
   \own events as needed for your application, and transmit them
   using <link PhotonPeer_opRaiseEvent@SPhotonPeer*@bool@EG_HashTable*@nByte, IPHOTONPEER_OpRaiseEvent()>.
   
   
   
   All events which are raised in reaction to some player's
   actions (like sending data), contain the actor number of the
   sending player in the "parameters" Hashtable. To extract
   this actor number from an event (where available) use code
   like this:
   
   <code>
   nByte key = EV_RT_KEY_ACTORNR;
   \*(int*)( EG_HashTable_getValFromKey(parameters, &amp;key, EG_BYTE, NULL )-\>obj_data );
   
   </code>
   
   If the received event has been raised by another player by
   calling PhotonPeer_opRaiseEvent(), the transmitted "evData"
   hashtable will be stored in the "parameters" hashtable of
   CB_ON_EVENT at key EV_RT_KEY_DATA. Please refer to the
   "realtime demo" in your SDK for sample code.
   Parameters
   pUser :    user data
   eventDataContent: the event
   See Also
   <link MemoryManagement, Sending and receiving data> , <link PhotonPeer_opRaiseEvent@SPhotonPeer*@bool@EG_HashTable*@nByte, PhotonPeer_opRaiseEvent()> */
typedef void(*CB_ON_EVENT)(void* pUser, CEventData* eventDataContent);

/* Summary
   Typedef for a callback function used for receiving debug
   messages generated by Photon functions.
   Description
   Please refer to <link PhotonPeer_SetCBDebugReturn@SPhotonPeer*@CB_DEBUG_RETURN@void*, IPHOTONPEER_SetCBDebugReturn()>
   Parameters
   pUser       : user data
   PdebugLevel : the minimum PhotonPeer_DebugLevel value needed for this message to be passed to your application
   debugString : string containing debug information                                                      */
typedef void(*CB_DEBUG_RETURN) (void* pUser, PhotonPeer_DebugLevel debugLevel, EG_CHAR* debugString);

typedef struct
{
	short peerID;
	nByte flags;
	nByte commandCount;
	int   sentTime;
	int   challenge;
} ProtocolHeader;

typedef struct _ENetChannel
{
	nByte channelNumber;

	EG_Vector* incomingReliableCommands;
	EG_Vector* incomingUnreliableCommands;

	int incomingReliableSequenceNumber;		// sequencenr of last dispatched command
	int incomingUnreliableSequenceNumber;

	EG_Vector* outgoingReliableCommands;
	EG_Vector* outgoingUnreliableCommands;

	int outgoingReliableSequenceNumber;
	int outgoingUnreliableSequenceNumber;

} ENetChannel;

typedef struct _SPhotonGlobal
{
	short peerCount;
} SPhotonGlobal;

/* <title SPhotonPeer structure>
   <toctitle SPhotonPeer structure>
   
   Summary
   SPhotonPeer is the struct that holds basic data related to
   Photon based functions*/
struct _SPhotonPeer
{
	// please do not use the member variables directly, but use the according setters/getters, which provide documentation and an abstraction layer, which determines, if a variable is private, readonly public or gives you public writeaccess
#ifdef _EG_BREW_PLATFORM
	PlatformSpecific		m_Platform;
#endif
	unsigned int			nRefs;
	short					peerID;
	int						challenge;
	char*					peerIpAddr;
	ConnectionState			connectionState;
	EG_Vector*				outgoingAcknowledgements;
	EG_Vector*				sentReliableCommands;
	ENetChannel**			channels;						
	nByte					channelCountUserchannels; // this is the number of user-channels. There is an additional exclusive channel for system messages.
	int						windowSize;  
	int*					unsequencedWindow;
	int						outgoingUnsequencedGroupNumber;
	int						incomingUnsequencedGroupNumber;
	nByte					initBytes[INIT_BYTES_LENGTH];
	nByte					udpCommandCount;
	nByte*					udpBuffer;
	int						udpBufferIndex;
	int						commandSize;
	SPhotonConnect*			rt;
	int						timeBase;
	int						timeInt;				
	int						timeoutInt;
	int						sentTimeAllowance;
	int						timeLastReceive;
	int						sentCountAllowance;
	int						timePingInterval;
	int						packetsLost;
	int						packetLoss;
	int						packetsSent;
	int						packetLossEpoch;
	int						packetLossVariance;
	int						packetThrottleEpoch;
	int						serverTimeOffset;
	bool					serverTimeOffsetIsAvailable;
	int						serverSentTime;
	int						roundTripTime;
	int						roundTripTimeVariance;
	int						lastRoundTripTime;
	int						lowestRoundTripTime;
	int						lastRoundTripTimeVariance;
	int						highestRoundTripTimeVariance;
	int						packetThrottleInterval;
	EG_Callback				cbOperationResult; //Pointer to callback function
	EG_Callback				cbPeerStatus; //Pointer to callback function
	EG_Callback				cbEventAction; //Pointer to callback function
	EG_Callback				cbDebugReturn;  // pointer to the udp debug callback function
	bool					isSendingCommand; //Indicates if sending command is in progress
	nByte*					secretKey; // Client private key
	nByte*					sharedKeyHash; // Shared key hash, used as key for encrypting messages
	int						secretKeySize; // Client private key size
	int						publicKeySize; // Client public key size
	bool					isEncryptionAvailable;
	unsigned short			warningTresholdQueueOutgoingReliable;
	unsigned short			warningTresholdQueueOutgoingUnreliable;
	unsigned short			warningTresholdQueueOutgoingAcks;
	unsigned short			warningTresholdQueueIncomingReliable;
	unsigned short			warningTresholdQueueIncomingUnreliable;
	unsigned short			warningTresholdQueueSent;
	bool					applicationIsInitialized;

    void*					pPeerLayer;
    bool					shouldScheduleDisconnectCB;

//#ifdef TEST_ON
    bool debugUseShortcut;
//#endif //TEST_ON
	PhotonPeer_DebugLevel	debugOutputLevel; // controls the level of debug output sent to the CB_DEBUG_RETURN callback
#if defined _EG_MARMALADE_PLATFORM && !defined I3D_ARCH_ARM && defined EG_DEBUGGER
	bool					firedMetricsWarning;
#endif
};

#ifdef __cplusplus
extern "C"
{
#endif
	// public API functions
	#ifdef _EG_BREW_PLATFORM
		int PhotonPeer_New(PlatformSpecific* pPlatform, SPhotonPeer** ppMod);
		unsigned long PhotonPeer_AddRef(SPhotonPeer* pPeer);
		unsigned long PhotonPeer_Release(SPhotonPeer* pPeer);
	#else
		int PhotonPeer_New(SPhotonPeer** ppMod, bool useTcp);
		unsigned int PhotonPeer_AddRef(SPhotonPeer* pPeer);
		unsigned int PhotonPeer_Release(SPhotonPeer* pPeer);
	#endif
	bool PhotonPeer_Connect(SPhotonPeer* pPeer, const EG_CHAR* ipaddr, const nByte appID[32]);
	void PhotonPeer_Disconnect(SPhotonPeer* pPeer);
	void PhotonPeer_service(SPhotonPeer* pPeer);
	void PhotonPeer_serviceBasic(SPhotonPeer* pPeer);
	void PhotonPeer_serviceWithoutDispatching(SPhotonPeer* pPeer);
	void PhotonPeer_sendOutgoingCommands(SPhotonPeer* pPeer);
	bool PhotonPeer_dispatchIncomingCommands(SPhotonPeer* pPeer);
	bool PhotonPeer_opCustom(SPhotonPeer* pPeer, nByte customOpCode, EG_HashTable* customOpParameters, bool sendReliable, nByte channelId, bool encrypt);
	void PhotonPeer_fetchServerTimestamp(SPhotonPeer* pPeer);

	// public API for encryption
	bool PhotonPeer_establishEncryption(SPhotonPeer* pPeer);

	// public API callback setters
	void PhotonPeer_SetCBOnOperationResponse(SPhotonPeer* pPeer, CB_ON_OPERATION_RESPONSE cb, void* pUser);
	void PhotonPeer_SetCBOnStatusChanged(SPhotonPeer* pPeer, CB_ON_STATUS_CHANGED cb, void* pUser);
	void PhotonPeer_SetCBOnEvent(SPhotonPeer* pPeer,CB_ON_EVENT cb, void* pUser);
	void PhotonPeer_SetCBDebugReturn(SPhotonPeer* pPeer, CB_DEBUG_RETURN cb, void* pUser);

	// public API getter/setter functions
	int PhotonPeer_getServerTimeOffset(SPhotonPeer* pPeer);
	int PhotonPeer_getServerTime(SPhotonPeer* pPeer);
	int PhotonPeer_getBytesOut(SPhotonPeer* pPeer);
	int PhotonPeer_getBytesIn(SPhotonPeer* pPeer);
	PeerState PhotonPeer_getPeerState(SPhotonPeer* pPeer);
	int PhotonPeer_getSentCountAllowance(SPhotonPeer* pPeer);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pPeer, int setSentCountAllowance);
	int PhotonPeer_getTimePingInterval(SPhotonPeer* pPeer);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pPeer, int setSentCountAllowance);
	void PhotonPeer_setTimePingInterval(SPhotonPeer* pPeer, int setTimePingInterval);
	int PhotonPeer_getRoundTripTime(SPhotonPeer* pPeer);
	int PhotonPeer_getRoundTripTimeVariance(SPhotonPeer* pPeer);
	int PhotonPeer_getIncomingReliableCommandsCount(SPhotonPeer* pPeer);
	bool PhotonPeer_setDebugOutputLevel(SPhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel);
	PhotonPeer_DebugLevel PhotonPeer_getDebugOutputLevel(SPhotonPeer* pPeer);
	short PhotonPeer_getPeerID(SPhotonPeer* pPeer);
	int PhotonPeer_getSentTimeAllowance(SPhotonPeer* pPeer);
	void PhotonPeer_setSentTimeAllowance(SPhotonPeer* pPeer, int setSentTimetAllowance);
	int PhotonPeer_getQueuedIncomingCommands(SPhotonPeer* pPeer);
	int PhotonPeer_getQueuedOutgoingCommands(SPhotonPeer* pPeer);
	char* PhotonPeer_getServerAdress(SPhotonPeer* pPeer);
	bool PhotonPeer_getIsEncryptionAvailable(SPhotonPeer* pPeer);
	short PhotonPeer_getPeerCount(void);

	// internals
	#ifdef EG_DEBUGGER
		#define PhotonPeer_sendErrors(peer, debugLevel, ...) PhotonPeer_sendErrorsInternal(peer, debugLevel, __WFILE__, __WFUNCTION__, __LINE__, __VA_ARGS__)
	#else
		#define PhotonPeer_sendErrors(peer, debugLevel, ...) ((void)0)
	#endif
	void PhotonPeer_sendErrorsInternal(SPhotonPeer* pPeer, PhotonPeer_DebugLevel debugLevel, const EG_CHAR* const file, const EG_CHAR* const function, unsigned int line, const EG_CHAR* error, ...);
	void PhotonPeer_internal_Disconnected(SPhotonPeer* pPeer);
	void PhotonPeer_internal_send(SPhotonPeer* pPeer, nByte cType, nByte* payload, unsigned int payloadSize, nByte channelId);
	void PhotonPeer_internal_sendDebugged(SPhotonPeer* pPeer, nByte cType, nByte* payload, unsigned int payloadSize, int debugReliableSequenceNumber, int debugUnreliableSequenceNumber, int debugUnsequencedGroupNumber, int debugLooseThisCommandCounter);
	void PhotonPeer_internal_queueOutgoingReliableCommand(SPhotonPeer* pPeer, SPhotonCommand* command);
	void PhotonPeer_internal_queueOutgoingUnreliableCommand(SPhotonPeer* pPeer, SPhotonCommand* command);
	void PhotonPeer_internal_queueOutgoingAcknowledgement(SPhotonPeer* pPeer, SPhotonCommand* command);
	bool PhotonPeer_internal_queueIncomingCommand(SPhotonPeer* pPeer, SPhotonCommand* command);
	void PhotonPeer_internal_queueSentReliableCommand(SPhotonPeer* pPeer, SPhotonCommand* command);
	void PhotonPeer_serviceInternal(SPhotonPeer* pPeer, bool dispatch);
	bool PhotonPeer_internal_serializeOperation(SPhotonPeer* pPeer, EG_HashTable* parameters, nByte opc, nByte** buffer,  int* buffSize, bool encrypt, nByte msgType);
	bool PhotonPeer_internal_deserializeOperation(SPhotonPeer* pPeer, nByte* inBuff, int inBuffLength);
	void PhotonPeer_internal_deserializeOperationResponse(SPhotonPeer* pPeer, nByte* inBuff, bool isEncrypted, int waitForBytes, nByte msgType);
	void PhotonPeer_internal_deserializeEvent(SPhotonPeer* pPeer, nByte* inBuff, bool isEncrypted, int waitForBytes);
	void PhotonPeer_internal_initPhotonPeer(SPhotonPeer* pPeer);
	void PhotonPeer_internal_freePhotonPeer(SPhotonPeer* pPeer);
	void PhotonPeer_internal_initEnetChannel(ENetChannel* channel, nByte channelNumber);
	void PhotonPeer_internal_releaseEnetChannel(ENetChannel* channel);
	int PhotonPeer_internal_serializeToBuffer(SPhotonPeer* pPeer, EG_Vector**);
	void PhotonPeer_internal_removeSentReliableCommand(SPhotonPeer* pPeer, int ackReceivedReliableSequenceNumber,  int ackReceivedChannel, SPhotonCommand** command);
	void PhotonPeer_internal_updateRoundTripTimeVariance(SPhotonPeer* pPeer, int time, int rttUpdateCount); 
	void PhotonPeer_internal_execute(SPhotonPeer* pPeer,SPhotonCommand* command);
	void PhotonPeer_internal_cbNetConnect(SPhotonPeer* pPeer, int nError);
	void PhotonPeer_internal_cbNetReceiveData(SPhotonPeer* pPeer, nByte* pBuf, int iCount, int nError);
	void PhotonPeer_internal_sortLastElementInQueue(EG_Vector** argQueue, bool sortByReliableSequenceNumber, SPhotonPeer* pPeer);
	SPhotonCommand* PhotonPeer_internal_getReliableCommandFromQueue(EG_Vector* queue, int reliableSequenceNumber);
	SPhotonCommand* PhotonPeer_internal_getUnreliableCommandFromQueue(EG_Vector* queue, int unreliableSequenceNumber);
	bool PhotonPeer_internal_removeReliableCommandFromQueue(EG_Vector** queue, int reliableSequenceNumber);
	bool PhotonPeer_internal_removeUnreliableCommandFromQueue(EG_Vector** queue, int unreliableSequenceNumber);
	void PhotonPeer_internal_clearAllQueues(SPhotonPeer* pPeer);
	void PhotonPeer_internal_initCallback(SPhotonPeer* pPeer);
	bool PhotonPeer_internal_opExchangeKeysForEncryption(SPhotonPeer* pPeer);
	void PhotonPeer_internal_deriveSharedKey(SPhotonPeer* pPeer, COperationResponse* pOperationResponse);
	bool PhotonPeer_internal_opCustom(SPhotonPeer* pPeer, nByte customOpCode, EG_HashTable* customOpParameters, bool sendReliable, nByte channelId, bool encrypt, nByte msgType);
#ifdef __cplusplus
}
#endif

#endif //__C_PHOTON_PEER_H__