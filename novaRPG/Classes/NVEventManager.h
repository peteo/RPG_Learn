//
//  NVEvent.h
//  novaRPGv2
//
//  Created by nova on 30.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "GDataXMLNode.h"
#import "NVAction.h"


@interface NVEventManager : NSObject {
	
}

+(NVEventManager *) sharedEventManager;
-(CCArray *) readEventData:(NSString *) eventSet fromFile:(NSString *) xmlFileName;

@end
