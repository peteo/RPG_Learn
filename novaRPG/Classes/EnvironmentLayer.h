//
//  EnvironmentLayer.h
//  novaRPGv2
//
//  Created by nova on 12.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface EnvironmentLayer : CCLayerColor {
}

-(id) initWithWeather:(int) weather atTime:(int) time;
-(void) startRain;

@end
