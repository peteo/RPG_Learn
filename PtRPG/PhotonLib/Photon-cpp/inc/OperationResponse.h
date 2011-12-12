/* Exit Games Photon - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __OPERATION_RESPONSE_H
#define __OPERATION_RESPONSE_H

#include "COperationResponse.h"
#include "Utils.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class OperationResponse
	{
	public:
		OperationResponse(const COperationResponse& cOperationResponse);
		~OperationResponse(void);

		OperationResponse(const OperationResponse& toCopy);
		OperationResponse& operator=(const OperationResponse& toCopy);

		const Object& operator[](unsigned int index) const;

		JString toString(bool withDebugMessage, bool withParameters, bool withParameterTypes=false) const;
		const Object& getParameterForCode(nByte parameterCode) const;

		nByte getOperationCode(void) const;
		short getReturnCode(void) const;
		const JString& getDebugMessage(void) const;
		const Hashtable& getParameters(void) const;
	private:
		nByte operationCode;
		short returnCode;
		JString debugMessage;
		Hashtable parameters;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif