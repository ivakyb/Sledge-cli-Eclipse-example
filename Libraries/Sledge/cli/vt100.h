/**
 * Sledge - wide functionality library, suitable for embedded systems, 
 * mainly for ARM Cortex and more particularly for STM32 family
 * 
 * Copyright (c) 2015, Ivan Kuvaldin. All rights reserved.
 * 
 * Licensed under BSD or MIT. 
 * Please refer to Licence.BSD.txt or Licence.MIT.txt provided with these sources.
 * You may obtain a copy of the Licenses at
 *      http://opensource.org/licenses/bsd-license.php  
 *      http://opensource.org/licenses/mit-license.php  
 */

/**
 * @file	Sledge/cli/vt100.h
 * \author 	Ivan "Kyb Sledgehammer" Kuvaldin <i.kyb[2]ya,ru>
 * @version	1.1.0
 * @date	2015-mar-20
 * For more information look at ./cli.h
 * BSD license
 */ 

#ifndef __VT100_H
#define __VT100_H

#ifdef __cplusplus
 extern "C" {
#endif

	 
#define ANSI_ESC_SEQ_CursorUp			"\x1B[A"
#define ANSI_ESC_SEQ_CursorDown			"\x1B[B"
#define ANSI_ESC_SEQ_CursorRight		"\x1B[C"
#define ANSI_ESC_SEQ_CursorLeft			"\x1B[D"
#define ANSI_ESC_SEQ_CursorUpNLinesTempl 	"\x1B[%dA" 	/// Move cursor up n lines		CUU
#define ANSI_ESC_SEQ_CursorDownNLinesTempl 	"\x1B[%dB" 	/// Move cursor down n lines 	CUD
#define ANSI_ESC_SEQ_CursorRightNLinesTempl "\x1B[%dC"	/// Move cursor right n lines 	CUF
#define ANSI_ESC_SEQ_CursorLeftNLinesTempl 	"\x1B[%dD" 	/// Move cursor left n lines 	CUB 	 
#define ANSI_ESC_SEQ_CursorHome 		"\x1B[H" 		/// Move cursor to upper left corner 	cursorhome
#define ANSI_ESC_SEQ_CursorHome2 		"\x1B[;H"	 	/// Move cursor to upper left corner 	cursorhome
#define ANSI_ESC_SEQ_CurLocTemplate 	"\x1B[%d;%dH" 	/// Move cursor to screen location v,h 	CUP
#define ANSI_ESC_SEQ_CursorHome3		"\x1B[f" 		/// Move cursor to upper left corner 	hvhome
#define ANSI_ESC_SEQ_CursorHome4 		"\x1B[;f" 		/// Move cursor to upper left corner 	hvhome
#define ANSI_ESC_SEQ_CurLocTemplate2 	"\x1B[%d;%df" 	/// Move cursor to screen location v,h 	CUP

#define ANSI_ESC_SEQ_ScrollUp1Line		"\x1BD" 	/// Move/scroll window up one line 			IND
#define ANSI_ESC_SEQ_ScrollDown1Line 	"\x1BM" 	/// Move/scroll window down one line 		RI
#define ANSI_ESC_SEQ_ScrollNextLine 	"\x1BE"		/// Move to next line 						NEL
#define ANSI_ESC_SEQ_CurSavePos			"\x1B7" 	/// Save cursor position and attributes 	DECSC
#define ANSI_ESC_SEQ_CurRestorePos 		"\x1B8"		/// Restore cursor position and attributes 	DECSC 
	 
#define ANSI_ESC_SEQ_ClearScrDown		"\x1B[J"	/// Clear screen from cursor down 	ED0
#define ANSI_ESC_SEQ_ClearScrDown2		"\x1B[0J"	/// Clear screen from cursor down 	ED0
#define ANSI_ESC_SEQ_ClearScrUp			"\x1B[1J"	/// Clear screen from cursor up 	ED1
#define ANSI_ESC_SEQ_ClearScr			"\x1B[2J"	/// Clear entire screen 			ED2 

#define ANSI_ESC_SEQ_EraseLineRight		"\x1B[K"	/// Clear line from cursor right 	EL0
#define ANSI_ESC_SEQ_EraseLineRight2	"\x1B[0K"	/// Clear line from cursor right 	EL0
#define ANSI_ESC_SEQ_EraseLineLeft		"\x1B[1K"	/// Clear line from cursor left 	EL1
#define ANSI_ESC_SEQ_EraseLine			"\x1B[2K"	/// Clear entire line 				EL2 


#define ANSI_ESC_SEQ_PrepareCursorPosition(str, line, column)	\
		sprintf(str, CLI_ANSI_ESC_SEQ_CursorPositionTemplate, line, column)


#ifdef __cpluspluss
}
#endif

#endif /* __VT100_H */
