//
//  NVNpc.h
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "cocos2d.h"
#import "NVMap.h"
#import "NVEventManager.h"
#import "NVAction.h"

@interface NVNpc : CCNode {
	CCSprite *_characterSprite;
	CCSpriteBatchNode *_spriteSheet;
	CCAnimation *_walkDownAnim;
	CCAnimation *_walkUpAnim;
	CCAnimation *_walkLeftAnim;
	CCAnimation *_walkRightAnim;

	float _moveSpeed;
	float _moveInterval;
	float _animSpeed;

	NSString *_spriteName;
	
	CGRect _boundingBox;
	
	NVMap *_currentMap;
	
	int _previousGID;
}

// Sprite and Spritesheet
@property (nonatomic,retain) CCSprite *characterSprite;
@property (nonatomic,retain) CCSpriteBatchNode *spriteSheet;

// Animations
@property (nonatomic,retain) CCAnimation *walkDownAnim;
@property (nonatomic,retain) CCAnimation *walkUpAnim;
@property (nonatomic,retain) CCAnimation *walkLeftAnim;
@property (nonatomic,retain) CCAnimation *walkRightAnim;

@property (nonatomic,retain) CCArray *reactionEvents;

-(id) initWithID:(int) npcid onMap:(NVMap *) currentMap;
-(void) lookInDirection:(int) lookDirection;
-(void) behaviourCircle:(ccTime) dt;
-(void) behaviourRandom:(ccTime) dt;
-(void) moveInDirection:(int) moveDirection withSpeed:(float) speed;

@end
