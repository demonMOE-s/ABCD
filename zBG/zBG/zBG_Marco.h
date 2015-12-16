#ifndef ___$zBG__MARCO_
#define ___$zBG__MARCO_

#ifdef ZBG_EXPORTS
#define ZBG_API __declspec(dllexport)
#else
#define ZBG_API __declspec(dllimport)
#endif

typedef char c8;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;
typedef double d64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int bool_;
typedef signed long long s64;
typedef unsigned long long u64;

#define STATIC static 
#define STDC_CALL __cdecl 
#define STDWIN32_CALL __stdcall
#define FORCEINLINE __forceinline
#define FOR	for 
#define WHILE while 
#define CONST const 
#define DO do 
#define IF if 
#define RETURN return
#define NAKED __declspec(naked)
#define ALIGN __declspec(align(16))
#define EXTERN extern 

#endif 