/*
 *  PtMap.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-27.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "PtMap.h"

PtMap *PtMap::PtMapWithName(std::string mapName)
{
	PtMap *pRet = new PtMap(mapName);
	if(pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

PtMap::PtMap(std::string mapName)
:_tileMap(NULL)
,_bgLayer(NULL)
,_gameObjects(NULL)
,_fgLayer(NULL)
,_extraLayer(NULL)
,_metaLayer(NULL)
,_npcs(NULL)
,_doors(NULL)
,_loadedMap(NULL)
,_mapSize_x(0)
,_mapSize_y(0)
{
	char pTempMap[32] = {0};
	sprintf(pTempMap,"%s.tmx",mapName.c_str());
	CCLOG("tiledMapWithTMXFile[%s]",pTempMap);
	
	_tileMap = CCTMXTiledMap::tiledMapWithTMXFile(pTempMap);
	
	//[NSString stringWithFormat:@"%@.tmx",mapName]];
	
	// Load layers and make the meta Layer invisible
	_bgLayer    = _tileMap->layerNamed("bg");
	_fgLayer    = _tileMap->layerNamed("fg");
	_extraLayer = _tileMap->layerNamed("extras");
	_metaLayer  = _tileMap->layerNamed("meta");
	_metaLayer->setIsVisible(true);
	_gameObjects = _tileMap->objectGroupNamed("go");
	
	// Cycle through all Gameobjects and check their type, sort them into arrays accordingly
	_npcs  = CCArray::arrayWithCapacity(10);
	_doors = CCArray::arrayWithCapacity(10);
	
	for (int i = 0; i < _gameObjects->getObjects()->count(); i += 1) 
	{
		if (_gameObjects->getObjects()->getObjectAtIndex(i))
		{
			CCString *objectType = _gameObjects->getObjects()->getObjectAtIndex(i)->objectForKey("type");
			
			if (objectType && strcmp(objectType->toStdString().c_str(),"NPC") == 0) 
			{
				_npcs->addObject(_gameObjects->getObjects()->getObjectAtIndex(i));
			}
			else
			{
				if (objectType && strcmp(objectType->toStdString().c_str(),"door") == 0) 
				{
					_doors->addObject(_gameObjects->getObjects()->getObjectAtIndex(i));
					CCLOG("Door count is %i",_doors->count());
				}
			}
		}
	}
	
	// Set mapsize properties (actual size)
	_mapSize_x = _tileMap->getTileSize().width  * _tileMap->getMapSize().width;
	_mapSize_y = _tileMap->getTileSize().height * _tileMap->getMapSize().height;
	
	// Mapname property
	CC_SAFE_DELETE(_loadedMap);
	_loadedMap = new std::string(mapName);
}

PtMap::~PtMap()
{
	CC_SAFE_DELETE(_loadedMap);
}


CCPoint PtMap::spawnPoint()
{
	CCStringToStringDictionary *spawnPoint = _gameObjects->objectNamed("playerspawn");
	int x = spawnPoint->objectForKey("x")->toInt();
	int y = spawnPoint->objectForKey("y")->toInt();
	return ccp(x,y);
}

CCPoint PtMap::npcSpawnForId(int npcID) 
{
	CCStringToStringDictionary * pDic = (CCStringToStringDictionary*)_npcs->objectAtIndex(npcID);
	int x = pDic->objectForKey("x")->toInt();
	int y = pDic->objectForKey("y")->toInt();
	return ccp(x,y);
}



// Helper methods
CCPoint PtMap::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}



CCPoint PtMap::GLForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = position.y / _tileMap->getTileSize().height;
    return ccp(x, y);
}


CCPoint PtMap::positionForTileCoord(CCPoint position)
{
    int x = ((position.x*_tileMap->getTileSize().width) + 16);
    int y = (((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y * _tileMap->getTileSize().height) - 16);
    return ccp(x, y);
}

bool PtMap::checkCollisionForPosition(CCPoint position)
{
	bool collidable = false;
	position = tileCoordForPosition(position);
	int tileGID = _metaLayer->tileGIDAt(position);
	// Collision checking
	// In previous Versions, this method checked for every eventuality (Water, NPCs, etc) and that was very expensive.
	// Right now, it only checks for the Collidable property. Every NPC that steps on a tile makes it collidable and passable again after it
	// leaves. Water is collidable, but reacts on Action and has its own water property.
	if (tileGID)
	{
		CCStringToStringDictionary *properties = _tileMap->propertiesForGID(tileGID);
		if (properties)
		{
			CCString *collision = properties->objectForKey("Collidable");
			if (collision && strcmp(collision->toStdString().c_str(),"True") == 0) 
			{
				// If Collidable is true, return Yes
				collidable = true;
			}
			else 
			{
				// If not, ... well.
				collidable = false;
			}	
		}		
	}
	
	return collidable;
}

void PtMap::setTileCollidable(bool collisionModifier,CCPoint position)
{
	if (collisionModifier == true) 
	{
		_metaLayer->setTileGID(1,position);
	}
	else 
	{
		_metaLayer->setTileGID(2,position);
	}
}

void PtMap::update(ccTime dt)
{
	
}
