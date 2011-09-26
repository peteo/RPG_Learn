/*
 *  MenuScene.h
 *  PtRPG
 *
 *  Created by Peteo on 11-9-26.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(MenuScene);
	
private:
	
	int		_menuType;
	CCMenu *_mainMenu;
	CCMenu *_saveMenu;
	std::string _saveName;
	std::string _saveLocation;
	
	// a selector callback
	//virtual void menuCloseCallback(CCObject* pSender);
	void onPlay(CCObject* sender);
	void onSettings(CCObject* sender);
	void onAbout(CCObject* sender);
	void onSelect(CCObject* sender);
	void newGame(CCObject* sender);
};

#endif // __MENU_SCENE_H__