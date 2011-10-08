/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

/*
This class is originally from mike95.com and quite similar to it's Java equivalent.
See license below.
We made a few adjustments for Neutron/Photon and added some additional functionality and a documentation.
*/

/*
   This library was downloaded from: http://www.mike95.com

   This library is copyright. It may freely be used for personal purposes 
   if the restriction listed below is adhered to.
       Author: Michael Olivero
       Email:  mike95@mike95.com

   //===============================
   //Start of Restriction Definition
   //===============================
   Anyone can have full use of the library provided they keep this complete comment
   with the source.  Also I would like to ask if any changes are made to the
   code for efficiency reasons, please let me know so I may look into your change and
   likewise incorporate it into library.  If a suggestion makes it into the library,
   your credits will be added to this information.

   Authors of Computer related books are welcome to include this source code as part
   of their publishing, provided credit the Author and make note of where the source
   code was obtained from: http://www.mike95.com
   //=============================
   //End of Restriction Definition
   //=============================


   Description:
   Visit http://www.mike95.com/c_plusplus/classes/JString/

   This library avoids the need to use pointers to char or manual
   memory manipulation while working with Strings.  This class has been
   based on the Java String class, and thus has all of the Java public functionality
   with a few extras [replace()] needed for useful functionality.

   //The following people have contributed to the solution
   //of bugs or improvements in this library
   //=====================================================
   //Carl Pupa, [pumacat@erols.com]
   //Thomas Watson, [w@tson.dk]
   //Subbiah, Venkat [vsubbiah@corvis.com]
   //Oren Tirosh [mailto:oren@hishome.net] 
*/ 

#ifndef __JString_H
#define __JString_H

#include "platformLayer.h"
#include "M95_types.h"
#include "debug_assert.h"

namespace std
{
	template<class _Elem, class _Traits> class basic_ostream;
}

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	class UTF8String;
	class ANSIString;

	/* Summary
	   The JString class is a representation of Text strings, based
	   on the String class from Sun Java.
	   Description
	   This class is used to avoid dealing with char pointers/arrays
	   directly, while staying independent from the String class in
	   the Standard Template Library of C++, as some compilers
	   (BREW) do not implement the STL.                                        */
	class JString 
	{
	public:
		JString(void);
		JString(const char* const Value);
		JString(const EG_CHAR* const Value);
		JString(const JString& Value);
		JString(const UTF8String& Value);
		JString(const ANSIString& Value);
		~JString(void);

		JString&				operator=(const JString& Rhs);
		JString&				operator=(const char* const Rhs);
		JString&				operator=(const EG_CHAR* const Rhs);
		JString&				operator=(const UTF8String& Rhs);
		JString&				operator=(const ANSIString& Rhs);
		JString&				operator=(char Rhs);
		JString&				operator=(EG_CHAR Rhs);
		JString&				operator=(short aNum);
		JString&				operator=(int aNum);
		JString&				operator=(int64 aNum);
		JString&				operator=(float aNum);
		JString&				operator=(double aNum);

								operator const EG_CHAR* (void) const;

		JString&			operator+=(const JString& Rhs);
		JString&			operator+=(const char* const Rhs);
		JString&			operator+=(const EG_CHAR* const Rhs);
		JString&			operator+=(const UTF8String& Rhs);
		JString&			operator+=(const ANSIString& Rhs);
		JString&			operator+=(char aChar);
		JString&			operator+=(EG_CHAR aWideChar);
		JString&			operator+=(int aNum);
		JString&			operator+=(int64 aNum);
		JString&			operator+=(short aNum);
		JString&			operator+=(float aNum);
		JString&			operator+=(double aNum);

		bool					operator==(const JString& Rhs) const;
		bool					operator!=(const JString& Rhs) const;
		bool					operator< (const JString& Rhs) const;
		bool					operator> (const JString& Rhs) const;
		bool					operator<=(const JString& Rhs) const;
		bool					operator>=(const JString& Rhs) const;

		EG_CHAR					operator[](unsigned int Index) const;
		EG_CHAR&				operator[](unsigned int Index);

		EG_CHAR					charAt(unsigned int index) const;
		int						compareTo(const JString& anotherString) const;
		const JString&			concat(const JString& str);
		const EG_CHAR*			cstr(void) const;
		JString					deleteChars(unsigned int start, unsigned int length);
		bool					endsWith(const JString& suffix) const;
		bool					equals(const JString& anotherString) const;
		bool					equalsIgnoreCase(const JString& anotherString) const;
		int						indexOf(char ch) const;
		int						indexOf(char ch, unsigned int fromIndex) const;
		int						indexOf(EG_CHAR ch) const;
		int						indexOf(EG_CHAR ch, unsigned int fromIndex) const;
		int						indexOf(const JString& str) const;
		int						indexOf(const JString& str, unsigned int fromIndex) const;
		int						lastIndexOf(char ch) const;
		int						lastIndexOf(char ch, unsigned int fromIndex) const;
		int						lastIndexOf(EG_CHAR ch) const;
		int						lastIndexOf(EG_CHAR ch, unsigned int fromIndex) const;
		int						lastIndexOf(const JString& str) const;
		int						lastIndexOf(const JString& str, unsigned int fromIndex) const;
		unsigned int			length(void) const;
		JString					replace(char oldChar, char newChar);
		JString					replace(EG_CHAR oldChar, EG_CHAR newChar);
		JString					replace(const JString& match, const JString& replace);
		bool					startsWith(const JString& prefix) const;
		bool					startsWith(const JString& prefix, unsigned int offset) const;
		JString					substring(unsigned int beginIndex) const;
		JString					substring(unsigned int beginIndex, unsigned int endIndex) const;
		JString					toLowerCase(void) const;
		JString					toUpperCase(void) const;
		int						toInt(void) const;
		JString					trim(void);
		UTF8String				UTF8Represantation(void) const;
		ANSIString				ANSIRepresentation(void) const;

	protected:
		EG_CHAR* Buffer;		// Stores the chars
		unsigned int BufferLen;	// Max strlen for Buffer
		unsigned int Length;	// Length of string

		void GetBuffer(unsigned int MaxStrLen);
		void Double( );
		void verifyIndex(unsigned int number) const;

	private:
		friend JString operator+(const JString& Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, const char* const Rsh);
		friend JString operator+(const char* const Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, const EG_CHAR* const Rsh);
		friend JString operator+(const EG_CHAR* const Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, const UTF8String& Rsh);
		friend JString operator+(const UTF8String& Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, const ANSIString& Rsh);
		friend JString operator+(const ANSIString& Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, char Rsh);
		friend JString operator+(char Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, EG_CHAR Rsh);
		friend JString operator+(EG_CHAR Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, int Rsh);
		friend JString operator+(int Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, int64 Rsh);
		friend JString operator+(int64 Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, short Rsh);
		friend JString operator+(short Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, float Rsh);
		friend JString operator+(float Lsh, const JString& Rsh);
		friend JString operator+(const JString& Lsh, double Rsh);
		friend JString operator+(double Lsh, const JString& Rsh);
	};

	/* Summary
	   Operator<<.

	   Used to print the JString to a std::wostream.*/
	template<class _Elem, class _Traits>
	::std::basic_ostream<_Elem, _Traits>& operator<<(::std::basic_ostream<_Elem, _Traits>& stream, const JString& string)
	{
		return stream << string.cstr();
	}

	JString operator+(const JString& Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, const char* const Rsh);
	JString operator+(const char* const Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, const EG_CHAR* const Rsh);
	JString operator+(const EG_CHAR* const Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, const UTF8String& Rsh);
	JString operator+(const UTF8String& Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, const ANSIString& Rsh);
	JString operator+(const ANSIString& Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, char Rsh);
	JString operator+(char Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, EG_CHAR Rsh);
	JString operator+(EG_CHAR Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, int Rsh);
	JString operator+(int Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, int64 Rsh);
	JString operator+(int64 Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, short Rsh);
	JString operator+(short Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, float Rsh);
	JString operator+(float Lsh, const JString& Rsh);
	JString operator+(const JString& Lsh, double Rsh);
	JString operator+(double Lsh, const JString& Rsh);

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif