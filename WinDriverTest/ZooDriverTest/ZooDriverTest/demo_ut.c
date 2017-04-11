#include "stdafx.h"

NTSTATUS UT_Param0();

PVOID pParam5[5] = {1, 2, 3, 4, 5};
NTSTATUS UT_Param5();

void UT_Init();

void UT_Uninit();

UT_FRAME_MAPPING_BEGIN
	UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 0, UT_Param0, NULL, "UT_Param0")
	UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 5, UT_Param5, pParam5, "UT_Param5")
UT_FRAME_MAPPING_END


NTSTATUS UT_Param0()
{
	ZooLogUT("UT_Param0 in Run\n");
	return STATUS_SUCCESS;
}

NTSTATUS UT_Param5(PVOID p1, PVOID p2, PVOID p3, PVOID p4, PVOID p5)
{
	ZooLogUT("UT_Param5 in Run, %d %d %d %d %d \n", p1, p2, p3, p4, p5);
	return STATUS_SUCCESS;
}

void UT_Init()
{
	ZooLogUT("UT_Init in Run\n");
}

void UT_Uninit()
{
	ZooLogUT("UT_Uninit in Run\n");
}