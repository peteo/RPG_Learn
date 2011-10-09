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

class PtMap;

USING_NS_CC;

typedef enum 
{
	kStateIdle = 0,
	kStateDown,
	kStateUp,
	kStateLeft,
	kStateRight
} _moveState;

class PtCharacter : public CCNode 
{
public:
	static PtCharacter * initWithSpritesheet(CCString *spriteName,PtMap * currentMap);
	
	PtCharacter(CCString *spriteName,PtMap * currentMap);
	
	virtual ~PtCharacter();
	
private:
	
	CCString *_spriteName;
	
	PtMap *_currentMap;
	
	int _previousGID;
	
	CCString *_ItemID;
	
public:
	void loadExtraAnimations();
	void lookInDirection(int lookDirection);
	void update();
	void setItemID(CCString * pId);
	inline CCString* getItemID(){return _ItemID;}
	
public:
	CCSprite		  *_characterSprite;
	CCSpriteBatchNode *_spriteSheet;
	
	CCSize    _ViewDistanceEnter;
	CCSize    _ViewDistanceExit;
	
	int _moveState;
	
	float _moveSpeed;
	float _animSpeed;
	
	int   _lookDirection;
	
	CCAnimation *_walkDownAnim;
	CCAnimation *_walkUpAnim;
	CCAnimation *_walkLeftAnim;
	CCAnimation *_walkRightAnim;
	
};

#endif