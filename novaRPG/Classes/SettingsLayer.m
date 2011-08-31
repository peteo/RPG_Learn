//
//  MenuLayer.m
//  novaRPGv2
//
//  Created by nova on 26.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SettingsLayer.h"


@implementation SettingsLayer

+(id) settingsScene
{
	// 'scene' is an autorelease object.
	CCScene *settingsScene = [CCScene node];
	
	// 'layer' is an autorelease object.
	SettingsLayer *settingsLayer = [SettingsLayer node];
	
	// add layer as a child to scene
	[settingsScene addChild: settingsLayer];

	// return the scene
	return settingsScene;
}

-(id) init {
	if ( (self = [super init]) ) {
	}
	return self;
}

-(void) onSelect:(id)sender {
	CCLOG(@"Its working!");
}

@end
