// Author: Zoo
#pragma once
#include "unit_test.h"

//	UT FILE


typedef struct _ZOO_UT_FRAME
{
	ULONG expect;			//	预期函数返回结果
	ULONG argc;				//	参数个数，目前最大支持20个，最少支持无参数
	PVOID func;				//	要测试的函数
	PVOID *pParamArray;		//	函数参数数组，每个元素是个LPVOID，用来给函数传参
	PCHAR strFunName;		//	函数名字，或者叫做函数的唯一标识，这个可以空，但是空了就无法在log里面分辨函数了
}ZOO_UT_FRAME;

typedef void (*FZooUtFunc)(void);

#define UT_FRAME_MAPPING_BEGIN				ZOO_UT_FRAME g_ZooUtFrame[] = {
#define UT_FRAME_MAPPING_MEMBER(_EXPECT, _ARGC, _FUNCTION, _PARAM, _FUNNAME)	{_EXPECT, _ARGC, _FUNCTION, _PARAM, _FUNNAME},
#define UT_FRAME_MAPPING_END				};ULONG g_ulUtFrameCount = sizeof(g_ZooUtFrame) / sizeof(g_ZooUtFrame[0]);

#define UT_FRAME_INIT_BEGIN					FZooUtFunc g_ZooUtInit[] = {
#define UT_FRAME_INIT_MEMBER(_FUNCTION)		(_FUNCTION),
#define UT_FRAME_INIT_END					};ULONG g_ulUtInitCount = sizeof(g_ZooUtInit) / sizeof(g_ZooUtInit[0]);

#define UT_FRAME_UNINIT_BEGIN				FZooUtFunc g_ZooUtUnInit[] = {
#define UT_FRAME_UNINIT_MEMBER(_FUNCTION)	(_FUNCTION),
#define UT_FRAME_UNINIT_END					};ULONG g_ulUtUninitCount = sizeof(g_ZooUtUnInit) / sizeof(g_ZooUtUnInit[0]);



NTSTATUS RunUT();