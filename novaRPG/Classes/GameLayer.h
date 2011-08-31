//
//  HelloWorldLayer.h
//  novaRPG
//
//  Created by nova on 01.01.11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//


// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "NVMap.h"
#import "NVCharacter.h"
#import "NVNpc.h"
#import "StateManager.h"
#import "TextBoxLayer.h"
#import "GDataXMLNode.h"
#import "NVEventManager.h"
#import "NVAction.h"
#import "EnvironmentLayer.h"

// HelloWorld Layer
@interface GameLayer : CCLayer <TextBoxDelegate>
{
	TextBoxLayer *textBox;
	
	NVMap *_tileMap;
	NVCharacter *_playerChar;
	
	CGRect _dDown1;
	CGRect _dDown2;
	CGRect _dUp1;
	CGRect _dUp2;
	CGRect _dLeft;
	CGRect _dRight;
	
	CGRect _dTop;
	CGRect _dBot;
	
	float _loopSpeed;
	
	CCArray *_npcarray;
}

// returns a Scene that contains the HelloWorld as the only child
+(id) gameScene;

// Camera Helper Methods
-(void) followPlayer:(id) sender;
-(void) centerCamera:(CGPoint)point;
-(void) moveCameraByTile:(CGPoint)point withDuration:(int) duration;
-(void) moveCameraToPos:(CGPoint)point withDuration:(int) duration;

// Textbox Actions
-(void) displayTextbox:(NSString *) displayText;

// Map Change
-(void) mapChange:(id) sender;

// Methods for Event Checking
-(void) checkForEvent;
-(void) triggerNPCEvent:(NVNpc *) npc withDirection:(int) lookDirection;

// Loops and Tick Methods
-(void) gameLoop: (ccTime) dt;
-(void) textBoxUpdate:(ccTime)dt;

@end
