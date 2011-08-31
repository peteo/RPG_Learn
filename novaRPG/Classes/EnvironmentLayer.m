//
//  EnvironmentLayer.m
//  novaRPGv2
//
//  Created by nova on 12.06.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "EnvironmentLayer.h"


@implementation EnvironmentLayer

-(id) initWithWeather:(int) weather atTime:(int) time {
	ccColor4B layerColor;
	switch (time) {
		case 0:
			layerColor = ccc4(255, 153, 0, 50);
			break;
		case 1:
			layerColor = ccc4(0, 0, 0, 0);
			break;
		case 2:
			layerColor = ccc4(0, 0, 100, 60);
			break;
		case 3:
			layerColor = ccc4(0, 0, 120, 80);
			break;
		default:
			layerColor = ccc4(0, 0, 0, 0);
			break;
	}
	
	if ( (self = [super initWithColor:layerColor]) ) {
		switch (weather) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				// Rain
				[self startRain];
				break;
			case 3:
				// Particle System goes here
				break;
			case 4:
				// Sprite Overlay goes here
				break;
			default:
				break;
		}
	}
	return self;
}

-(void) startRain {
	CCParticleSystem *emitter = [CCParticleRain node];
	
	[self addChild: emitter z:10];
	
	CGPoint p = emitter.position;
	
	emitter.position = ccp( p.x, p.y);
	
	emitter.life = 4;
	
	emitter.texture = [[CCTextureCache sharedTextureCache] addImage: @"Raindrop.png"];
	
	emitter.startSize = 20.0f;
	
	CCParticleSystem *emitter2 = [CCParticleRain node];
	
	[self addChild: emitter2 z:11];
		
	emitter2.position = ccp( p.x, p.y);
	
	emitter2.life = 4;
	
	emitter2.texture = [[CCTextureCache sharedTextureCache] addImage: @"Raindrop.png"];
	
	emitter2.startSize = 10.0f;
}

@end
