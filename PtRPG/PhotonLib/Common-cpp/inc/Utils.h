/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __UTILS_H
#define __UTILS_H

//////////////////////////////////////////////////////////////////////////
// For internal use only
//////////////////////////////////////////////////////////////////////////

#include "KeyObject.h"
#include "ValueObject.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	// internal
	class Utils : protected Base
	{
	private:
		friend class NeutronSession;
		friend class NeutronGame;
		friend class PhotonPeer;
		friend class LitePeer;
		friend class EventData;
		friend class OperationResponse;

	protected:
		static EG_HashTable* convertToEGHash(const Hashtable* const origHash, EG_HashTable* convHash=NULL);
		static EG_Vector* convertToEGVector(const JVector<Object>* const origVec);
		static EG_Object* convertToEGObject(const Object* const origObj, EG_Object* convObj=NULL);
		static Hashtable* convertToOOPHash(const EG_HashTable* const origHash, Hashtable* convHash=NULL);
		static JVector<Object>* convertToOOPVector(const EG_Vector* const origVec);
		static Object* convertToOOPObject(const EG_Object* const origObj, Object* convObj=NULL);
		static void convertObjectsInArrayToC(const Object& cppObj, void** cData, unsigned int recursionDepth=0);
		static void convertObjectsInCArrayToCPP(const EG_Object& cObj, void** cppData);
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif