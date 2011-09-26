//
//  HelloWorldLayer.m
//  novaRPG
//
//  Created by nova on 01.01.11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

// Import the interfaces

#import "GameLayer.h"
#import "novaRPGv2AppDelegate.h"
#import "WaitLayer.h"


#define DISTANCEENTER CGSizeMake( 64.0f, 64.0f)
#define DISTANCEEXIT  CGSizeMake(128.0f,128.0f)

@implementation GameLayer

+(id) gameScene
{
	// 'scene' is an autorelease object.
	CCScene *gameScene = [CCScene node];
	
	// 'layer' is an autorelease object.
	GameLayer *gameLayer = [GameLayer node];
	
	// -----------------WIP--------------------
	
	// EnvironmentLayer *envLayer = [[[EnvironmentLayer alloc] initWithWeather:0 atTime:1] autorelease];
	
	// -----------------WIP--------------------
	
	// add layer as a child to scene
	[gameScene addChild: gameLayer];
	//[gameScene addChild: envLayer];
	
	// return the scene
	return gameScene;
}


-(void) onExit:(id)sender
{
	/*
	[_Link CloseConnection];
	*/
	
	NSURL *URL = [NSURL URLWithString:[NSString stringWithFormat:@"punchball://?foo=1&amp;bar=2"]];
	[[UIApplication sharedApplication] openURL:URL];
	
}

// on "init" you need to initialize your instance
-(id) init
{
	if( (self=[super init] ))
	{
		novaRPGv2AppDelegate * app = [novaRPGv2AppDelegate getAppDelegate];
		
		UIDevice *myDevice = [UIDevice currentDevice];
		
		NSString *deviceID = [myDevice uniqueIdentifier];
		
		NSLog(@"deviceID[%@]",deviceID);
		
		app.Link.dataReceiver = self;
		
		_Link = app.Link;
		
		// Load Tilemap
		_tileMap = [[NVMap alloc] initWithMap:[[StateManager sharedStateManager] getCurrentMap]];
		[self addChild:_tileMap.tileMap];
		
		CCLOG(@"mapSize[%f][%f]tileSize[%f][%f]",_tileMap.tileMap.mapSize.width,
				  _tileMap.tileMap.mapSize.height,
			      _tileMap.tileMap.tileSize.width,
			      _tileMap.tileMap.tileSize.height);
		
		// Load Playersprite
		_playerChar = [[NVCharacter alloc] initWithSpritesheet:@"playersprite_female" onMap:_tileMap];
		_playerChar.characterSprite.position = [_tileMap spawnPoint];
		[self addChild:_playerChar.spriteSheet];
		
		_playerChar.ItemID = deviceID;
		
		_playerChar.ViewDistanceEnter = DISTANCEENTER;
		_playerChar.ViewDistanceExit  = DISTANCEEXIT;
		
		//Enable Touch Support
		self.isTouchEnabled = YES;
		
		// Initializing the V-Pad
		_dDown1 = CGRectMake(0,   0,   240, 90);
		_dDown2 = CGRectMake(240, 0,   240, 90);
		_dUp1	= CGRectMake(0,   230, 240, 90);
		_dUp2	= CGRectMake(240, 230, 240, 90);
		_dLeft	= CGRectMake(0,   90,  240, 140);
		_dRight = CGRectMake(240, 90,  240, 140);
		
		//_dTop = CGRectMake(200, 230, 80, 90);
		//_dBot = CGRectMake(200, 0, 80, 90);
		
		_loopSpeed = 0;
		
		_npcarray		   = [[CCArray alloc] init];
		_RemoteplayerArray = [[CCArray alloc] init];
		_ViewDistanceArray = [[NSMutableDictionary alloc] initWithCapacity:10];

		//Load NPCs on Map
		for (int i = 0;i < [_tileMap.npcs count]; i += 1) 
		{
			NVNpc *npc = [[NVNpc alloc] initWithID:i onMap:_tileMap];
			[self addChild:npc.spriteSheet z:i + 1];
			[_npcarray addObject:npc];
			[npc release];
		}
		
		// Reorder Children
		[self reorderChild:_tileMap.bgLayer z:0];
		[self reorderChild:_tileMap.fgLayer z:[_npcarray count] + 5];
		[self reorderChild:_tileMap.extraLayer z:[_npcarray count] + 6];
		[self reorderChild:_playerChar.spriteSheet z:[_npcarray count] + 1];
		
		// Register to the Notification Center for a possible Mapchange
		[[NSNotificationCenter defaultCenter] addObserver: self
												 selector: @selector(mapChange:)
													 name: @"mapChange" object: nil];
		
		// Start the GameLoop
		[self schedule:@selector(gameLoop:) interval: _loopSpeed];
		[self runAction:[CCFollow actionWithTarget:_playerChar.characterSprite]];
		
		_bIsEnterWorlded = NO;
		
		[_Link EnterWorld:_playerChar];
		
		//test
		CCMenuItem *menuItem = [CCMenuItemFont itemFromString:@"Exit" target:self selector:@selector(onExit:)];
        CCMenu * mainMenu = [CCMenu menuWithItems:menuItem,nil];
        mainMenu.position = ccp(464,50);
        [self addChild:mainMenu z:100];
		
		_viewDistance = [NViewDistance node];
		
		_viewDistance.ViewDistanceEnter = _playerChar.ViewDistanceEnter;
		_viewDistance.ViewDistanceExit  = _playerChar.ViewDistanceExit;
		_viewDistance.ItemID = _playerChar.ItemID;
		_viewDistance.position = _playerChar.characterSprite.position;
		[self addChild:_viewDistance z:101];
		
		_RadarView = [NVRadar node];
		_RadarView.position = _playerChar.characterSprite.position;
		[self addChild:_RadarView z:102];
		
	}
	return self;
}

// Camera actions go here
-(void) followPlayer:(id) sender 
{
	[self runAction:[CCFollow actionWithTarget:_playerChar.characterSprite]];
}
	
-(void) centerCamera:(CGPoint) point 
{
	CGSize winSize = [[CCDirector sharedDirector] winSize];
	self.position = ccp(-point.x+winSize.width/2,-point.y+winSize.height/2);
}

-(void) moveCameraByTile:(CGPoint)point withDuration:(int) duration 
{
	[self runAction:[CCMoveBy actionWithDuration:duration position:ccp(_tileMap.tileMap.tileSize.width*-point.x,_tileMap.tileMap.tileSize.height*-point.y)]];
}

-(void) moveCameraToPos:(CGPoint)point withDuration:(int) duration 
{
	CGSize winSize = [[CCDirector sharedDirector] winSize];
	[self runAction:[CCMoveTo actionWithDuration:duration position:ccp(-point.x+winSize.width/2,-point.y+winSize.height/2)]];
}

-(void) displayTextbox:(NSString *)displayText 
{
	//WIP, textbox is working perfectly but needs a new background. 
	// It will be inserted in the class "TextBoxLayer" so it's default and can be used anywhere.
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
}

-(void) mapChange:(id)sender
{
	[[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:1 scene:[GameLayer gameScene] withColor:ccc3(0, 0, 0)]];
}
	
-(void) checkForEvent 
{
	switch (_playerChar.lookDirection) 
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
			for (NVNpc *npc in _npcarray) {
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x - 32,_playerChar.characterSprite.position.y)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:4];
				}
			}
			break;
		case kStateRight:
			//Right, obviously 4.
			for (NVNpc *npc in _npcarray) {
				CGPoint npcpos = [_tileMap tileCoordForPosition:npc.characterSprite.position];
				if (CGPointEqualToPoint([_tileMap tileCoordForPosition:ccp(_playerChar.characterSprite.position.x + 32,_playerChar.characterSprite.position.y)],npcpos) == YES) {
					[self triggerNPCEvent:npc withDirection:3];
				}
			}
			break;
		default:
			break;
	}
}

-(void) triggerNPCEvent:(NVNpc *)npc withDirection:(int)lookDirection {
	//The events are triggered one after another, put in a sequence with the previous time
	//as a delay. This makes it seem as if the actions are actually executed in a sequence - 
	//this way they can still have different targets. (May seem a little complicated but works perfectly.)
	float previousDuration = 0;
	for (NVAction *currentAction in npc.reactionEvents) {
		//Find out type of action. (Cycle through reaction array in npc)
		switch (currentAction.type) {
			case kTextEvent:
				[npc lookInDirection:lookDirection];
				[self displayTextbox:currentAction.content];
				break;
			case kCameraEvent:
				if (textBox) {
				}
				else {
					if (previousDuration != 0) {
						// Triggers a Camera event, e.g. moves the camera according to the event data.
						CGSize winSize = [[CCDirector sharedDirector] winSize];
						CGPoint targetPosition = [_tileMap positionForTileCoord:currentAction.position];
						CCSequence *nextAction = [CCSequence actions:[CCDelayTime actionWithDuration:previousDuration],[CCMoveTo actionWithDuration:currentAction.duration position:ccp(-targetPosition.x + winSize.width/2,-targetPosition.y + winSize.height/2)],nil];
						[self runAction:nextAction];
						// Every new action after the first one is started in a sequence with the previous delay as CCDelayTime as the first action.
						// This way, the actions are being executed in a sequence without being in a CCSequence. :)
						previousDuration = previousDuration + currentAction.duration;
					}
					else {
						[self moveCameraToPos:[_tileMap positionForTileCoord:currentAction.position] withDuration:currentAction.duration];
						previousDuration = currentAction.duration;
					}
				}
			break;
			case kReturnEvent:
				if (previousDuration != 0) {
					CCSequence *nextAction = [CCSequence actions:[CCDelayTime actionWithDuration:previousDuration],[CCCallFunc actionWithTarget:self selector:@selector(followPlayer:)],nil];
					[self runAction:nextAction];
				}
				else {
					[self followPlayer:self];
				}
				break;
			default:
				break;
		}
	}
}

// Touch Handling methods start here
// Set up Touch Dispatcher
-(void) registerWithTouchDispatcher 
{
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
}

// Actual Touch Handling happens here
-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event 
{
	if(_bIsEnterWorlded == NO)
	{
		return YES;
	}
	
	if (!textBox)
	{
		CGPoint touchLocation = [touch locationInView: [touch view]];		
		touchLocation = [[CCDirector sharedDirector] convertToGL: touchLocation];
		
		if (CGRectContainsPoint(_dDown1, touchLocation) 
			|| CGRectContainsPoint(_dDown2, touchLocation)) 
		{
			_playerChar.moveState = kStateDown;
		}
		
		else if (CGRectContainsPoint(_dUp1, touchLocation) 
			|| CGRectContainsPoint(_dUp2, touchLocation)) 
		{
			_playerChar.moveState = kStateUp;
		}
		
		else if (CGRectContainsPoint(_dLeft, touchLocation)) 
		{
			_playerChar.moveState = kStateLeft;
		}
		
		else if (CGRectContainsPoint(_dRight, touchLocation)) 
		{
			_playerChar.moveState = kStateRight;
		}
		/*
		if (CGRectContainsPoint(_dTop, touchLocation)) 
		{
			//Supposed to open the menu later on
		}
		
		if (CGRectContainsPoint(_dBot, touchLocation)) 
		{
			[self checkForEvent];
		}
		*/
	}
	else 
	{
		[textBox advanceText];
	}

	// Return YES to bind the Touch to self
	return YES;
}

-(void) ccTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event 
{
	if(_bIsEnterWorlded == NO)
	{
		return;
	}
	
	CGPoint touchLocation = [touch locationInView: [touch view]];		
    touchLocation = [[CCDirector sharedDirector] convertToGL: touchLocation];
	
	if (CGRectContainsPoint(_dDown1, touchLocation) 
		|| CGRectContainsPoint(_dDown2, touchLocation)) 
	{
		_playerChar.moveState = kStateDown;
	}
	
	else if (CGRectContainsPoint(_dUp1, touchLocation) 
		|| CGRectContainsPoint(_dUp2, touchLocation)) 
	{
		_playerChar.moveState = kStateUp;
	}
	
	else if (CGRectContainsPoint(_dLeft, touchLocation)) 
	{
		_playerChar.moveState = kStateLeft;
	}
	
	else if (CGRectContainsPoint(_dRight, touchLocation)) 
	{
		_playerChar.moveState = kStateRight;
	}

	/*
	if (CGRectContainsPoint(_dTop, touchLocation)) 
	{
		CCLOG(@"V-Pad Top");
	}

	if (CGRectContainsPoint(_dBot, touchLocation)) 
	{
		CCLOG(@"V-Pad Bot");
	}
	*/
}

// Stop all Movement on TouchEnded
-(void) ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event 
{
	_playerChar.moveState = kStateIdle;
}

// Gameloop and loop method start here
-(void) gameLoop:(ccTime) dt
{
	_viewDistance.position  = _playerChar.characterSprite.position;
	
	_RadarView.position     = _playerChar.characterSprite.position;
	_RadarView.CharacterPos = [_tileMap GLForPosition:_playerChar.characterSprite.position];
	
	//CCLOG(@"[%f][%f]",_RadarView.CharacterPos.x,_RadarView.CharacterPos.y);

	for(NVCharacter * pCharacter in _RemoteplayerArray)
	{
		if(pCharacter.spriteSheet.visible)
		{
			NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:pCharacter.ItemID];
			pViewDistance.position = pCharacter.characterSprite.position;
		}
	}
	
	if ([_playerChar.characterSprite numberOfRunningActions] == 0 
				&& _playerChar.moveState != kStateIdle)
	{
		[_playerChar update];
		
		//CCLOG(@"playerChar[%f][%f]",_playerChar.characterSprite.position.x,_playerChar.characterSprite.position.y);
		
		float pPos[2];
		
		switch (_playerChar.moveState) 
		{
			case kStateDown:
			{
				pPos[0] = _playerChar.characterSprite.position.x;
				pPos[1] = _playerChar.characterSprite.position.y - 32;
			}
				break;
			case kStateUp:
			{
				pPos[0] = _playerChar.characterSprite.position.x;
				pPos[1] = _playerChar.characterSprite.position.y + 32;
			}
				break;
			case kStateLeft:
			{
				pPos[0] = _playerChar.characterSprite.position.x - 32;
				pPos[1] = _playerChar.characterSprite.position.y;
			}
				break;
			case kStateRight:
			{
				pPos[0] = _playerChar.characterSprite.position.x + 32;
				pPos[1] = _playerChar.characterSprite.position.y;
			}
				break;
			default:
				break;
		}
		
		float pRotation[1];
		pRotation[0] = _playerChar.moveState;
		
		//转换为右上角为原点的坐标系
		pPos[0] = (640 - pPos[0]);
		pPos[1] = (640 - pPos[1]);
		
		[_Link MoveAbsolute:pPos:pRotation:_playerChar.ItemID];
	}
}

-(void) textBoxUpdate:(ccTime) dt 
{
	[textBox update:dt];
}

-(void) textBox:(TextBoxLayer *)tbox didFinishAllTextWithPageCount:(int)pc {
	[self removeChild:textBox cleanup:YES];
	textBox = nil;
	[self unschedule:@selector(textBoxUpdate:)];
	[self schedule:@selector(gameLoop:) interval:_loopSpeed];
	for (NVNpc *npc in _npcarray) {
		[npc resumeSchedulerAndActions];
	}
}

- (void) dealloc
{
	//[_Link ExitWorld];
	
	[_Link DestroyItem:_playerChar.ItemID];
	[_Link SendOutgoingCommands];
	
	[_tileMap			 release];
	[_playerChar		 release];
	[_npcarray			 release];
	[_RemoteplayerArray  release];
	[_ViewDistanceArray  release];
	
	[super dealloc];
}

#pragma mark -
#pragma mark Link Delegate

- (void)receivePacket:(int)packetID objectIndex:(int)objectIndex data:(NSDictionary*)returnValues
{
	
}

- (void)LinkOperationResult:(nByte)opCode :(int)returnCode :(NSMutableDictionary*)returnValues :(short)invocID
{
	switch(opCode)
	{
		case CreateWorld:
		{
			if(returnCode == Ok)
			{
				_Link.state = stateCreateWorlded;
				//创建世界成功
				[_Link EnterWorld:_playerChar];
			}
		}
			break;
			
		case EnterWorld:
		{
			if(returnCode == WorldNotFound)
			{
				[_Link CreateWorld];
			}
			else if(returnCode == Ok)
			{
				_Link.state = stateEnterWorlded;
				//加入世界成功
				CCLOG(@"EnterWorld_Succeed");
				
				[_Link RadarSubscribe:WORLD_NAME];
				
				_bIsEnterWorlded = YES;
			}
		}
			break;
			
		case ExitWorld:
		{
			
		}
			break;
			
		default:
			break;
	}
}

- (void)LinkEventAction:(nByte)eventCode :(NSMutableDictionary*)photonEvent
{
	switch (eventCode)
	{
		case ItemMoved:
		{
			NSString * pItemID = nil;
			pItemID = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)ItemId]];
			
			if(pItemID == nil)
			{
				return;
			}
			
			EGArray* OldPositionArry = nil;
			EGArray* PositionArry    = nil;
			EGArray* RotationArry    = nil;
			
			OldPositionArry = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)OldPosition]];
			PositionArry    = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)Position]];
			RotationArry    = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)Rotation]];
			
			//if([ary.Type compare:[NSString stringWithUTF8String:@encode(float)]])
			//	DEBUG_RELEASE(NSAssert(false, "ERROR: unexpected type"), break);
			
			float Pos[2];
			//坐标X
			[[PositionArry objectAtIndex:0] getValue:&Pos[0]];
			
			//坐标Y
			[[PositionArry objectAtIndex:1] getValue:&Pos[1]];
			
			//转换为左下角为原点的坐标系
			Pos[0] = (640 - Pos[0]);
			Pos[1] = (640 - Pos[1]);
			
			//移动方向 moveState
			float pRotation[1];
			[[RotationArry objectAtIndex:0] getValue:&pRotation[0]];
			int pMoveState = pRotation[0];
			
			CGPoint pPoint = CGPointMake(Pos[0], Pos[1]);
			
			CCLOG(@"RemotePlayer[%f][%f]",pPoint.x,pPoint.y);
			
			for (NVCharacter *Character in _RemoteplayerArray)
			{
				if([Character.ItemID isEqual:pItemID])
				{
					Character.moveState = pMoveState;
					
					switch (pMoveState)
					{
						case kStateIdle:
							break;
						case kStateDown:
							// Move Down
							[Character lookInDirection:1];
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y-32)]];
							[Character.characterSprite runAction:[CCMoveTo  actionWithDuration:Character.moveSpeed position:pPoint]];
							[Character.characterSprite runAction:[CCAnimate actionWithAnimation:Character.walkDownAnim]];
						}
							break;
						case kStateUp:
							// Move Up
							[Character lookInDirection:2];
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x,_characterSprite.position.y+32)]];
							[Character.characterSprite runAction:[CCMoveTo  actionWithDuration:Character.moveSpeed position:pPoint]];
							[Character.characterSprite runAction:[CCAnimate actionWithAnimation:Character.walkUpAnim]];
						}
							break;
						case kStateLeft:
							// Move Left
							[Character lookInDirection:3];
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x-32,_characterSprite.position.y)]];
							[Character.characterSprite runAction:[CCMoveTo  actionWithDuration:Character.moveSpeed position:pPoint]];
							[Character.characterSprite runAction:[CCAnimate actionWithAnimation:Character.walkLeftAnim]];
						}
							break;
						case kStateRight:
							// Move Right
							[Character lookInDirection:4];
							//if (![_currentMap checkCollisionForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]) 
						{
							//[_currentMap.metaLayer setTileGID:_previousGID at:[_currentMap tileCoordForPosition:_characterSprite.position]];
							//_previousGID = [_currentMap.metaLayer tileGIDAt:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
							//[_currentMap setTileCollidable:YES atTileCoord:[_currentMap tileCoordForPosition:ccp(_characterSprite.position.x+32,_characterSprite.position.y)]];
							[Character.characterSprite runAction:[CCMoveTo  actionWithDuration:Character.moveSpeed position:pPoint]];
							[Character.characterSprite runAction:[CCAnimate actionWithAnimation:Character.walkRightAnim]];
						}
							break;
						default:
							break;
					}
					return;
				}
			}
		}
			break;
		case ItemDestroyed:
		{
			CCLOG(@"ItemDestroyed");
			
			NSString * pItemID = nil;
			pItemID = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)ItemId]];
			
			if(pItemID)
			{
				for (NVCharacter *Character in _RemoteplayerArray)
				{
					if([Character.ItemID isEqual:pItemID])
					{
						NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						
						[self removeChild:pViewDistance         cleanup:YES];
						[self removeChild:Character.spriteSheet cleanup:YES];
						
						for(NVRemotePlayRadar * pRemotePlayRadar in _RadarView.RemotePlayRadarArray)
						{
							if([pRemotePlayRadar.ItemID isEqual:pItemID])
							{
								[_RadarView.RemotePlayRadarArray removeObject:pRemotePlayRadar];
							}
						}
						
						[_ViewDistanceArray removeObjectForKey:Character.ItemID];
						[_RemoteplayerArray removeObject:Character];
						
						return;
					}
				}
			}
			
		}
			break;
		case ItemSubscribed:
		{
			CCLOG(@"ItemSubscribed");
			
			NSString * pItemID = nil;
			pItemID = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)ItemId]];
			
			if(pItemID)
			{
				EGArray* PositionArry    = nil;
				EGArray* RotationArry    = nil;
				
				PositionArry    = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)Position]];
				RotationArry    = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)Rotation]];
				
				float Pos[2];
				[[PositionArry objectAtIndex:0] getValue:&Pos[0]];
				[[PositionArry objectAtIndex:1] getValue:&Pos[1]];
				//转换为左下角为原点的坐标系
				Pos[0] = (640 - Pos[0]);
				Pos[1] = (640 - Pos[1]);
				
				float pRotation[1];
				[[RotationArry objectAtIndex:0] getValue:&pRotation[0]];
				
				int pMoveState = (int)pRotation[0];
				
				for (NVCharacter *Character in _RemoteplayerArray)
				{
					if([Character.ItemID isEqual:pItemID])
					{
						[Character.spriteSheet setVisible:YES];
						Character.characterSprite.position = CGPointMake(Pos[0], Pos[1]);
						switch (pMoveState)
						{
							case kStateIdle:
								break;
							case kStateDown:
								[Character lookInDirection:1];
								break;
							case kStateUp:
								[Character lookInDirection:2];
								break;
							case kStateLeft:
								[Character lookInDirection:3];
								break;
							case kStateRight:
								[Character lookInDirection:4];
								break;
							default:
								break;
						}
						
						NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						[pViewDistance setVisible:YES];
						pViewDistance.position = Character.characterSprite.position;
						
						return;
					}
				}
				
				//新的玩家加入
				
				NVCharacter * pRemoteplayer = [[NVCharacter alloc] initWithSpritesheet:@"playersprite_female" onMap:_tileMap];
				pRemoteplayer.characterSprite.position = CGPointMake(Pos[0], Pos[1]);
				switch (pMoveState)
				{
					case kStateIdle:
						break;
					case kStateDown:
						[pRemoteplayer lookInDirection:1];
						break;
					case kStateUp:
						[pRemoteplayer lookInDirection:2];
						break;
					case kStateLeft:
						[pRemoteplayer lookInDirection:3];
						break;
					case kStateRight:
						[pRemoteplayer lookInDirection:4];
						break;
					default:
						break;
				}
				pRemoteplayer.ItemID = pItemID;
				[self addChild:pRemoteplayer.spriteSheet];
				
				[_RemoteplayerArray addObject:pRemoteplayer];
				
				[self reorderChild:pRemoteplayer.spriteSheet z:[_npcarray count] + [_RemoteplayerArray count] + 2];
				
				[pRemoteplayer release];
				
				//添加玩家得视野
				NViewDistance * pViewDistance = [NViewDistance node];
				
				pViewDistance.ViewDistanceEnter = DISTANCEENTER;
				pViewDistance.ViewDistanceExit  = DISTANCEEXIT;
				pViewDistance.ItemID = pRemoteplayer.ItemID;
				pViewDistance.position = pRemoteplayer.characterSprite.position;
				[self addChild:pViewDistance z:101];
				
				[_ViewDistanceArray setObject:pViewDistance forKey:pViewDistance.ItemID];
				
				//雷达中添加玩家
				NVRemotePlayRadar * pRemotePlayRadar = [[NVRemotePlayRadar alloc] init];
				
				pRemotePlayRadar.ItemID = pRemoteplayer.ItemID;
				pRemotePlayRadar.Pos    = [_tileMap GLForPosition:pRemoteplayer.characterSprite.position];
				
				[_RadarView.RemotePlayRadarArray addObject:pRemotePlayRadar];
				
				[pRemotePlayRadar release];
				
			}
		}
			break;
		case ItemUnsubscribed:
		{
			CCLOG(@"ItemUnsubscribed");
			
			NSString * pItemID = nil;
			pItemID = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)ItemId]];
			
			if(pItemID)
			{
				for (NVCharacter *Character in _RemoteplayerArray)
				{
					if([Character.ItemID isEqual:pItemID])
					{
						[Character.spriteSheet setVisible:NO];
						
						NViewDistance * pViewDistance = (NViewDistance*)[_ViewDistanceArray objectForKey:Character.ItemID];
						
						[pViewDistance setVisible:NO];
						
						return;
					}
				}
			}
		}
		case RadarUpdate:
		{
			CCLOG(@"RadarUpdate");
			NSString * pItemID = nil;
			pItemID = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)ItemId]];
			
			EGArray* PositionArry    = nil;
			PositionArry    = [photonEvent objectForKey:[KeyObject withByteValue:(nByte)Position]];
			
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
			
		}
			break;
		default:
			break;
	}
}

@end
