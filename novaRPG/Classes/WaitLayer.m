//
//  WaitLayer.m
//  novaRPGv2
//
//  Created by Peteo on 11-9-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "WaitLayer.h"


@implementation WaitLayer

+(id) WaitScene
{
	// 'scene' is an autorelease object.
	CCScene *waitScene = [CCScene node];
	
	// 'layer' is an autorelease object.
	WaitLayer *waitLayer = [WaitLayer node];
	
	// add layer as a child to scene
	[waitScene addChild: waitLayer];
	
	// return the scene
	return waitScene;
}

-(id) init
{
	if ( (self = [super init]) ) 
	{
		CGSize size = [[CCDirector sharedDirector] winSize];
		
		CCLabelTTF * label = [CCLabelTTF labelWithString: @"Loading ..." fontName: @"Marker Felt" fontSize: 64 ];
		
		label.position = CGPointMake(size.width / 2 , size.height / 2 );
		
		[self addChild:label];
	}
	return self;
}

@end
