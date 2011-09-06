//
//  NVCode.h
//  novaRPGv2
//
//  Created by Peteo on 11-9-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "LitePeer.h"

typedef enum EErrorCode
{
	/// <summary>
	/// The ok code.
	/// </summary>
	Ok = 0, 
	
	/// <summary>
	/// The fatal.
	/// </summary>
	Fatal = 1, 
	
	/// <summary>
	/// The parameter out of range.
	/// </summary>
	ParameterOutOfRange = 51, 
	
	/// <summary>
	/// The operation not supported.
	/// </summary>
	OperationNotSupported, 
	
	/// <summary>
	/// The invalid operation parameter.
	/// </summary>
	InvalidOperationParameter, 
	
	/// <summary>
	/// The invalid operation.
	/// </summary>
	InvalidOperation, 
	
	/// <summary>
	/// The avatar access denied.
	/// </summary>
	ItemAccessDenied, 
	
	/// <summary>
	/// interest area not found.
	/// </summary>
	InterestAreaNotFound, 
	
	/// <summary>
	/// The interest area already exists.
	/// </summary>
	InterestAreaAlreadyExists, 
	
	/// <summary>
	/// The world already exists.
	/// </summary>
	WorldAlreadyExists = 101, 
	
	/// <summary>
	/// The world not found.
	/// </summary>
	WorldNotFound, 
	
	/// <summary>
	/// The item already exists.
	/// </summary>
	ItemAlreadyExists, 
	
	/// <summary>
	/// The item not found.
	/// </summary>
	ItemNotFound
	
}EErrorCode;

typedef enum EEventCode /*: byte */
{
	/// <summary>
	/// The actor leave.
	/// </summary>
	ItemDestroyed = 1, 
	
	/// <summary>
	/// The actor move.
	/// </summary>
	ItemMoved, 
	
	/// <summary>
	/// The item properties set.
	/// </summary>
	ItemPropertiesSet, 
	
	/// <summary>
	/// The item generic.
	/// </summary>
	ItemGeneric, 
	
	/// <summary>
	/// The world exited.
	/// </summary>
	WorldExited, 
	
	/// <summary>
	/// The item subscribed.
	/// </summary>
	ItemSubscribed, 
	
	/// <summary>
	/// The item unsubscribed.
	/// </summary>
	ItemUnsubscribed, 
	
	/// <summary>
	/// The item properties.
	/// </summary>
	ItemProperties, 
	
	/// <summary>
	/// The radar update.
	/// </summary>
	RadarUpdate, 
	
	/// <summary>
	/// The counter data.
	/// </summary>
	CounterData
	
}EEventCode;


typedef enum EEventReceiver
{
	/// <summary>
	/// The item subscriber.
	/// </summary>
	ItemSubscriber = 1, 
	
	/// <summary>
	/// The item owner.
	/// </summary>
	ItemOwner = 2
	
}EEventReceiver;


typedef enum EItemType
{
	/// <summary>
	/// The avatar.
	/// </summary>
	Avatar, 
	
	/// <summary>
	/// The bot (fake avatar).
	/// </summary>
	Bot
	
}EItemType;

typedef enum EOperationCode /*: short */
{
	/// <summary>
	/// The nil (nothing).
	/// </summary>
	NIL = 0, 
	
	/// <summary>
	/// Create world operation code
	/// </summary>
	CreateWorld = 90, 
	
	/// <summary>
	/// The enter world.
	/// </summary>
	EnterWorld = 91, 
	
	/// <summary>
	/// The exit world.
	/// </summary>
	ExitWorld = 92, 
	
	/// <summary>
	/// The move code.
	/// </summary>
	Move = 93, 
	
	/// <summary>
	/// The raise generic event.
	/// </summary>
	RaiseGenericEvent = 94, 
	
	/// <summary>
	/// The set properties.
	/// </summary>
	SetProperties = 95, 
	
	/// <summary>
	/// The spawn item.
	/// </summary>
	SpawnItem = 96, 
	
	/// <summary>
	/// The destroy item.
	/// </summary>
	DestroyItem = 97, 
	
	/// <summary>
	/// The subscribe item.
	/// </summary>
	SubscribeItem = 98, 
	
	/// <summary>
	/// The unsubscribe item.
	/// </summary>
	UnsubscribeItem = 99, 
	
	/// <summary>
	/// The set view distance.
	/// </summary>
	SetViewDistance = 100, 
	
	/// <summary>
	/// The attach interest area.
	/// </summary>
	AttachInterestArea = 101, 
	
	/// <summary>
	/// The detach interest area.
	/// </summary>
	DetachInterestArea = 102, 
	
	/// <summary>
	/// The add interest area.
	/// </summary>
	AddInterestArea = 103, 
	
	/// <summary>
	/// The remove interest area.
	/// </summary>
	RemoveInterestArea = 104, 
	
	/// <summary>
	/// The get properties.
	/// </summary>
	GetProperties = 105, 
	
	/// <summary>
	/// The move interest area.
	/// </summary>
	MoveInterestArea = 106, 
	
	/// <summary>
	/// The radar subscribe.
	/// </summary>
	RadarSubscribe = 107, 
	
	/// <summary>
	/// The unsubscribe counter.
	/// </summary>
	UnsubscribeCounter = 108, 
	
	/// <summary>
	/// The subscribe counter.
	/// </summary>
	SubscribeCounter = 109
	
}EOperationCode;

typedef enum EParameterCode /*: short */
{
	/// <summary>
	/// The error code.
	/// </summary>
	ErrorCode = 0, 
	
	/// <summary>
	/// The debug message.
	/// </summary>
	DebugMessage = 1, 
	
	/// <summary>
	/// The event code.
	/// </summary>
	EventCode = 60, 
	
	/// <summary>
	/// The operation code.
	/// </summary>
	OperationCode = 60, 
	
	/// <summary>
	/// The username.
	/// </summary>
	Username = 91, 
	
	/// <summary>
	/// The old position.
	/// </summary>
	OldPosition = 92, 
	
	/// <summary>
	/// The position.
	/// </summary>
	Position = 93, 
	
	/// <summary>
	/// The properties.
	/// </summary>
	Properties = 94, 
	
	/// <summary>
	/// The item id.
	/// </summary>
	ItemId = 95, 
	
	/// <summary>
	/// The item type.
	/// </summary>
	ItemType = 96, 
	
	/// <summary>
	/// The properties revision.
	/// </summary>
	PropertiesRevision = 97, 
	
	/// <summary>
	/// The custom event code.
	/// </summary>
	CustomEventCode = 98, 
	
	/// <summary>
	/// The event data.
	/// </summary>
	EventData = 99, 
	
	/// <summary>
	/// The top left corner.
	/// </summary>
	TopLeftCorner = 100, 
	
	/// <summary>
	/// The tile dimensions.
	/// </summary>
	TileDimensions = 101, 
	
	/// <summary>
	/// The bottom right corner.
	/// </summary>
	BottomRightCorner = 102, 
	
	/// <summary>
	/// The world name.
	/// </summary>
	WorldName = 103, 
	
	/// <summary>
	/// The view distance.
	/// </summary>
	ViewDistanceEnter = 104, 
	
	/// <summary>
	/// The properties set.
	/// </summary>
	PropertiesSet = 105, 
	
	/// <summary>
	/// The properties unset.
	/// </summary>
	PropertiesUnset = 106, 
	
	/// <summary>
	/// The event reliability.
	/// </summary>
	EventReliability = 107, 
	
	/// <summary>
	/// The event receiver.
	/// </summary>
	EventReceiver = 108, 
	
	/// <summary>
	/// The subscribe.
	/// </summary>
	Subscribe = 109, 
	
	/// <summary>
	/// The view distance exit.
	/// </summary>
	ViewDistanceExit = 110, 
	
	/// <summary>
	/// The interest area id.
	/// </summary>
	InterestAreaId = 111, 
	
	/// <summary>
	/// The counter receive interval.
	/// </summary>
	CounterReceiveInterval = 112, 
	
	/// <summary>
	/// The counter name.
	/// </summary>
	CounterName = 113, 
	
	/// <summary>
	/// The counter time stamps.
	/// </summary>
	CounterTimeStamps = 114, 
	
	/// <summary>
	/// The counter values.
	/// </summary>
	CounterValues = 115,
	
	/// <summary>
	/// The current rotation.
	/// </summary>
	Rotation = 116,
	
	/// <summary>
	/// The previous rotation.
	/// </summary>
	OldRotation = 117
}EParameterCode;
	
@interface NVCode : NSObject 
{
	
}

@end
