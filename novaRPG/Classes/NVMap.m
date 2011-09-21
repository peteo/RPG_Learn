//
//  NVMap.m
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVMap.h"


@implementation NVMap

@synthesize tileMap = _tileMap;
@synthesize bgLayer = _bgLayer;
@synthesize fgLayer = _fgLayer;
@synthesize extraLayer = _extraLayer;
@synthesize metaLayer = _metaLayer;
@synthesize gameObjects = _gameObjects;

@synthesize npcs = _npcs;
@synthesize doors = _doors;

@synthesize mapSize_x = _mapSize_x;
@synthesize mapSize_y = _mapSize_y;

@synthesize loadedMap = _loadedMap;

// Initialize and load map
-(id) initWithMap:(NSString *) mapName 
{
	CCLOG(@"tiledMapWithTMXFile[%@]",[NSString stringWithFormat:@"%@.tmx",mapName]);
	self.tileMap = [CCTMXTiledMap tiledMapWithTMXFile:[NSString stringWithFormat:@"%@.tmx",mapName]];
	
	// Load layers and make the meta Layer invisible
	self.bgLayer = [_tileMap layerNamed:@"bg"];
	self.fgLayer = [_tileMap layerNamed:@"fg"];
	self.extraLayer = [_tileMap layerNamed:@"extras"];
	self.metaLayer = [_tileMap layerNamed:@"meta"];
	_metaLayer.visible = YES;
	self.gameObjects = [_tileMap objectGroupNamed:@"go"];
	
	// Cycle through all Gameobjects and check their type, sort them into arrays accordingly
	self.npcs = [[CCArray alloc] init];
	self.doors = [[CCArray alloc] init];
	for (int i = 0; i < [_gameObjects.objects count]; i += 1) {
		if ([_gameObjects.objects objectAtIndex:i]) {
			NSString *objectType = [[_gameObjects.objects objectAtIndex:i] valueForKey:@"type"];
			if (objectType && [objectType compare:@"NPC"] == NSOrderedSame) {
				[_npcs addObject:[_gameObjects.objects objectAtIndex:i]];
			}
			else {
				if (objectType && [objectType compare:@"door"] == NSOrderedSame) {
					[_doors addObject:[_gameObjects.objects objectAtIndex:i]];
					CCLOG(@"Door count is %i",[_doors count]);
				}
			}
		}
	}
	
	// Set mapsize properties (actual size)
	self.mapSize_x = _tileMap.tileSize.width * _tileMap.mapSize.width;
	self.mapSize_y = _tileMap.tileSize.height * _tileMap.mapSize.height;
	
	// Mapname property
	_loadedMap = mapName;
	return self;
}

// Get Spawnpoint
- (CGPoint) spawnPoint {
	NSMutableDictionary *spawnPoint = [_gameObjects objectNamed:@"playerspawn"];
	int x = [[spawnPoint valueForKey:@"x"] intValue];
	int y = [[spawnPoint valueForKey:@"y"] intValue];
	return ccp(x,y);
}

// Get NPC Spawnpoint
- (CGPoint) npcSpawnForId:(int) npcID {
	int x = [[[_npcs objectAtIndex:npcID] valueForKey:@"x"] intValue];
	int y = [[[_npcs objectAtIndex:npcID] valueForKey:@"y"] intValue];
	return ccp(x,y);
}

// Helper methods
- (CGPoint)tileCoordForPosition:(CGPoint)position {
	// Gets a static position for the current map.
    int x = position.x / _tileMap.tileSize.width;
    int y = ((_tileMap.mapSize.height * _tileMap.tileSize.height) - position.y) / _tileMap.tileSize.height;
    return ccp(x, y);
}

- (CGPoint)GLForPosition:(CGPoint)position {
	// Gets a static position for the GL.
    int x = position.x / _tileMap.tileSize.width;
    int y = position.y / _tileMap.tileSize.height;
    return ccp(x, y);
}

- (CGPoint)positionForTileCoord:(CGPoint)position {
    int x = ((position.x*_tileMap.tileSize.width) + 16);
    int y = (((_tileMap.mapSize.height * _tileMap.tileSize.height) - position.y * _tileMap.tileSize.height) - 16);
    return ccp(x, y);
}

-(BOOL) checkCollisionForPosition:(CGPoint) position 
{
	BOOL collidable = NO;
	position = [self tileCoordForPosition:position];
	int tileGID = [_metaLayer tileGIDAt:position];
	// Collision checking
	// In previous Versions, this method checked for every eventuality (Water, NPCs, etc) and that was very expensive.
	// Right now, it only checks for the Collidable property. Every NPC that steps on a tile makes it collidable and passable again after it
	// leaves. Water is collidable, but reacts on Action and has its own water property.
	if (tileGID) {
		NSDictionary *properties = [_tileMap propertiesForGID:tileGID];
		if (properties) {
			NSString *collision = [properties valueForKey:@"Collidable"];
			if (collision && [collision compare:@"True"] == NSOrderedSame) {
				// If Collidable is true, return Yes
				collidable = YES;
			}
			else {
				// If not, ... well.
				collidable = NO;
			}			
		}		
	}

	return collidable;
}

-(void) setTileCollidable:(BOOL) collisionModifier atTileCoord:(CGPoint) position {
	if (collisionModifier == YES) {
		[_metaLayer setTileGID:1 at:position];
	}
	else {
		[_metaLayer setTileGID:2 at:position];
	}
}

-(void) update:(float)dt {
	
}


// Dealloc method
-(void) dealloc {
	self.tileMap = nil;
	self.bgLayer = nil;
	self.fgLayer = nil;
	self.metaLayer = nil;
	self.gameObjects = nil;	
	
	[super dealloc];
}

@end
