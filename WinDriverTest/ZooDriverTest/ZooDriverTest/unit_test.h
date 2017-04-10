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

NTSTATUS RunUT();

