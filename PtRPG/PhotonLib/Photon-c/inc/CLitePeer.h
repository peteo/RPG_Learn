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
	bool LitePeer_opRaiseEvent(SPhotonPeer* pPeer, bool sendReliable, EG_HashTable* evData, nByte eventCode, nByte channelId, int* targetActors, short numTargetActors);
	bool LitePeer_opJoin(SPhotonPeer* pPeer, EG_CHAR* gameId);
	bool LitePeer_opJoinWithProperties(SPhotonPeer* pPeer, EG_CHAR* gameId, EG_HashTable* gameProperties, EG_HashTable* actorProperties, bool broadcastActorProperties);
	bool LitePeer_opLeave(SPhotonPeer* pPeer, EG_CHAR* gameId);
	bool LitePeer_opSetPropertiesOfActor(SPhotonPeer* pPeer, int actorNr, EG_HashTable* properties, bool broadcast, nByte channelId);
	bool LitePeer_opSetPropertiesOfGame(SPhotonPeer* pPeer, EG_HashTable* properties, bool broadcast, nByte channelId);
	bool LitePeer_opGetProperties(SPhotonPeer* pPeer, nByte channelId);
	bool LitePeer_opGetPropertiesOfActorByStringKeys(SPhotonPeer* pPeer, EG_CHAR** actorProperties, short numActorProperties, int* actorNrList, short numActors, nByte channelId);
	bool LitePeer_opGetPropertiesOfActorByByteKeys(SPhotonPeer* pPeer, nByte* actorProperties, short numActorProperties, int* actorNrList, short numActors, nByte channelId);
	bool LitePeer_opGetPropertiesOfGameByStringKeys(SPhotonPeer* pPeer, EG_CHAR** gameProperties, short numGameProperties, nByte channelId);
	bool LitePeer_opGetPropertiesOfGameByByteKeys(SPhotonPeer* pPeer, nByte* gameProperties, short numGameProperties, nByte channelId);

	// internals
	bool LitePeer_internal_opRaiseEvent(SPhotonPeer* pPeer, bool sendReliable, EG_HashTable* evData, nByte eventCode, nByte channelId, int* targetActors, short numTargetActors, bool copy);
	bool LitePeer_internal_opJoin(SPhotonPeer* pPeer, EG_CHAR* gameId, EG_HashTable* gameProperties, EG_HashTable* actorProperties, bool broadcastActorProperties, bool copy);
	bool LitePeer_internal_opSetPropertiesOfActor(SPhotonPeer* pPeer, int actorNr, EG_HashTable* properties, bool broadcast, nByte channelId, bool copy);
	bool LitePeer_internal_opSetPropertiesOfGame(SPhotonPeer* pPeer, EG_HashTable* properties, bool broadcast, nByte channelId, bool copy);
#ifdef __cplusplus
}
#endif 

#endif //__C_LITE_PEER_H__