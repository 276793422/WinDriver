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