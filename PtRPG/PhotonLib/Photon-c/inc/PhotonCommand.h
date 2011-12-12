/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_COMMAND_H
#define __PHOTON_COMMAND_H

#include "platformLayer.h"
#include "Constants.h"
#include "PhotonPlatformLayer.h"
#include "PhotonConstants.h"

typedef struct
{
	nByte  Command;
	nByte  ChannelID;
	nByte  Flags;
	nByte  Reserved;
	int   CommandLength;
	int   ReliableSequenceNumber;
} CommandHeader; 

typedef struct
{
	nByte  Ident;
	short Ticket;
	short DataLength;
	nByte  MessageType;
} PhotonUDPHeader; 

/* \ \  */
struct _SPhotonCommand
{
	#ifdef _EG_BREW_PLATFORM
		PlatformSpecific m_Platform;
	#endif

    unsigned int nRefs;

    nByte commandFlags;
    nByte commandType;

    //variables from CommandHeader
    nByte commandChannelID;

	//variables for fragments (not used otherwise)
	int startSequenceNumber;
	int fragmentCount;
	int fragmentNumber;
	int totalLength;
	int fragmentOffset;
	int fragmentsRemaining;

    int               debugReliableSequenceNumber;
    int               debugUnreliableSequenceNumber;
    int               debugUnsequencedGroupNumber;
    int               debugLooseThisCommandCounter;

    int               reliableSequenceNumber;
    int               unreliableSequenceNumber;
    int               unsequencedGroupNumber;
	nByte			  reservedByte;

    nByte*            commandPayload; // replaces "Packet"
    int               commandPayloadLen;
	int               commandSentTime; //last time the command was sent
	int               commandOriginalSentTime; //first time the command was sent
    nByte             commandSentCount; //counts the number of retries (before calling it a loss)
    int               ackReceivedReliableSequenceNumber; //for ACK commands
    int               ackReceivedSentTime; //for ACK commands
	int				  roundTripTimeout; // milliseconds until the command is resent
};

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _EG_BREW_PLATFORM
	int PhotonCommand_New(PlatformSpecific* pPlatform, SPhotonCommand** ppMod);
	unsigned long PhotonCommand_AddRef(SPhotonCommand* po);
	unsigned long PhotonCommand_Release(SPhotonCommand* po);
#else
	int PhotonCommand_New(SPhotonCommand** ppMod);
	unsigned int PhotonCommand_AddRef(SPhotonCommand* po);
	unsigned int PhotonCommand_Release(SPhotonCommand* po);
#endif

  void PhotonCommand_CreateCopy(SPhotonCommand* pMe, SPhotonCommand* pSrc);
  void PhotonCommand_CreateCommand(SPhotonCommand* pMe, SPhotonPeer* pPeer, nByte cType, nByte* payload, unsigned int payloadSize);
  void PhotonCommand_CreateCommandFromBuffer(SPhotonCommand* pMe, SPhotonPeer* pPeer, nByte* pBuffer, unsigned int bufferSize, int* nRead, int sentTime);
  void PhotonCommand_CreateCommandFromTcpBuffer(SPhotonCommand* pMe, SPhotonPeer* pPeer, nByte* pBuffer, unsigned int bufferSize, int* nRead);
  void PhotonCommand_createAck(SPhotonCommand* pMe, SPhotonPeer* pPeer, SPhotonCommand* commandToAck);
  void PhotonCommand_serialize(SPhotonCommand* pMe, nByte** buf, int* size);

#ifdef __cplusplus
}
#endif

#endif //__PHOTON_COMMAND_H__
