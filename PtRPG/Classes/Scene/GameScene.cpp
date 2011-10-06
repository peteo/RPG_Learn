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
		
		//[_Link MoveAbsolute:pPos:pRotation:_playerChar.ItemID];
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










