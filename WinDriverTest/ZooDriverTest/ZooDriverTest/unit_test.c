#include "stdafx.h"
#include "unit_test.h"

extern ZOO_UT_FRAME g_ZooUtFrame[];
extern ULONG g_ulCount;


static ULONG _UT_TestCall0(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall1(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall2(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall3(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall4(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall5(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall6(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall7(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall8(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall9(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall10(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall11(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall12(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall13(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall14(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall15(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall16(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall17(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall18(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall19(PVOID func, PVOID *pParamArray);
static ULONG _UT_TestCall20(PVOID func, PVOID *pParamArray);

typedef ULONG (*_UT_TestCall_Array)(PVOID func, PVOID *pParamArray);
static _UT_TestCall_Array g_UtCallArray[21] = 
{
	_UT_TestCall0,
	_UT_TestCall1,
	_UT_TestCall2,
	_UT_TestCall3,
	_UT_TestCall4,
	_UT_TestCall5,
	_UT_TestCall6,
	_UT_TestCall7,
	_UT_TestCall8,
	_UT_TestCall9,
	_UT_TestCall10,
	_UT_TestCall11,
	_UT_TestCall12,
	_UT_TestCall13,
	_UT_TestCall14,
	_UT_TestCall15,
	_UT_TestCall16,
	_UT_TestCall17,
	_UT_TestCall18,
	_UT_TestCall19,
	_UT_TestCall20
};


//	判断参数列表是否异常
static void _UT_TestParam(ZOO_UT_FRAME *p, ULONG ulCount)
{
	ULONG i;
	for (i = 0; i < ulCount ;i++)
	{
		if (p->argc > 20)
		{
			ZooLogUT("Index %d ，函数 %s() ，参数个数异常 : %d \n", i, p->strFunName, p->argc);
			g_ZooUtFrame[i].func = NULL;
			continue;
		}
		if (p->argc != 0 && p->pParamArray == NULL)
		{
			ZooLogUT("Index %d ，函数 %s() ，参数列表异常 : 0x%08X \n", i, p->strFunName, p->pParamArray);
			g_ZooUtFrame[i].func = NULL;
		}
		else if (p->argc == 0 && p->pParamArray != NULL)
		{
			ZooLogUT("Index %d ，函数 %s() ，参数列表异常 : 0x%08X \n", i, p->strFunName, p->pParamArray);
			g_ZooUtFrame[i].func = NULL;
		}
	}
}

//	 判断函数名字是否为空
static void _UT_TestFunName(ZOO_UT_FRAME *p, ULONG ulCount)
{
	ULONG i;
	for (i = 0; i < ulCount ;i++)
	{
		if (p[i].strFunName == NULL)
		{
			p[i].strFunName = "_zoo_unknow_name";
		}
	}
}

static ULONG _UT_TestCall(PVOID func, ULONG argc, PVOID *pParamArray)
{
	if (argc > 20)
	{
		return -1;
	}
	return g_UtCallArray[argc](func, pParamArray);
}

NTSTATUS UT_Init()
{
	return STATUS_SUCCESS;
}

NTSTATUS UT_Start()
{
	ULONG ulCount = g_ulCount;
	ZOO_UT_FRAME *utArray = g_ZooUtFrame;
	ULONG i;
	ZOO_UT_FRAME *p;
	ULONG ulRet;

	_UT_TestFunName(g_ZooUtFrame, ulCount);
	_UT_TestParam(g_ZooUtFrame, ulCount);

	for (i = 0; i < ulCount ;i++)
	{
		p = &utArray[i];
		if (p->func == NULL)
		{
			continue;
		}
		ulRet = 0;
		ulRet = _UT_TestCall(p->func, p->argc, p->pParamArray);

		if (ulRet == p->expect)
		{
			ZooLogUT("UT Success : fun = %s , argc = %d , index = %d \n", p->strFunName, p->argc, i);
		}
		else
		{
			ZooLogUT("UT Error : fun = %s , argc = %d , return = %u, expect = %u, index = %d\n", p->strFunName, p->argc, ulRet, p->expect, i);
		}
	}

	return STATUS_SUCCESS;
}

NTSTATUS UT_Uninit()
{
	return STATUS_SUCCESS;
}

NTSTATUS RunUT()
{
	NTSTATUS status;
	status = UT_Init();
	if (!NT_SUCCESS(status))
	{
		ZooLogV("UT 框架初始化失败\n");
		return status;
	}
	else
	{
		ZooLogV("UT 框架初始化成功\n");
	}

	status = UT_Start();
	if (!NT_SUCCESS(status))
	{
		ZooLogV("UT 框架启动失败\n");
	}
	else
	{
		ZooLogV("UT 框架启动成功\n");
	}

	status = UT_Uninit();
	if (!NT_SUCCESS(status))
	{
		ZooLogV("UT 框架销毁失败\n");
	}
	else
	{
		ZooLogV("UT 框架销毁成功\n");
	}

	return status;
}

static ULONG _UT_TestCall0(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(void);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction();
}

static ULONG _UT_TestCall1(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0]);
}

static ULONG _UT_TestCall2(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1]);
}

static ULONG _UT_TestCall3(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2]);
}

static ULONG _UT_TestCall4(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3]);
}

static ULONG _UT_TestCall5(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4]);
}

static ULONG _UT_TestCall6(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5]);
}

static ULONG _UT_TestCall7(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6]);
}

static ULONG _UT_TestCall8(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7]);
}

static ULONG _UT_TestCall9(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8]);
}

static ULONG _UT_TestCall10(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9]);
}

static ULONG _UT_TestCall11(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10]);
}

static ULONG _UT_TestCall12(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11]);
}

static ULONG _UT_TestCall13(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12]);
}

static ULONG _UT_TestCall14(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13]);
}

static ULONG _UT_TestCall15(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14]);
}

static ULONG _UT_TestCall16(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14],
		pParamArray[15]);
}

static ULONG _UT_TestCall17(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14],
		pParamArray[15],pParamArray[16]);
}

static ULONG _UT_TestCall18(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14],
		pParamArray[15],pParamArray[16],pParamArray[17]);
}

static ULONG _UT_TestCall19(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14],
		pParamArray[15],pParamArray[16],pParamArray[17],pParamArray[18]);
}

static ULONG _UT_TestCall20(PVOID func, PVOID *pParamArray)
{
	typedef ULONG (*FPFunction0)(PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,
		PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID,PVOID);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction( pParamArray[0], pParamArray[1], pParamArray[2], pParamArray[3], pParamArray[4],
		pParamArray[5], pParamArray[6], pParamArray[7], pParamArray[8], pParamArray[9],
		pParamArray[10],pParamArray[11],pParamArray[12],pParamArray[13],pParamArray[14],
		pParamArray[15],pParamArray[16],pParamArray[17],pParamArray[18],pParamArray[19]);
}