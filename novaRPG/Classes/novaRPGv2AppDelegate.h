//
//  novaRPGv2AppDelegate.h
//  novaRPGv2
//
//  Created by nova on 21.04.11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NVLink.h"


@class RootViewController;

@interface novaRPGv2AppDelegate : NSObject <UIApplicationDelegate> 
{
	UIWindow			*window;
	RootViewController	*viewController;
	
	NVLink				*_Link;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) NVLink   *Link;

+ (novaRPGv2AppDelegate * ) getAppDelegate;

@end
