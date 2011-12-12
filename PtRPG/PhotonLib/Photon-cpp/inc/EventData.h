/* Exit Games Photon - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __EVENT_DATA_H
#define __EVENT_DATA_H

#include "CEventData.h"
#include "Utils.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class EventData
	{
	public:
		EventData(const CEventData& cEventData);
		~EventData(void);

		EventData(const EventData& toCopy);
		EventData& operator=(const EventData& toCopy);

		const Object& operator[](unsigned int index) const;

		JString toString(bool withParameters, bool withParameterTypes=false) const;
		const Object& getParameterForCode(nByte parameterCode) const;

		nByte getCode(void) const;
		const Hashtable& getParameters(void) const;
	private:
		nByte code;
		Hashtable parameters;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif