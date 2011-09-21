//
//  NVRadar.h
//  novaRPGv2
//
//  Created by Peteo on 11-9-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "cocos2d.h"


@interface NVRemotePlayRadar : NSObject
{
	CGPoint   _Pos;
	NSString *_ItemID;
}

@property (readwrite,assign) CGPoint Pos;
@property (nonatomic,retain) NSString * ItemID;

@end


@interface NVRadar : CCNode 
{
	CGPoint _CharacterPos;
	
	CCArray *_RemotePlayRadarArray;
}

@property (readwrite,assign) CGPoint CharacterPos;
@property (nonatomic,retain) CCArray * RemotePlayRadarArray;

@end
