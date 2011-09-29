/*
 *  PtCharacter.h
 *  PtRPG
 *
 *  Created by Peteo on 11-9-29.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#ifndef __PT_CHARACTER_H__
#define __PT_CHARACTER_H__

#include "cocos2d.h"
#include "PtMap.h"

typedef enum 
{
	kStateIdle = 0,
	kStateDown,
	kStateUp,
	kStateLeft,
	kStateRight
} _moveState;

USING_NS_CC;

class PtCharacter : public CCNode 
{
public:
	static PtCharacter * initWithSpritesheet(CCString *spriteName,PtMap * currentMap);
	
	PtCharacter(CCString *spriteName,PtMap * currentMap);
	
	virtual ~PtCharacter();
	
private:
	
	CCAnimation *_walkDownAnim;
	CCAnimation *_walkUpAnim;
	CCAnimation *_walkLeftAnim;
	CCAnimation *_walkRightAnim;
	
	float _moveSpeed;
	float _animSpeed;
	
	int _lookDirection;
	
	CCString *_spriteName;
	
	PtMap *_currentMap;
	
	int _previousGID;
	
	CCString *_ItemID;
	CCSize    _ViewDistanceEnter;
	CCSize    _ViewDistanceExit;
	
public:
	void loadExtraAnimations();
	void lookInDirection(int lookDirection);
	void update();
	void setItemID(CCString * pId);
	
public:
	CCSprite		  *_characterSprite;
	CCSpriteBatchNode *_spriteSheet;
	
	int _moveState;
	
};

#endif