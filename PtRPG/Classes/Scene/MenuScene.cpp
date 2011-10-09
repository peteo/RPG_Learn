/*
 *  MenuScene.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-26.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "GameScene.h"
#include "MenuScene.h"

CCScene* MenuScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::node();
	
	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	// Initialize Main Menu
	
	CCMenuItem *menuItem1 = CCMenuItemFont::itemFromString("Play",this,menu_selector(MenuScene::onPlay));
	CCMenuItem *menuItem2 = CCMenuItemFont::itemFromString("Settings",this,menu_selector(MenuScene::onSettings));
	CCMenuItem *menuItem3 = CCMenuItemFont::itemFromString("About",this,menu_selector(MenuScene::onAbout));
	
	_mainMenu = CCMenu::menuWithItems(menuItem1,menuItem2,menuItem3,NULL);
	
	_mainMenu->alignItemsVertically();
	
	addChild(_mainMenu);
	
	return true;
}

/*
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
*/

void MenuScene::onPlay(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5,GameScene::scene(),ccc3(0,0,0)));
}

void MenuScene::onSettings(CCObject* sender)
{
	
}

void MenuScene::onAbout(CCObject* sender)
{
	
}

void MenuScene::onSelect(CCObject* sender)
{
	
}

void MenuScene::newGame(CCObject* sender)
{
	
}