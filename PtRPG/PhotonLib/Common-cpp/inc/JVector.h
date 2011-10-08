/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

/*
This class is originally from mike95.com and quite similar to it's Java equivalent.
See license below.
We made a few adjustments for neutron/photon and added a documentation.
*/

/*
   This library was downloaded from: http://www.mike95.com

   This library is copyright.  It may freely be used for personal purposes 
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
   Visit http://www.mike95.com/c_plusplus/classes/JVector/

   Standard collection class.  It's public member functions
   are identical to the Java Vector public member functions (except for any Java specific
   Java related functions).

   //The following people have contributed to the solution
   //of bugs or additional features in this library
   //=====================================================
   //Carl Pupa, email: pumacat@erols.com
   //Adam Doppelt, email: amd@gurge.com
   //Dave O'Keefe, email: okeefe@cs.stanford.edu
*/

#ifndef __JVECTOR_H
#define __JVECTOR_H

// #pragma once //don't work ADS1.2

#include "Base.h"
#include "M95_types.h"

#undef min

// ron -- added to work with BREW
//#include "AEEStdLib.h"

#ifndef _EG_BREW_PLATFORM
namespace ExitGames
{
#endif
	/* Summary
	   This is a C++ implementation of the <i>Vector</i> Container
	   class from Sun Java.
	   Description
	   This class is based on the Java Vector class and as such
	   contains all the public member functions of its Java
	   equivalent. Unlike Java, typecasts are not necessary since
	   C++ allows template instantiation of types at compile time.
	   In addition to the Java public member functions, the
	   following were also added in order to take advantage of the
	   \operator overloading feature available in C++.
	   
	   
	   
	   <c>const Etype &amp; operator[](UINT index) const; // for
	   indexing item</c>
	   
	   <c>Etype &amp; operator[](UINT index); // for setting value
	   at index</c>
	   
	   
	   
	   <b><i>Please note that although it's possible to store
	   different types of Objects in the same JVector, this is not
	   conform to the Neutron nor to the Photon Server's protocol.
	   To comply with the protocol, each element in the Vector has
	   to be of type Object, and all of these Objects have to
	   contain the same data type, e.g. Object\<int\>. </i></b>      */
	template <class Etype>
	class JVector:protected Base
	{
	public:
		JVector(bool isObject=true, unsigned int initialCapacity=40, unsigned int capacityIncrement=10);
		JVector(const JVector<Etype>& rhv);
		JVector& operator=(const JVector<Etype> &rhv);
		/* Summary
		Destructor. */
		~JVector(void);

		
		unsigned int capacity() const;
		bool contains(const Etype& elem) const;
		const Etype& firstElement() const;
		int indexOf(const Etype& elem) const;
		bool isEmpty() const;
		const Etype& lastElement() const;
		int lastIndexOf(const Etype& elem) const;
		unsigned int size() const;
		void copyInto(Etype* array) const;

		
		void addElement(const Etype& obj);
		void ensureCapacity(unsigned int minCapacity);
		void removeAllElements(void);
		bool removeElement(const Etype& obj);
		void trimToSize();

		Etype & elementAt(unsigned int index) const;		  
		void insertElementAt(const Etype &obj, unsigned int index); 
		void removeElementAt(unsigned int index);				   
		void setElementAt(const Etype &obj, unsigned int index);	


		
		const Etype & operator[](unsigned int index) const;
		Etype & operator[](unsigned int index);

	protected:
		int min(unsigned int left, unsigned int right) const;
		void verifyIndex(unsigned int index) const;
		unsigned int m_size;
		unsigned int m_capacity;
		unsigned int m_increment;
		Etype** m_pData;
		bool m_isObject;
	};



	//===============================================================
	//Implementation of constructor, destructor, and member functions
	//Necessary location for appropriate template instantiation.
	//===============================================================

	/* Summary
	   Constructor.
	   
	   Creates an empty <link JVector> of elements of the type of
	   the template parameter. Neutron mostly uses <link Object>
	   as type, to wrap the real datatype, which makes it possible,
	   to put different types of data into the same JVector.
	   Parameters
	   isObject :           false, if the template parameter is a
	                        primitive type, true if it is a class
	                        object. The default is true
	   initialCapacity :    the amount of elements, the JVector can
	                        take without need for resize. If you
	                        choose this too small, the JVector needs
	                        expensive resizes later (it's most
	                        likely, that the complete memory has to
	                        be copied to a new location on resize),
	                        if you choose it too big, you will waste
	                        much memory. The default is 40.
	   capacityIncrement :  Every time, you add an element to the
	                        Vector and it has no capacity left
	                        anymore, it's capacity will grow with
	                        this amount of elements on automatic
	                        resize. If you pass a too small value
	                        here, expensive resize will be needed
	                        more often, if you choose a too big one,
	                        possibly memory is wasted. The default is
	                        10.                                         */
	template <class Etype>
	JVector<Etype>::JVector(bool isObject, unsigned int initialCapacity, unsigned int capacityIncrement) 
	{
		m_size = 0;
		m_capacity = initialCapacity;
		m_isObject = isObject;
		/*if (m_isObject) 
			m_pData = new Etype*[m_capacity];
		else*/
		m_pData = (Etype**)MALLOC(m_capacity*sizeof(void*));

		m_increment = capacityIncrement;
	}

	/* Summary
	   Copy-Constructor.
	   
	   Creates an object out of a deep copy of its parameter.
	   
	   The parameter has to be of the same template overload as the
	   \object, you want to create.
	   Parameters
	   toCopy :  The object to copy.                                */
	template <class Etype>
	JVector<Etype>::JVector(const JVector<Etype>& rhv)
	{
		m_size = rhv.m_size;
		m_capacity = rhv.m_capacity;
		m_isObject = rhv.m_isObject;
		/*if(m_isObject)
			m_pData = new Etype*[m_capacity];
		else*/
		m_pData = (Etype**)MALLOC(m_capacity*sizeof(void*));
		m_increment = rhv.m_increment;

		for(unsigned int i=0; i<m_size; i++)
		{
			if(m_isObject)
				m_pData[i] = new Etype(*(rhv.m_pData[i]));
			else
			{
				Etype* temp = (Etype*)MALLOC(sizeof(Etype));
				*temp=*(rhv.m_pData[i]);
				m_pData[i] = temp;
			}
			
		}
	}

	/* Summary
	   Operator =.
	   
	   Makes a deep copy of its right operand into its left operand.
	   Both operands have to be of the same template overload.
	   
	   This overwrites old data in the left operand.                 */
	template <class Etype>
	JVector<Etype>& JVector<Etype>::operator=(const JVector<Etype> &rhv)
	{
		/*if(m_isObject)
			m_pData = new Etype*[ m_capacity ];
		else*/

		if(m_pData)
		{
			removeAllElements();
			FREE(m_pData);
		}

		m_size = rhv.m_size;
		m_capacity = rhv.m_capacity;
		m_isObject = rhv.m_isObject;

		m_pData = (Etype**)MALLOC(m_capacity*sizeof(void*));
		m_increment = rhv.m_increment;

		for(unsigned int i=0; i<m_size; i++)
		{
			if(m_isObject)
				m_pData[i] = new Etype(*(rhv.m_pData[i]));
			else
			{
				Etype* temp = (Etype*)MALLOC(sizeof(Etype));
				*temp=*(rhv.m_pData[i]);
				m_pData[i] = temp;
			}
		}
		return *this;
	}

	template <class Etype>
	JVector<Etype>::~JVector()
	{
		removeAllElements();
		FREE(m_pData);
	}

	/* Summary
	   \Returns the current capacity of the <link JVector>.
	   Returns
	   the current capacity.                                */
	template <class Etype>
	unsigned int
	JVector<Etype>::capacity() const
	{
		return m_capacity;
	}

	/* Summary
	   Checks, if the <link JVector> contains the passed data as an
	   element.
	   Parameters
	   elem :  a reference to the data, you want to check. Needs to
	           be either a primitive type or an object of a class
	           with an overloaded == operator.
	   Returns
	   true, if the element was found, false otherwise.             */
	template <class Etype>
	bool
	JVector<Etype>::contains(const Etype &elem) const
	{
		for(unsigned int i=0; i<m_size; i++)
		{
			if(*m_pData[i] == elem)
				return true;
		}

		return false;
	}

	/* Summary
	   Copies all elements of the <link JVector> into the passed
	   array. The caller has to make sure, the array is big enough,
	   to take all elements of the vector, otherwise calling this
	   method produces a buffer overflow.
	   Parameters
	   array :  an array of variables of the type of the template
	            overload.
	   Returns
	   nothing.                                                     */
	template <class Etype>
	void
	JVector<Etype>::copyInto(Etype* array) const
	{
		for(unsigned int i=0; i<m_size; i++)
			array[i] = *m_pData[i];
	}

	/* Summary
	   \Returns the element of the <link JVector> at the passed
	   index. This does not check for valid indexes and shows
	   unexpected behavior for invalid indexes!
	   Parameters
	   index :  the index of the element, that should be returned.
	            Must not be bigger than the current size of the
	            vector!
	   Returns
	   the element at the passed index.                            */
	template <class Etype>
	Etype &
	JVector<Etype>::elementAt(unsigned int index) const
	{
		verifyIndex(index);
		return *m_pData[index];
	}

	/* Summary
	   \Returns the first element of the <link JVector>. Shows
	   unexpected behaviour for empty vectors.
	   Returns
	   the first element.                                      */
	template <class Etype>
	const Etype &
	JVector<Etype>::firstElement() const
	{
		verifyIndex(0);
		return *m_pData[0];
	}

	/* Summary
	   Searches the <link JVector> from the first element in forward
	   direction for the passed element and returns the first index,
	   where it was found.
	   Parameters
	   elem :  the element, to search for.
	   Returns
	   the index of the first found of the passed element or -1, if
	   the element could not be found at all.                        */
	template <class Etype>
	int
	JVector<Etype>::indexOf(const Etype &elem) const
	{
		for(unsigned int i=0; i<m_size; i++)
		{
			if(*m_pData[i] == elem)
				return i;
		}
		return -1;
	}

	/* Summary
	   Checks, if the <link JVector> is empty.
	   Returns
	   true, if the JVector is empty, or false, if it contains at
	   least one element.                                         */
	template <class Etype>
	bool
	JVector<Etype>::isEmpty() const
	{
		return m_size == 0;
	}

	/* Summary
	   \Returns the last element of the <link JVector>. Shows
	   unexpected behaviour for empty vectors.
	   Returns
	   the last element.                                      */
	template <class Etype>
	const Etype &
	JVector<Etype>::lastElement() const
	{
		verifyIndex(0);
		return *m_pData[m_size - 1];
	}

	/* Summary
	   Searches the <link JVector> from the last element in backward
	   direction for the passed element and returns the first index,
	   where it was found.
	   Parameters
	   elem :  the element, to search for.
	   Returns
	   the index of the first found of the passed element or -1, if
	   the element could not be found at all.                        */
	template <class Etype>
	int
	JVector<Etype>::lastIndexOf(const Etype &elem) const
	{
		//check for empty vector
		if(m_size == 0)
			return -1;

		unsigned int i = m_size;
		
		do
		{
			i -= 1;
			if(*m_pData[i] == elem)
				return i;

		}
		while(i);

		return -1;
	}

	/* Summary
	   Return the size of the <link JVector>.
	   Returns
	   the size.                              */
	template <class Etype>
	unsigned int
	JVector<Etype>::size() const
	{
		return m_size;
	}

	/* Summary
	   Adds an element to the <link JVector>. This automatically
	   resizes the JVector to it's old size + the capacityIncrement,
	   you passed, when creating the vector (if you passed not
	   capacityIncrement, it was set to it's default value (see
	   constructor doc)), if the size of the JVector has already
	   reached it's capacity, which means, that most likely the
	   whole vector has to be copied to new memory. So this can be
	   an expensive operation for huge vectors.
	   Parameters
	   elem :  the element, to add.
	   Returns
	   nothing.                                                      */
	template <class Etype>
	void
	JVector<Etype>::addElement(const Etype &obj)
	{
		if(m_size == m_capacity)
			ensureCapacity(m_capacity+m_increment);

		if(m_isObject)
			m_pData[m_size++] = new Etype(obj);
		else
		{
			Etype* temp = (Etype*)MALLOC(sizeof(Etype));
			*temp = obj;
			m_pData[m_size++] = temp;
		}
	}

	/* Summary
	   Resizes the <link JVector> to the passed capacity, if it's
	   \old capacity has been smaller. Most likely the whole JVector
	   has to be copied into new memory, so this is an expensive
	   \operation for huge JVectors. Call this method, before you
	   add a lot of elements to the vector, to avoid multiple
	   expensive resizes through adding.
	   Parameters
	   minCapacity :  the new capacity for the JVector.
	   Returns
	   nothing.                                                      */
	template <class Etype>
	void
	JVector<Etype>::ensureCapacity(unsigned int minCapacity)
	{
		if(minCapacity > m_capacity)
		{
			unsigned int i;
			m_capacity = minCapacity;
			//Etype** temp = NULL;
			/*if (m_isObject)
				temp = new Etype*[ m_capacity ];
			else*/
			Etype**	temp = (Etype**) MALLOC(m_capacity*sizeof(void*));
			
			//copy all the elements over upto newsize
			for(i=0; i<m_size; i++)
				temp[i] = m_pData[i];

			/*if (m_isObject)
				delete [] m_pData;
			else*/
			FREE(m_pData);
			
			m_pData = temp;

		}
	}

	/* Summary
	   Inserts parameter one into the <link JVector> at the index,
	   passed as parameter two. Because all elements above or at the
	   passed index have to be moved one position up, it is
	   expensive, to insert an element at an low index into a huge
	   JVector.
	   Parameters
	   obj :    the element, to insert.
	   index :  the position in the JVector, the element is inserted
	            at.
	   Returns
	   nothing.                                                      */
	template <class Etype>
	void
	JVector<Etype>::insertElementAt(const Etype &obj, unsigned int index)
	{
		if (index == m_size)
			addElement(obj);
		else
		{
			verifyIndex(index);	//this will throw if true

			if(m_size == m_capacity)
				ensureCapacity(m_capacity + m_increment);

			Etype* newItem;
			if (m_isObject)
				newItem = new Etype(obj); //pointer to new item
			else
			{
				newItem = (Etype*) MALLOC(sizeof(obj));
				*newItem=obj;
			}
			Etype* tmp; //temp to hold item to be moved over.
			
			for(unsigned int i=index; i<=m_size; i++)
			{
				tmp = m_pData[i];
				m_pData[i] = newItem;

				if(i != m_size)
					newItem = tmp;
				else
					break;
			}
			m_size++;
		}
	}

	/* Summary
	   Clears the <link JVector>.
	   Returns
	   nothing.                   */
	template <class Etype>
	void
	JVector<Etype>::removeAllElements()
	{
		//avoid memory leak
		for(unsigned int i=0; i<m_size; i++)
			if(m_isObject)
				delete m_pData[i];
			else
				FREE(m_pData[i]);

		m_size = 0;
	}

	/* Summary
	   Removes the passed element from the <link JVector>.
	   Parameters
	   obj :  the element, to remove.
	   Returns
	   true, if the element has been removed, false, if it could not
	   be found.                                                     */
	template <class Etype>
	bool
	JVector<Etype>::removeElement(const Etype &obj)
	{
		for(unsigned int i=0; i<m_size; i++)
		{
			if(*m_pData[i] == obj)
			{
				removeElementAt(i);
				return true;
			}
		}

		return false;
	}

	/* Summary
	   Removes the element at the passed index from the <link JVector>.
	   Shows unexpected behaviour for invalid indexes.
	   Parameters
	   index :  the index of the element to remove.
	   Returns
	   nothing.                                                         */
	template <class Etype>
	void
	JVector<Etype>::removeElementAt(unsigned int index)
	{
		verifyIndex(index);

		if(m_isObject)
			delete m_pData[index];
		else
			FREE(m_pData[index]);
		

		for(unsigned int i=index+1; i<m_size; i++)
			m_pData[i-1] = m_pData[i];

		m_size--;
	}

	/* Summary
	   Sets the element at the passed index of the <link JVector> to
	   the passed new value. Shows unexpected behaviour for invalid
	   indexes.
	   Parameters
	   obj :    the new value.
	   index :  the index of the element, which is set to the new
	            value.
	   Returns
	   nothing.                                                      */
	template <class Etype>
	void
	JVector<Etype>::setElementAt(const Etype &obj, unsigned int index)
	{
		verifyIndex(index);
		
		*m_pData[index] = obj;
	}

	/* Summary
	   Trims the capacity of the <link JVector> to the size, it
	   currently uses. Call this method for a JVector with huge
	   unused capacity, if you do not want to add further elements
	   to it and if you are short of memory. This method copies the
	   whole vector to new memory, so it is expensive for huge
	   vectors. If you only add one element to the JVector later,
	   it's copied again.                                           */
	template <class Etype>
	void
	JVector<Etype>::trimToSize()
	{
		if(m_size != m_capacity)
		{
			//Etype** temp = new Etype*[m_size];
			Etype** temp = (Etype**) MALLOC(m_size*sizeof(void*));
			unsigned int i;

			for(i=0; i<m_size; i++)
				temp[i] = m_pData[i];

			/*if (m_isObject)
				delete [] m_pData;
			else*/
			FREE(m_pData);

			m_pData = temp;
			m_capacity = m_size;
		}
	}

	template <class Etype>
	int
	JVector<Etype>::min(unsigned int left, unsigned int right) const
	{
		return left<right?left:right;
	}
	  
	template <class Etype>
	void
	JVector<Etype>::verifyIndex(unsigned int index) const
	{
		if(index >= m_size)
			debugReturn("JVector: Index Out Of Bounds");
	}

	/* Summary
	   \operator[]. Wraps the method <link JVector::elementAt@unsigned int@const, elementAt>(),
	   so you have same syntax like for arrays.                                                 */
	template <class Etype>
	const Etype &
	JVector<Etype>::operator[](unsigned int index) const
	{
		return elementAt(index);
	}

	/* Summary
	   \operator[]. Wraps the method <link JVector::elementAt@unsigned int@const, elementAt>(),
	   so you have same syntax like for arrays.                                                 */
	template <class Etype>
	Etype &
	JVector<Etype>::operator[](unsigned int index)
	{
		verifyIndex(index);
		return *m_pData[index];
	}

#ifndef _EG_BREW_PLATFORM
}
#endif

#endif