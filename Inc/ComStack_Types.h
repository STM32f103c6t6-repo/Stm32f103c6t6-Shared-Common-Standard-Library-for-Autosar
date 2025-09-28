/* =====================================================================================================================
 *  File        : ComStack_Types.h
 *  Layer       : Shared
 *  Purpose     : Definition data structure for Communication Stack
 *                 - Used for MCAL (Can), ECU Abstraction (CanIf/UartIf), Services (PduR/Com/Logger/Det), RTE, Application.
 *  Target MCU  : STM32F103C6T6
 *  Note        :
 * ===================================================================================================================*/

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------------------------------------------------
 *  Macro for version
 * -------------------------------------------------------------------------------------------------------------------*/
#define COMSTACK_TYPES_AR_MAJOR_VERSION 	(1U)
#define COMSTACK_TYPES_AR_MINOR_VERSION 	(0U)
#define COMSTACK_TYPES_AR_PATCH_VERSION 	(0U)


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------------------------------------------------------
 *  Value function for API
 * -------------------------------------------------------------------------------------------------------------------*/
#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

typedef uint8_t Std_ReturnType ; /*Return for API */
#ifndef E_OK
#define E_OK 		((Std_ReturnType)0x00u) /*Success*/
#endif
#ifndef E_NOT_OK
#define E_NOT_OK	((Std_ReturnType)0x01u) /*Error*/

/* ---------------------------------------------------------------------------------------------------------------------
 *  NetworkHandleType
 *  - Detect network channel.
 *  - used in Servic/ECU abstraction.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef uint8_t NetworkHandleType;

/* ---------------------------------------------------------------------------------------------------------------------
 *  Define PDU (Protocol Data Unit)
 *  - PduIDtype: ID logic for each PDU.
 *  - PduLengthType: Length of payload (Byte unit).
 *  - PduInfotype: data buffer (address + length + metadata).
 *
 *  Application :
 *  - Services/Com: pack/unpack signal <-> PDU.
 *  - Services/PduR: routing PDU.
 *  - ECU Abstraction/CanIf & UartIf: send/receiver buffer.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef uint16_t PduIdType;
typedef uint16_t PduLengthType;

struct PduInfoType {
	uint8_t*		SduDataPtr;		/* Pointer of payload (Tx or Rx).*/
	PduLengthType	SduLength;		/* Số byte hợp lệ trong payload.*/
	uint8_t*		MetaDataPtr;	/* Metadata. */
};

/* ---------------------------------------------------------------------------------------------------------------------
 *  Buffer request result for Transport Protocol (TP)
 *  - When PduR/Com/Tp need buffer, api return this state.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	BUFREQ_OK = 0,			/* Buffer Ready.*/
	BUFREQ_E_NOT_OK,		/* Buffer not ok. */
	BUFREQ_E_BUSY,			/* busy, try again.*/
	BUFREQ_E_OVFL			/* not enough capacity. */
} BufReq_ReturnType;

/* ---------------------------------------------------------------------------------------------------------------------
 *  TpDataStateType & RetryInfoType
 *  - Describe data state and retry information.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	TP_DATACONF = 0,	/* Data has done confirm. */
	TP_DATARETRY,		/* Need to send data again. */
	TP_CONFPENDING		/* Wait confirm pre-data. */
} TpDataStateType;

struct RetryInfoType
{
	TpDataStateType TpDataState;	/* State of pre-Data. */
	PduLengthType	TxTpDataCnt;	/* Number of bytes remaining to send (when retrying). */
};

/* ---------------------------------------------------------------------------------------------------------------------
 *  NotifResultType
 *  - Result notification for Tx/Rx event has completed or error in Tp/Com.
 *  - use in callback notify to Service/Application .
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	NTFRSLT_OK = 0,	 		// Success.
	NTFRSLT_E_NOT_OK,		// Common issue.
	NTFRSLT_E_TIMEOUT_A,	// Timeout phase A.
	NTFRSLT_E_TIMEOUT_BS,	// Timeout block size.
	NTFRSLT_E_TIMEOUT_CR,	// Timeout wait accept.
	NTFRSLT_E_WRONG_SN,		// Error sequence number.
	NTFRSLT_E_PROTOCOL,		// Protocol error.
	NTFRSLT_E_CANCELATION,	// Cancel by request.
	NTFRSLT_E_NO_BUFFER		// Buffer not enough capacity.
};

/* ---------------------------------------------------------------------------------------------------------------------
 *  CAN_IDType
 *  - Describe CAN ID with IDE:
 *  	bit31: 1 = Extended ID (29 bits), 0 = standard ID (11 bits).
 *  	bit28...0 : ID value.
 *  - provide macro inline.
 *  - use for ECU Abtraction/Canif and Services/Com/PduR.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef uint32_t CAN_IdType;

#define CAN_ID_FLAG_IDE		(1u << 31)		//IDE flag.
#define CAN_STD_ID_MASK		(0x7FFu)		//mask 11 bits.
#define CAN_EXT_ID_MASK		(0x1FFFFFFFu)	//mask 29 bits.

static inline CAN_IdType CAN_MAKE_STD_ID(uint16_t stdId)
{
	return ((CAN_IdType)(extId & CAN_STD_ID_MASK));
}

static inline CAN_IdType CAN_MAKE_EXT_ID(uint16_t stdId)
{
	return ((CAN_IdType)(extId & CAN_EXT_ID_MASK));
}

static inline bool CAN_ID_IS_EXT(CAN_IdType id)
{
	return((id & CAN_ID_FLAG_IDE) != 0u);
}

static inline uint32_t CAN_ID_GET_RAW(CAN_IdType id)
{
	return(CAN_ID_IS_EXT(id)) ? (id & CAN_EXT_ID_MASK) : (id & CAN_STD_ID_MASK);
}

/* ---------------------------------------------------------------------------------------------------------------------
 *  ComStack_TxPriorityType
 *  - priority of transmission.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	COMSTACK_TX_PRIO_LOW = 0,
	COMSTACK_TX_PRIO_HIGH
} ComStack_TxPriorityType;

/* ---------------------------------------------------------------------------------------------------------------------
 *  ComStack_ControllerStateType
 *  - Controller state communication.
 *  - Use by Canif/UartIf/EcuM for manage switch state START/STOP/SLEEP.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	COMSTACK_CONTROLLER_UNINIT =0, 		// Not started yet.
	COMSTACK_CONTROLLER_STOPPED,		// Stop.
	COMSTACK_CONTROLLER_STARTED,		// action.
	COMSTACK_CONTROLLER_SLEEP			// sleep.
}ComStack_ControllerStateType;

/* ---------------------------------------------------------------------------------------------------------------------
 *  PduR_RoutingResultType
 *  - result of PDU (Pdur) for notify App/Services.
 * -------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
	PDUR_ROUTING_OK =0,
	PDUR_ROUTING_E_NOT_OK
}PduR_RoutingResultType;

#ifdef __cplusplus
}
#endif

#endif /* COMSTACK_TYPES_H_ */
