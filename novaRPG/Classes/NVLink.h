//
//  NVLink.h
//  novaRPGv2
//
//  Created by Peteo on 11-9-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import  "cocos2d.h"
#include "LitePeer.h"

#import  "NVCharacter.h"
#import  "NVCode.h"

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

@protocol DataReceiver

- (void)receivePacket:(int)packetID objectIndex:(int)objectIndex data:(NSDictionary*)returnValues;

- (void)LinkOperationResult:(nByte)opCode :(int)returnCode :(NSMutableDictionary*)returnValues :(short)invocID;

- (void)LinkEventAction:(nByte)eventCode :(NSMutableDictionary*)photonEvent;

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
@property(nonatomic, assign)   States state;

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
-(void) SendOutgoingCommands;

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
-(void) EnterWorld:(NVCharacter*)pCharacter;

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
-(void) CreateWorld;

/// <summary>
/// The exit world.
/// </summary>
/// <param name="game">
/// The mmo game.
/// </param>

-(void) ExitWorld;

/// <summary>
/// The destroy item.
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

-(void) DestroyItem:(NSString*)itemId;

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

-(BOOL) MoveAbsolute:(float[])newPosition /*float[] rotation */ :(NSString*)itemId ;


@end
