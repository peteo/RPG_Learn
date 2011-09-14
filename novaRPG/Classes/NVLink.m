//
//  NVLink.m
//  novaRPGv2
//
//  Created by Peteo on 11-9-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVLink.h"

#define URL_TEST_SERVER	 L"172.18.19.73:5055"

//#define URL_TEST_SERVER	 L"udp.exitgames.com:5055"

#define WORLD_NAME		 @"WOW-WORLD"

@implementation NVLink

@synthesize dataReceiver = _dataReceiver;
@synthesize IsWaiting    = _IsWaiting;
@synthesize state        = _state;

-(void) onTime:(NSTimer*)Timer
{
	//b_TimerIsRunning = YES;
	[self Run];
}

- (id)init
{
	[super init];
	
	_timer		   = nil;
	
	_LitePeer      = [[LitePeer alloc] init:self];
	_state         = statePhotonPeerCreated;
	
	_timer		   = [[NSTimer scheduledTimerWithTimeInterval:0.1 
													   target:self
													 selector:@selector(onTime:) 
													 userInfo:nil 
												      repeats:YES]retain];
	
	_IsWaiting	   = NO;
	
	_ChannelCount		= 3;
	_RadarChannel		= 0;
	_DiagnosticsChannel = 0;
	_OperationChannel	= 0;
	_ItemChannel		= 0;
	
	return self;
}

- (void)dealloc
{
	[self CloseConnection];
	
	[_LitePeer release];
	
	if(_timer)
	{
		[_timer invalidate];
	}
	[_timer     release];
	
	[super dealloc];
}

-(void) Run
{
	[_LitePeer service:true];
	
	switch (_state)
	{
		case statePhotonPeerCreated:
			[self CreateConnection];
			_IsWaiting = YES;
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
			CCLOG(@"stateKeysExchanged");
			//[self EnterLobby];
			break;
		case stateEnterLobbying:
			break;
		case stateEnterLobbyed:
			break;
		case stateLeaving:
			break;
		case stateDisconnecting:
			[self CloseConnection];
			break;
		case stateDisconnected:
			break;
		case stateErrorConnecting:
			break;
		default:
			break;
	}
}

#pragma mark -
#pragma mark Photon Delegate

- (void) PhotonPeerOperationResult:(nByte)opCode :(int)returnCode :(NSMutableDictionary*)returnValues :(short)invocID
{
	CCLOG(@"OperationResult called, opCode = [%d] , returnCode = [%d] invocID = [%d]",opCode, returnCode, invocID);
	
	CCLOG(@"%@", [Utils hashToString:returnValues :true]);
	
	if(_dataReceiver)
	{
		[_dataReceiver LinkOperationResult:opCode:returnCode:returnValues:invocID];
	}
}


- (void) PhotonPeerStatus:(int)statusCode
{
	switch(statusCode)
	{
		case SC_CONNECT:
			_state = stateConnected;
			CCLOG(@"-------CONNECTED-------");
			_IsWaiting = NO;
			break;
		case SC_DISCONNECT:
			_state = stateDisconnected;
			CCLOG(@"-------DISCONNECTED-------");
			
			UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示！" message:@"无法连接服务器!" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
			[alert show];
			[alert release];
			
			break;
		case SC_EXCEPTION:
			break;
		default:
			break;
	}
}

- (void) PhotonPeerEventAction:(nByte)eventCode :(NSMutableDictionary*)photonEvent
{
	CCLOG(@"-----Listener::EventAction called, eventCode = %d", eventCode);
	
	if(!photonEvent)
		return;
	
	CCLOG(@"%@", [Utils hashToString:photonEvent :true]);
	
	if(_dataReceiver)
	{
		[_dataReceiver LinkEventAction:eventCode :photonEvent];
	}
}

-(void) PhotonPeerDebugReturn:(PhotonPeer_DebugLevel)debugLevel :(NSString*)string
{
	char* lvlstr;
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
			lvlstr = "";
			break;
	}
	printf("%s%s\n", lvlstr, [string UTF8String]);
}

#pragma mark -
#pragma mark Photon Methods

-(void) CreateConnection
{
	//char* server = "udp.exitgames.com:5055";
	
	//nByte * pAppName = (nByte *)"LiteLobby";
	
	nByte * pAppName = (nByte *)"MmoDemo";
	
	//[m_pLitePeer Connect:[NSString stringWithUTF8String:server]];
	
	[_LitePeer Connect:[NSString stringWithUTF32String:URL_TEST_SERVER]:pAppName];
	
	_state = stateConnecting;
}


-(void) CloseConnection
{
	[_LitePeer Disconnect];
}

-(void) ExchangeKeys
{
	[_LitePeer opExchangeKeysForEncryption];
}

-(void) SendOperation:(EOperationCode)operationCode : (NSMutableDictionary*) parameter : (bool) sendReliable : (nByte) channelId 
{
	[_LitePeer opCustom:operationCode :parameter :sendReliable :channelId];
	
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
	
	[_LitePeer sendOutgoingCommands];
}

-(void) SendOutgoingCommands
{
	[_LitePeer sendOutgoingCommands];
}

-(void) EnterWorld:(NSString*) worldName :(NSString*) username : (NSMutableDictionary*) properties : (float[]) position : (float[]) rotation : (float[]) viewDistanceEnter : (float[]) viewDistanceExit
{
	/*
	var data = new Hashtable
	{
		{ (byte)ParameterCode.WorldName, worldName }, 
		{ (byte)ParameterCode.Username, username }, 
		{ (byte)ParameterCode.Position, position }, 
		{ (byte)ParameterCode.ViewDistanceEnter, viewDistanceEnter }, 
		{ (byte)ParameterCode.ViewDistanceExit, viewDistanceExit }
	};
	*/
	
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	[data setObject:worldName forKey:[KeyObject withByteValue:(nByte)WorldName]];
	[data setObject:username  forKey:[KeyObject withByteValue:(nByte)Username]];
	
	NSValue * PositionArray[2];
	
	for(int i = 0; i < 2; i ++)
	{
		PositionArray[i] = [NSValue valueWithBytes:&position[i] objCType:@encode(float)];
	}
	
	[data setObject:[EGArray arrayWithObjects:PositionArray count:2] forKey:[KeyObject withByteValue:(nByte)Position]];
	
	
	NSValue * DistanceEnterArray[2];
	
	for(int i = 0; i < 2; i ++)
	{
		DistanceEnterArray[i] = [NSValue valueWithBytes:&viewDistanceEnter[i] objCType:@encode(float)];
	}
	
	[data setObject:[EGArray arrayWithObjects:DistanceEnterArray count:2] forKey:[KeyObject withByteValue:(nByte)ViewDistanceEnter]];
	
	
	NSValue * DistanceExitArray[2];
	
	for(int i = 0; i < 2; i ++)
	{
		DistanceExitArray[i] = [NSValue valueWithBytes:&viewDistanceExit[i] objCType:@encode(float)];
	}
	
	[data setObject:[EGArray arrayWithObjects:DistanceExitArray count:2] forKey:[KeyObject withByteValue:(nByte)ViewDistanceExit]];
	
	
	if (properties != nil)
	{
		[data setObject:properties  forKey:[KeyObject withByteValue:(nByte)Properties]];
	}
	
	/*
	if (rotation != null)
	{
		data.Add((byte)ParameterCode.Rotation, rotation);
	}
	*/
	
	[self SendOperation:EnterWorld :data :true :_OperationChannel];
	
	[data release];
}

-(void) EnterWorld:(NVCharacter*)pCharacter
{
	float positionArry[2];
	float DistanceEnterArry[2];
	float DistanceExitArry[2];
	
	//CCLOG(@"EnterWorld_POS[%f][%f]",pos.x,pos.y);
	
	positionArry[0] = pCharacter.characterSprite.position.x;
	//转换为左上角为原点的坐标系	
	positionArry[1] = (640 - pCharacter.characterSprite.position.y);
	//positionArry[2] = 0.0f;

	DistanceEnterArry[0] = pCharacter.ViewDistanceEnter.width;
	DistanceEnterArry[1] = pCharacter.ViewDistanceEnter.height;
	//DistanceEnterArry[2] = 0.0f;
	
	DistanceExitArry[0] = pCharacter.ViewDistanceExit.width;
	DistanceExitArry[1] = pCharacter.ViewDistanceExit.height;
	//DistanceExitArry[2] = 0.0f;
	
	_state = stateEnterWorlding;
	
	[self EnterWorld:WORLD_NAME :pCharacter.ItemID :nil :positionArry :NULL :DistanceEnterArry :DistanceExitArry];
	
}



-(void) CreateWorld:(NSString*) worldName : (float[]) topLeftCorner : (float[]) bottomRightCorner : (float[]) tileDimensions
{
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	/*
	var data = new Hashtable
	{
		{ (byte)ParameterCode.WorldName, worldName }, 
		{ (byte)ParameterCode.TopLeftCorner, topLeftCorner }, 
		{ (byte)ParameterCode.BottomRightCorner, bottomRightCorner }, 
		{ (byte)ParameterCode.TileDimensions, tileDimensions }
	};
	*/
	
	[data setObject:worldName forKey:[KeyObject withByteValue:(nByte)WorldName]];
	
	
	NSValue * TopLeftCornerArray[2];
	for(int i = 0; i < 2; i ++)
	{
		TopLeftCornerArray[i] = [NSValue valueWithBytes:&topLeftCorner[i] objCType:@encode(float)];
	}
	[data setObject:[EGArray arrayWithObjects:TopLeftCornerArray count:2] forKey:[KeyObject withByteValue:(nByte)TopLeftCorner]];
	
	
	NSValue * BottomRightCornerArray[2];
	for(int i = 0; i < 2; i ++)
	{
		BottomRightCornerArray[i] = [NSValue valueWithBytes:&bottomRightCorner[i] objCType:@encode(float)];
	}
	[data setObject:[EGArray arrayWithObjects:BottomRightCornerArray count:2] forKey:[KeyObject withByteValue:(nByte)BottomRightCorner]];
	
	
	NSValue * TileDimensionsArray[2];
	for(int i = 0; i < 2; i ++)
	{
		TileDimensionsArray[i] = [NSValue valueWithBytes:&tileDimensions[i] objCType:@encode(float)];
	}
	[data setObject:[EGArray arrayWithObjects:TileDimensionsArray count:2] forKey:[KeyObject withByteValue:(nByte)TileDimensions]];
	
	
	[self SendOperation:CreateWorld :data :true :_OperationChannel];
	
	[data release];
}

-(void) CreateWorld
{
	float topLeftCornerArry[2];
	float bottomRightCornerArry[2];
	float tileDimensionsArry[2];
	
	topLeftCornerArry[0] = 1.0f;
	topLeftCornerArry[1] = 1.0f;
	//topLeftCornerArry[2] = 0.0f;
	
	bottomRightCornerArry[0] = 640.0f;
	bottomRightCornerArry[1] = 640.0f;
	//bottomRightCornerArry[2] =   0.0f;
	
	tileDimensionsArry[0] = 1.0f;
	tileDimensionsArry[1] = 1.0f;
	//tileDimensionsArry[2] = 0.0f;
	
	_state = stateCreateWorlding;
	
	[self CreateWorld:WORLD_NAME :topLeftCornerArry :bottomRightCornerArry :tileDimensionsArry];
	
}

-(void) ExitWorld
{
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	[self SendOperation:ExitWorld :data :true :_OperationChannel];
	
	[data release];
}

-(void) DestroyItem:(NSString*)itemId
{
	
	//var data = new Hashtable {}, { (byte)ParameterCode.ItemType, itemType } };
	
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	[data setObject:itemId forKey:[KeyObject withByteValue:(nByte)ItemId]];
	
	Byte p = 0;
	
	[data setObject: [NSValue valueWithBytes:&p objCType:@encode(Byte)] forKey:[KeyObject withByteValue:(nByte)ItemType]];
	
	[self SendOperation:DestroyItem :data :true :_ItemChannel];
	
	[data release];
	
}

-(void) Move:(NSString*)itemId /*: byte? itemType*/ : (float[]) position : (float[]) rotation : (bool) sendReliable
{
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	NSValue * valArray[2];
	for(int i = 0; i < 2; i ++)
	{
		valArray[i] = [NSValue valueWithBytes:&position[i] objCType:@encode(float)];
	}
	[data setObject:[EGArray arrayWithObjects:valArray count:2] forKey:[KeyObject withByteValue:(nByte)Position]];
	
	//var data = new Hashtable { { (byte)ParameterCode.Position, position } };
	
	if (itemId)
	{
		[data setObject:itemId forKey:[KeyObject withByteValue:(nByte)ItemId]];
	}
	
	/*
	if (itemType.HasValue)
	{
		data.Add((byte)ParameterCode.ItemType, itemType.Value);
	}
	*/
	
	if (rotation != NULL)
	{
		//data.Add((byte)ParameterCode.Rotation, rotation);
		NSValue * rotationArray[1];
		for(int i = 0; i < 1; i ++)
		{
			rotationArray[i] = [NSValue valueWithBytes:&rotation[i] objCType:@encode(float)];
		}
		[data setObject:[EGArray arrayWithObjects:rotationArray count:1] forKey:[KeyObject withByteValue:(nByte)Rotation]];
	}
	
	CCLOG(@"Move[%f][%f]",position[0],position[1]);
	
	[self SendOperation:Move :data :sendReliable :_ItemChannel];
	
	[data release];
}

-(BOOL) MoveAbsolute:(float[])newPosition :(float[])rotation :(NSString*)itemId
{
	if (newPosition[0] < 16.0f /*this.Game.WorldData.TopLeftCorner[0]*/)
	{
		return NO;
	}
	
	if (newPosition[0] > 624.0f /*this.Game.WorldData.BottomRightCorner[0]*/)
	{
		return NO;
	}
	
	if (newPosition[1] < 16.0f /*this.Game.WorldData.TopLeftCorner[1]*/)
	{
		return NO;
	}
	
	if (newPosition[1] > 624.0f /*this.Game.WorldData.BottomRightCorner[1]*/)
	{
		return NO;
	}
	
	//this.SetPositions(newPosition, this.Position, rotation, this.Rotation);
	
	[self Move:itemId :newPosition :rotation :false];
	
	//Operations.Move(this.Game, this.Id, this.Type, newPosition, rotation, this.Game.Settings.SendReliable);
	
	return YES;
}

@end
