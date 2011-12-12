/*
 *  PtLink.h
 *  PtRPG
 *
 *  Created by Peteo on 11-10-8.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#ifndef __PT_LINK_H__
#define __PT_LINK_H__

#include "LitePeer.h"
#include "PtCode.h"
#include "cocos2d.h"

#define URL_TEST_SERVER	 L"114.80.197.41:5055"

//#define URL_TEST_SERVER	 L"172.18.19.117:5055"

//#define URL_TEST_SERVER	 L"udp.exitgames.com:5055"

#define WORLD_NAME		 L"WOW-WORLD8"

typedef enum States
{
	statePhotonPeerCreated,
	
	stateConnecting,
	stateConnected,
	stateErrorConnecting,
	
	stateKeysExchanging,
	stateKeysExchanged,
	
	stateJoining,
	stateErrorJoining,
	stateJoined,
	
	stateLeaving,
	stateErrorLeaving,
	stateLeft,
	
	stateReceiving,
	stateDisconnecting,
	stateDisconnected,
	
	stateEnterLobbying,
	stateEnterLobbyed,
	
	stateCreateWorlding,
	stateCreateWorlded,
	
	stateEnterWorlding,
	stateEnterWorlded
	
}States;

using namespace ExitGames;
USING_NS_CC;

class PtCharacter;

class PtLink : public PhotonListener
{
public:
	PtLink();
	virtual ~ PtLink();
	bool InitLib(PhotonListener * pListener);

private:
	LitePeer       * m_pLitePeer;
	PhotonListener * m_pListener;
	
	int	_outgoingOperationCount;
	
	//Channel Setting
	int _ChannelCount;
	int _RadarChannel;
	int _DiagnosticsChannel;
	int _OperationChannel;
	int _ItemChannel;
	int _MoveChannel;
	
public:
	
	States       _state;
	bool         _IsWaiting;

private:
	void onOperationResponse(const ExitGames::OperationResponse& operationResponse);
	void onStatusChanged(int statusCode);
	void onEvent(const ExitGames::EventData& eventData);
	void debugReturn(PhotonPeer_DebugLevel debugLevel, const ExitGames::JString& string);

public:
	
	void Run();
	
	/// <summary>
	/// connect to the server.
	/// </summary>
	void CreateConnection();
	
	/// <summary>
	/// disconnect.
	/// </summary>
	void CloseConnection();
	
	/// <summary>
	/// Exchange clien and server Keys.
	/// </summary>
	void ExchangeKeys();
	
	/// <summary>
	/// The send operation.
	/// </summary>
	/// <param name="operationCode">
	/// The operation code.
	/// </param>
	/// <param name="parameter">
	/// The parameter.
	/// </param>
	/// <param name="sendReliable">
	/// The send reliable.
	/// </param>
	/// <param name="channelId">
	/// The channel Id.
	/// </param>
	void SendOperation(ExitGameCode::EOperationCode operationCode,const Hashtable& parameter,bool sendReliable,nByte channelId);
	void SendOutgoingCommands();
	
	/// <summary>
	/// The enter world.
	/// </summary>
	/// <param name="game">
	/// The mmo game.
	/// </param>
	/// <param name="username">
	/// The username.
	/// </param>
	/// <param name="properties">
	/// The properties.
	/// </param>
	/// <param name="position">
	/// The position.
	/// </param>
	/// <param name="rotation">
	/// The rotation.
	/// </param>
	/// <param name="viewDistanceEnter">
	/// The view Distance Enter.
	/// </param>
	/// <param name="viewDistanceExit">
	/// The view Distance Exit.
	/// </param>
	
	void EnterWorld(CCString* username,const Hashtable& properties,float position[],float rotation[],float viewDistanceEnter[],float viewDistanceExit[]);
	void EnterWorld(PtCharacter* pCharacter);
	
	/// <summary>
	/// The create world.
	/// </summary>
	/// <param name="game">
	/// The mmo game.
	/// </param>
	/// <param name="worldName">
	/// The world name.
	/// </param>
	/// <param name="topLeftCorner">
	/// The top left corner.
	/// </param>
	/// <param name="bottomRightCorner">
	/// The bottom right corner.
	/// </param>
	/// <param name="tileDimensions">
	/// The tile dimensions.
	/// </param>
	
	void CreateWorld(float topLeftCorner[],float bottomRightCorner[],float tileDimensions[]);
	void CreateWorld();
	
	/// <summary>
	/// The exit world.
	/// </summary>
	
	void ExitWorld();
	
	/// <summary>
	/// The destroy item.
	/// </summary>
	/// <param name="itemId">
	/// The item id.
	/// </param>
	
	void DestroyItem(CCString* itemId);
	
	/// <summary>
	/// The move operation.
	/// </summary>
	/// <param name="game">
	/// The mmo game.
	/// </param>
	/// <param name="itemId">
	/// The item id.
	/// </param>
	/// <param name="position">
	/// The position.
	/// </param>
	/// <param name="rotation">
	/// The rotation.
	/// </param>
	/// <param name="sendReliable">
	/// The send Reliable.
	/// </param>
	
	void Move(CCString* itemId,float position[],float rotation[],bool sendReliable);
	
	/// <summary>
	/// The move operation.
	/// </summary>
	/// <param name="newPosition">
	/// The new position.
	/// </param>
	/// <param name="rotation">
	/// The rotation.
	/// </param>
	/// <returns>
	/// The move absolute.
	/// </returns>
	
	bool MoveAbsolute(float newPosition[],float rotation[],CCString* itemId);
	
	/// <summary>
	/// The radar subscribe.
	/// </summary>

	void RadarSubscribe();
};

#endif