//
//  NVLink.m
//  novaRPGv2
//
//  Created by Peteo on 11-9-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVLink.h"

@implementation NVLink

@synthesize dataReceiver = _dataReceiver;
@synthesize IsWaiting = _IsWaiting;

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
			NSLog(@"stateConnected");
			//[self ExchangeKeys];
			//_state = stateKeysExchanging;
			break;
		case stateKeysExchanging:
			// Waiting for callback
			break;
		case stateKeysExchanged:
			NSLog(@"stateKeysExchanged");
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
	NSLog(@"OperationResult called, opCode = [%d] , returnCode = [%d] invocID = [%d]",opCode, returnCode, invocID);
	
	NSLog(@"%@", [Utils hashToString:returnValues :true]);
	
	switch(opCode)
	{
		case OPC_RT_JOIN:
			_state = stateJoined;
			NSLog(@"stateJoined");
			break;
		case OPC_RT_LEAVE:
			_state = stateLeft;
			NSLog(@"stateLeft");
			break;
		case OPC_RT_RAISE_EV:
			break;
		case OPC_RT_EXCHANGEKEYSFORENCRYPTION:
			[_LitePeer deriveSharedKey:(nByte*)((EGArray*)[returnValues objectForKey:[KeyObject withByteValue:P_SERVER_KEY]]).CArray];
			_state = stateKeysExchanged;
			break;
		default:
			break;
	}
}


- (void) PhotonPeerStatus:(int)statusCode
{
	switch(statusCode)
	{
		case SC_CONNECT:
			_state = stateConnected;
			NSLog(@"-------CONNECTED-------");
			_IsWaiting = NO;
			break;
		case SC_DISCONNECT:
			_state = stateDisconnected;
			NSLog(@"-------DISCONNECTED-------");
			
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
	NSLog(@"-----Listener::EventAction called, eventCode = %d", eventCode);
	
	if(!photonEvent)
		return;
	
	NSLog(@"%@", [Utils hashToString:photonEvent :true]);
	
	//NSMutableDictionary * eventData = nil;
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

#define URL_TEST_SERVER	 L"172.18.19.73:5055"

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
	
	// avoid operation congestion (QueueOutgoingUnreliableWarning)
	_outgoingOperationCount++;
	if (_outgoingOperationCount > 10)
	{
		[_LitePeer sendOutgoingCommands];
		_outgoingOperationCount = 0;
	}
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
	
	NSValue * valArray[2];
	
	for(int i = 0; i < 2; i ++)
	{
		valArray[i] = [NSValue valueWithBytes:&position[i] objCType:@encode(float)];
	}
	
	[data setObject:[EGArray arrayWithObjects:valArray count:2] forKey:[KeyObject withByteValue:(nByte)Position]];
	
	
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
	
	[self SendOperation:EnterWorld :data :true :_OperationChannel ];
	
	[data release];
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
	
	[self SendOperation:CreateWorld :data :true :_OperationChannel];
	
	[data release];
}

-(void) ExitWorld
{
	NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
	
	[self SendOperation:ExitWorld :data :true :_OperationChannel];
	
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
	
	if (rotation != null)
	{
		data.Add((byte)ParameterCode.Rotation, rotation);
	}
	*/
	
	[self SendOperation:Move :data :sendReliable :_ItemChannel];
	
	[data release];
}

@end
