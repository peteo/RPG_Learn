//
//  NVRadar.m
//  novaRPGv2
//
//  Created by Peteo on 11-9-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVRadar.h"

#define RADAR_W 20
#define RADAR_H 20

#define RADAR_OFFSET 5

@implementation NVRemotePlayRadar

@synthesize Pos    = _Pos;
@synthesize ItemID = _ItemID;

- (void) dealloc
{
	[_ItemID release];
	
	[super dealloc];
}

@end


@implementation NVRadar

@synthesize CharacterPos = _CharacterPos;
@synthesize RemotePlayRadarArray = _RemotePlayRadarArray;

-(id) init
{
	if( (self=[super init] ))
	{
		_RemotePlayRadarArray = [[CCArray alloc] init];
	}
	return self;
}

-(void) draw
{
	CGPoint pPos = ccp(0 + 240 - (RADAR_W - 1) * RADAR_OFFSET,0 + 160 - (RADAR_H - 1) * RADAR_OFFSET);
	
	//画格子线
	// make the line 1 pixels thick
	glLineWidth(1.0f);
	glColor4f(1, 0, 1, 0.2f);
	
	for(int i = 0;i < RADAR_W;i ++)
	{
		ccDrawLine(ccp(pPos.x + i * RADAR_OFFSET,pPos.y),ccp(pPos.x + i * RADAR_OFFSET,pPos.y + (RADAR_H - 1) * RADAR_OFFSET));
	}
	
	for(int j = 0;j < RADAR_H;j ++)
	{
		ccDrawLine(ccp(pPos.x,pPos.y + j * RADAR_OFFSET),ccp(pPos.x + (RADAR_W - 1) * RADAR_OFFSET,pPos.y + j * RADAR_OFFSET));
	}
	
	glColor4f(0, 0, 0, 1);
	glLineWidth(5.0f);
	//画点
	ccDrawCircle(ccp(pPos.x + RADAR_OFFSET * _CharacterPos.x,pPos.y + RADAR_OFFSET * _CharacterPos.y), 2, 0, 2, NO);
	
	//画远程玩家
	glColor4f(0, 1, 0, 1);
	for(NVRemotePlayRadar * pRemotePlayRadar in _RemotePlayRadarArray)
	{
		ccDrawCircle(ccp(pPos.x + RADAR_OFFSET * pRemotePlayRadar.Pos.x,pPos.y + RADAR_OFFSET * pRemotePlayRadar.Pos.y), 2, 0, 2, NO);
	}
	
	
	// reset line width & color as to not interfere with draw code in other nodes that draws lines
	glLineWidth(1.0f);
	glColor4f(1, 1, 1, 1);
	
}

- (void) dealloc
{
	[_RemotePlayRadarArray release];
	
	[super dealloc];
}

@end
