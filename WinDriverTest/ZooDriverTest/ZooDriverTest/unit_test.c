#include "stdafx.h"
#include "unit_test.h"

typedef struct _ZOO_UT_FRAME
{
	ULONG expect;			//	预期函数返回结果
	ULONG argc;				//	参数个数，目前最大支持20个，最少支持无参数
	PVOID func;				//	要测试的函数
	PVOID *pParamArray;		//	函数参数数组，每个元素是个LPVOID，用来给函数传参
	PCHAR strFunName;		//	函数名字，或者叫做函数的唯一标识，这个可以空，但是空了就无法在log里面分辨函数了
}ZOO_UT_FRAME;

ZOO_UT_FRAME g_ZooUtFrame[] = 
{
	{STATUS_SUCCESS, 0, UT_Init, NULL, "ZooTest"}
};

static ULONG _UT_TestCall0(PVOID func);

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
		if (p->strFunName == NULL)
		{
			p->strFunName = "_zoo_unknow_name";
		}
	}
}

static ULONG _UT_TestCall(PVOID func, ULONG argc, PVOID *pParamArray)
{
	ULONG ulRet = 0;
	switch (argc)
	{
	case 1:
		ulRet = _UT_TestCall0(func);
		break;
	case 2:
		break;
	default:
		ulRet = -1;
		break;
	}
	return ulRet;
}

NTSTATUS UT_Init()
{
	return STATUS_SUCCESS;
}

NTSTATUS UT_Start()
{
	ULONG ulCount = sizeof(g_ZooUtFrame) / sizeof(g_ZooUtFrame[0]);
	ULONG i;
	ZOO_UT_FRAME *p;
	ULONG ulRet;

	_UT_TestFunName(g_ZooUtFrame, ulCount);
	_UT_TestParam(g_ZooUtFrame, ulCount);

	for (i = 0; i < ulCount ;i++)
	{
		p = &g_ZooUtFrame[i];
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

static ULONG _UT_TestCall0(PVOID func)
{
	typedef ULONG (__stdcall *FPFunction0)(void);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction();
}