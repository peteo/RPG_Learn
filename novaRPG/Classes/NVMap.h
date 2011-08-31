//
//  NVMap.h
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "cocos2d.h"


@interface NVMap : CCNode {
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_bgLayer;
	CCTMXObjectGroup *_gameObjects;
	CCTMXLayer *_fgLayer;
	CCTMXLayer *_extraLayer;
	CCTMXLayer *_metaLayer;
	
	CCArray *_npcs;
	CCArray *_doors;
	
	int _mapSize_x;
	int _mapSize_y;
	
	NSString *_loadedMap;
}

@property (nonatomic,retain) CCTMXTiledMap *tileMap;
@property (nonatomic,retain) CCTMXLayer *bgLayer;
@property (nonatomic,retain) CCTMXLayer *fgLayer;
@property (nonatomic,retain) CCTMXLayer *extraLayer;
@property (nonatomic,retain) CCTMXLayer *metaLayer;
@property (nonatomic,retain) CCTMXObjectGroup *gameObjects;

@property (nonatomic,retain) CCArray *npcs;
@property (nonatomic,retain) CCArray *doors;

@property (readwrite,assign) int mapSize_x;
@property (readwrite,assign) int mapSize_y;

@property (readonly,assign) NSString *loadedMap;

-(id) initWithMap:(NSString *) mapName;
-(CGPoint) spawnPoint;
-(CGPoint) npcSpawnForId:(int) npcID;

// Helper methods go here
-(CGPoint) tileCoordForPosition:(CGPoint) position;
-(CGPoint) positionForTileCoord:(CGPoint) position;

// Methods for Collision Checking
-(BOOL) checkCollisionForPosition:(CGPoint) position;
-(void) setTileCollidable:(BOOL) collisionModifier atTileCoord:(CGPoint) position;

-(void) update:(float) dt;


@end
