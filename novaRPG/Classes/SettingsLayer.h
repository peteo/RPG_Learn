//
//  MenuLayer.h
//  novaRPGv2
//
//  Created by nova on 26.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"	

@interface SettingsLayer : CCLayer 
{
	CCMenu *_settingsMenu;
}

+(id) settingsScene;

-(void) onSelect:(id) sender;

@end
