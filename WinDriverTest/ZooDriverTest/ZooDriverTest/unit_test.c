#include "stdafx.h"
#include "unit_test.h"

typedef struct _ZOO_UT_FRAME
{
	ULONG expect;			//	Ԥ�ں������ؽ��
	ULONG argc;				//	����������Ŀǰ���֧��20��������֧���޲���
	PVOID func;				//	Ҫ���Եĺ���
	PVOID *pParamArray;		//	�����������飬ÿ��Ԫ���Ǹ�LPVOID����������������
	PCHAR strFunName;		//	�������֣����߽���������Ψһ��ʶ��������Կգ����ǿ��˾��޷���log����ֱ溯����
}ZOO_UT_FRAME;

ZOO_UT_FRAME g_ZooUtFrame[] = 
{
	{STATUS_SUCCESS, 0, UT_Init, NULL, "ZooTest"}
};

static ULONG _UT_TestCall0(PVOID func);

//	�жϲ����б��Ƿ��쳣
static void _UT_TestParam(ZOO_UT_FRAME *p, ULONG ulCount)
{
	ULONG i;
	for (i = 0; i < ulCount ;i++)
	{
		if (p->argc > 20)
		{
			ZooLogUT("Index %d ������ %s() �����������쳣 : %d \n", i, p->strFunName, p->argc);
			g_ZooUtFrame[i].func = NULL;
			continue;
		}
		if (p->argc != 0 && p->pParamArray == NULL)
		{
			ZooLogUT("Index %d ������ %s() �������б��쳣 : 0x%08X \n", i, p->strFunName, p->pParamArray);
			g_ZooUtFrame[i].func = NULL;
		}
		else if (p->argc == 0 && p->pParamArray != NULL)
		{
			ZooLogUT("Index %d ������ %s() �������б��쳣 : 0x%08X \n", i, p->strFunName, p->pParamArray);
			g_ZooUtFrame[i].func = NULL;
		}
	}
}

//	 �жϺ��������Ƿ�Ϊ��
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
		ZooLogV("UT ��ܳ�ʼ��ʧ��\n");
		return status;
	}
	else
	{
		ZooLogV("UT ��ܳ�ʼ���ɹ�\n");
	}

	status = UT_Start();
	if (!NT_SUCCESS(status))
	{
		ZooLogV("UT �������ʧ��\n");
	}
	else
	{
		ZooLogV("UT ��������ɹ�\n");
	}

	status = UT_Uninit();
	if (!NT_SUCCESS(status))
	{
		ZooLogV("UT �������ʧ��\n");
	}
	else
	{
		ZooLogV("UT ������ٳɹ�\n");
	}

	return status;
}

static ULONG _UT_TestCall0(PVOID func)
{
	typedef ULONG (__stdcall *FPFunction0)(void);
	FPFunction0 pfpFunction = (FPFunction0)func;
	return pfpFunction();
}