/*
 *  GameScene.h
 *  PtRPG
 *
 *  Created by Peteo on 11-9-26.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameScene);
	
private:
	
};

#endif // __GAME_SCENE_H__