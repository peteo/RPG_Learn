/*
 *  PtLink.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-10-8.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "PtLink.h"
#include "PtCharacter.h"


PtLink::PtLink()
:m_pLitePeer(NULL)
,m_pListener(NULL)
{
	
}

PtLink::~PtLink()
{
	CloseConnection();
	
	if(m_pLitePeer)
	{
		delete m_pLitePeer;
		m_pLitePeer = NULL;
	}
}

bool PtLink::InitLib(PhotonListener * pListener)
{
	m_pLitePeer = new LitePeer(this);
	
	m_pListener = pListener;
	
	_state      = statePhotonPeerCreated;
	
	_IsWaiting	= false;
	
	_ChannelCount		= 3;
	_RadarChannel		= 0;
	_DiagnosticsChannel = 0;
	_OperationChannel	= 0;
	_ItemChannel		= 0;
	_MoveChannel        = 0;
	
	return true;
}


void PtLink::PhotonPeerOperationResult(nByte opCode, int returnCode, const Hashtable& returnValues,short invocID)
{
	CCLOG("OperationResult called, opCode = [%d] , returnCode = [%d] invocID = [%d]",opCode, returnCode, invocID);
	
	//CCLOG("%s", returnValues.toString(true).ANSIRepresentation().cstr());
	
	if(m_pListener)
	{
		m_pListener->PhotonPeerOperationResult(opCode,returnCode,returnValues,invocID);
	}
}

void PtLink::PhotonPeerStatus(int statusCode)
{
	switch(statusCode)
	{
		case SC_CONNECT:
			_state = stateConnected;
			CCLOG("-------CONNECTED-------");
			_IsWaiting = false;
			break;
		case SC_DISCONNECT:
			_state = stateDisconnected;
			CCLOG("-------DISCONNECTED-------");
			/*
			UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示！" message:@"无法连接服务器!" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
			[alert show];
			[alert release];
			*/
			break;
		case SC_EXCEPTION:
			break;
		default:
			break;
	}
	
	if(m_pListener)
	{
		m_pListener->PhotonPeerStatus(statusCode);
	}
}

void PtLink::PhotonPeerEventAction(nByte eventCode,const Hashtable& photonEvent)
{
	CCLOG("-----Listener::EventAction called, eventCode = %d", eventCode);
	
	//CCLOG("%s", photonEvent.toString(true).cstr());
	
	if(m_pListener)
	{
		m_pListener->PhotonPeerEventAction(eventCode,photonEvent);
	}
}

void PtLink::PhotonPeerDebugReturn(PhotonPeer_DebugLevel debugLevel, const JString& string)
{
	ExitGames::JString lvlstr;
	switch(debugLevel)
	{
		case DEBUG_LEVEL_OFF:
			lvlstr = "FATAL ERROR: ";
			break;
		case DEBUG_LEVEL_ERRORS:
			lvlstr = "ERROR: ";
			break;
		case DEBUG_LEVEL_WARNINGS:
			lvlstr = "WARNING: ";
			break;
		case DEBUG_LEVEL_INFO:
			lvlstr = "INFO: ";
			break;
		case DEBUG_LEVEL_ALL:
			lvlstr = "DEBUG: ";
			break;
		default:
			break;
	}
	wprintf(L"%ls%ls\n", lvlstr.cstr(), string.cstr());
}


void PtLink::Run()
{
	m_pLitePeer->service(true);
	
	m_pLitePeer->sendOutgoingCommands();
	
	switch (_state)
	{
		case statePhotonPeerCreated:
			CreateConnection();
			_IsWaiting = true;
			break;
		case stateConnecting:
			// Waiting callback function
			break;
		case stateConnected:
			// exchanging keys
			//NSLog(@"stateConnected");
			//[self ExchangeKeys];
			//_state = stateKeysExchanging;
			break;
		case stateKeysExchanging:
			// Waiting for callback
			break;
		case stateKeysExchanged:
			CCLOG("stateKeysExchanged");
			//[self EnterLobby];
			break;
		case stateEnterLobbying:
			break;
		case stateEnterLobbyed:
			break;
		case stateLeaving:
			break;
		case stateDisconnecting:
			CloseConnection();
			break;
		case stateDisconnected:
			break;
		case stateErrorConnecting:
			break;
		default:
			break;
	}
}

void PtLink::CreateConnection()
{
	nByte * pAppName = (nByte *)"MmoDemo";
	
	m_pLitePeer->Connect(URL_TEST_SERVER,pAppName);

	_state = stateConnecting;
}


void PtLink::CloseConnection()
{
	m_pLitePeer->Disconnect();
}


void PtLink::ExchangeKeys()
{
	m_pLitePeer->opExchangeKeysForEncryption();
}


void PtLink::SendOperation(ExitGameCode::EOperationCode operationCode,const Hashtable& parameter,bool sendReliable,nByte channelId)
{
	m_pLitePeer->opCustom(operationCode,parameter,sendReliable,channelId);
	
	/*
	 CCLOG(@"SendOperation");
	 CCLOG(@"%@", [Utils hashToString:parameter :true]);
	 
	 // avoid operation congestion (QueueOutgoingUnreliableWarning)
	 _outgoingOperationCount++;
	 if (_outgoingOperationCount > 10)
	 {
	 [_LitePeer sendOutgoingCommands];
	 _outgoingOperationCount = 0;
	 }
	 */
	
	m_pLitePeer->sendOutgoingCommands();
}

void PtLink::SendOutgoingCommands()
{
	m_pLitePeer->sendOutgoingCommands();
}


void PtLink::EnterWorld(CCString* username,const Hashtable& properties,float position[],float rotation[],float viewDistanceEnter[],float viewDistanceExit[])
{
	ExitGames::Hashtable data;
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::WorldName), ExitGames::ValueObject<ExitGames::JString>(WORLD_NAME));
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Username),  ExitGames::ValueObject<ExitGames::JString>(username->m_sString.c_str()));
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position),          ExitGames::ValueObject<float*>(position, 2));
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ViewDistanceEnter), ExitGames::ValueObject<float*>(viewDistanceEnter, 2));
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ViewDistanceExit),  ExitGames::ValueObject<float*>(viewDistanceExit, 2));
	
	if (&properties != NULL)
	{
		data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Properties),    ExitGames::ValueObject<ExitGames::Hashtable>(properties));
	}
	
	SendOperation(ExitGameCode::EnterWorld,data,true,_OperationChannel);
}

void PtLink::EnterWorld(PtCharacter* pCharacter)
{
	float positionArry[2];
	float DistanceEnterArry[2];
	float DistanceExitArry[2];
	
	//CCLOG(@"EnterWorld_POS[%f][%f]",pos.x,pos.y);
	
	//转换为右上角为原点的坐标系	
	positionArry[0] = (640 - pCharacter->_characterSprite->getPosition().x);
	positionArry[1] = (640 - pCharacter->_characterSprite->getPosition().y);
	
	DistanceEnterArry[0] = pCharacter->_ViewDistanceEnter.width;
	DistanceEnterArry[1] = pCharacter->_ViewDistanceEnter.height;
	
	DistanceExitArry[0]  = pCharacter->_ViewDistanceExit.width;
	DistanceExitArry[1]  = pCharacter->_ViewDistanceExit.height;
	
	_state = stateEnterWorlding;
	
	ExitGames::Hashtable data;
	
	EnterWorld(pCharacter->getItemID(),data,positionArry,NULL,DistanceEnterArry,DistanceExitArry);
}

void PtLink::CreateWorld(float topLeftCorner[],float bottomRightCorner[],float tileDimensions[])
{
	ExitGames::Hashtable data;
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::WorldName), ExitGames::ValueObject<ExitGames::JString>(WORLD_NAME));
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::TopLeftCorner),          ExitGames::ValueObject<float*>(topLeftCorner, 2));
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::BottomRightCorner),      ExitGames::ValueObject<float*>(bottomRightCorner, 2));
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::TileDimensions),         ExitGames::ValueObject<float*>(tileDimensions, 2));
	
	SendOperation(ExitGameCode::CreateWorld,data,true,_OperationChannel);
}

void PtLink::CreateWorld()
{
	float topLeftCornerArry[2];
	float bottomRightCornerArry[2];
	float tileDimensionsArry[2];
	
	topLeftCornerArry[0] = 1.0f;
	topLeftCornerArry[1] = 1.0f;
	
	bottomRightCornerArry[0] = 640.0f;
	bottomRightCornerArry[1] = 640.0f;
	
	tileDimensionsArry[0] = 32.0f;
	tileDimensionsArry[1] = 32.0f;
	
	_state = stateCreateWorlding;
	
	CreateWorld(topLeftCornerArry,bottomRightCornerArry,tileDimensionsArry);
}


void PtLink::ExitWorld()
{
	ExitGames::Hashtable data;
	
	SendOperation(ExitGameCode::ExitWorld,data,true,_OperationChannel);
}

void PtLink::DestroyItem(CCString* itemId)
{
	ExitGames::Hashtable data;
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId), ExitGames::ValueObject<ExitGames::JString>(itemId->m_sString.c_str()));
	
	Byte p = 0;

	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemType), ExitGames::ValueObject<Byte>(p));
	
	SendOperation(ExitGameCode::DestroyItem,data,true,_ItemChannel);
}

void PtLink::Move(CCString* itemId,float position[],float rotation[],bool sendReliable)
{
	ExitGames::Hashtable data;
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position),          ExitGames::ValueObject<float*>(position, 2));
	
	if (itemId)
	{
		data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId),        ExitGames::ValueObject<ExitGames::JString>(itemId->m_sString.c_str()));
	}
	
	if (rotation != NULL)
	{
		data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Rotation),      ExitGames::ValueObject<float*>(rotation, 2));
	}
	
	SendOperation(ExitGameCode::Move,data,sendReliable,_MoveChannel);
}

bool PtLink::MoveAbsolute(float newPosition[],float rotation[],CCString* itemId)
{
	if (newPosition[0] < 16.0f /*this.Game.WorldData.TopLeftCorner[0]*/)
	{
		return false;
	}
	
	if (newPosition[0] > 624.0f /*this.Game.WorldData.BottomRightCorner[0]*/)
	{
		return false;
	}
	
	if (newPosition[1] < 16.0f /*this.Game.WorldData.TopLeftCorner[1]*/)
	{
		return false;
	}
	
	if (newPosition[1] > 624.0f /*this.Game.WorldData.BottomRightCorner[1]*/)
	{
		return false;
	}
	
	Move(itemId,newPosition,rotation,false);
	
	return true;
}

void PtLink::RadarSubscribe()
{
	ExitGames::Hashtable data;
	
	data.put(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::WorldName),      ExitGames::ValueObject<ExitGames::JString>(WORLD_NAME));
	
	SendOperation(ExitGameCode::RadarSubscribe,data,true,_RadarChannel);
}
