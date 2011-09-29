//
//  PtUtils.mm
//  PtRPG
//
//  Created by Peteo on 11-9-29.
//  Copyright 2011 The9. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "PtUtils.h"

USING_NS_CC;

CCString * PtUtils::getDeviceID()
{
	CCString *pRet = new CCString();
	pRet->autorelease();
	
	UIDevice *myDevice = [UIDevice currentDevice];
	
	NSString *deviceID = [myDevice uniqueIdentifier];
	
	pRet->m_sString = [deviceID UTF8String];
	
	return pRet;
}
