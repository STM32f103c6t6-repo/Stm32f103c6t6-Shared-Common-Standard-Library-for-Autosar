/* =====================================================================================================================
 *  File        : LogLevels.h
 *  Layer       : Shared
 *  Purpose     : Definition level of log for all system
 *  Target MCU  : STM32F103C6T6
 *  Note        :
 * ===================================================================================================================*/

#ifndef LOGTAGS_H_
#define LOGTAGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------------------------------------------------
 *  Macro for version
 * -------------------------------------------------------------------------------------------------------------------*/
#define LOG_TAGS_AR_MAJOR_VERSION		(1u)
#define LOG_TAGS_AR_MINOR_VERSION		(0u)
#define LOG_TAGS_AR_PATCH_VERSION		(0u)

#include <stdint.h>

/* ---------------------------------------------------------------------------------------------------------------------
*   TAG List (enum) — arranged by layer for easy reading of logs
*
* 	Naming conventions:
* 	- MCAL_* : MCAL level driver
* 	- ECU_* : ECU Abstraction (Interfaces)
* 	- SRV_* : Services (EcuM, PduR, Com, Det, Logger)
* 	- RTE : Runtime Environment
* 	- APP_* : Application (SWC)
* 	- SYS/BOOT : System/General Boot
*
* 	Note:
* 	- The enum value is stable to be used as an index bit in the mask.
* 	- If a new TAG is needed, add it to the end of the list (keep the old values ​​stable).
* -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	/* System */
	LOGTAG_BOOT = 0,
	LOGTAG_SYS,

	/* MCAL */
	LOGTAG_MCAL_MCU,
	LOGTAG_MCAL_PORT,
	LOGTAG_MCAL_DIO,
	LOGTAG_MCAL_GPT,
	LOGTAG_MCAL_ICU,
	LOGTAG_MCAL_ADC,
	LOGTAG_MCAL_PWM,
	LOGTAG_MCAL_CAN,
	LOGTAG_MCAL_UART,

	/* ECU Abstraction */
	LOGTAG_ECU_PORTIF,
	LOGTAG_ECU_SENSORIF,
	LOGTAG_ECU_ADCIF,
	LOGTAG_ECU_PWMIF,
	LOGTAG_ECU_MOTORIF,
	LOGTAG_ECU_CANIF,
	LOGTAG_ECU_UARTIF,

	/* Services */
	LOGTAG_SRV_ECUM,
	LOGTAG_SRV_PDUR,
	LOGTAG_SRV_COM,
	LOGTAG_SRV_DET,
	LOGTAG_SRV_LOGGER,

	/* RTE */
	LOGTAG_RTE,

	/* Application SWCs */
	LOGTAG_APP_SENSORSUPERVISOR,
	LOGTAG_APP_OBSTACLEDETECTION,
	LOGTAG_APP_PEDALREADER,
	LOGTAG_APP_MOTORCONTROL,


	LOGTAG_COUNT 		// count Tag, always end of this enum
}LogTag_t;

/* ---------------------------------------------------------------------------------------------------------------------
*   Bitmask filter TAG
* -------------------------------------------------------------------------------------------------------------------*/
typedef uint64_t LogTagMask_t;
#define LOG_TAG_BIT(tag)		((LogTagMask_t) 1ULL << (uint64_t)(tag))
#define LOG_TAG_MASK_NONE		((LogTagMask_t)0ULL)
#define LOG_TAG_MASK_ALL		(~(LogTagMask_t)0ULL)

/* Default: enable important TAG + some driver */
#ifndef LOG_TAG_MASK_DEFAULT
#define LOG_TAG_MASK_DEFAULT (      \
      LOG_TAG_BIT(LOGTAG_BOOT)      \
    | LOG_TAG_BIT(LOGTAG_SYS)       \
    | LOG_TAG_BIT(LOGTAG_SRV_ECUM)  \
    | LOG_TAG_BIT(LOGTAG_SRV_DET)   \
    | LOG_TAG_BIT(LOGTAG_SRV_LOGGER)\
    | LOG_TAG_BIT(LOGTAG_MCAL_CAN)  \
    | LOG_TAG_BIT(LOGTAG_MCAL_UART) \
    | LOG_TAG_BIT(LOGTAG_ECU_CANIF) \
    | LOG_TAG_BIT(LOGTAG_ECU_UARTIF)\
)
#endif

/*Macro checks if TAG is enabled according to current mask*/
#define LOG_TAG_ENABLE(_mask_,_tag_)	( ((LogTagMask_t)(_mask_) & LOG_TAG_BIT(_tag_)) != 0ULL )

/* ---------------------------------------------------------------------------------------------------------------------
*   Helper: ECU Role -> string
*   	- put in compile defines of app.
* -------------------------------------------------------------------------------------------------------------------*/
#ifndef ECU_ROLE
#define ECU_ROLE	ECU_UNKNOWN
#endif

#define ECU_SENSOR	1
#define ECU_MOTOR	2
#define ECU_UNKNOW	0

static inline const char* LOG_EcuRoleString(void)
{
#if 	(ECU_ROLE == ECU_SENSOR)
	return "SENSOR";
#elif	(ECU_ROLE == ECU_MOTOR)
	return "MOTOR";
#else
	return "UNKNOWN";
#endif
}

/* ---------------------------------------------------------------------------------------------------------------------
*   Helper: TAG -> full string
* -------------------------------------------------------------------------------------------------------------------*/
static inline const char* LOG_TagToString(LogTag_t tag)
{
	switch(tag)
	{
		case LOGTAG_BOOT:					return "BOOT";
		case LOGTAG_SYS:					return "SYS";

		case LOGTAG_MCAL_MCU:				return "MCAL.MCU";
		case LOGTAG_MCAL_PORT:				return "MCAL.PORT";
		case LOGTAG_MCAL_DIO: 				return "MCAL.DIO";
		case LOGTAG_MCAL_GPT:				return "MCAL.GPT";
		case LOGTAG_MCAL_ICU:				return "MCAL.ICU";
		case LOGTAG_MCAL_ADC:				return "MCAL.ADC";
		case LOGTAG_MCAL_PWM:				return "MCAL.PWM";
		case LOGTAG_MCAL_CAN:				return "MCAL.CAN";
		case LOGTAG_MCAL_UART:				return "MCAL.UART";

		case LOGTAG_ECU_PORTIF:				return "ECU.PortIf";
		case LOGTAG_ECU_SENSORIF:			return "ECU.SensorIf";
		case LOGTAG_ECU_ADCIF:				return "ECU.AdcIf";
		case LOGTAG_ECU_PWMIF:				return "ECU.PwmIf";
		case LOGTAG_ECU_MOTORIF:			return "ECU.MotorIf";
		case LOGTAG_ECU_CANIF:				return "ECU.CanIf";
		case LOGTAG_ECU_UARTIF:				return "ECU.UartIf";

		case LOGTAG_SRV_ECUM:				return "SRV.ECUM";
		case LOGTAG_SRV_PDUR:				return "SRV.Pdur";
		case LOGTAG_SRV_COM:				return "SRV.Com";
		case LOGTAG_SRV_DET:				return "SRV.Det";
		case LOGTAG_SRV_LOGGER:				return "SRV.Logger";

		case LOGTAG_RTE:					return "RTE";

		case LOGTAG_APP_SENSORSUPERVISOR:	return "APP.SensorSupervisor";
		case LOGTAG_APP_OBSTACLEDETECTION:	return "APP.ObstacleDetection";
		case LOGTAG_APP_PEDALREADER:		return "APP.PedalReader";
		case LOGTAG_APP_MOTORCONTROL:		return "APP.MotorControl";

		default:							return "UNKNOWN";
	}
}

/* ---------------------------------------------------------------------------------------------------------------------
*   Helper: TAG -> 3-4 character abbreviation
* -------------------------------------------------------------------------------------------------------------------*/

static inline const char* LOG_TagAbbrev(LogTag_t tag)
{
	switch(tag)
	{
		case LOGTAG_BOOT:					return "BOOT";
		case LOGTAG_SYS:					return "SYS";

		case LOGTAG_MCAL_MCU:				return "M.MCU";
		case LOGTAG_MCAL_PORT:				return "M.PRT";
		case LOGTAG_MCAL_DIO: 				return "M.DIO";
		case LOGTAG_MCAL_GPT:				return "M.GPT";
		case LOGTAG_MCAL_ICU:				return "M.ICU";
		case LOGTAG_MCAL_ADC:				return "M.ADC";
		case LOGTAG_MCAL_PWM:				return "M.PWM";
		case LOGTAG_MCAL_CAN:				return "M.CAN";
		case LOGTAG_MCAL_UART:				return "M.UAR";

		case LOGTAG_ECU_PORTIF:				return "E.PRT";
		case LOGTAG_ECU_SENSORIF:			return "E.SNS";
		case LOGTAG_ECU_ADCIF:				return "E.ADC";
		case LOGTAG_ECU_PWMIF:				return "E.PWM";
		case LOGTAG_ECU_MOTORIF:			return "E.MOT";
		case LOGTAG_ECU_CANIF:				return "E.CIF";
		case LOGTAG_ECU_UARTIF:				return "E.UIF";

		case LOGTAG_SRV_ECUM:				return "SRV.ECUM";
		case LOGTAG_SRV_PDUR:				return "SRV.Pdur";
		case LOGTAG_SRV_COM:				return "SRV.Com";
		case LOGTAG_SRV_DET:				return "SRV.Det";
		case LOGTAG_SRV_LOGGER:				return "SRV.Logger";

		case LOGTAG_RTE:					return "RTE";

		case LOGTAG_APP_SENSORSUPERVISOR:	return "A.SSV";
		case LOGTAG_APP_OBSTACLEDETECTION:	return "A.OBS";
		case LOGTAG_APP_PEDALREADER:		return "A.PDL";
		case LOGTAG_APP_MOTORCONTROL:		return "A.MOT";

		default:							return "UNk";
	}
}

#ifdef __cplusplus
}
#endif

#endif /* LOGTAGS_H_ */
