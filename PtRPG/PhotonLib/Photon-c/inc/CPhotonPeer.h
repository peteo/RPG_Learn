/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_PHOTON_PEER_H
#define __C_PHOTON_PEER_H

#include "data_structures.h"

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

   Each call of an operation gets an ID, called the invocID. This can be matched to the IDs
   returned with any operation call. This way, an application could track if a certain
   call of an operation was successful and not only if some of the last calls to it were.

   Parameters
   pUser :         user data
   opCode :        opCode of the operation
   retCode :       result of the operation in form of an integer return value
   returnValues :  any returned values for the operation
   invocID :       the <link Invocation IDs, invocation ID> of the operation                         */
typedef void(*OPERATIONRESULT_CB)(void* pUser, nByte opCode, int returnCode, EG_HashTable* returnValues, short invocID);

/* Summary 
   PEERSTATUS_CB is used to denote errors or simply state-changes of the respective PhotonPeer.
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
typedef void(*PEERSTATUS_CB)(void* pUser, int statusCode);

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
   
   <link PhotonPeer_SetCBEventAction@SPhotonPeer*@PHOTONEVENTACTION_CB@void*, IPHOTONPEER_SetCBEventAction()>
   
   This way, an application can react on any event, based on its
   eventCode.
   
   The following Neutron events are reported by default:
   
   EV_RT_JOIN
   
   EV_RT_LEAVE
   
   These events are predefined and will be triggered as soon as
   a player has joined or has left the game the local player is
   currently active in. To transmit in-game data, define your
   \own events as needed for your application, and transmit them
   using <link PhotonPeer_opRaiseEvent@SPhotonPeer*@bool@EG_HashTable*@nByte, IPHOTONPEER_OpRaiseEvent()>.
   
   
   
   All events which are raised in reaction to some player's
   actions (like sending data), contain the actor number of the
   sending player in the "returnValues" Hashtable. To extract
   this actor number from an event (where available) use code
   like this:
   
   <code>
   nByte key = EV_RT_KEY_ACTORNR;
   \*(int*)( EG_HashTable_getValFromKey( retVals, &amp;key, EG_BYTE, NULL )-\>obj_data );
   
   </code>
   
   If the received event has been raised by another player by
   calling PhotonPeer_opRaiseEvent(), the transmitted "evData"
   hashtable will be stored in the "returnValues" hashtable of
   PHOTONEVENTACTION_CB at key EV_RT_KEY_DATA. Please refer to the
   "realtime demo" in your SDK for sample code.
   Parameters
   pUser :         user data
   evCode :        code of the Neutron event (see <link Basic operations>
                   )
   returnValues :  Hashtable containing the event data
   See Also
   <link MemoryManagement, Sending and receiving data> , <link PhotonPeer_opRaiseEvent@SPhotonPeer*@bool@EG_HashTable*@nByte, PhotonPeer_opRaiseEvent()> */
typedef void(*PHOTONEVENTACTION_CB)(void* pUser, nByte opCode, EG_HashTable* returnValues);

/* Summary
   Typedef for a callback function used for receiving debug
   messages generated by Photon functions.
   Description
   Please refer to <link PhotonPeer_SetCBDebugReturn@SPhotonPeer*@PHOTONDEBUG_CB@void*, IPHOTONPEER_SetCBDebugReturn()>
   Parameters
   Param1 :  user data
   Param2 :  the minimum PhotonPeer_DebugLevel value needed for this message to be passed to your application
   Param2 :  string containing debug information                                                      */
typedef void(*PHOTONDEBUG_CB) (void* pUser, PhotonPeer_DebugLevel debugLevel, EG_CHAR* debugString);

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
    PeerState				peerState;
	EG_Vector*				incomingCommands;
    EG_Vector*				outgoingAcknowledgements;
    EG_Vector*				sentReliableCommands;
	ENetChannel**			channels;						
	int						channelCountUserchannels;		// this is the number of user-channels. There is an additional exclusive channel for system messages.
    int						windowSize;  
    int*					unsequencedWindow;
    int						outgoingUnsequencedGroupNumber;
    int						incomingUnsequencedGroupNumber;
    short					peerCount;
	nByte					INIT_BYTES[INIT_BYTES_LENGTH];
    nByte					UDP_PACKAGE_HEADER_LENGTH;
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
    int						ENET_PEER_PACKET_LOSS_SCALE;
    int						ENET_PEER_DEFAULT_ROUND_TRIP_TIME;
    int						ENET_PEER_PACKET_THROTTLE_INTERVAL;
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
    short					invocID;
	nByte*					secretKey; // Client private key
	nByte*					publicKey; // Client public key
	nByte*					sharedKeyHash; // Shared key hash, used as key for encrypting messages
	int						secretKeySize; // Client private key size
	int						publicKeySize; // Client public key size
	bool					isEncryptionAvailable;
	unsigned short			warningTresholdQueueOutgoingReliable;
	unsigned short			warningTresholdQueueOutgoingUnreliable;
	unsigned short			warningTresholdQueueOutgoingAcks;
	unsigned short			warningTresholdQueueIncoming;
	unsigned short			warningTresholdQueueSent;
	
//#ifdef TEST_ON
    bool debugUseShortcut;
//#endif //TEST_ON
	PhotonPeer_DebugLevel	debugOutputLevel; // controls the level of debug output sent to the PHOTONDEBUG_CB callback
#if defined(_EG_MARMALADE_PLATFORM) && defined(EG_DEBUGGER)
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
		unsigned long PhotonPeer_AddRef(SPhotonPeer* po);
		unsigned long PhotonPeer_Release(SPhotonPeer* po);
	#else
		int PhotonPeer_New(SPhotonPeer** ppMod);
		unsigned int PhotonPeer_AddRef(SPhotonPeer* po);
		unsigned int PhotonPeer_Release(SPhotonPeer* po);
	#endif
	bool PhotonPeer_Connect(SPhotonPeer* p, EG_CHAR* ipaddr, const nByte appID[32]);
	void PhotonPeer_Disconnect(SPhotonPeer* p);
	void PhotonPeer_service(SPhotonPeer* p);
	void PhotonPeer_serviceBasic(SPhotonPeer* p);
	void PhotonPeer_serviceWithoutDispatching(SPhotonPeer* p);
	void PhotonPeer_sendOutgoingCommands(SPhotonPeer* p);
	bool PhotonPeer_dispatchIncomingCommands(SPhotonPeer* p);
	short PhotonPeer_opCustom(SPhotonPeer* pSPeer, nByte customOpCode, EG_HashTable* customOpParameters, bool sendReliable, nByte channelId, bool encrypt);
	void PhotonPeer_fetchServerTimestamp(SPhotonPeer* pSPeer);

	// public API for encryption
	short PhotonPeer_opExchangeKeysForEncryption(SPhotonPeer* p);
	void PhotonPeer_deriveSharedKey(SPhotonPeer* p, nByte* serverPublicKey);

	// public API callback setters
	void PhotonPeer_SetCBOperationResult(SPhotonPeer* p, OPERATIONRESULT_CB cb, void* pUser);
	void PhotonPeer_SetCBPeerStatus(SPhotonPeer* p, PEERSTATUS_CB cb, void* pUser);
	void PhotonPeer_SetCBEventAction(SPhotonPeer* p,PHOTONEVENTACTION_CB cb, void* pUser);
	void PhotonPeer_SetCBDebugReturn(SPhotonPeer* p, PHOTONDEBUG_CB cb, void* pUser);

	// public API getter/setter functions
	int PhotonPeer_getServerTimeOffset(SPhotonPeer* pMe);
	int PhotonPeer_getServerTime(SPhotonPeer* pMe);
	int PhotonPeer_getBytesOut(SPhotonPeer* pMe);
	int PhotonPeer_getBytesIn(SPhotonPeer* pMe);
	PeerState PhotonPeer_getPeerState(SPhotonPeer* pMe);
	int PhotonPeer_getSentCountAllowance(SPhotonPeer* pMe);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pMe, int setSentCountAllowance);
	int PhotonPeer_getTimePingInterval(SPhotonPeer* pMe);
	void PhotonPeer_setSentCountAllowance(SPhotonPeer* pMe, int setSentCountAllowance);
	void PhotonPeer_setTimePingInterval(SPhotonPeer* pMe, int setTimePingInterval);
	int PhotonPeer_getRoundTripTime(SPhotonPeer* pMe);
	int PhotonPeer_getRoundTripTimeVariance(SPhotonPeer* pMe);
	int PhotonPeer_getIncomingReliableCommandsCount(SPhotonPeer* pMe);
	bool PhotonPeer_setDebugOutputLevel(SPhotonPeer* pMe, PhotonPeer_DebugLevel debugLevel);
	PhotonPeer_DebugLevel PhotonPeer_getDebugOutputLevel(SPhotonPeer* pMe);
	short PhotonPeer_getPeerID(SPhotonPeer* pMe);
	int PhotonPeer_getSentTimeAllowance(SPhotonPeer* pMe);
	void PhotonPeer_setSentTimeAllowance(SPhotonPeer* pMe, int setSentTimetAllowance);
	unsigned int PhotonPeer_getQueuedIncomingCommands(SPhotonPeer* pMe);
	unsigned int PhotonPeer_getQueuedOutgoingCommands(SPhotonPeer* pMe);
	char* PhotonPeer_getServerAdress(SPhotonPeer* pMe);
	bool PhotonPeer_getIsEncryptionAvailable(SPhotonPeer* pMe);

	// internals
	#ifdef EG_DEBUGGER
		#define PhotonPeer_sendErrors PhotonPeer_sendErrorsInternal
	#else
		#define PhotonPeer_sendErrors(peer, debugLevel, error, ...) ((void)0)
	#endif
	void PhotonPeer_sendErrorsInternal(SPhotonPeer* p, PhotonPeer_DebugLevel debugLevel, EG_CHAR* error, ...);
	void PhotonPeer_internal_Disconnected(SPhotonPeer* p);
	void PhotonPeer_internal_send(SPhotonPeer* pPeer, nByte cType, nByte* payload, unsigned int payloadSize, nByte channelId);
	void PhotonPeer_internal_sendDebugged(SPhotonPeer* p, nByte cType, nByte* payload, unsigned int payloadSize, int debugReliableSequenceNumber, int debugUnreliableSequenceNumber, int debugUnsequencedGroupNumber, int debugLooseThisCommandCounter);
	void PhotonPeer_internal_queueOutgoingReliableCommand(SPhotonPeer* p, SPhotonCommand* command);
	void PhotonPeer_internal_queueOutgoingUnreliableCommand(SPhotonPeer* p, SPhotonCommand* command);
	void PhotonPeer_internal_queueOutgoingAcknowledgement(SPhotonPeer* p, SPhotonCommand* command);
	bool PhotonPeer_internal_queueIncomingCommand(SPhotonPeer* p, SPhotonCommand* command);
	void PhotonPeer_internal_queueSentReliableCommand(SPhotonPeer* p, SPhotonCommand* command);
	void PhotonPeer_serviceInternal(SPhotonPeer* p, bool dispatch);
	bool PhotonPeer_internal_serializeOperation(SPhotonPeer* p, EG_HashTable* parameters, nByte opc, nByte** buffer,  int* buffSize, bool encrypt);
	bool PhotonPeer_internal_deserializeOperation(SPhotonPeer* p, nByte* inBuff, int inBuffLength);
	void PhotonPeer_internal_initPhotonPeer(SPhotonPeer* p);
	void PhotonPeer_internal_freePhotonPeer(SPhotonPeer* p);
	void PhotonPeer_internal_initEnetChannel(ENetChannel* channel, nByte channelNumber);
	void PhotonPeer_internal_releaseEnetChannel(ENetChannel* channel);
	int PhotonPeer_internal_serializeToBuffer(SPhotonPeer* p, EG_Vector**);
	void PhotonPeer_internal_removeSentReliableCommand(SPhotonPeer* p, int ackReceivedReliableSequenceNumber,  int ackReceivedChannel, SPhotonCommand** command);
	void PhotonPeer_internal_updateRoundTripTimeVariance(SPhotonPeer* p, int time, int rttUpdateCount); 
	void PhotonPeer_internal_execute(SPhotonPeer* p,SPhotonCommand* command);
	void PhotonPeer_internal_cbNetConnect(void* pUser, int nError);
	void PhotonPeer_internal_cbNetReceiveData(void* pUser, nByte* pBuf, int iCount, int nError);
	void PhotonPeer_internal_sortLastElementInQueue(EG_Vector** argQueue, bool sortByReliableSequenceNumber);
	SPhotonCommand* PhotonPeer_internal_getReliableCommandFromQueue(EG_Vector* queue, int reliableSequenceNumber);
	SPhotonCommand* PhotonPeer_internal_getUnreliableCommandFromQueue(EG_Vector* queue, int unreliableSequenceNumber);
	bool PhotonPeer_internal_removeReliableCommandFromQueue(EG_Vector** queue, int reliableSequenceNumber);
	bool PhotonPeer_internal_removeUnreliableCommandFromQueue(EG_Vector** queue, int unreliableSequenceNumber);
	void PhotonPeer_internal_reportAllQueues(SPhotonPeer* p);
	void PhotonPeer_internal_reportChannel(SPhotonPeer* p, int channelIndex);
	void PhotonPeer_internal_clearAllQueues(SPhotonPeer* p);
	void PhotonPeer_internal_initCallback(SPhotonPeer* p);
#ifdef __cplusplus
}
#endif

#endif //__C_PHOTON_PEER_H__
