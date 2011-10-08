/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __EGTIME_H
#define __EGTIME_H

#include "Base.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class EGTime:protected Base
	{
	public:
		EGTime(int time);

		EGTime& operator=(const int &time);
		const EGTime& operator+=(const EGTime &time);
		const EGTime& operator-=(const EGTime &time);
		EGTime operator+(const EGTime &time);
		EGTime operator-(const EGTime &time);

		bool operator>(const EGTime &time) const;
		bool operator<(const EGTime &time) const;
		bool operator>=(const EGTime &time) const;
		bool operator<=(const EGTime &time) const;
		bool operator==(const EGTime &time) const;
		bool operator!=(const EGTime &time) const;

		bool Overflowed(const EGTime &time) const;

	private:
		int t;
	};
#ifndef _EG_BREW_PLATFORM
}
#endif

#endif