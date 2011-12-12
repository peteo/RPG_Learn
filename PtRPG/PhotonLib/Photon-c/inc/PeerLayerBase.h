
#ifndef __PEER_LAYER_BASE_H
#define __PEER_LAYER_BASE_H

#include "Photon.h"
#include "data_structures.h"

class PeerLayerBase
{
public:
	static PeerLayerBase* Create(bool useTcp);

	virtual int Init(void** ppMod, SPhotonPeer* pPeer) = 0;
	virtual bool CreateConnection(SPhotonConnect* pConnect, char* ipAddr, CONNECT_CB pfn, void* pUser) = 0;
	virtual void SendOutgoingCommands(SPhotonPeer* pPeer) = 0;
	virtual void ConnectService(SPhotonConnect* pConnect) = 0;
	virtual void CopyCommandToBuffer(SPhotonCommand* pCommand, nByte* pDst, const nByte* pSrc, int& size) = 0;
	virtual void FetchServerTimestamp(SPhotonPeer* pPeer) = 0;
	virtual void OnConnectCallback(SPhotonPeer* pPeer, int nError) = 0;
	virtual void OnReceiveDataCallback(SPhotonPeer* pPeer, nByte* pBuf, int iCount, int nError) = 0;
	virtual void OnDisconnectCommand(SPhotonPeer* pPeer) = 0;
	virtual bool NeedToCheckSequenceNumber(void) = 0;

protected:
	static void PhotonPeer_cbfSendCommandsCB(SPhotonPeer* pPeer, int nError);
};

#endif