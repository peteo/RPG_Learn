/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __ENET_PEER_LAYER_H
#define __ENET_PEER_LAYER_H

#include "PeerLayerBase.h"

class EnetPeerLayer: public PeerLayerBase
{
private:
    virtual int Init(void** ppMod, SPhotonPeer* pPeer);
    virtual bool CreateConnection(SPhotonConnect* pConnect, char* ipAddr, CONNECT_CB pfn, void* pUser);
    virtual void SendOutgoingCommands(SPhotonPeer* pPeer);
    virtual void ConnectService(SPhotonConnect* pConnect);
    virtual void CopyCommandToBuffer(SPhotonCommand* pCommand, nByte* pDst, const nByte* pSrc, int& size);
    virtual void FetchServerTimestamp(SPhotonPeer* pPeer);
    virtual void OnConnectCallback(SPhotonPeer* pPeer, int nError);
    virtual void OnReceiveDataCallback(SPhotonPeer* pPeer, nByte* pBuf, int iCount, int nError);
    virtual void OnDisconnectCommand(SPhotonPeer* pPeer);
	virtual bool NeedToCheckSequenceNumber(void);
};

#endif