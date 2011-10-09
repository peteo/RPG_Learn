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

#include "PtLink.h"
#include "cocos2d.h"

#include "PtMap.h"
#include "PtCharacter.h"

USING_NS_CC;

class GameScene : public CCLayer ,public PhotonListener
{
public:
	
	virtual ~GameScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameScene);
	
	virtual void registerWithTouchDispatcher(void);
	
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
private:
	
	PtMap *_tileMap;
	
	PtCharacter  *_playerChar;
	
	CCRect _dDown1;
	CCRect _dDown2;
	CCRect _dUp1;
	CCRect _dUp2;
	CCRect _dLeft;
	CCRect _dRight;
	
	float _loopSpeed;
	
	CCArray *_npcarray;
	CCArray *_RemoteplayerArray;
	
	PtLink  *_Link;
	bool    _bIsEnterWorlded;
	
private:
	
	// Camera Helper Methods
	void followPlayer(void * sender);
	void centerCamera(CCPoint point);
	void moveCameraByTile(CCPoint point ,int duration);
	void moveCameraToPos(CCPoint point ,int duration);
	
	// Textbox Actions
	void displayTextbox(CCString * displayText);
	
	// Map Change
	void mapChange(void * sender);
	
	// Methods for Event Checking
	void checkForEvent();
	//void triggerNPCEvent(PtNpc * npc ,int lookDirection);
	
	// Loops and Tick Methods
	void gameLoop(ccTime dt);
	void textBoxUpdate(ccTime dt);
	
public:
	void PhotonPeerOperationResult(nByte opCode, int returnCode, const Hashtable& returnValues,short invocID);
	void PhotonPeerStatus(int statusCode);
	void PhotonPeerEventAction(nByte eventCode,const Hashtable& photonEvent);
	void PhotonPeerDebugReturn(PhotonPeer_DebugLevel debugLevel, const JString& string);
};

#endif // __GAME_SCENE_H__