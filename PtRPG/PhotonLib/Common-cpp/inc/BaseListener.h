/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __BASE_LISTENER_H
#define __BASE_LISTENER_H

#include "WrapperDefines.h"
#include "JString.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	/* Summary
	   This class defines the listener interface for the debug
	   callback mechanism of the Utility-classes (except <link JString>)
	   used by both Neutron and Photon.
	   Description
	   If some error occurs while using the Utility classes, there
	   is a callback mechanism that will send error messages about
	   what went wrong, to help you debugging. To receive these
	   error messages you have to derive from BaseListener and
	   implement the virtual function in your derived class. Then
	   register your class by calling the static method <link Base::setListener@BaseListener*, Base::setListener()>.
	   
	   Implementing this listener is optional. If you do not do it,
	   you get no debug returns from Neutron / Photon Utilities in
	   error cases, but you can still use the utility classes.
	   
	   The Neutron Wrapper provides a similar debug callback
	   interface as well as the Photon Wrapper
	   Example
	   First we create a class implementing the BaseListener
	   interface:
	   
	   
	   
	   <c>class MyUtilsDebugListener:public ExitGames::BaseListener</c>
	   
	   <c>{</c>
	   
	   <c>public:</c>
	   
	   <c> void debugReturn(ExitGames::JString string)</c>
	   
	   <c> {</c>
	   
	   <c> std::cout \<\< string.cstr() \<\< std::endl;</c>
	   
	   <c> }</c>
	   
	   <c>};</c>
	   
	   
	   
	   In our application we register our listener by calling the
	   static method Base::setListener():
	   
	   
	   
	   ...
	   
	   <c>m_pUtilsDebugListener = new MyUtilsDebugListener;</c>
	   
	   <c>ExitGames::Base::setListener(m_pUtilsDebugListener);</c>
	   
	   ...
	   See Also
	   <link Base> , <link Base::setListener@BaseListener*, Base::setListener()>                                     */
	class BaseListener
	{
	public:
		/* Summary
		   This is the callback method for debug-messages from all
		   Neutron Utility-classes except for <link JString>.
		   Description
		   Please refer to <link BaseListener> for more information and
		   a code example.
		   See Also
		   <link BaseListener>                                          */
		virtual void debugReturn(const JString& string) = 0;
	};

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif