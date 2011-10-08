/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __C_LITE_PEER_H
#define __C_LITE_PEER_H

#include "data_structures.h"
#include "PhotonCommand.h"

#ifdef __cplusplus
extern "C"
{
#endif
	// public API functions
	short LitePeer_opRaiseEvent(SPhotonPeer* p, bool sendReliable, EG_HashTable* evData, nByte eventCode, nByte channelId, int* targetActors, short numTargetActors);
	short LitePeer_opJoin(SPhotonPeer* p, EG_CHAR* gameId);
	short LitePeer_opJoinWithProperties(SPhotonPeer* p, EG_CHAR* gameId, EG_HashTable* gameProperties, EG_HashTable* actorProperties, bool broadcastActorProperties);
	short LitePeer_opLeave(SPhotonPeer* p, EG_CHAR* gameId);
	short LitePeer_opSetPropertiesOfActor(SPhotonPeer* pSPeer, int actorNr, EG_HashTable* properties, bool broadcast, nByte channelId);
	short LitePeer_opSetPropertiesOfGame(SPhotonPeer* pSPeer, EG_HashTable* properties, bool broadcast, nByte channelId);
	short LitePeer_opGetProperties(SPhotonPeer* pSPeer, nByte channelId);
	short LitePeer_opGetPropertiesOfActorByStringKeys(SPhotonPeer* pSPeer, int* actorNrList, short numActors, EG_CHAR** actorProperties, short numActorProperties, nByte channelId);
	short LitePeer_opGetPropertiesOfActorByByteKeys(SPhotonPeer* pSPeer, int* actorNrList, short numActors, nByte* actorProperties, short numActorProperties, nByte channelId);
	short LitePeer_opGetPropertiesOfGameByStringKeys(SPhotonPeer* pSPeer, EG_CHAR** gameProperties, short numGameProperties, nByte channelId);
	short LitePeer_opGetPropertiesOfGameByByteKeys(SPhotonPeer* pSPeer, nByte* gameProperties, short numGameProperties, nByte channelId);

	// internals
	short LitePeer_internal_opRaiseEvent(SPhotonPeer* p, bool sendReliable, EG_HashTable* evData, nByte eventCode, nByte channelId, int* targetActors, short numTargetActors, bool copy);
	short LitePeer_internal_opJoin(SPhotonPeer* p, EG_CHAR* gameId, EG_HashTable* gameProperties, EG_HashTable* actorProperties, bool broadcastActorProperties, bool copy);
	short LitePeer_internal_opSetPropertiesOfActor(SPhotonPeer* pSPeer, int actorNr, EG_HashTable* properties, bool broadcast, nByte channelId, bool copy);
	short LitePeer_internal_opSetPropertiesOfGame(SPhotonPeer* pSPeer, EG_HashTable* properties, bool broadcast, nByte channelId, bool copy);
#ifdef __cplusplus
}
#endif 

#endif //__C_LITE_PEER_H__