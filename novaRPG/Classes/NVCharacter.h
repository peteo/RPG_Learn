//
//  NVCharacter.h
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "cocos2d.h"
#import "NVMap.h"
#import "StateManager.h"

typedef enum 
{
	kStateIdle = 0,
	kStateDown,
	kStateUp,
	kStateLeft,
	kStateRight
} _moveState;

@interface NVCharacter : CCNode 
{
	CCSprite *_characterSprite;
	CCSpriteBatchNode *_spriteSheet;
	CCAnimation *_walkDownAnim;
	CCAnimation *_walkUpAnim;
	CCAnimation *_walkLeftAnim;
	CCAnimation *_walkRightAnim;

	float _moveSpeed;
	float _animSpeed;
	
	int _moveState;
	
	int _lookDirection;

	NSString *_spriteName;
	
	NVMap *_currentMap;
	
	int _previousGID;
	
	NSString *_ItemID;
	CGSize    _ViewDistanceEnter;
	CGSize    _ViewDistanceExit;
}

// Sprite and Spritesheet
@property (nonatomic,retain) CCSprite *characterSprite;
@property (nonatomic,retain) CCSpriteBatchNode *spriteSheet;


// Animations
@property (nonatomic,retain) CCAnimation *walkDownAnim;
@property (nonatomic,retain) CCAnimation *walkUpAnim;
@property (nonatomic,retain) CCAnimation *walkLeftAnim;
@property (nonatomic,retain) CCAnimation *walkRightAnim;

// Speeds
@property (readwrite,assign) float moveSpeed;
@property (readwrite,assign) float animSpeed;

// States
@property (readwrite,assign) int moveState;
@property (readwrite,assign) int lookDirection;

//ViewDistance
@property (readwrite,assign) CGSize ViewDistanceEnter;
@property (readwrite,assign) CGSize ViewDistanceExit;

@property (nonatomic,retain) NSString * ItemID;

-(id) initWithSpritesheet:(NSString *)spriteName onMap:(NVMap *) currentMap;
-(void) loadExtraAnimations;
-(void) lookInDirection:(int) lookDirection;
-(void) update;

@end
