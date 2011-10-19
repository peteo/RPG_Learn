/*
 *  PtCode.cpp
 *  PtRPG
 *
 *  Created by Peteo on 11-9-27.
 *  Copyright 2011 The9. All rights reserved.
 *
 */


#include "org_photon_lib_PhotonHelper.h"
#include "../../libs/cocos2dx/platform/android/jni/JniHelper.h"

#include <jni.h>

using namespace cocos2d;

extern "C"
{
	void  Java_Call_Connect()
	{
		JniMethodInfo t;
		
		if (JniHelper::getStaticMethodInfo(t, 
										   "org/photon/lib/PhotonHelper",
										   "connect",
										   "()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
		}
	}
}