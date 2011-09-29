/*
 *  PtMap.h
 *  PtRPG
 *
 *  Created by Peteo on 11-9-27.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#ifndef __PT_MAP_H__
#define __PT_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class PtMap : public CCLayer 
{
private:
	
	CCTMXObjectGroup *_gameObjects;
	
	int _mapSize_x;
	int _mapSize_y;
	
	std::string *_loadedMap;
	
public:
	
	CCTMXTiledMap	 *_tileMap;
	CCTMXLayer		 *_metaLayer;
	CCTMXLayer	     *_fgLayer;
	CCTMXLayer		 *_extraLayer;
	CCTMXLayer		 *_bgLayer;
	
	CCArray *_npcs;
	CCArray *_doors;

public:
	
	static PtMap * PtMapWithName(std::string mapName);
	
	PtMap(std::string mapName);
	
	virtual ~PtMap();
	
	// Get Spawnpoint
	CCPoint spawnPoint();
	
	// Get NPC Spawnpoint
	CCPoint npcSpawnForId(int npcID);
	
	// Helper methods go here
	
	// Gets a static position for the current map.
	CCPoint tileCoordForPosition(CCPoint position);
	
	CCPoint positionForTileCoord(CCPoint position);
	
	// Gets a static position for the GL.
	CCPoint GLForPosition(CCPoint position);
	
	// Methods for Collision Checking
	bool checkCollisionForPosition(CCPoint position);
	void setTileCollidable(bool collisionModifier, CCPoint position);
	
	void update(ccTime dt);
	
};

#endif