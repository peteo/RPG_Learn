/*======================================================
FILE:  AEEComdef.h

SERVICES:  Definitions of Basic data structures used in AEE.

GENERAL DESCRIPTION:
	Base level data structure definitions, typedefs, etc. for AEE

        Copyright � 1999-2002 QUALCOMM Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
=====================================================*/

/* guard against re-inclusion */
#if !defined(AEECOMDEF_H)
#define AEECOMDEF_H

/* GCC packed works a little differently */
#if !defined(GCCPACKED)
// For the GCC compiler
# if defined(__GNUC__)
#  define GCCPACKED  __attribute__ ((packed))
# else  //__GNUC__
#  define GCCPACKED 
# endif //__GNUC__
#endif // ifndef GCCPACKED

/* Make sure exports are only done when building for Windows */
#if defined(AEE_SIMULATOR)
# ifdef AEE_OEM_EXPORTS
#  define AEE_EXPORTS __declspec(dllexport)
# else
#  define AEE_EXPORTS __declspec(dllimport)
# endif // AEE_OEM_EXPORTS
#else
# define AEE_EXPORTS
#endif // AEE_SIMULATOR

#ifndef CODE_SECTION
#if defined(PALMOS)
#define CODE_SECTION(x) __attribute__ ((section (x)))
#else /* #if defined(PALMOS) */
#define CODE_SECTION(x)
#endif /* #if defined(PALMOS) */
#endif /* #ifndef CODE_SECTION */


#if !defined(MAX_UINT16)
#define MAX_UINT16 0x0ffff
#endif

#if !defined(MAX_INT16)
#define MAX_INT16 0x07fff
#endif


#if !defined(MAX_UINT32)
#define MAX_UINT32 0xffffffff
#endif

#if !defined(MAX_INT32)
#define MAX_INT32 0x7fffffff
#endif

/* =========================================================================
   guard against handset comdef.h's, because they define most of the below
   unconditionally
   ========================================================================= */

#if !defined(COMDEF_H)

/* =========================================================================
             "S T A N D A R D"    D E C L A R A T I O N S

DEFINED TYPES

       Name      Definition
       -------   --------------------------------------------------------
       byte      8  bit unsigned value
       word      16 bit unsigned value 
       dword     32 bit unsigned value

       uint1     byte
       uint2     word
       uint4     dword

       uint8     8  bit unsigned value
       uint16    16 bit unsigned value
       uint32    32 bit unsigned value
       uint64    64 bit unsigned value

       int8      8  bit signed value
       int16     16 bit signed value 
       int32     32 bit signed value
       int 64    64 bit signed value

       sint31    32 bit signed value 
       sint15    16 bit signed value
       sint7     8  bit signed value

       int1      8  bit signed value
       int2      16 bit signed value
       int4      32 bit signed value

       bool   8 bit bool value

DEFINED CONSTANTS

       Name      Definition
       -------   --------------------------------------------------------
       true      Asserted bool condition (Logical 1)
       false     Deasserted bool condition (Logical 0)
 
       ON        Asserted condition
       OFF       Deasserted condition

       NULL      Pointer to nothing

       PACKED    Used to indicate structures which should use packed
                 alignment 

       INLINE    Used to inline functions for compilers which support this

===========================================================================*/

/*===========================================================================

                            Data Declarations

===========================================================================*/

/* For AEE_SIMULATOR apps we want to use the Win32 definitions and/or those
** supplied by the Win32 compiler for things like NULL, MAX, MIN
** abs, labs, etc.
*/
#ifdef AEE_SIMULATOR
   #ifndef WIN32
      #define WIN32
   #endif
#endif

/* ------------------------------------------------------------------------
** Constants
** ------------------------------------------------------------------------ */

#ifndef true
#define true   1   /* Boolean true value. */
#endif
#ifndef false
#define false  0   /* Boolean false value. */
#endif

#ifndef ON
#define  ON   1    /* On value. */
#endif
#ifndef OFF
#define  OFF  0    /* Off value. */
#endif

#ifdef _lint
  #define NULL 0   
#endif

#ifndef NULL
  #define NULL  0
#endif

/* ---------------------------------------------------------------------
** Compiler Keyword Macros
** --------------------------------------------------------------------- */ 

#if defined(__arm)
  #define PACKED __packed
#else
  #define PACKED
#endif

/* ----------------------------------------------------------------------
**                          STANDARD MACROS
** ---------------------------------------------------------------------- */

#ifndef MAX
   #define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef MIN
   #define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

#ifndef ABS
   #define ABS(VAL) (((VAL)>0)?(VAL):(-(VAL)))
#endif

#if !defined(ARR_SIZE)
   #define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))
#endif /* #if !defined(ARR_SIZE) */

#endif /* #if !defined(COMDEF_H) */
#endif /* #if !defined(AEECOMDEF_H) */
