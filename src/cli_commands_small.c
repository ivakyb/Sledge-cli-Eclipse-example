/**
 * Sledge - wide functionality library, suitable for embedded systems, 
 * mainly for ARM Cortex and more particularly for STM32 family
 * 
 * Copyright (c) 2015, Ivan Kuvaldin. All rights reserved.
 * 
 * Licensed under BSD or MIT. 
 * Please refer to Licence.BSD.txt or Licence.MIT.txt provided with these sources.
 * You may obtain a copy of the Licenses at
 *      http://opensource.org/licenses/bsd-license.php <br/>
 *      http://opensource.org/licenses/mit-license.php <br/>
 */
/**
 * \file 	Sledge/cli/cli-commands.c
 * \author 	Ivan "Kyb Sledgehammer" Kuvaldin <i.kyb[2]ya,ru>
 * For more information look at ./cli.h
 * 
 * This file is part of sledge/cli module. 
 * Provides commands list and functions implementation
 */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//#include <ctype.h>
#include <stdio.h>

//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"

//#include "lwip/netif.h"

//#include "network/udpSenderOptions.h"
//#include "network/udpSender.h"
//#include "ptpd-2.0.0/src/ptpd.h"

//#include "mainConfig.h"

#include "Sledge/cli/cli.h"
//#include "Sledge/c11n/c11n.h"
#include "Sledge/misc/utils.h"
//#include "Sledge/misc/uid.h"
//#include "Sledge/misc/strtrim.h"

/** ==== DEBUG ====
 */
//#undef DEBUG_LEVEL
//#define DEBUG_LEVEL  CLI_DEBUG_LEVEL
//#include "Sledge/dassel/debug.h"
//#include "Sledge/dassel/assert.h"


/**
 * All following functions have the same syntax.
 * @param[OUT] *response 	the pointer to string which will contain response
 * @param[IN]   respLen		max length of response
 * @param[IN]   argc 		arguments number
 * @param[IN]  *argv[] 		arguments
 * @param[IN]  *opts 		Options which will be passed to concrete command processor
 * @retval Error code. 0 is OK. 1 is signal to close connection. <0 - any error
 */
//static cli_COMMAND_FUNCTION( cli_get  );
//static cli_COMMAND_FUNCTION( cli_set  );
//static cli_COMMAND_FUNCTION( cli_param );

//static cli_COMMAND_FUNCTION( cli_date );

static cli_COMMAND_FUNCTION( cli_help );
static cli_COMMAND_FUNCTION( cli_info );
//static cli_COMMAND_FUNCTION( сli_tasklist );
static cli_COMMAND_FUNCTION( cli_clear );
static cli_COMMAND_FUNCTION( cli_exit );
//static cli_COMMAND_FUNCTION( cli_unknown );
//static cli_COMMAND_FUNCTION( cli_reset );

/// MUST be sorted in ASCENDING order.
const CliCommand_t COMMANDS[] = {
	/*-name-+-function-+--short description-*/
	{"?"    ,  cli_help, "The same as help" },
	{"clear", cli_clear, "Clear the screen" },
	{"cls"  , cli_clear, "The same as clear" },
	{"exit" ,  cli_exit, "Close telnet connection" },
	{"hello",  cli_info, "The same as info" },
	{"help" ,  cli_help, "Show this short help" },
	{"info" ,  cli_info, "Print information about device and firmware" },
	{"reset", cli_reset, "Reset the uC" },
	{"stats",      NULL, "Statistics" },
};

const size_t COMMANDS_COUNT = sizeofarr(COMMANDS);


/** 
 * ==== FUNCTIONS ====
 */

/** 
 * Compilies help message.
 */
cli_COMMAND_FUNCTION( cli_help )
{
	size_t i, len;

	/// Clear string
	response[0] = '\0';
	len = 0;

	/// Loop over each shell command.
	for (i = 0; i < COMMANDS_COUNT; ++i) {
		len += snprintf( response+len, respLen-len, "%s\t %s"NEWLINE, COMMANDS[i].name, COMMANDS[i].help);
	}

	return 0;
}


/**
 * This function returns 1. This must be recognized as signal 
 * to close current TCP/Telnet connection.
 * Its analog shell_exit uses FALSE.
 * @return 1
 */
cli_COMMAND_FUNCTION( cli_exit )
{
	strlcpy( response, "Closing connection..."NEWLINE, respLen);
	return 1;
}


/** 
 * Information about device.
 */
cli_COMMAND_FUNCTION( cli_info )
{
	char ipbuf[16];
	extern struct netif xnetif;
	
	snprintf( response, respLen,
			"Firmware built at " __TIME__ " " __DATE__);
	return 0;
}


/** 
 * Clear screen. Useful with telnet, but not with netcat.
 */
cli_COMMAND_FUNCTION( cli_clear )
{
	//*response = '\f';
	strlcpy( response, "\x1b[2J\x1b[H", respLen);
	return 0;
}


/** 
 * Reset uC.
 */
int8_t cli_reset( char *response, size_t respLen, int argc, /*const*/ char *argv[], void *opts )
{
	//NVIC_SystemReset();
	// We should never come here
	response[0] = '\0';
	return 0;
}


/** 
 * Unknown command.
 */
cli_COMMAND_FUNCTION( cli_unknown )
//int8_t cli_unknown( char *response, size_t respLen, int argc, /*const*/ char *argv[], void *opts )
{
	snprintf( response, respLen, "Unknown command \"%s\". Type \"help\" or \"?\" to see valid commands."NEWLINE, argv[0] );
	return 0;
}
