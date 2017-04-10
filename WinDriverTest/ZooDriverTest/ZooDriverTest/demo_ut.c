#include "stdafx.h"

NTSTATUS AVLUT_Init();

PVOID pParam5[5] = {1, 2, 3, 4, 5};
NTSTATUS AVLUT_Init5();

ZOO_UT_FRAME g_ZooUtFrame[] = 
{
	{STATUS_SUCCESS, 0, AVLUT_Init, NULL, "AVLUT_Init"},
	{STATUS_SUCCESS, 5, AVLUT_Init5, pParam5, "AVLUT_Init5"}
};

ULONG g_ulCount = sizeof(g_ZooUtFrame) / sizeof(g_ZooUtFrame[0]);


NTSTATUS AVLUT_Init()
{

	ZooLogV("UT in Run\n");
	return STATUS_SUCCESS;
}

NTSTATUS AVLUT_Init5(PVOID p1, PVOID p2, PVOID p3, PVOID p4, PVOID p5)
{

	ZooLogV("UT 5 in Run, %d %d %d %d %d \n", p1, p2, p3, p4, p5);
	return STATUS_SUCCESS;
}