//
//  StateManager.h
//  novaRPGv2
//
//  Created by Hilmar Wiegand on 22.05.11.
//  Copyright 2011 FlameCC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GDataXMLNode.h"


@interface StateManager : NSObject {
	GDataXMLDocument *_doc;
	int _activeState;
	NSString *_currentMap;
	NSString *_systemFont;
	int _textSpeed;
}

+(StateManager*) sharedStateManager;
-(void) reloadData;
-(NSString *) dataFilePath:(BOOL)dynamicPath forResource:(NSString *)resourceID;
-(void) setActiveSaveState:(int)saveID;
-(NSArray *) loadStates;
-(void) saveActiveState;
-(void) createNewState;
-(void) deleteStateWithID:(int) stateID;
-(int) getSaveCount;
-(void) setCurrentMap:(NSString *)mapName;
-(NSString *) getCurrentMap;
-(NSString *) getSystemFont;
-(int) getTextSpeed;

@end
