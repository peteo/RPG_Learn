//
//  NViewDistance.m
//  novaRPGv2
//
//  Created by Peteo on 11-9-9.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NViewDistance.h"


@implementation NViewDistance

@synthesize ViewDistanceEnter = _ViewDistanceEnter;
@synthesize ViewDistanceExit  = _ViewDistanceExit;
@synthesize ItemID = _ItemID;

-(void) drawRectFaster:(CGRect)rect
{
	CGPoint pos1, pos2, pos3, pos4;
	pos1 = CGPointMake(rect.origin.x, rect.origin.y);
	pos2 = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
	pos3 = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
	pos4 = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y);
	
	CGPoint vertices[8];
	vertices[0] = pos1;
	vertices[1] = pos2;
	vertices[2] = pos2;
	vertices[3] = pos3;
	vertices[4] = pos3;
	vertices[5] = pos4;
	vertices[6] = pos4;
	vertices[7] = pos1;
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 8);
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}

// Draw the object rectangles for debugging and illustration purposes.
-(void) draw
{
	// make the line 3 pixels thick
	glLineWidth(3.0f);
	glColor4f(1, 0, 1, 1);
	
	/*
	int numObjects = [[objectLayer objects] count];
	for (int i = 0; i < numObjects; i++)
	{
		NSDictionary* properties = [[objectLayer objects] objectAtIndex:i];
		CGRect rect = [self getRectFromObjectProperties:properties tileMap:tileMap];
		[self drawRectFaster:rect];
	}
	*/
	
	CGRect rectDistanceEnter = CGRectMake(-_ViewDistanceEnter.width,-_ViewDistanceEnter.height, _ViewDistanceEnter.width * 2, _ViewDistanceEnter.height * 2);
	[self drawRectFaster:rectDistanceEnter];
	
	CGRect rectDistanceExit  = CGRectMake(-_ViewDistanceExit.width, -_ViewDistanceExit.height, _ViewDistanceExit.width * 2, _ViewDistanceExit.height * 2);
	[self drawRectFaster:rectDistanceExit];
	
	// show center screen position
	//CGSize screenSize = [[CCDirector sharedDirector] winSize];
	//CGPoint center = CGPointMake(self.position.x + screenSize.width * 0.5f, self.position.y + screenSize.height * 0.5f);
	//CGPoint center = CGPointMake(464,164);
	//CCLOG(@"NViewDistance[%f][%f]",self.position.x,self.position.y);
	
	ccDrawCircle(ccp(0,0), 10, 0, 8, NO);
	
	// reset line width & color as to not interfere with draw code in other nodes that draws lines
	glLineWidth(1.0f);
	glColor4f(1, 1, 1, 1);
}

-(void) dealloc
{
	[_ItemID release];
	
	[super dealloc];
}

@end
