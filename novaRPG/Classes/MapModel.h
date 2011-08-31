//
//  MapModel.h
//  novaRPG
//
//  Created by nova on 02.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface MapModel : CCNode {
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_bgLayer;
	CCTMXObjectGroup *_gameObjects;
	CCTMXLayer *_fgLayer;
	CCTMXLayer *_metaLayer;
	NSMutableArray *_npcs;
}

@property (nonatomic,retain) CCTMXTiledMap *tileMap;
@property (nonatomic,retain) CCTMXLayer *bgLayer;
@property (nonatomic,retain) CCTMXLayer *fgLayer;
@property (nonatomic,retain) CCTMXLayer *metaLayer;
@property (nonatomic,retain) CCTMXObjectGroup *gameObjects;
@property (nonatomic,retain) NSMutableArray *npcs;

-(id) loadMap:(NSString *) mapName;
-(CGPoint) spawnPoint;
-(CGPoint) npcSpawnForId:(int) npcID;

// Helper methods go here
-(CGPoint) tileCoordForPosition:(CGPoint) position;
-(CGPoint) positionForTileCoord:(CGPoint) position;
-(BOOL) checkCollisionForTile:(CGPoint) position;
-(BOOL) checkCollisionForPosition:(CGPoint) position;

@end
