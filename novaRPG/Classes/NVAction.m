//
//  NVAction.m
//  novaRPGv2
//
//  Created by nova on 08.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NVAction.h"


@implementation NVAction

@synthesize type = _type;
@synthesize duration = _duration;
@synthesize target = _target;
@synthesize position = _position;
@synthesize content = _content;

-(id)initTextAction:(NSString *)textContent {
	if ( (self = [super init]) ) {
		self.type = kTextEvent;
		_content = textContent;
		NSLog(@"Created TextAction with content: %@",textContent);
	}
	return self;
}

-(id)initMoveAction:(CGPoint)targetPosition withDuration:(float)moveDuration withTarget:(NSString *)targetName {
	if ( (self = [super init]) ) {
		self.type = kMoveEvent;
		_position = targetPosition;
		_duration = moveDuration;
		_target = targetName;
		NSLog(@"Created MoveAction with target position: %@, duration: %f, target: %@",NSStringFromCGPoint(self.position),self.duration, self.target);
	}
	return self;
}

-(id)initCameraAction:(CGPoint)targetPosition withDuration:(float)moveDuration {
	if ( (self = [super init]) ) {
		self.type = kCameraEvent;
		_position = targetPosition;
		_duration = moveDuration;
		NSLog(@"Created CameraAction with target position: %@, duration: %f",NSStringFromCGPoint(self.position),self.duration);
	}
	return self;
}

-(id)initReturnAction {
	if ( (self = [super init]) ) {
		self.type = kReturnEvent;
		NSLog(@"Created ReturnAction");
	}
	return self;
}

-(int)eventType {
	return self.type;
}

@end
