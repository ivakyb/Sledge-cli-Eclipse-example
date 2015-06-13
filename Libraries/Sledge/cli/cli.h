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
 * \file 	Sledge/cli/cli.h
 * \author 	Ivan "Kyb Sledgehammer" Kuvaldin <i.kyb[2]ya,ru>
 * \version	2.0.0
 * \date 	2015-mar-19
 * \link 	
 * \git 	
 * \brief 	Sledge/CLI \-- is simple kernel for command-line interface
 *
 * @changes
 *	ver.2.1.0 	date 2015-mar-25
 *		* Универсальный интерфейс для всех комманд cmd(respbuf,buflen,argc,argv)
 * 			Буффер предоставляется пользователем
 * 
 *	ver.2.0.0 	date 2015-mar-19
 *		+ Универсальный интерфейс для всех комманд. func(argc,argv)
 * 		+ Реинтерабельные функции с внешним буффером. func_r(resp, argc, argv)
 * 
 *	ver.1.0.0 	date 2014.09.01
 * 		+ First implementation
 *
 * \TODO
 *  + stats command 
 *		+ for main program, 
 * 		+ for FreeRTOS, 
 * 		+ for LwIP
 *  + nested commands
 *  + возможно добавить параметр opts
 *
 * Thanks to Mike P. Thompson for his code and ideas.
 */

#ifndef __CLI_H
#define __CLI_H

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdint.h>
//#include <stdbool.h>
#include <stddef.h>
//#include "cliConfig.h"
#include "SledgeConfig.h"


#ifndef CLI_CMD_NAME_SIZE
// #warning CLI_CMD_NAME_SIZE should be defined in "SledgeConfig.h"
 #define CLI_CMD_NAME_SIZE 	20
#endif

#ifndef CLI_ARGV_MAX
// #warning CLI_ARGV_MAX should be defined in "SledgeConfig.h"
 #define CLI_ARGV_MAX 	8
#endif

#ifndef NEWLINE
 //#warning NEWLINE should be defined in "SledgeConfig.h"
 #define NEWLINE 	"\n"
#endif

typedef signed char int8_t;
#ifndef __CC_ARM
#define strlcpy strncpy
#endif

/**
 * All command functions have the same syntax.
 * @param[OUT] *response 	The ponter to string which will contain a response
 * @param[IN]   respLen		Max length of response
 * @param[IN]   argc 		Arguments number
 * @param[IN]  *argv[] 		Arguments
 * @param[IN]  *opts 		Options which will be passed to concrete command processor
 * @retval Error code. 0 is OK. 1 is signal to close connection. <0 - any error
 */
//#define cli_COMMAND_FUNCTION(func) 	int8_t (func)( char* respBuf, size_t respSize, int argc, char *argv[] )
//#define cli_COMMAND_FUNCTION(func) 	(int8_t (func)( char *response, size_t respLen, int argc, char *argv[], void *opts ))
#define cli_COMMAND_FUNCTION(func) 	int8_t (func)(char *response, size_t respLen, int argc, char *argv[], void *opts)

//typedef int8_t (*CliFunction_t)( char* respBuf, size_t as, int argc, char **argv );
typedef cli_COMMAND_FUNCTION(*CliFunction_t);

typedef struct CliCommand_t
{
	const char name[CLI_CMD_NAME_SIZE];	/// The name of command. Must be first to use bsearch() and strcmp().
	const CliFunction_t func;			/// Pointer to the command handler
	const char * const help;			/// Pointer to the short help string
	const char * const manual;			/// Pointer to the man string
} CliCommand_t;


extern const CliCommand_t COMMANDS[];
extern const size_t COMMANDS_COUNT;

/*
 * ==== FUNCTIONS ====
 */

/**
 * Process the command and fills the response string.
 * @param[OUT] *response 	The ponter to string which will contain a response
 * @param[IN]   respLen		Max length of response
 * @param[IN]  *cmdline 	Command line
 * @param[IN]  *opts 		Options which will be passed to concrete command processor
 * @retval Error code. 0 is OK. 1 is signal to close connection. <0 - any error
 */
int8_t cli_command( char *response, size_t respLen, /*const*/char *cmdline, void *opts);

/**
 * Search command by name
 */
CliCommand_t * cli_searchCommandByName( const char * cmdname );

/**
 * All following functions have the same syntax.
 * @param[OUT] *response 	The ponter to string which will contain a response
 * @param[IN]   respLen		Max length of response
 * @param[IN]   argc 		Arguments number
 * @param[IN]  *argv[] 		Arguments
 * @param[IN]  *opts 		Options which will be passed to concrete command processor
 * @retval Error code. 0 is OK. 1 is signal to close connection. <0 - any error
 */
//int8_t (func)( char *response, size_t respLen, int argc, char *argv[], void *opts )
/**
 * Reset the uC. Depended on the target CPU.
 */
cli_COMMAND_FUNCTION(cli_reset);
/**
 * This function is called if the requested command is unknown.
 */
cli_COMMAND_FUNCTION(cli_unknown);

/**
 * This function is for strings which are not null terminated but have '\n' or '\r' at the end.
 * Find the next line symbol and Replace it with '\0'
 */
char * cli_terminate_string( char *str, int maxlen );


#ifdef __cplusplus
}
#endif

#endif /* __CLI_H */
