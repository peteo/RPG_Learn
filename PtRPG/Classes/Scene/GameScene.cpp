/*
 *  GameScene.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-26.
 *  Copyright 2011 The9. All rights reserved.
 *
 */

#include "GameScene.h"
#include "PtUtils.h"

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

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_npcarray);
	CC_SAFE_RELEASE(_RemoteplayerArray);
	
	CC_SAFE_DELETE(_playerChar);
	CC_SAFE_DELETE(_tileMap);
	CC_SAFE_DELETE(_Link);
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
	
	_Link = new PtLink();
	_Link->InitLib(this);
	
	// Load Tilemap
	//_tileMap = PtMap::PtMapWithName("testmapFinal");
	
	_tileMap = new PtMap("testmapFinal");
	addChild(_tileMap->_tileMap);
	
	// Load Playersprite
	CCString * pSpritName = new CCString("playersprite_female");
	
	//_playerChar = PtCharacter::initWithSpritesheet(pSpritName,_tileMap);
	
	_playerChar = new PtCharacter(pSpritName,_tileMap);
	
	_playerChar->_characterSprite->setPosition(_tileMap->spawnPoint());
	
	addChild(_playerChar->_spriteSheet);

	//_playerChar->setItemID(PtUtils::getDeviceID());
	
	CC_SAFE_DELETE(pSpritName);
	
	//Enable Touch Support	
	this->setIsTouchEnabled(true);
	
	// Initializing the V-Pad
	_dDown1 = CCRectMake(0,   0,   240, 90);
	_dDown2 = CCRectMake(240, 0,   240, 90);
	_dUp1	= CCRectMake(0,   230, 240, 90);
	_dUp2	= CCRectMake(240, 230, 240, 90);
	_dLeft	= CCRectMake(0,   90,  240, 140);
	_dRight = CCRectMake(240, 90,  240, 140);
	
	_loopSpeed = 0;
	
	_npcarray		   = CCArray::arrayWithCapacity(4);
    _npcarray->retain();
	
	_RemoteplayerArray = CCArray::arrayWithCapacity(4);
	_RemoteplayerArray->retain();
	
	//Load NPCs on Map
	for (int i = 0;i < _tileMap->_npcs->count();i += 1) 
	{
		/*
		NVNpc *npc = [[NVNpc alloc] initWithID:i onMap:_tileMap];
		[self addChild:npc.spriteSheet z:i + 1];
		[_npcarray addObject:npc];
		[npc release];
		*/
	}
	
	// Reorder Children
	reorderChild(_tileMap->_bgLayer,0);
	reorderChild(_tileMap->_fgLayer,		_npcarray->count() + 5);
	reorderChild(_tileMap->_extraLayer,		_npcarray->count() + 6);
	reorderChild(_playerChar->_spriteSheet, _npcarray->count() + 1);
	
	// Start the GameLoop
	schedule(schedule_selector(GameScene::gameLoop),_loopSpeed);
	runAction(CCFollow::actionWithTarget(_playerChar->_characterSprite));

	//test
	_bIsEnterWorlded = true;
	
	//[_Link EnterWorld:_playerChar];
	
	return true;
}

void GameScene::gameLoop(ccTime dt)
{
	_Link->Run();
	
	CCObject    * pObject;
	CCARRAY_FOREACH(_RemoteplayerArray, pObject)
	{
		PtCharacter * pCharacter = (PtCharacter*)pObject;
		if(pCharacter && pCharacter->_spriteSheet->getIsVisible())
		{
			//NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:pCharacter.ItemID];
			//pViewDistance->getPosition() = pCharacter->_characterSprite->getPosition();
		}
	}
	
	if (_playerChar->_characterSprite->numberOfRunningActions() == 0 
		&& _playerChar->_moveState != kStateIdle)
	{
		_playerChar->update();
		
		//CCLOG(@"playerChar[%f][%f]",_playerChar.characterSprite.position.x,_playerChar.characterSprite.position.y);
		
		float pPos[2];
		
		switch (_playerChar->_moveState) 
		{
			case kStateDown:
			{
				pPos[0] = _playerChar->_characterSprite->getPosition().x;
				pPos[1] = _playerChar->_characterSprite->getPosition().y - 32;
			}
				break;
			case kStateUp:
			{
				pPos[0] = _playerChar->_characterSprite->getPosition().x;
				pPos[1] = _playerChar->_characterSprite->getPosition().y + 32;
			}
				break;
			case kStateLeft:
			{
				pPos[0] = _playerChar->_characterSprite->getPosition().x - 32;
				pPos[1] = _playerChar->_characterSprite->getPosition().y;
			}
				break;
			case kStateRight:
			{
				pPos[0] = _playerChar->_characterSprite->getPosition().x + 32;
				pPos[1] = _playerChar->_characterSprite->getPosition().y;
			}
				break;
			default:
				break;
		}
		
		float pRotation[1];
		pRotation[0] = _playerChar->_moveState;
		
		//转换为右上角为原点的坐标系
		pPos[0] = (640 - pPos[0]);
		pPos[1] = (640 - pPos[1]);
		
		_Link->MoveAbsolute(pPos,pRotation,_playerChar->getItemID());
	}
}

// Camera actions go here
void GameScene::followPlayer(void * sender)
{
	runAction(CCFollow::actionWithTarget(_playerChar->_characterSprite));
}

void GameScene::centerCamera(CCPoint point)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(-point.x+winSize.width/2,-point.y+winSize.height/2));
}

void GameScene::moveCameraByTile(CCPoint point,int duration)
{
	runAction(CCMoveBy::actionWithDuration(duration,ccp(_tileMap->_tileMap->getTileSize().width * -point.x,_tileMap->_tileMap->getTileSize().height * -point.y)));
}

void GameScene::moveCameraToPos(CCPoint point,int duration)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	runAction(CCMoveTo::actionWithDuration(duration,ccp(-point.x+winSize.width/2,-point.y+winSize.height/2)));
}

void GameScene::displayTextbox(CCString * displayText)
{
	//WIP, textbox is working perfectly but needs a new background. 
	// It will be inserted in the class "TextBoxLayer" so it's default and can be used anywhere.
	/*
	textBox = [[TextBoxLayer alloc] initWithColor:ccc4(0, 0, 255, 255) width:480 height:40 padding:10 text:displayText];
	textBox.delegate = self;
	textBox.position = ccp(0-self.position.x,0-self.position.y);
	[self addChild:textBox z:20];
	[self schedule:@selector(textBoxUpdate:) interval:0];
	[self unschedule:@selector(gameLoop:)];
	for (NVNpc *npc in _npcarray) 
	{
		[npc pauseSchedulerAndActions];
	}
	*/
}

void GameScene::mapChange(void * sender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1,[GameLayer gameScene],ccc3(0, 0, 0)));
}

void GameScene::checkForEvent()
{
	/*
	switch (_playerChar->_lookDirection)
	{
		case kStateDown:
			//Check down, lookdirection is 1
			for (NVNpc *npc in _npcarray) 
			{
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x,_playerChar.characterSprite.position.y - 32)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:2];
				}
			}
			break;
		case kStateUp:
			//check up, lookdirection is 2
			for (NVNpc *npc in _npcarray) 
			{
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x,_playerChar.characterSprite.position.y + 32)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:1];
				}
			}
			break;
		case kStateLeft:
			//Check left, lookdirection equals 3
			for (NVNpc *npc in _npcarray) 
			{
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x - 32,_playerChar.characterSprite.position.y)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:4];
				}
			}
			break;
		case kStateRight:
			//Right, obviously 4.
			for (NVNpc *npc in _npcarray) 
			{
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x + 32,_playerChar.characterSprite.position.y)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:3];
				}
			}
			break;
		default:
			break;
	}
	*/
}

/*
void GameScene::triggerNPCEvent(PtNpc *npc int lookDirection)
{
	//The events are triggered one after another, put in a sequence with the previous time
	//as a delay. This makes it seem as if the actions are actually executed in a sequence - 
	//this way they can still have different targets. (May seem a little complicated but works perfectly.)
	float previousDuration = 0;
	for (NVAction *currentAction in npc.reactionEvents) 
	{
		//Find out type of action. (Cycle through reaction array in npc)
		switch (currentAction.type) 
		{
			case kTextEvent:
				[npc lookInDirection:lookDirection];
				[self displayTextbox:currentAction.content];
				break;
			case kCameraEvent:
				if (textBox) 
				{
					
				}
				else 
				{
					if (previousDuration != 0) 
					{
						// Triggers a Camera event, e.g. moves the camera according to the event data.
						CGSize winSize = [[CCDirector sharedDirector] winSize];
						CGPoint targetPosition = [_tileMap positionForTileCoord:currentAction.position];
						CCSequence *nextAction = [CCSequence actions:[CCDelayTime actionWithDuration:previousDuration],[CCMoveTo actionWithDuration:currentAction.duration position:ccp(-targetPosition.x + winSize.width/2,-targetPosition.y + winSize.height/2)],nil];
						[self runAction:nextAction];
						// Every new action after the first one is started in a sequence with the previous delay as CCDelayTime as the first action.
						// This way, the actions are being executed in a sequence without being in a CCSequence. :)
						previousDuration = previousDuration + currentAction.duration;
					}
					else 
					{
						[self moveCameraToPos:[_tileMap positionForTileCoord:currentAction.position] withDuration:currentAction.duration];
						previousDuration = currentAction.duration;
					}
				}
				break;
			case kReturnEvent:
				if (previousDuration != 0) 
				{
					CCSequence *nextAction = [CCSequence actions:[CCDelayTime actionWithDuration:previousDuration],[CCCallFunc actionWithTarget:self selector:@selector(followPlayer:)],nil];
					[self runAction:nextAction];
				}
				else 
				{
					[self followPlayer:self];
				}
				break;
			default:
				break;
		}
	}
}
*/


// Touch Handling methods start here
// Set up Touch Dispatcher
void GameScene::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(_bIsEnterWorlded == false)
	{
		return true;
	}
	
	//if (!textBox)
	{
		CCPoint touchLocation = touch->locationInView(touch->view());		
		touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
		
		if (CCRect::CCRectContainsPoint(_dDown1, touchLocation) 
			|| CCRect::CCRectContainsPoint(_dDown2, touchLocation)) 
		{
			_playerChar->_moveState = kStateDown;
		}
		
		else if (CCRect::CCRectContainsPoint(_dUp1, touchLocation) 
				 || CCRect::CCRectContainsPoint(_dUp2, touchLocation)) 
		{
			_playerChar->_moveState = kStateUp;
		}
		
		else if (CCRect::CCRectContainsPoint(_dLeft, touchLocation)) 
		{
			_playerChar->_moveState = kStateLeft;
		}
		
		else if (CCRect::CCRectContainsPoint(_dRight, touchLocation)) 
		{
			_playerChar->_moveState = kStateRight;
		}
	}
	/*
	else 
	{
		[textBox advanceText];
	}
	*/
	
	// Return YES to bind the Touch to self
	return true;
}

void GameScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(_bIsEnterWorlded == false)
	{
		return;
	}
	
	CCPoint touchLocation = touch->locationInView(touch->view());		
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	
	if (CCRect::CCRectContainsPoint(_dDown1, touchLocation) 
		|| CCRect::CCRectContainsPoint(_dDown2, touchLocation)) 
	{
		_playerChar->_moveState = kStateDown;
	}
	
	else if (CCRect::CCRectContainsPoint(_dUp1, touchLocation) 
			 || CCRect::CCRectContainsPoint(_dUp2, touchLocation)) 
	{
		_playerChar->_moveState = kStateUp;
	}
	
	else if (CCRect::CCRectContainsPoint(_dLeft, touchLocation)) 
	{
		_playerChar->_moveState = kStateLeft;
	}
	
	else if (CCRect::CCRectContainsPoint(_dRight, touchLocation)) 
	{
		_playerChar->_moveState = kStateRight;
	}
}

void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	_playerChar->_moveState = kStateIdle;
}

void GameScene::textBoxUpdate(ccTime dt) 
{
	//[textBox update:dt];
}

/*
-(void) textBox:(TextBoxLayer *)tbox didFinishAllTextWithPageCount:(int)pc 
{
	[self removeChild:textBox cleanup:YES];
	textBox = nil;
	[self unschedule:@selector(textBoxUpdate:)];
	[self schedule:@selector(gameLoop:) interval:_loopSpeed];
	for (NVNpc *npc in _npcarray) {
		[npc resumeSchedulerAndActions];
	}
}
*/

void GameScene::PhotonPeerOperationResult(nByte opCode, int returnCode, const Hashtable& returnValues,short invocID)
{
	switch(opCode)
	{
		case ExitGameCode::CreateWorld:
		{
			if(returnCode == ExitGameCode::Ok)
			{
				_Link->_state = stateCreateWorlded;
				//创建世界成功
				_Link->EnterWorld(_playerChar);
			}
		}
			break;
			
		case ExitGameCode::EnterWorld:
		{
			if(returnCode == ExitGameCode::WorldNotFound)
			{
				_Link->CreateWorld();
			}
			else if(returnCode == ExitGameCode::Ok)
			{
				_Link->_state = stateEnterWorlded;
				//加入世界成功
				CCLOG("EnterWorld_Succeed");
				
				_Link->RadarSubscribe();
				
				_bIsEnterWorlded = true;
			}
		}
			break;
			
		case ExitGameCode::ExitWorld:
		{
			
		}
			break;
		default:
			break;
	}
}

void GameScene::PhotonPeerStatus(int statusCode)
{
	
}

void GameScene::PhotonPeerEventAction(nByte eventCode,const Hashtable& photonEvent)
{
	switch (eventCode)
	{
		case ExitGameCode::ItemMoved:
		{
			CCString * pItemID = NULL;
			ExitGames::JString pStrItemID;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))
			{
				pStrItemID = (ExitGames::ValueObject<ExitGames::JString>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))).getDataCopy();
				pItemID = new CCString(pStrItemID.ANSIRepresentation().cstr());
				pItemID->autorelease();
			}
			
			if(pItemID == NULL)
			{
				return;
			}
			
			float* OldPositionArry = NULL;
			float* PositionArry    = NULL;
			float* RotationArry    = NULL;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::OldPosition)))
				OldPositionArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::OldPosition)))).getDataCopy();
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))
				PositionArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))).getDataCopy();
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Rotation)))
				RotationArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Rotation)))).getDataCopy();
			
			float Pos[2];
			//坐标X
			Pos[0] = PositionArry[0];
			
			//坐标Y
			Pos[1] = PositionArry[1];
			
			//转换为左下角为原点的坐标系
			Pos[0] = (640 - Pos[0]);
			Pos[1] = (640 - Pos[1]);
			
			//移动方向 moveState
			float pRotation[1];
			pRotation[0] = RotationArry[0];
			
			int pMoveState = pRotation[0];
			
			CCPoint pPoint = CCPointMake(Pos[0], Pos[1]);
			
			CCLOG("RemotePlayer[%f][%f]",pPoint.x,pPoint.y);
			
			CCObject  * pObject = NULL;
			CCARRAY_FOREACH(_RemoteplayerArray, pObject)
			{
				PtCharacter * pCharacter = (PtCharacter*)pObject;
				
				if(0 == strcmp(pCharacter->getItemID()->m_sString.c_str(),pItemID->m_sString.c_str()))
				{
					pCharacter->_moveState = pMoveState;
					
					switch (pMoveState)
					{
						case kStateIdle:
							break;
						case kStateDown:
							// Move Down
							pCharacter->lookInDirection(1);
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
							pCharacter->_characterSprite->runAction(CCMoveTo::actionWithDuration(pCharacter->_moveSpeed,pPoint));
							pCharacter->_characterSprite->runAction(CCAnimate::actionWithAnimation(pCharacter->_walkDownAnim));
						}
							break;
						case kStateUp:
							// Move Up
							pCharacter->lookInDirection(2);
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
							pCharacter->_characterSprite->runAction(CCMoveTo::actionWithDuration(pCharacter->_moveSpeed,pPoint));
							pCharacter->_characterSprite->runAction(CCAnimate::actionWithAnimation(pCharacter->_walkUpAnim));
						}
							break;
						case kStateLeft:
							// Move Left
							pCharacter->lookInDirection(3);
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
							pCharacter->_characterSprite->runAction(CCMoveTo::actionWithDuration(pCharacter->_moveSpeed,pPoint));
							pCharacter->_characterSprite->runAction(CCAnimate::actionWithAnimation(pCharacter->_walkLeftAnim));
						}
							break;
						case kStateRight:
							// Move Right
							pCharacter->lookInDirection(4);
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
							pCharacter->_characterSprite->runAction(CCMoveTo::actionWithDuration(pCharacter->_moveSpeed,pPoint));
							pCharacter->_characterSprite->runAction(CCAnimate::actionWithAnimation(pCharacter->_walkRightAnim));
						}
							break;
						default:
							break;
					}
					return;
				}
			}
			
			FREEIF(OldPositionArry);
			FREEIF(PositionArry);
			FREEIF(RotationArry);
		}
			break;
		case ExitGameCode::ItemDestroyed:
		{
			CCLOG("ItemDestroyed");
			
			CCString * pItemID = NULL;
			ExitGames::JString pStrItemID;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))
			{
				pStrItemID = (ExitGames::ValueObject<ExitGames::JString>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))).getDataCopy();
				pItemID = new CCString(pStrItemID.ANSIRepresentation().cstr());
				pItemID->autorelease();
			}
			
			if(pItemID)
			{	
				CCObject  * pObject = NULL;
				CCARRAY_FOREACH(_RemoteplayerArray, pObject)
				{
					PtCharacter * pCharacter = (PtCharacter*)pObject;
					
					if(0 == strcmp(pCharacter->getItemID()->m_sString.c_str(),pItemID->m_sString.c_str()))
					{
						//NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						
						//[self removeChild:pViewDistance         cleanup:YES];
						removeChild(pCharacter->_spriteSheet,true);
						
						/*
						for(NVRemotePlayRadar * pRemotePlayRadar in _RadarView.RemotePlayRadarArray)
						{
							if([pRemotePlayRadar.ItemID isEqual:pItemID])
							{
								[_RadarView.RemotePlayRadarArray removeObject:pRemotePlayRadar];
							}
						}
						*/
						
						//[_ViewDistanceArray removeObjectForKey:Character.ItemID];
						_RemoteplayerArray->removeObject(pCharacter);
						
						return;
					}
				}
			}
		}
			break;
		case ExitGameCode::ItemSubscribed:
		{
			CCLOG("ItemSubscribed");
			
			CCString * pItemID = NULL;
			ExitGames::JString pStrItemID;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))
			{
				pStrItemID = (ExitGames::ValueObject<ExitGames::JString>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))).getDataCopy();
				pItemID = new CCString(pStrItemID.ANSIRepresentation().cstr());
				pItemID->autorelease();
			}
			
			if(pItemID)
			{
				float* PositionArry    = NULL;
				float* RotationArry    = NULL;
				
				if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))
					PositionArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))).getDataCopy();
				
				if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Rotation)))
					RotationArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Rotation)))).getDataCopy();
				
				float Pos[2];
				Pos[0] = PositionArry[0];
				Pos[1] = PositionArry[1];
				
				//转换为左下角为原点的坐标系
				Pos[0] = (640 - Pos[0]);
				Pos[1] = (640 - Pos[1]);
				
				float pRotation[1];
				pRotation[0] = RotationArry[0];
				
				int pMoveState = (int)pRotation[0];
				
				CCObject  * pObject = NULL;
				CCARRAY_FOREACH(_RemoteplayerArray, pObject)
				{
					PtCharacter * pCharacter = (PtCharacter*)pObject;
					
					if(0 == strcmp(pCharacter->getItemID()->m_sString.c_str(),pItemID->m_sString.c_str()))
					{
						pCharacter->_spriteSheet->setIsVisible(true);
						pCharacter->_characterSprite->setPosition(CCPointMake(Pos[0], Pos[1]));
						switch (pMoveState)
						{
							case kStateIdle:
								break;
							case kStateDown:
								pCharacter->lookInDirection(1);
								break;
							case kStateUp:
								pCharacter->lookInDirection(2);
								break;
							case kStateLeft:
								pCharacter->lookInDirection(3);
								break;
							case kStateRight:
								pCharacter->lookInDirection(4);
								break;
							default:
								break;
						}
						
						/*
						NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						[pViewDistance setVisible:YES];
						pViewDistance.position = Character.characterSprite.position;
						*/
						
						return;
					}
				}
				
				//新的玩家加入
				
				CCString * pSpritName = new CCString("playersprite_female");
				
				PtCharacter * pRemoteplayer = new PtCharacter(pSpritName,_tileMap);
				
				pRemoteplayer->autorelease();
		
				pRemoteplayer->_characterSprite->setPosition(CCPointMake(Pos[0], Pos[1]));
				switch (pMoveState)
				{
					case kStateIdle:
						break;
					case kStateDown:
						pRemoteplayer->lookInDirection(1);
						break;
					case kStateUp:
						pRemoteplayer->lookInDirection(2);
						break;
					case kStateLeft:
						pRemoteplayer->lookInDirection(3);
						break;
					case kStateRight:
						pRemoteplayer->lookInDirection(4);
						break;
					default:
						break;
				}
				pRemoteplayer->setItemID(pItemID);
				addChild(pRemoteplayer->_spriteSheet);
				
				_RemoteplayerArray->addObject(pRemoteplayer);
				
				reorderChild(pRemoteplayer->_spriteSheet,_npcarray->count() + _RemoteplayerArray->count() + 2);

				//添加玩家得视野
				/*
				NViewDistance * pViewDistance = [NViewDistance node];
				
				pViewDistance.ViewDistanceEnter = DISTANCEENTER;
				pViewDistance.ViewDistanceExit  = DISTANCEEXIT;
				pViewDistance.ItemID = pRemoteplayer.ItemID;
				pViewDistance.position = pRemoteplayer.characterSprite.position;
				[self addChild:pViewDistance z:101];
				
				[_ViewDistanceArray setObject:pViewDistance forKey:pViewDistance.ItemID];
				*/
				
				//雷达中添加玩家
				/*
				NVRemotePlayRadar * pRemotePlayRadar = [[NVRemotePlayRadar alloc] init];
				
				pRemotePlayRadar.ItemID = pRemoteplayer.ItemID;
				pRemotePlayRadar.Pos    = [_tileMap GLForPosition:pRemoteplayer.characterSprite.position];
				
				[_RadarView.RemotePlayRadarArray addObject:pRemotePlayRadar];
				
				[pRemotePlayRadar release];
				*/
				
				CC_SAFE_DELETE(pSpritName);
				
				FREEIF(PositionArry);
				FREEIF(RotationArry);
			}
		}
			break;
		case ExitGameCode::ItemUnsubscribed:
		{
			CCLOG("ItemUnsubscribed");
			
			CCString * pItemID = NULL;
			ExitGames::JString pStrItemID;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))
			{
				pStrItemID = (ExitGames::ValueObject<ExitGames::JString>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))).getDataCopy();
				pItemID = new CCString(pStrItemID.ANSIRepresentation().cstr());
				pItemID->autorelease();
			}
			
			if(pItemID)
			{
				CCObject  * pObject = NULL;
				CCARRAY_FOREACH(_RemoteplayerArray, pObject)
				{
					PtCharacter * pCharacter = (PtCharacter*)pObject;
					
					if(0 == strcmp(pCharacter->getItemID()->m_sString.c_str(),pItemID->m_sString.c_str()))
					{
						pCharacter->_spriteSheet->setIsVisible(false);
						
						//NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						
						//[pViewDistance setVisible:NO];
						
						return;
					}
				}
			}
		}
		case ExitGameCode::RadarUpdate:
		{
			CCLOG("RadarUpdate");
			
			CCString * pItemID = NULL;
			ExitGames::JString pStrItemID;
			
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))
			{
				pStrItemID = (ExitGames::ValueObject<ExitGames::JString>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::ItemId)))).getDataCopy();
				pItemID = new CCString(pStrItemID.ANSIRepresentation().cstr());
				pItemID->autorelease();
			}
			
			float* PositionArry    = NULL;
			if(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))
				PositionArry = (ExitGames::ValueObject<float*>(photonEvent.getValue(ExitGames::KeyObject<nByte>((nByte)ExitGameCode::Position)))).getDataCopy();
			
			/*
			for(NVRemotePlayRadar * pRemotePlayRadar in _RadarView.RemotePlayRadarArray)
			{
				if([pRemotePlayRadar.ItemID isEqual:pItemID])
				{
					float Pos[2];
					[[PositionArry objectAtIndex:0] getValue:&Pos[0]];
					[[PositionArry objectAtIndex:1] getValue:&Pos[1]];
					//转换为左下角为原点的坐标系
					Pos[0] = (640 - Pos[0]);
					Pos[1] = (640 - Pos[1]);
					
					pRemotePlayRadar.Pos = [_tileMap GLForPosition:ccp(Pos[0],Pos[1])];
				}
			}
			*/
			
			FREEIF(PositionArry);
		}
			break;
		default:
			break;
	}
}

void GameScene::PhotonPeerDebugReturn(PhotonPeer_DebugLevel debugLevel, const JString& string)
{
	
}

