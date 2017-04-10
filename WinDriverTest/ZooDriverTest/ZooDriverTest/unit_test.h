// Author: Zoo
#pragma once
#include "unit_test.h"

//	UT FILE


typedef struct _ZOO_UT_FRAME
{
	ULONG expect;			//	Ԥ�ں������ؽ��
	ULONG argc;				//	����������Ŀǰ���֧��20��������֧���޲���
	PVOID func;				//	Ҫ���Եĺ���
	PVOID *pParamArray;		//	�����������飬ÿ��Ԫ���Ǹ�LPVOID����������������
	PCHAR strFunName;		//	�������֣����߽���������Ψһ��ʶ��������Կգ����ǿ��˾��޷���log����ֱ溯����
}ZOO_UT_FRAME;

typedef void (*FZooUtFunc)(void);

NTSTATUS RunUT();

