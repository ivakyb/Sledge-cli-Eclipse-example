/**
 * @file 	Sledge/misc/utils.h 
 */

#ifndef __SLEDGE_UTILS_H_
#define __SLEDGE_UTILS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/// For STATIC_ASSERT
//#include "../dassel/assert.h"

	 
/** Конкатинация во время компиляции. Подробнее в интернете */
#define CONCAT(First, Second) 			CONCAT_HELPER(First, Second)
#define CONCAT_HELPER(First, Second) 	(First ## Second)


/**
 * === STRING ===
 */

/// New line is: 0=LF (Linux), 1=CR (old Mac), 2=CR+LF (Windows)
#ifndef NEWLINE_OPTION
 #define NEWLINE_OPTION 	0
#endif

#ifndef NEWLINE
 #if NEWLINE_OPTION == 0 || defined(NEWLINE_NIX)	/// *nix
  #define NEWLINE 	"\n"
 #elif NEWLINE_OPTION == 1 || defined(NEWLINE_MAC)	/// Old Mac
  #define NEWLINE 	"\r"
 #elif NEWLINE_OPTION == 2 || defined(NEWLINE_WIN)	/// Windows
  #define NEWLINE 	"\r\n"
 #else
  #error "NEWLINE_OPTION must be selected properly."
 #endif /* NEWLINE_OPTION */
 //#define NL  NEWLINE
#endif /* NEWLINE */


//#define isSpace(ch) 	(ch == ' ')
#define isSpace(ch) 	(((ch) == ' ') || ((ch) == '\r') || ((ch) == '\n'))
//#define isSpace(c)           (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')

/// Character code support macros
#define isUpper(c)	( ('A'<=(c)) && ((c)<='Z') )
#define isLower(c)	( ('a'<=(c)) && ((c)<='z') )
#define isDigit(c)	( ('0'<=(c)) && ((c)<='9') )


/**
 * === ARRAYS ===
 * Works only in the compilation unit, where array `a` defined.
 */
#define array_length(a)		( sizeofarr(a) )	/// @DEPRICATED
#define sizeofarr(a)		( sizeof(a) / sizeof((a)[0]) )


/**
 * === BITS and BIT FIELDS ===
 */
#define BIT(x) 	((uint32_t)1<<(x))
#define BIT0 	BIT(0)
#define BIT1 	BIT(1)
#define BIT2 	BIT(2)
#define BIT3 	BIT(3)
#define BIT4 	BIT(4)
#define BIT5 	BIT(5)
#define BIT6 	BIT(6)
#define BIT7 	BIT(7)
#define BIT8 	BIT(8)
#define BIT9 	BIT(9)
#define BIT10 	BIT(10)
#define BIT11 	BIT(11)
#define BIT12 	BIT(12)
#define BIT13 	BIT(13)
#define BIT14 	BIT(14)
#define BIT15 	BIT(15)

#define BITA 	BIT(0xA)
#define BITB 	BIT(0xB)
#define BITC 	BIT(0xC)
#define BITD 	BIT(0xD)
#define BITE 	BIT(0xE)
#define BITF 	BIT(0xF)


/**
 * === BIT-MASKS ===
 */
#define BIT_MASK(x)  ( BIT(x)-1 )
/*#define BIT_MASK1    BIT_MASK(1)
#define BIT_MASK2    BIT_MASK(2)
#define BIT_MASK3    BIT_MASK(3)
#define BIT_MASK4    BIT_MASK(4)
#define BIT_MASK5    BIT_MASK(5)
#define BIT_MASK6    BIT_MASK(6)
#define BIT_MASK7    BIT_MASK(7)
#define BIT_MASK8    BIT_MASK(8)
#define BIT_MASK9    BIT_MASK(9)
#define BIT_MASK10   BIT_MASK(10)
#define BIT_MASK11   BIT_MASK(11)
#define BIT_MASK12   BIT_MASK(12)
#define BIT_MASK13   BIT_MASK(13)
#define BIT_MASK14   BIT_MASK(14)
#define BIT_MASK15   BIT_MASK(15)
#define BIT_MASK16   BIT_MASK(16)
#define BIT_MASK17   BIT_MASK(17)
#define BIT_MASK18   BIT_MASK(18)
#define BIT_MASK19   BIT_MASK(19)
#define BIT_MASK20   BIT_MASK(20)
#define BIT_MASK21   BIT_MASK(21)
#define BIT_MASK22   BIT_MASK(22)
#define BIT_MASK23   BIT_MASK(23)
#define BIT_MASK24   BIT_MASK(24)
#define BIT_MASK25   BIT_MASK(25)
#define BIT_MASK26   BIT_MASK(26)
#define BIT_MASK27   BIT_MASK(27)
#define BIT_MASK28   BIT_MASK(28)
#define BIT_MASK29   BIT_MASK(29)
#define BIT_MASK30   BIT_MASK(30)
#define BIT_MASK31   BIT_MASK(31)*/
#define BIT_MASK32   (BIT_MASK(31) | BIT(31))



/**
 * Create bit-mask from one bit to another inclusive.
 * \param x,y bit number from and to
 * \return bit-mask
 * \note BIT_MASK
 */
#define BIT_MASK_FROM_TO(x,y) 	( x > y ? ( BIT_MASK(x+1) & ~BIT_MASK(y) ) : ( BIT_MASK(y+1) & ~BIT_MASK(x) ) )
//#define BITMASK(x,y)   ( x > y ? ( BIT_MASK(x) & ~BIT_MASK(y) ) : ( BIT_MASK(y) & ~BIT_MASK(x) ) )
//#define BIT_MASK(x,y)  (BITMASK(x,y))



#ifdef __cplusplus
 }
#endif

#endif /*__SLEDGE_UTILS_H_*/
