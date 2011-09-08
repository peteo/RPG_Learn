//
//  MenuLayer.m
//  novaRPGv2
//
//  Created by nova on 26.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MenuLayer.h"
#import "novaRPGv2AppDelegate.h"

@implementation MenuLayer

+(id) menuScene
{
	// 'scene' is an autorelease object.
	CCScene *menuScene = [CCScene node];
	
	// 'layer' is an autorelease object.
	MenuLayer *menuLayer = [MenuLayer node];
	
	// add layer as a child to scene
	[menuScene addChild: menuLayer];
	
	// return the scene
	return menuScene;
}

-(id) init {
	if ( (self = [super init]) ) {
		CGSize winSize = [[CCDirector sharedDirector] winSize];
		
		// Initialize Main Menu
		CCMenuItem *menuItem1 = [CCMenuItemFont itemFromString:@"Play" target:self selector:@selector(onPlay:)];
        CCMenuItem *menuItem2 = [CCMenuItemFont itemFromString:@"Settings" target:self selector:@selector(onSettings:)];
        CCMenuItem *menuItem3 = [CCMenuItemFont itemFromString:@"About" target:self selector:@selector(onAbout:)];
		
        _mainMenu = [CCMenu menuWithItems:menuItem1, menuItem2, menuItem3, nil];
        [_mainMenu alignItemsVertically];
        [self addChild:_mainMenu];
		
		// Inititalize Save Menu
		CCMenuItem *newGame = [CCMenuItemFont itemFromString:@"New Game" target:self selector:@selector(newGame:)];
		_saveMenu = [CCMenu menuWithItems:newGame,nil];
		
		NSArray *saveStates = [[StateManager sharedStateManager] loadStates];
		NSArray *currentSaveName = [NSArray array];
		NSArray *currentSaveLocation = [NSArray array];
		
		NSUInteger index = 0;
		for (GDataXMLElement *currentSave in saveStates) {
			currentSaveName = [currentSave nodesForXPath:[NSString stringWithFormat:@"//SaveState[@id='%i']/SaveName",index + 1]  error:nil];
			if ([currentSaveName count] > 0) {
				_saveName = [[currentSaveName objectAtIndex:0] stringValue];
			}
			else {
				_saveName = @"unknown save";
			}
			
			
			currentSaveLocation = [currentSave nodesForXPath:[NSString stringWithFormat:@"//SaveState[@id='%i']/CurrentMap",index + 1] error:nil];
			if ([currentSaveLocation count] > 0) {
				_saveLocation = [[currentSaveLocation objectAtIndex:0] stringValue];
			}
			else {
				_saveLocation = @"unknown location";
			}
			
			CCMenuItem *saveState = [CCMenuItemFont itemFromString:[NSString stringWithFormat:@"%i. %@, %@",index + 1,_saveName,_saveLocation] 
															target:self
														  selector:@selector(onSelect:)
									 ];
			saveState.tag = index + 1;
			[_saveMenu addChild:saveState];
			
			index++;
		}
		
		[_saveMenu alignItemsVertically];
        [self addChild:_saveMenu];
		_saveMenu.position = ccp(_saveMenu.position.x + winSize.width,winSize.height/2);
		
	}
	return self;
}

-(void) onPlay:(id)sender {
	CCLOG(@"Its working!");
	[self runAction:[CCEaseSineInOut actionWithAction:[CCMoveBy actionWithDuration:0.8 position:ccp(-[[CCDirector sharedDirector] winSize].width,0)]]];
}

-(void) onSettings:(id)sender {
}

-(void) onAbout:(id)sender {
}

-(void) onSelect:(id)sender 
{
	novaRPGv2AppDelegate * app = [novaRPGv2AppDelegate getAppDelegate];
	
	if(app.Link.IsWaiting)
	{
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示！" message:@"正在连接服务器!" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
		[alert show];
		[alert release];
	}
	else
	{
		CCMenuItem *item = (CCMenuItem *) sender;
		[[StateManager sharedStateManager] setActiveSaveState:item.tag];
		[[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:0.5 scene:[GameLayer gameScene] withColor:ccc3(0, 0, 0)]];
	}
}

-(void) newGame:(id)sender 
{
	/*
	novaRPGv2AppDelegate * app = [novaRPGv2AppDelegate getAppDelegate];
	
	if(app.Link.IsWaiting)
	{
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示！" message:@"正在连接服务器!" delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil];
		[alert show];
		[alert release];
	}
	else
	*/
	
	{
		[[StateManager sharedStateManager] createNewState];
		[[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:0.5 scene:[GameLayer gameScene] withColor:ccc3(0, 0, 0)]];
	}
}

@end
