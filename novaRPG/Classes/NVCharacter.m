//
//  NVCharacter.m
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVCharacter.h"


@implementation NVCharacter

@synthesize characterSprite = _characterSprite;
@synthesize spriteSheet = _spriteSheet;
@synthesize walkDownAnim = _walkDownAnim;
@synthesize walkUpAnim = _walkUpAnim;
@synthesize walkLeftAnim = _walkLeftAnim;
@synthesize walkRightAnim = _walkRightAnim;

@synthesize moveSpeed = _moveSpeed;
@synthesize animSpeed = _animSpeed;

@synthesize moveState = _moveState;
@synthesize lookDirection = _lookDirection;


// Load .plist into FrameChache and .png into a Batchnode, then spawn the Sprite and its AnimStates
-(id) initWithSpritesheet:(NSString *) spriteName onMap:(NVMap *) currentMap 
{
	_spriteName = spriteName;
	self.lookDirection = 1;
	[[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:[NSString stringWithFormat:@"%@.plist",spriteName]];
	self.spriteSheet = [CCSpriteBatchNode batchNodeWithFile:[NSString stringWithFormat:@"%@.png",spriteName]];
	// Create the Sprite itself
	self.characterSprite = [CCSprite spriteWithSpriteFrameName:[NSString stringWithFormat:@"%@1-0.png",spriteName]];
	// and add it to the SpriteSheet
	[_spriteSheet addChild:_characterSprite];
	// also, set Display ID
	[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",spriteName]]];
	
	self.animSpeed = 0.1;
	
	// Load all Animation Frames into their Arrays and create the Animations
	// For Down-Animation: Framegroup 1
	NSMutableArray *walkDownFrames = [NSMutableArray array];
	[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-1.png",spriteName]]];
	[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",spriteName]]];
	[walkDownFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-2.png",spriteName]]];
	self.walkDownAnim = [CCAnimation animationWithFrames:walkDownFrames delay:_animSpeed];
	
	// For Up-Animation: Framegroup 2
	NSMutableArray *walkUpFrames = [NSMutableArray array];		
	[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-1.png",spriteName]]];
	[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-0.png",spriteName]]];
	[walkUpFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-2.png",spriteName]]];
	self.walkUpAnim = [CCAnimation animationWithFrames:walkUpFrames delay:_animSpeed];
	
	// For Left-Animation: Framegroup 3
	NSMutableArray *walkLeftFrames = [NSMutableArray array];		
	[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-1.png",spriteName]]];
	[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-0.png",spriteName]]];
	[walkLeftFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-2.png",spriteName]]];
	self.walkLeftAnim = [CCAnimation animationWithFrames:walkLeftFrames delay:_animSpeed];
	
	// For Right-Animation: Framegroup 4
	NSMutableArray *walkRightFrames = [NSMutableArray array];		
	[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-1.png",spriteName]]];
	[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-0.png",spriteName]]];
	[walkRightFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-2.png",spriteName]]];
	self.walkRightAnim = [CCAnimation animationWithFrames:walkRightFrames delay:_animSpeed];
	
	self.moveSpeed = 0.3;

	self.moveState = kStateIdle;
	
	_currentMap  = currentMap;
	_previousGID = 2;
	
	return self;
}

-(void) loadExtraAnimations {
	// Place for Extra-Animations (Framegroups 5-9)
}

-(void) lookInDirection:(int) lookDirection {
	switch (lookDirection) {
		case 0:
			break;
		case 1:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@1-0.png",_spriteName]]];
			self.lookDirection = 1;
			break;
		case 2:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@2-0.png",_spriteName]]];
			self.lookDirection = 2;
			break;
		case 3:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@3-0.png",_spriteName]]];
			self.lookDirection = 3;
			break;
		case 4:
			[_characterSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:@"%@4-0.png",_spriteName]]];
			self.lookDirection = 4;
			break;
		default:
			break;
	}
}
	


-(void) update 
{
	switch (self.moveState) 
	{
		case kStateIdle:
			break;
		case kStateDown:
			// Move Down
			[self lookInDirection:1];
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]) 
			{
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(0,-32)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkDownAnim]];
			}
			else 
			{
				for (NSDictionary *properties in _currentMap.doors) 
				{
					if (CGPointEqualToPoint([_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)], [_currentMap tileCoordForPosition:ccp([[properties valueForKey:@"x"] floatValue],[[properties valueForKey:@"y"] floatValue])])) {
						[[StateManager sharedStateManager] setCurrentMap:[properties valueForKey:@"map"]];
						[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
						[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(0,-32)]];
						[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkDownAnim]]; 
						[[NSNotificationCenter defaultCenter] postNotificationName: @"mapChange" object: nil];
					}
				}
			}

			break;
		case kStateUp:
			// Move Up
			[self lookInDirection:2];
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]) {
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(0,32)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkUpAnim]];
			}
			break;
		case kStateLeft:
			// Move Left
			[self lookInDirection:3];
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]) {
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(-32,0)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkLeftAnim]];
			}
			break;
		case kStateRight:
			// Move Right
			[self lookInDirection:4];
			if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]) {
				[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
				_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
				[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
				[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(32,0)]];
				[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkRightAnim]];
			}
			break;
		default:
			break;
	}

}

-(void) dealloc
{
	self.characterSprite = nil;
	self.spriteSheet = nil;
	self.walkDownAnim = nil;
	self.walkUpAnim = nil;
	self.walkLeftAnim = nil;
	self.walkRightAnim = nil;
	[super dealloc];
}

@end
