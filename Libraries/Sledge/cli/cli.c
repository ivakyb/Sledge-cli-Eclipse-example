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
 * \file 	Sledge/cli/cli.c
 * \author 	Ivan "Kyb Sledgehammer" Kuvaldin <i.kyb[2]ya,ru>
 * \brief 	For more information look at ./cli.h
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//#include <stdio.h>
#include <stdlib.h>

#include "./cli.h"
#include "../misc/utils.h"
//#include "../misc/uid.h"
//#include "../misc/strtrim.h"

/* ==== DEBUG ====
 */
//#undef DEBUG_LEVEL
//#define DEBUG_LEVEL  CLI_DEBUG_LEVEL
//#include "Sledge/dassel/debug.h"
//#include "Sledge/dassel/assert.h"


#ifdef STM32F4XX
 #include "stm32f4xx.h" //#include "core_cm4.h"
#else
 #warning NVIC_SystemReset() does nothing
 #define NVIC_SystemReset() ((void)0)
#endif

#if CLI_REGISTER_SENS > 0
 #define string_compare strcmp
#else
 #define string_compare strcasecmp
#endif


/* 
 * ==== FUNCTIONS ====
 */

/*
 * This function is for strings which are not null terminated but have '\n' or '\r' at the end.
 * Find the next line symbol and Replace it with '\0'
 */
char * cli_terminate_string( char *str, int maxlen )
{
	/// cmdline string is not null-terminated, it may be terminated with '\n', so we must terminate it with '\0'
	int i=0;

	while( 	   str[i] != '\n'
			&& str[i] != '\r'
			&& str[i] != '\0'
			&& i < maxlen-1
	){
		i++;
	}
	str[i] = '\0';

	return str;
}

/** 
 * Parse out the next non-space word from a string.
 * @arg str  [IN]	 Pointer to pointer to the string. Nested pointer to string will be changed.
 * @arg word [OUT]	 Pointer to pointer of next word.
 * @returns	0:Failed, 1:Successful 
 */
static int cli_parse(char **str, char **word)
{
	// Skip leading spaces.
	while (**str && isSpace(**str)) (*str)++;

	// Set the word.
	*word = *str;

	// Skip non-space characters.
	while (**str && !isSpace(**str)) (*str)++;

	// Null terminate the word.
	if (**str) *(*str)++ = 0;

	return (*str != *word) ? 1 : 0;
}


typedef signed char int8_t;
/** 
 * Processes the command and fills the response string. Responses to the command representer by *str.
 * @NOTE	This function uses non-reentrant version of strtok(). Function strtok() directly applied 
 * 			to \p cmdLine. That is why if you will use \p cmdLine after this function, it would be copied before.
 * @param[OUT]	*response :	the ponter to string withch will contain response
 * @param[IN]	  resplen :	
 * @param[IN]	 *cmdline :	the string which contains string representation of command.
 * @param[IN]	    *opts :	Options which may be passed to concrete command processor
 * @retval value returned by executed command, or 0.
 */
// Attempt to execute the shell command.
//bool cli_command(char *cmdline)
int8_t cli_command( char *response, size_t respLen, /*const*/char *cmdline, void/*SenderOptions_t*/ *opts) 
{
	char *argv[CLI_ARGV_MAX];
	int argc = 0;
	int8_t rv = 0;
	//struct shell_command *command = NULL;
	CliCommand_t *command = NULL;
	
	// cmdline string may not be null-terminated, but end-line symbol exists, so we must terminate it with '\0'
	//cli_terminate_string( cmdline, CMDLINE_MAX_LENGTH );
	
	// Parse the command and any arguments into an array.
	do{
		cli_parse( &cmdline, &argv[argc] );
		if (*argv[argc] == '\0') 
			break;
	}while( argc++ < sizeofarr(argv) );
	
	if( argc == 0 ){
		response[0] = '\0'; 	/// Empty response
		return 0;
	}
	
	// Search for a matching command.
	command = cli_searchCommandByName( argv[0] );
	
	// Call the command handler if found.
	if (command) {
		if( command->func ){
			rv = (command->func)(response, respLen, argc, argv, opts );
		} else {
			strlcpy( response, "Command not implemented yet"NEWLINE, respLen );
		}
	} else {
		cli_unknown(response, respLen, argc, argv, opts);
	}
	
	return rv;	//(void) rv;
}


/**
 * Search command by name
 */
CliCommand_t * cli_searchCommandByName( const char * cmdname )
{
	return (CliCommand_t *) bsearch(/*key*/  cmdname, 
									/*base*/ COMMANDS, 
									/*nmemb*/COMMANDS_COUNT,   //array_length(COMMANDS),
									/*size*/ sizeof(CliCommand_t), 
									/*compareFunction*/(int(*)(const void*, const void*))string_compare );
}


/**
 * У MinGW+eclipse какие-то траблы с пониманнием __weak, __attribute__((weak))
 * и этого выражения ранее определенного в SledgeConfig.h. Об этом есть баг-репорты в инете.
 */
//#ifdef __GNUC__
// #define __weak __attribute__((weak))
//#endif

///**
// * Compile help message.
// */
//__weak cli_COMMAND_FUNCTION( cli_help )
//{
//	size_t i, len;
//
//	/// Clear string
//	response[0] = '\0';
//	len = 0;
//
//	/// Loop over each shell command.
//	for (i = 0; i < COMMANDS_COUNT; ++i) {
//		len += snprintf( response+len, respLen-len, "%s\t %s"NEWLINE, COMMANDS[i].name, COMMANDS[i].help);
//	}
//
//	return 0;
//}
//
//
///**
// * This function returns 1. This must be recognized as signal
// * to close current TCP/Telnet connection.
// * Its analog shell_exit uses FALSE.
// * @return 1
// */
//__weak cli_COMMAND_FUNCTION( cli_exit )
//{
//	strlcpy( response, "Closing connection..."NEWLINE, respLen);
//	return 1;
//}
//
//
///**
// * Reset uC.
// */
//__weak cli_COMMAND_FUNCTION( cli_reset ) /*__attribute__((weak))*/
////( char *response, size_t respLen, int argc, /*const*/ char *argv[], void *opts )
//{
//	NVIC_SystemReset();
//	/// We will never come here
//	return 0;
//}


/**
 * Unknown command.
 */
//__weak cli_COMMAND_FUNCTION( cli_unknown ) /*__attribute__((weak))*/
////( char *response, size_t respLen, int argc, /*const*/ char *argv[], void *opts )
//{
//	snprintf( response, respLen, "Unknown command \"%s\". Type \"help\" or \"?\" to see valid commands."NEWLINE, argv[0] );
//	return 0;
//}
