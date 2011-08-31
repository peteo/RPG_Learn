//
//  StateManager.m
//  novaRPGv2
//
//  Created by Hilmar Wiegand on 22.05.11.
//  Copyright 2011 FlameCC. All rights reserved.
//

#import "StateManager.h"


@implementation StateManager

static StateManager* _sharedStateManager = nil;

+(StateManager *) sharedStateManager
{
	@synchronized([StateManager class])
	{
		if (!_sharedStateManager)
			[[self alloc] init];
		
		return _sharedStateManager;
	}
	
	return nil;
}

+ (id) alloc
{
	@synchronized([StateManager class])
	{
		NSAssert(_sharedStateManager == nil, @"Attempted to allocate a second instance of a singleton.");
		_sharedStateManager = [super alloc];
		return _sharedStateManager;
	}
	
	return nil;
}

- (id) init {
	self = [super init];
	if (self != nil) {
		// initialize stuff here
		// Load the Data, set the doc member var and define system defaults on init
		NSString *filePath = [self dataFilePath:YES forResource:@"GameState"];
		NSData *xmlData = [[NSMutableData alloc] initWithContentsOfFile:filePath];
		NSError *error;
		_doc = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&error];
		_systemFont = @"arial16.fnt";
		_textSpeed = 40;
	}
	
	return self;
}

// Reloads the Savestate from Documents directory
-(void) reloadData {
	[_doc release];
	NSString *filePath = [self dataFilePath:YES forResource:@"GameState"];
	NSData *xmlData = [[NSMutableData alloc] initWithContentsOfFile:filePath];
	NSError *error;
	_doc = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&error];
}

// Returns the datapath in the documents directory if it is existant, or asked for it specifically when saving.
- (NSString *) dataFilePath:(BOOL)dynamicPath forResource:(NSString *) resourceID {
	if (dynamicPath) {
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex:0];
		NSString *documentsPath = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.xml",resourceID]];
		return documentsPath;
	} 
	else {
        return [[NSBundle mainBundle] pathForResource:resourceID ofType:@"xml"];
    }
}

// -----------------WIP--------------------
- (void) setActiveSaveState:(int)saveID {
	
	//WIP, actually barely working
	if (_doc) {
		_activeState = saveID;
		NSArray *mapElement = [_doc nodesForXPath:[NSString stringWithFormat:@"/GameState/SaveState[@id='%i']/CurrentMap",saveID] error:nil];
		GDataXMLElement *mapName = [mapElement objectAtIndex:0];
		_currentMap = mapName.stringValue;
	}
	else
	NSLog(@"Savestate File not found!",saveID);
}
// -----------------WIP--------------------

- (NSArray *) loadStates {
	if (_doc) {
		NSArray *saveStates = [_doc nodesForXPath:@"/GameState/SaveState" error:nil];
		return saveStates;
	}
	else {
		NSLog(@"Savestate File not found!");
		return nil;
	}
}

-(void) saveActiveState {
	//Root element...
	GDataXMLElement *gameStateElement = [GDataXMLNode elementWithName:@"GameState"];
	
	//Load states... Wow commenting this seems stupid but nvm
	NSArray *saveStates = [self loadStates];
	
	//Add every state to the root element as it was exceeept....
	for (GDataXMLElement *currentSave in saveStates) {
		if ([[[currentSave attributeForName:@"id"] stringValue] intValue] ==  _activeState) {
			//It's the active state! In that case, all the elements are defined anew here.
			//This can be changed to change what's saved and what not.
			GDataXMLElement *saveStateElement = [GDataXMLNode elementWithName:@"SaveState"];
			GDataXMLElement *saveIDElement = [GDataXMLNode attributeWithName:@"id" stringValue:@"1"];
			GDataXMLElement *saveNameElement = [GDataXMLNode elementWithName:@"SaveName" stringValue:@"saved state"];
			GDataXMLElement *currentMapElement = [GDataXMLNode elementWithName:@"CurrentMap" stringValue:@"testMapFinal"];
			[saveStateElement addChild:saveNameElement];
			[saveStateElement addChild:currentMapElement];
			[saveStateElement addAttribute:saveIDElement];
			
			[gameStateElement addChild:saveStateElement];
			NSLog(@"active was saved");
		}
		
		else {
			//State is not active, pass it on.
			[gameStateElement addChild:currentSave];
		}

	}
	
	//Prepare doc for save
	GDataXMLDocument *document = [[[GDataXMLDocument alloc] initWithRootElement:gameStateElement] autorelease];
    NSData *xmlData = document.XMLData;
	
	//Get Path
    NSString *filePath = [self dataFilePath:YES forResource:@"GameState"];
	
	//..And wrap it up!
    NSLog(@"Saving xml data to %@...", filePath);
    [xmlData writeToFile:filePath atomically:YES];
}

-(void) createNewState {
	// Create an empty root element
	GDataXMLElement *gameStateElement = [GDataXMLNode elementWithName:@"GameState"];
	
	//Load all previous saves and add them to the root element first. Can be moved.
	NSArray *saveStates = [self loadStates];
	for (GDataXMLElement *currentSave in saveStates) {
		[gameStateElement addChild:currentSave];
	}
	
	//Create the new save and add the default values to it. This is where the starting map etc is hardcoded! 
	//I'm thinking about changing this to be external, but I'm not sure what it would get me.
	GDataXMLElement *saveStateElement = [GDataXMLNode elementWithName:@"SaveState"];
	GDataXMLElement *saveIDElement = [GDataXMLNode attributeWithName:@"id" stringValue:[NSString stringWithFormat:@"%i",[saveStates count] + 1]];
	GDataXMLElement *saveNameElement = [GDataXMLNode elementWithName:@"SaveName" stringValue:@"newly created game"];
	GDataXMLElement *currentMapElement = [GDataXMLNode elementWithName:@"CurrentMap" stringValue:@"testMapFinal"];
	[saveStateElement addChild:saveNameElement];
	[saveStateElement addChild:currentMapElement];
	[saveStateElement addAttribute:saveIDElement];
	
	//Add new state to root Element and make a remark about it in the console.
	[gameStateElement addChild:saveStateElement];
	NSLog(@"new game was added");
	
	//Initiate Doc for saving...
	GDataXMLDocument *document = [[[GDataXMLDocument alloc] initWithRootElement:gameStateElement] autorelease];
    NSData *xmlData = document.XMLData;
	
	//Get filepath...
    NSString *filePath = [self dataFilePath:YES forResource:@"GameState"];
	
	// Save and tell the world. 
    NSLog(@"Saving xml data to %@...", filePath);
    [xmlData writeToFile:filePath atomically:YES];
	
	//Reload so new save is displayed - also current save now is previous saves + 1.
	[self reloadData];
	[self setActiveSaveState:[saveStates count] + 1];
}

-(void) deleteStateWithID:(int) stateID {
	//Root element...
	GDataXMLElement *gameStateElement = [GDataXMLNode elementWithName:@"GameState"];
	
	NSArray *saveStates = [self loadStates];
	
	//Add every state to the root element as it was exceeept....
	NSUInteger index = 1;
	for (GDataXMLElement *currentSave in saveStates) {
		if ([[[currentSave attributeForName:@"id"] stringValue] intValue] ==  stateID) {
			//It's the state we want to delete. And in that case, we delete it. duh.
			//(Or better yet we exclude it from saving.)
		}
		
		else {
			//State is not active, change the id and save it back.
			[gameStateElement addChild:currentSave];
		}
		
	}
	
	//Prepare doc for save
	GDataXMLDocument *document = [[[GDataXMLDocument alloc] initWithRootElement:gameStateElement] autorelease];
    NSData *xmlData = document.XMLData;
	
	//Get Path
    NSString *filePath = [self dataFilePath:YES forResource:@"GameState"];
	
	//..And wrap it up!
    NSLog(@"Saving xml data to %@...", filePath);
    [xmlData writeToFile:filePath atomically:YES];
}
	

- (int) getSaveCount {
	int saveCount = 0;
	if (_doc) {
		NSArray *saveStates = [_doc nodesForXPath:@"/GameState/SaveState" error:nil];
		saveCount = [saveStates count];
	}
	else {
		NSLog(@"Savestate File not found!");
	}
	return saveCount;
}

-(void) setCurrentMap:(NSString *)mapName {
	_currentMap = mapName;
}


- (NSString *) getCurrentMap {
	if (_currentMap)
		return _currentMap;
	else
		return nil;
}

- (NSString *) getSystemFont {
	return _systemFont;
}

-(int) getTextSpeed {
	return _textSpeed;
}

@end
