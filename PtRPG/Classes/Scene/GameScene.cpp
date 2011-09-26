/*
 *  GameScene.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-26.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "GameScene.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	GameScene *layer = GameScene::node();
	
	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	return true;
}