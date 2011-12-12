/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#ifndef __COMPILE_TIME_ASSERT_TRUE_H
#define __COMPILE_TIME_ASSERT_TRUE_H

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif

	template<bool> struct CompileTimeAssertTrue;
	template<> struct CompileTimeAssertTrue<true> {};

	#define COMPILE_TIME_ASSERT_TRUE(expr) {CompileTimeAssertTrue<expr> ASSERTION_FAILED; (void)ASSERTION_FAILED;}
	#define COMPILE_TIME_ASSERT_TRUE_MSG(expr, msg) {CompileTimeAssertTrue<expr> ASSERTION_FAILED_##msg; (void)ASSERTION_FAILED_##msg;}

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif