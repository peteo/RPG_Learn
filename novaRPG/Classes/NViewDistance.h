//
//  NViewDistance.h
//  novaRPGv2
//
//  Created by Peteo on 11-9-9.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "cocos2d.h"

@interface NViewDistance : CCNode
{
	CGSize    _ViewDistanceEnter;
	CGSize    _ViewDistanceExit;
	NSString *_ItemID;
}

@property (readwrite,assign) CGSize ViewDistanceEnter;
@property (readwrite,assign) CGSize ViewDistanceExit;
@property (nonatomic,retain) NSString * ItemID;

@end
