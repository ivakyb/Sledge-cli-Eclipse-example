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
 * \file 	SledgeConfig.h
 * \author 	
 */
 
#ifndef __SledgeConfig_h
#define __SledgeConfig_h

/** ┌———————————————————————————————————————————————————————————————————————┐
	│				Configuration of c11n module							│  
	└———————————————————————————————————————————————————————————————————————┘ */
/** \addtogroup Configuration_of_c11n_module  Configuration of c11n module
  *	@{ */

/// Maximum length of parameter name
#define c11n_MAX_PARAMETER_NAME_LEN 	30

/// Maximum length of module name
#define c11n_MAX_MODULE_NAME_LEN 		25

/// Allow c11n_Type contain 64bit data itself, but not pointers. 1:allow, 0:disable.
#define c11n_64BIT_DATA  0

/** @} */


/** ┌———————————————————————————————————————————————————————————————————————┐
	│		Command line interface compilation configuration				│  
	└———————————————————————————————————————————————————————————————————————┘ */
/** \addtogroup Command_line_interface_compilation_configuration  Command line interface compilation configuration 
  *	@{ */

/// Чувствительность к регистру
#define CLI_REGISTER_SENS	0

/// Максимальное число аргументов с учётом комманды
#define CLI_ARGV_MAX		8

/// Макс. длинна имени комманды
#define CLI_CMD_NAME_SIZE  10

/// Приветствие
#define CLI_GREETING 	"==========================================="NEWLINE \
                        "==== Welcome to SLEDGE Telnet interface ==="NEWLINE \
                        "==========================================="NEWLINE

/// Приглашение коммандной строки
#define CLI_INVITE		"> "

/** @} */



#ifdef __GNUC__
 #define __weak __attribute__((weak))
#endif

#endif /*__SledgeConfig_h*/
