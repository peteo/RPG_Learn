//
//  MenuLayer.h
//  novaRPGv2
//
//  Created by nova on 26.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"	
#import "StateManager.h"
#import "GameLayer.h"

@interface MenuLayer : CCLayer {
	int _menuType;
	CCMenu *_mainMenu;
	CCMenu *_saveMenu;
	NSString *_saveName;
	NSString *_saveLocation;
}

+(id) menuScene;
-(void) onPlay:(id) sender;
-(void) onSettings:(id) sender;
-(void) onAbout:(id) sender;
-(void) onSelect:(id) sender;
-(void) newGame:(id) sender;


@end
