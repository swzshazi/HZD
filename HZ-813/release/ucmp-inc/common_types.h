#ifndef _HZTYPES_H
#define _HZTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATA_TYPES
#define DATA_TYPES
typedef signed char     int8;
typedef signed short	int16;
typedef unsigned char   Uint8;
typedef unsigned short  Uint16;
#ifdef  OMAP_DSP
typedef int			    int32;
typedef unsigned int	Uint32;
#else
typedef long			int32;
typedef unsigned long	Uint32;
#endif
typedef float			float32;
typedef long long       int64;
typedef unsigned long long Uint64;
#endif

enum VAR_TYPES{
    T_SOE,
    T_BIT,
    T_INT8,
    T_INT16,
    T_INT32,
    T_FLOAT,
    T_STR,
    T_INT32_L,
    T_FLOAT_L,
    T_STR_L,
    T_COMPONENT,
    T_NET,
    T_NONE,
    T_BIT_L,
    T_BLOCK,    
	T_UINT8,
	T_UINT16, 
	T_UINT32,
	T_SOE_T
	//待补充完善
};

	
enum   VAR_LEVELS{
	LEVEL0,	
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4
	};

#ifdef __cplusplus
}
#endif
#endif
