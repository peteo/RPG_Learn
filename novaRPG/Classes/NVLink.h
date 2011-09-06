//
//  NVLink.h
//  novaRPGv2
//
//  Created by Peteo on 11-9-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import  "cocos2d.h"
#import  "NVCode.h"
#include "LitePeer.h"

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
	stateEnterLobbyed
	
}States;

@protocol DataReceiver

- (void)receivePacket:(int)packetID objectIndex:(int)objectIndex data:(NSDictionary*)returnValues;

@end

@interface NVLink : NSObject < PhotonListener >
{
	id<DataReceiver> _dataReceiver;
	
	LitePeer    *_LitePeer;
	States       _state;
	BOOL         _IsWaiting;
	
	NSTimer		*_timer;
	
	int			 _outgoingOperationCount;
	
	//Channel Setting
	int _ChannelCount;
	int _RadarChannel;
	int _DiagnosticsChannel;
	int _OperationChannel;
	int _ItemChannel;
	
	
}

@property(nonatomic, assign)   id<DataReceiver> dataReceiver;
@property(nonatomic, readonly) BOOL IsWaiting;

-(void) Run;
-(void) CreateConnection;
-(void) CloseConnection;
-(void) ExchangeKeys;

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

-(void) SendOperation:(EOperationCode)operationCode : (NSMutableDictionary*) parameter : (bool) sendReliable : (nByte) channelId ;

/// <summary>
/// The enter world.
/// </summary>
/// <param name="game">
/// The mmo game.
/// </param>
/// <param name="worldName">
/// The world name.
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

-(void) EnterWorld:(NSString*) worldName :(NSString*) username : (NSMutableDictionary*) properties : (float[]) position : (float[]) rotation : (float[]) viewDistanceEnter : (float[]) viewDistanceExit;	

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

-(void) CreateWorld:(NSString*) worldName : (float[]) topLeftCorner : (float[]) bottomRightCorner : (float[]) tileDimensions;

/// <summary>
/// The exit world.
/// </summary>
/// <param name="game">
/// The mmo game.
/// </param>

-(void) ExitWorld;

/// <summary>
/// The move operation.
/// </summary>
/// <param name="game">
/// The mmo game.
/// </param>
/// <param name="itemId">
/// The item id.
/// </param>
/// <param name="itemType">
/// The item type.
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

-(void) Move:(NSString*)itemId /*: byte? itemType*/ : (float[]) position : (float[]) rotation : (bool) sendReliable;


@end
