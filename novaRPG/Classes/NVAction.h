//
//  NVAction.h
//  novaRPGv2
//
//  Created by nova on 08.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
	kTextEvent = 0,
	kMoveEvent,
	kCameraEvent,
	kReturnEvent
} _type;


@interface NVAction : NSObject {
	int _type;
	NSString *_target;
	float _duration;
	CGPoint _position;
	NSString *_content;
}

@property (readwrite,assign) int type;
@property (readwrite,assign) NSString *target;
@property (readwrite,assign) float duration;
@property (readwrite,assign) CGPoint position;
@property (readwrite,assign) NSString *content;

-(id) initTextAction:(NSString *) textContent;
-(id) initMoveAction:(CGPoint) targetPosition withDuration:(float) moveDuration withTarget:(NSString *) targetName;
-(id) initCameraAction:(CGPoint) targetPosition withDuration:(float) moveDuration;
-(id) initReturnAction;

-(int) eventType;
@end
