/*
 *
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* =====================================================================================================================
 *  Version
 * ===================================================================================================================*/
#define STD_AR_RELEASE_MAJOR_VERSION			(1u)
#define STD_AR_RELEASE_MINOR_VERSION			(0u)
#define STD_AR_RELEASE_PATCH_VERSION			(0u)

/* =====================================================================================================================
 *  Compiler
 * ===================================================================================================================*/
#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

/* =====================================================================================================================
 *  Basic types
 * ===================================================================================================================*/
typedef unsigned char 				uint8;
typedef   signed char				sint8;
typedef unsigned short				uint16;
typedef   signed short				sint16;
typedef unsigned long				uint32;
typedef   signed long				sint32;
typedef unsigned long long			uint64;
typedef   signed long long			sint64;

typedef float						float32;
typedef double						float64;

/* Boolean */
typedef uint8 bool;

#ifndef boolean
#define boolean	(bool)
#endif

#ifndef TRUE
#define TRUE	((bool)1u)
#endif
#ifndef FALSE
#define FALSE	((bool)0u)
#endif

/* Std macros */
#define STD_HIGH	(1u)
#define STD_LOW		(0u)
#define STD_ACTIVE	(1u)
#define STD_IDLE	(0u)
#define STD_ON		(1u)
#define STD_OFF		(0u)

/* Version info struct*/
typedef struct {
	uint16 		vendorID;
	uint16 		moduleID;
	uint8 		sw_major_version;
	uint8 		sw_minor_version;
	uint8 		sw_patch_version;
} Std_VersionInfoType;


#ifdef __cplusplus
}
#endif

#endif /* STD_TYPES_H_ */
