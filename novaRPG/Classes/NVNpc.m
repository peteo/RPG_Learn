//
//  NVNpc.m
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVNpc.h"


@implementation NVNpc

@synthesize characterSprite = _characterSprite;
@synthesize spriteSheet = _spriteSheet;

@synthesize walkDownAnim = _walkDownAnim;
@synthesize walkUpAnim = _walkUpAnim;
@synthesize walkLeftAnim = _walkLeftAnim;
@synthesize walkRightAnim = _walkRightAnim;

@synthesize reactionEvents;


// Load .plist into FrameChache and .png into a Batchnode, then spawn the Sprite and its AnimStates
-(id) initWithID:(int) npcid onMap:(NVMap *) currentMap 
{
	if ((self = [super init])) 
	{
		[super onEnter];
		
		_currentMap = currentMap;
		
		_spriteName = [[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"displayid"];
		[[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:[NSString stringWithFormat:@"%@.plist",_spriteName]];
		self.spriteSheet = [CCSpriteBatchNode batchNodeWithFile:[NSString stringWithFormat:@"%@.png",_spriteName]];
		// Create the Sprite itself
		self.characterSprite = [CCSprite spriteWithSpriteFrameName:[NSString stringWithFormat:@"%@1-0.png",_spriteName]];
		// and add it to the SpriteSheet
		[_spriteSheet addChild:_characterSprite];
		// also, set Display ID
		[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",_spriteName]]];
		
		_animSpeed = [[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"animspeed"] floatValue];
		
		// Load all Animation Frames into their Arrays and create the Animations
		// For Down-Animation: Framegroup 1
		NSMutableArray *walkDownFrames = [NSMutableArray array];
		[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-1.png",_spriteName]]];
		[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",_spriteName]]];
		[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-2.png",_spriteName]]];
		self.walkDownAnim = [CCAnimation animationWithFrames:walkDownFrames delay:_animSpeed];
		
		// For Up-Animation: Framegroup 2
		NSMutableArray *walkUpFrames = [NSMutableArray array];		
		[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-1.png",_spriteName]]];
		[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-0.png",_spriteName]]];
		[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-2.png",_spriteName]]];
		self.walkUpAnim = [CCAnimation animationWithFrames:walkUpFrames delay:_animSpeed];
		
		// For Left-Animation: Framegroup 3
		NSMutableArray *walkLeftFrames = [NSMutableArray array];		
		[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-1.png",_spriteName]]];
		[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-0.png",_spriteName]]];
		[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-2.png",_spriteName]]];
		self.walkLeftAnim = [CCAnimation animationWithFrames:walkLeftFrames delay:_animSpeed];
		
		// For Right-Animation: Framegroup 4
		NSMutableArray *walkRightFrames = [NSMutableArray array];		
		[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-1.png",_spriteName]]];
		[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-0.png",_spriteName]]];
		[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-2.png",_spriteName]]];
		self.walkRightAnim = [CCAnimation animationWithFrames:walkRightFrames delay:_animSpeed];
		
		_moveSpeed = [[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"movespeed"] floatValue];
		
		// Set Position
		_characterSprite.position = [_currentMap npcSpawnForId:npcid];
		
		// Get Bounding Box for Movement
		_boundingBox = CGRectMake(_characterSprite.position.x, _characterSprite.position.y, 
								  [[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"movearea_x"] floatValue] * 32, 
								  [[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"movearea_y"] floatValue] * 32);
		
		// Set LookDirection
		[self lookInDirection:[[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"lookdirection"] intValue]];
		
		// Set previousGID so NPCs can be placed anywhere and the meta tile beneath them will still be retained when they move
		_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:_characterSprite.position]];
		
		// Mark the current Position as Collidable
		[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:_characterSprite.position]];
		
		switch ([[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"behaviour"] intValue]) {
			case 0:
				break;
			case 1:
				// Circle
				break;
			case 2:
				[self schedule:@selector(behaviourRandom:) interval:[[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"moveinterval"] floatValue]];
				break;
				
			default:
				break;
		}
		
		self.reactionEvents = [[NVEventManager sharedEventManager] readEventData:[[_currentMap.npcs objectAtIndex:npcid] valueForKey:@"name"] 
																	fromFile:_currentMap.loadedMap];
		CCLOG(@"test: the first action type  is %i",[[self.reactionEvents objectAtIndex:0] eventType]);
	
	}
	return self;
}

-(void) lookInDirection:(int) lookDirection {
	switch (lookDirection) {
		case 0:
			break;
		case 1:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",_spriteName]]];
			break;
		case 2:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-0.png",_spriteName]]];
			break;
		case 3:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-0.png",_spriteName]]];
			break;
		case 4:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-0.png",_spriteName]]];
			break;
		default:
			break;
	}
}

-(void) behaviourCircle:(ccTime) dt {
	
}

-(void) behaviourRandom:(ccTime) dt {
	// Move into random direction with predefined movespeed on every tick
	[self moveInDirection:arc4random()%5 withSpeed:_moveSpeed];
}

-(void) moveInDirection:(int)moveDirection withSpeed:(float)speed {
	switch (moveDirection) {
		case 0:
			break;
		case 1:
			// Check for Collision on Map, check for bounding box so the Sprite doesn't move out of it's area
			// Move Down
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]
				&& CGRectContainsPoint(_boundingBox,ccp(_characterSprite.position.x,_characterSprite.position.y-32))) {
				[self lookInDirection:1];
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:_moveSpeed position:ccp(0,-32)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkDownAnim]]; 				
			}
			break;
		case 2:
			// Move Up
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]
				&& CGRectContainsPoint(_boundingBox,ccp(_characterSprite.position.x,_characterSprite.position.y+32))) {
				[self lookInDirection:2];
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:_moveSpeed position:ccp(0,32)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkUpAnim]];
			}
			break;
		case 3:
			// Move Left
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]
				&& CGRectContainsPoint(_boundingBox,ccp(_characterSprite.position.x-32,_characterSprite.position.y))) {
				[self lookInDirection:3];
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:_moveSpeed position:ccp(-32,0)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkLeftAnim]];
			}
			break;
		case 4:
			// Move Right
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]
				&& CGRectContainsPoint(_boundingBox,ccp(_characterSprite.position.x+32,_characterSprite.position.y))) {
				[self lookInDirection:4];
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:_moveSpeed position:ccp(32,0)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkRightAnim]];
			}
			break;
		default:
			break;
	}
}

-(void) dealloc {
	self.characterSprite = nil;
	self.spriteSheet = nil;
	self.walkDownAnim = nil;
	self.walkUpAnim = nil;
	self.walkLeftAnim = nil;
	self.walkRightAnim = nil;
	[super dealloc];
}

@end
