/* =====================================================================================================================
 *  File        : LogLevels.h
 *  Layer       : Shared
 *  Purpose     : Definition level of log for all system
 *  Target MCU  : STM32F103C6T6
 *  Note        :
 * ===================================================================================================================*/
#ifndef LOGLEVELS_H_
#define LOGLEVELS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------------------------------------------------
 *  Macro for version
 * -------------------------------------------------------------------------------------------------------------------*/
#define LOG_LEVELS_AR_MAJOR_VERSION		(1u)
#define LOG_LEVELS_AR_MINOR_VERSION		(0u)
#define LOG_LEVELS_AR_PATCH_VERSION		(0u)

/* ---------------------------------------------------------------------------------------------------------------------
 *  level of log :
 *  	- LOG_OFF 	: OFF log.
 *  	- LOG_ERROR : when error occur.
 *  	- LOG_WARN	: Warning, system can self-healing.
 *  	- LOG_INFO	: state information.
 *  	- LOG_DEBUG : Log clearly.
 *  	- LOG_TRACE :
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	LOG_OFF = 0,
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_TRACE
}LogLevel_t;

/* ---------------------------------------------------------------------------------------------------------------------
 *  level of log default for system:
 *  - it can override by compiler LOG_LEVEL_DEFAULT =  xxx .
 * -------------------------------------------------------------------------------------------------------------------*/
#ifndef LOG_LEVEL_DEFAULT
#define LOG_LEVEL_DEFAULT		LOG_DEBUG
#endif

/* ---------------------------------------------------------------------------------------------------------------------
 *  Option to enable/disable global logging
 *  - ENABLE_UART_LOG is recommended to be declared in the app project (Preprocessor Defines).
 * -------------------------------------------------------------------------------------------------------------------*/
#ifndef ENABLE_UART_LOG
#define ENABLE_UART_LOG			(1)
#endif

/* ---------------------------------------------------------------------------------------------------------------------
 *  Helper: convert log -> string
 * -------------------------------------------------------------------------------------------------------------------*/
static inline const char* LOG_LevelToString(LogLevel_t lvl)
{
	switch(lvl)
	{
		case LOG_ERROR: return "ERROR";
		case LOG_WARN:	return "WARN";
		case LOG_INFO:	return "INFO";
		case LOG_DEBUG: return "DEBUG";
		case LOG_TRACE: return "TRACE";
		case LOG_OFF:
		default:		return "OFF";
	}
}

/* ---------------------------------------------------------------------------------------------------------------------
 *  Macro compare log level
 *  - LOG_LEVEL_ENABLE(lvl): return true if  lvl <= LOG_LEVEL_DEFAULT
 * -------------------------------------------------------------------------------------------------------------------*/
#define LOG_LEVEL_ENABLE(_lvl)		((_lvl) <= LOG_LEVEL_DEFAULT)

/* ---------------------------------------------------------------------------------------------------------------------
 *  One character labels for log brevity: E/W/I/D/T
 * -------------------------------------------------------------------------------------------------------------------*/
static inline char LOG_LeveChar(LogLevel_t lvl)
{
	switch(lvl)
	{
		case LOG_ERROR: return "E";
		case LOG_WARN:	return "W";
		case LOG_INFO:	return "I";
		case LOG_DEBUG: return "D";
		case LOG_TRACE: return "T";
		case LOG_OFF:
		default:		return "O";
	}
}


#ifdef __cplusplus
}
#endif

#endif /* LOGLEVELS_H_ */
