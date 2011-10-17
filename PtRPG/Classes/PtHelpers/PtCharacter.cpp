/*
 *  PtCharacter.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-29.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "PtCharacter.h"
#include "PtMacros.h"
#include "PtMap.h"

PtCharacter * PtCharacter::initWithSpritesheet(CCString *spriteName,PtMap * currentMap)
{
	PtCharacter *pRet = new PtCharacter(spriteName,currentMap);
	if(pRet)
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

PtCharacter::PtCharacter(CCString *spriteName,PtMap * currentMap)
:_characterSprite(NULL)
,_spriteSheet(NULL)
,_walkDownAnim(NULL)
,_walkUpAnim(NULL)
,_walkLeftAnim(NULL)
,_walkRightAnim(NULL)
,_spriteName(NULL)
,_currentMap(NULL)
,_ItemID(NULL)
,_moveSpeed(0)
,_animSpeed(0)
,_moveState(0)
,_lookDirection(0)
,_previousGID(0)
,_ViewDistanceEnter(0,0)
,_ViewDistanceExit(0,0)
{
	_spriteName    =  new CCString(spriteName->toStdString().c_str());
	_lookDirection =  1;
	
	char pTempSpriteName[64] = {0};
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"img/%s.plist",spriteName->toStdString().c_str());
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pTempSpriteName);
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"img/%s.png",spriteName->toStdString().c_str());
	_spriteSheet = CCSpriteBatchNode::batchNodeWithFile(pTempSpriteName);
	
	// Create the Sprite itself
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s1-0.png",spriteName->toStdString().c_str());
	_characterSprite = CCSprite::spriteWithSpriteFrameName(pTempSpriteName);
	
	// and add it to the SpriteSheet
	_spriteSheet->addChild(_characterSprite);
	// also, set Display ID
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s1-0.png",spriteName->toStdString().c_str());
	_characterSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	_animSpeed = 0.1;
	
	// Load all Animation Frames into their Arrays and create the Animations
	// For Down-Animation: Framegroup 1
	CCMutableArray<CCSpriteFrame*> *walkDownFrames = new CCMutableArray<CCSpriteFrame*>();
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s1-1.png",spriteName->toStdString().c_str());
	walkDownFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s1-0.png",spriteName->toStdString().c_str());
	walkDownFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
		
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s1-2.png",spriteName->toStdString().c_str());
	walkDownFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	_walkDownAnim = CCAnimation::animationWithFrames(walkDownFrames,_animSpeed);
	_walkDownAnim->retain();
	CC_SAFE_DELETE(walkDownFrames);
	
	// For Up-Animation: Framegroup 2
	CCMutableArray<CCSpriteFrame*> *walkUpFrames = new CCMutableArray<CCSpriteFrame*>();
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s2-1.png",spriteName->toStdString().c_str());
	walkUpFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s2-0.png",spriteName->toStdString().c_str());
	walkUpFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s2-2.png",spriteName->toStdString().c_str());
	walkUpFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	_walkUpAnim = CCAnimation::animationWithFrames(walkUpFrames,_animSpeed);
	_walkUpAnim->retain();
	CC_SAFE_DELETE(walkUpFrames);
	
	// For Left-Animation: Framegroup 3	
	CCMutableArray<CCSpriteFrame*> *walkLeftFrames = new CCMutableArray<CCSpriteFrame*>();
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s3-1.png",spriteName->toStdString().c_str());
	walkLeftFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s3-0.png",spriteName->toStdString().c_str());
	walkLeftFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s3-2.png",spriteName->toStdString().c_str());
	walkLeftFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	_walkLeftAnim = CCAnimation::animationWithFrames(walkLeftFrames,_animSpeed);
	_walkLeftAnim->retain();
	CC_SAFE_DELETE(walkLeftFrames);
	
	
	// For Right-Animation: Framegroup 4
	CCMutableArray<CCSpriteFrame*> *walkRightFrames = new CCMutableArray<CCSpriteFrame*>();
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s4-1.png",spriteName->toStdString().c_str());
	walkRightFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s4-0.png",spriteName->toStdString().c_str());
	walkRightFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
	sprintf(pTempSpriteName,"%s4-2.png",spriteName->toStdString().c_str());
	walkRightFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
	
	_walkRightAnim = CCAnimation::animationWithFrames(walkRightFrames,_animSpeed);
	_walkRightAnim->retain();
	CC_SAFE_DELETE(walkRightFrames);
	
	_moveSpeed   = 0.3;
	_moveState   = kStateIdle;
	_currentMap  = currentMap;
	_previousGID = 2;
	
}

PtCharacter::~PtCharacter()
{
	CC_SAFE_DELETE(_spriteName);
	CC_SAFE_DELETE(_ItemID);
	
	CC_SAFE_RELEASE(_walkDownAnim);
	CC_SAFE_RELEASE(_walkUpAnim);
	CC_SAFE_RELEASE(_walkLeftAnim);
	CC_SAFE_RELEASE(_walkRightAnim);
}

void PtCharacter::loadExtraAnimations()
{
	// Place for Extra-Animations (Framegroups 5-9)
}

void PtCharacter::setItemID(CCString * pId)
{
	CC_SAFE_DELETE(_ItemID);
	_ItemID = new CCString(pId->toStdString().c_str());
	CCLOG("ItemID[%s]",_ItemID->toStdString().c_str());
}

void PtCharacter::lookInDirection(int lookDirection)
{
	char pTempSpriteName[32] = {0};
	
	switch (lookDirection) 
	{
		case 0:
			break;
		case 1:
			ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
			sprintf(pTempSpriteName,"%s1-0.png",_spriteName->toStdString().c_str());
			_characterSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
			_lookDirection = 1;
			break;
		case 2:
			ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
			sprintf(pTempSpriteName,"%s2-0.png",_spriteName->toStdString().c_str());
			_characterSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
			_lookDirection = 2;
			break;
		case 3:
			ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
			sprintf(pTempSpriteName,"%s3-0.png",_spriteName->toStdString().c_str());
			_characterSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
			_lookDirection = 3;
			break;
		case 4:
			ZeroMemory(pTempSpriteName,sizeof(pTempSpriteName));
			sprintf(pTempSpriteName,"%s4-0.png",_spriteName->toStdString().c_str());
			_characterSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pTempSpriteName));
			_lookDirection = 4;
			break;
		default:
			break;
	}
}

void PtCharacter::update()
{
	switch (_moveState)
	{
		case kStateIdle:
			break;
		case kStateDown:
			// Move Down
			lookInDirection(1);
			if(_currentMap->tileCoordForPosition(_characterSprite->getPosition()).y >=  _currentMap->_tileMap->getMapSize().height - 1)
				return;
			
			if (!_currentMap->checkCollisionForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y-32))) 
			{
				_currentMap->_metaLayer->setTileGID(_previousGID,_currentMap->tileCoordForPosition(_characterSprite->getPosition()));
				_previousGID = _currentMap->_metaLayer->tileGIDAt(_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y-32)));
				_currentMap->setTileCollidable(true,_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y-32)));
				_characterSprite->runAction(CCMoveBy::actionWithDuration(_moveSpeed,ccp(0,-32)));
				_characterSprite->runAction(CCAnimate::actionWithAnimation(_walkDownAnim));
			}
			/*
			else 
			{
				for (NSDictionary *properties in _currentMap.doors) 
				{
					if (CGPointEqualToPoint([_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)], [_currentMap tileCoordForPosition:ccp([[properties valueForKey:@"x"] floatValue],[[properties valueForKey:@"y"] floatValue])])) 
					{
						[[StateManager sharedStateManager] setCurrentMap:[properties valueForKey:@"map"]];
						[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
						[_characterSprite runAction:[CCMoveBy actionWithDuration:self.moveSpeed position:ccp(0,-32)]];
						[_characterSprite runAction:[CCAnimate actionWithAnimation:_walkDownAnim]]; 
						[[NSNotificationCenter defaultCenter] postNotificationName: @"mapChange" object: nil];
					}
				}
			}
			*/
			
			break;
		case kStateUp:
			// Move Up
			lookInDirection(2);
			if(_currentMap->tileCoordForPosition(_characterSprite->getPosition()).y <= 0)
				return;
			
			if (!_currentMap->checkCollisionForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y+32)))
			{
				_currentMap->_metaLayer->setTileGID(_previousGID,_currentMap->tileCoordForPosition(_characterSprite->getPosition()));
				_previousGID = _currentMap->_metaLayer->tileGIDAt(_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y+32)));
				_currentMap->setTileCollidable(true,_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x,_characterSprite->getPosition().y+32)));
				
				
				_characterSprite->runAction(CCMoveBy::actionWithDuration(_moveSpeed,ccp(0,32)));
				_characterSprite->runAction(CCAnimate::actionWithAnimation(_walkUpAnim));
			}
			break;
		case kStateLeft:
			// Move Left
			lookInDirection(3);
			if(_currentMap->tileCoordForPosition(_characterSprite->getPosition()).x <= 0)
				return;
			
			if (!_currentMap->checkCollisionForPosition(ccp(_characterSprite->getPosition().x-32,_characterSprite->getPosition().y)))
			{
				_currentMap->_metaLayer->setTileGID(_previousGID,_currentMap->tileCoordForPosition(_characterSprite->getPosition()));
				_previousGID = _currentMap->_metaLayer->tileGIDAt(_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x-32,_characterSprite->getPosition().y)));
				_currentMap->setTileCollidable(true,_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x-32,_characterSprite->getPosition().y)));
				
				_characterSprite->runAction(CCMoveBy::actionWithDuration(_moveSpeed,ccp(-32,0)));
				_characterSprite->runAction(CCAnimate::actionWithAnimation(_walkLeftAnim));
			}
			break;
		case kStateRight:
			// Move Right
			lookInDirection(4);
			if(_currentMap->tileCoordForPosition(_characterSprite->getPosition()).x >= _currentMap->_tileMap->getMapSize().width - 1)
				return;
			
			if (!_currentMap->checkCollisionForPosition(ccp(_characterSprite->getPosition().x+32,_characterSprite->getPosition().y)))
			{
				_currentMap->_metaLayer->setTileGID(_previousGID,_currentMap->tileCoordForPosition(_characterSprite->getPosition()));
				_previousGID = _currentMap->_metaLayer->tileGIDAt(_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x+32,_characterSprite->getPosition().y)));
				_currentMap->setTileCollidable(true,_currentMap->tileCoordForPosition(ccp(_characterSprite->getPosition().x+32,_characterSprite->getPosition().y)));
				
				_characterSprite->runAction(CCMoveBy::actionWithDuration(_moveSpeed,ccp(32,0)));
				_characterSprite->runAction(CCAnimate::actionWithAnimation(_walkRightAnim));
			}
			break;
		default:
			break;
	}
}