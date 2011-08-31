//
//  NVEvent.m
//  novaRPGv2
//
//  Created by nova on 30.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVEventManager.h"


@implementation NVEventManager
static NVEventManager* _sharedEventManager = nil;

+(NVEventManager *) sharedEventManager
{
	@synchronized([NVEventManager class])
	{
		if (!_sharedEventManager)
			[[self alloc] init];
		
		return _sharedEventManager;
	}
	
	return nil;
}

+(id)alloc
{
	@synchronized([NVEventManager class])
	{
		NSAssert(_sharedEventManager == nil, @"Attempted to allocate a second instance of a singleton.");
		_sharedEventManager = [super alloc];
		return _sharedEventManager;
	}
	
	return nil;
}

-(id)init {
	self = [super init];
	if (self != nil) {
		// initialize stuff here
	}
	
	return self;
}

-(CCArray*) readEventData:(NSString *) eventSet fromFile:(NSString *) xmlFileName {
	CCArray *outputArray = [NSMutableArray array];
	NSString *filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"event_%@",xmlFileName] ofType:@"xml"];	
	NSData *xmlData = [[NSMutableData alloc] initWithContentsOfFile:filePath];
	NSError *error;
	GDataXMLDocument *eventNode = [[GDataXMLDocument alloc] initWithData:xmlData options:0 error:&error];
	if (eventNode) {
		NSArray *actions = [eventNode nodesForXPath:[NSString stringWithFormat:@"//event[@name='%@']/action",eventSet] error:nil];
		for (GDataXMLElement *action in actions) {
			// Determine Event Type by checking the type attribute
			if ([[[action attributeForName:@"type"] stringValue] compare:@"text"] == NSOrderedSame) {
				NVAction *outputAction = [[NVAction alloc] initTextAction:[[action attributeForName:@"content"] stringValue]];
				[outputArray addObject:outputAction ];
			}
			else {
				if ([[[action attributeForName:@"type"] stringValue] compare:@"move"] == NSOrderedSame) {
					// Check if there is a targetted position
					NSString *tempPos = [[action attributeForName:@"position"] stringValue];
					NSArray *pos = [tempPos componentsSeparatedByString:@","];
					float x = [[pos objectAtIndex:0] floatValue];
					float y = [[pos objectAtIndex:1] floatValue];
					CGPoint targetPosition = CGPointMake(x,y);
					NSLog(@"position:%f,%f",x,y);
					NSLog(@"point is %@",NSStringFromCGPoint(targetPosition));
					NVAction *outputAction = [[NVAction alloc] initMoveAction:targetPosition 
												   withDuration:[[[action attributeForName:@"duration"] stringValue] floatValue] 
													 withTarget:[[action attributeForName:@"target"] stringValue]
								];
					[outputArray addObject:outputAction];
				}
				else {
					if ([[[action attributeForName:@"type"] stringValue] compare:@"camera"] == NSOrderedSame) {
						// Check if there is a targetted position
						NSString *tempPos = [[action attributeForName:@"position"] stringValue];
						CGPoint targetPosition;
						if (tempPos) {
							NSArray *pos = [tempPos componentsSeparatedByString:@","];
							targetPosition = CGPointMake([[pos objectAtIndex:0] floatValue], [[pos objectAtIndex:1] floatValue]);
						}
						NVAction *outputAction = [[NVAction alloc] initCameraAction:targetPosition 
														 withDuration:[[[action attributeForName:@"duration"] stringValue] floatValue]
									];
						[outputArray addObject:outputAction];
					}
					else {
						if ([[[action attributeForName:@"type"] stringValue] compare:@"return"] == NSOrderedSame) {
							NVAction *outputAction = [[NVAction alloc] initReturnAction];
							[outputArray addObject:outputAction];
						}
					}

				}

			}
		}
		
	}
	return outputArray;	
}

@end
