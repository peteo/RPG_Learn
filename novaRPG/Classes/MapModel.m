//
//  MapModel.m
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "MapModel.h"
#import "GDataXMLNode.h"
#import "PropertyParser.h"


@implementation MapModel

@synthesize tileMap = _tileMap;
@synthesize bgLayer = _bgLayer;
@synthesize fgLayer = _fgLayer;
@synthesize metaLayer = _metaLayer;
@synthesize gameObjects = _gameObjects;
@synthesize npcs = _npcs;

// Initialize and load map
-(id) loadMap:(NSString *) mapName {
	self.tileMap = [CCTMXTiledMap tiledMapWithTMXFile:[NSString stringWithFormat:@"%@.tmx",mapName]];
	
	self.bgLayer = [_tileMap layerNamed:@"bg"];
	self.fgLayer = [_tileMap layerNamed:@"fg"];
	self.metaLayer = [_tileMap layerNamed:@"meta"];
	_metaLayer.visible = NO;
	self.gameObjects = [_tileMap objectGroupNamed:@"go"];
	self.npcs = [[[NSMutableArray alloc] init] autorelease];
	for (int i = 0; i < [_gameObjects.objects count]; i += 1) {
		if ([_gameObjects.objects objectAtIndex:i]) {
			NSString *objectType = [[_gameObjects.objects objectAtIndex:i] valueForKey:@"type"];
			CCLOG(@"%@",[[_gameObjects.objects objectAtIndex:i] valueForKey:@"type"]);
			if (objectType && [objectType compare:@"NPC"] == NSOrderedSame) {
				[_npcs addObject:[_gameObjects.objects objectAtIndex:i]];
			}
		}
	}
	
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
    int x = position.x / _tileMap.tileSize.width;
    int y = ((_tileMap.mapSize.height * _tileMap.tileSize.height) - position.y) / _tileMap.tileSize.height;
    return ccp(x, y);
}

- (CGPoint)positionForTileCoord:(CGPoint)position {
    int x = ((position.x*_tileMap.tileSize.width) + 16);
    int y = (((_tileMap.mapSize.height * _tileMap.tileSize.height) - position.y * _tileMap.tileSize.height) - 16);
    return ccp(x, y);
}

-(BOOL) checkCollisionForTile:(CGPoint) position {
	BOOL collidable = NO;
	int tileGid = [_metaLayer tileGIDAt:position];
	// Collision checking
	if (tileGid) {
		NSDictionary *properties = [_tileMap propertiesForGID:tileGid];
		if (properties) {
			NSString *collision = [properties valueForKey:@"Collidable"];
			if (collision && [collision compare:@"True"] == NSOrderedSame) {
				// If Collidable is true
				collidable = YES;
			}
			else {
				collidable = NO;
			}			
		}		
	}
	return collidable;
}

-(BOOL) checkCollisionForPosition:(CGPoint) position {
	BOOL collidable = NO;
	position = [self tileCoordForPosition:position];
	int tileGid = [_metaLayer tileGIDAt:position];
	// Collision checking
	if (tileGid) {
		NSDictionary *properties = [_tileMap propertiesForGID:tileGid];
		if (properties) {
			NSString *collision = [properties valueForKey:@"Collidable"];
			if (collision && [collision compare:@"True"] == NSOrderedSame) {
				// If Collidable is true
				collidable = YES;
			}
			else {
				collidable = NO;
				// Check NPC Collision
				for (int i = 0; i < [_npcs count]; i = i+1) {
					if (CGPointEqualToPoint(ccp([[[_npcs objectAtIndex:i] valueForKey:@"x"] intValue],[[[_npcs objectAtIndex:i] valueForKey:@"y"] intValue]), [self positionForTileCoord:position])) {
						collidable = YES;
					}
					else {
						if(!collidable) {
						collidable = NO;
						}
					}

				}
			}			
		}		
	}
	return collidable;
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
