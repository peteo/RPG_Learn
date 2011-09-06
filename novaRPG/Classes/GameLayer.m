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

// on "init" you need to initialize your instance
-(id) init
{
	if( (self=[super init] ))
	{
		novaRPGv2AppDelegate * app = [novaRPGv2AppDelegate getAppDelegate];
		
		app.Link.dataReceiver = self;
		
		_Link = app.Link;
		
		// Load Tilemap
		_tileMap = [[NVMap alloc] initWithMap:[[StateManager sharedStateManager] getCurrentMap]];
		[self addChild:_tileMap.tileMap];
		
		// Load Playersprite
		_playerChar = [[NVCharacter alloc] initWithSpritesheet:@"playersprite_female" onMap:_tileMap];
		_playerChar.characterSprite.position = [_tileMap spawnPoint];
		[self addChild:_playerChar.spriteSheet];
		
		
		// Remote Player
		_Remoteplayer = [[NVCharacter alloc] initWithSpritesheet:@"playersprite_female" onMap:_tileMap];
		_Remoteplayer.characterSprite.position = [_tileMap spawnPoint];
		[self addChild:_Remoteplayer.spriteSheet];
		
		
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
		
		_npcarray = [[CCArray alloc] init];

		//Load NPCs on Map
		for (int i = 0;i < [_tileMap.npcs count]; i += 1) 
		{
			NVNpc *npc = [[NVNpc alloc] initWithID:i onMap:_tileMap];
			[self addChild:npc.spriteSheet z:i + 1];
			[_npcarray addObject:npc];
		}
		
		// Reorder Children
		[self reorderChild:_tileMap.bgLayer z:0];
		[self reorderChild:_tileMap.fgLayer z:[_npcarray count] + 5];
		[self reorderChild:_tileMap.extraLayer z:[_npcarray count] + 6];
		[self reorderChild:_playerChar.spriteSheet z:[_npcarray count] + 1];
		[self reorderChild:_Remoteplayer.spriteSheet z:[_npcarray count] + 2];
		
		
		// Register to the Notification Center for a possible Mapchange
		[[NSNotificationCenter defaultCenter] addObserver: self
												 selector: @selector(mapChange:)
													 name: @"mapChange" object: nil];
		
		// Start the GameLoop
		[self schedule:@selector(gameLoop:) interval: _loopSpeed];
		[self runAction:[CCFollow actionWithTarget:_playerChar.characterSprite]];
	}
	return self;
}

// Camera actions go here
-(void) followPlayer:(id) sender {
	[self runAction:[CCFollow actionWithTarget:_playerChar.characterSprite]];
}
	
-(void) centerCamera:(CGPoint) point {
	CGSize winSize = [[CCDirector sharedDirector] winSize];
	self.position = ccp(-point.x+winSize.width/2,-point.y+winSize.height/2);
}

-(void) moveCameraByTile:(CGPoint)point withDuration:(int) duration {
	[self runAction:[CCMoveBy actionWithDuration:duration position:ccp(_tileMap.tileMap.tileSize.width*-point.x,_tileMap.tileMap.tileSize.height*-point.y)]];
}

-(void) moveCameraToPos:(CGPoint)point withDuration:(int) duration {
	CGSize winSize = [[CCDirector sharedDirector] winSize];
	[self runAction:[CCMoveTo actionWithDuration:duration position:ccp(-point.x+winSize.width/2,-point.y+winSize.height/2)]];
}

-(void) displayTextbox:(NSString *)displayText {
	//WIP, textbox is working perfectly but needs a new background. 
	// It will be inserted in the class "TextBoxLayer" so it's default and can be used anywhere.
	textBox = [[TextBoxLayer alloc] initWithColor:ccc4(0, 0, 255, 255) width:480 height:40 padding:10 text:displayText];
	textBox.delegate = self;
	textBox.position = ccp(0-self.position.x,0-self.position.y);
	[self addChild:textBox z:20];
	[self schedule:@selector(textBoxUpdate:) interval:0];
	[self unschedule:@selector(gameLoop:)];
	for (NVNpc *npc in _npcarray) {
		[npc pauseSchedulerAndActions];
	}
}

-(void) mapChange:(id)sender {
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
-(void) registerWithTouchDispatcher {
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
}

// Actual Touch Handling happens here
-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event 
{
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
	if ([_playerChar.characterSprite numberOfRunningActions] == 0 
				&& _playerChar.moveState != kStateIdle)
	{
		[_playerChar update];
		
		//CCLOG(@"playerChar[%f][%f]",_playerChar.characterSprite.position.x,_playerChar.characterSprite.position.y);
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
	_tileMap	= nil;
	_playerChar = nil;
	
	[super dealloc];
}

- (void)receivePacket:(int)packetID objectIndex:(int)objectIndex data:(NSDictionary*)returnValues
{
	
}

@end
