#include "stdafx.h"

#include "avltable.h"

NTSTATUS UT_Param0();


//UT_FRAME_MAPPING_BEGIN
//UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 0, UT_Param0, NULL, "UT_Param0")
//UT_FRAME_MAPPING_END

typedef struct 
{
	char buf[260];
	char subbuf[128];
	ULONG u1;
	ULONG u2;
	ULONG u3;
	ULONG u4;
}INFO;


//	参数2和参数3的类型是相同的
RTL_GENERIC_COMPARE_RESULTS AvlConpare(struct _ZOO_GENERIC_TABLE *Table, PVOID FirstStruct, PVOID SecondStruct)
{
	INFO *p1 = FirstStruct;
	INFO *p2 = SecondStruct;
	int n = strcmp(p1->buf, p2->buf);
	ZooLogDebug("AVL tree AvlConpare: p1 = %s , p2 = %s \n", p1->buf, p2->buf);
	if (n == 0)
	{
		return GenericEqual;
	}
	else if (n > 0)
	{
		return GenericGreaterThan;
	}
	else if (n < 0)
	{
		return GenericLessThan;
	}
	return GenericEqual;
}

PVOID AvlAlloc(struct _ZOO_GENERIC_TABLE *Table, CLONG ByteSize)
{
	PVOID p = ExAllocatePoolWithTag(PagedPool, ByteSize, 'AVLT');
	ZooLogDebug("AVL tree : AvlAlloc : %d , PVOID = 0x%08X\n" , ByteSize, p);
	return p;
}

VOID AvlFree(struct _ZOO_GENERIC_TABLE *Table, PVOID Buffer)
{
	ZooLogDebug("AVL tree : PVOID : 0x%08X\n" , Buffer);
	ExFreePoolWithTag(Buffer, 'AVLT');
}

NTSTATUS UT_Param0()
{
	INFO info;

	BOOLEAN b1 = FALSE;
	INFO p1;
	PVOID pt1 = NULL;

	BOOLEAN b2 = FALSE;
	INFO p2;
	PVOID pt2 = NULL;

	INFO p3;
	PVOID pt3 = NULL;
	ZOO_GENERIC_TABLE Table;

	ZooInitializeGenericTable(&Table, AvlConpare, AvlAlloc, AvlFree, NULL);
	ZooLogDebug("AVL tree 初始化成功\n");

	strcpy(p1.buf, "111111");
	strcpy(p1.subbuf, "1111111");
	ZooInsertElementGenericTable(&Table, &p1, sizeof(p1), &b1);
	if (b1)
	{
		ZooLogDebug("AVL tree b1 插入成功\n");
	}
	else
	{
		ZooLogDebug("AVL tree b1 插入失败\n");
	}
	strcpy(p2.buf, "222222");
	strcpy(p2.subbuf, "2222222");
	ZooInsertElementGenericTable(&Table, &p2, sizeof(p2), &b2);
	if (b2)
	{
		ZooLogDebug("AVL tree b2 插入成功\n");
	}
	else
	{
		ZooLogDebug("AVL tree b2 插入失败\n");
	}

	pt1 = ZooLookupElementGenericTable(&Table, &p1);
	ZooLogDebug("AVL tree pt1 查找结束 : 0x%08X\n", pt1);

	pt2 = ZooLookupElementGenericTable(&Table, &p2);
	ZooLogDebug("AVL tree pt2 查找结束 : 0x%08X\n", pt2);

	strcpy(p3.buf, "333333");
	strcpy(p3.subbuf, "3333333");
	pt3 = ZooLookupElementGenericTable(&Table, &p3);
	ZooLogDebug("AVL tree pt3 查找结束 : 0x%08X\n", pt3);

	ZooLogDebug("ZooNumberGenericTableElements = %d \n", ZooNumberGenericTableElements(&Table));

	if (ZooDeleteElementGenericTable(&Table, &p1))
	{
		ZooLogDebug("AVL tree b1 删除成功\n");
	}
	else
	{
		ZooLogDebug("AVL tree b1 删除失败\n");
	}
	if (ZooDeleteElementGenericTable(&Table, &p2))
	{
		ZooLogDebug("AVL tree b2 删除成功\n");
	}
	else
	{
		ZooLogDebug("AVL tree b2 删除失败\n");
	}
	if (ZooDeleteElementGenericTable(&Table, &p3))
	{
		ZooLogDebug("AVL tree b3 删除成功\n");
	}
	else
	{
		ZooLogDebug("AVL tree b3 删除失败\n");
	}
}



ZOO_GENERIC_TABLE Table;
PVOID pa1[5] = {&Table, AvlConpare, AvlAlloc, AvlFree, NULL};

BOOLEAN b1 = FALSE;
INFO p1 = {"111111", "1111111", 0};
PVOID pa2[4] = {&Table, &p1, sizeof(p1), &b1};

BOOLEAN b2 = FALSE;
INFO p2 = {"222222", "2222222", 0};
PVOID pa3[4] = {&Table, &p2, sizeof(p2), &b2};

PVOID pa4[2] = {&Table, &p1};

PVOID pa5[2] = {&Table, &p2};

PVOID pa6[2] = {&Table, &p1};
PVOID pa7[2] = {&Table, &p1};
PVOID pa8[2] = {&Table, &p1};


UT_FRAME_MAPPING_BEGIN
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 5, ZooInitializeGenericTable, pa1, "ZooInitializeGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 4, ZooInsertElementGenericTable, pa2, "ZooInsertElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 4, ZooInsertElementGenericTable, pa3, "ZooInsertElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 2, ZooLookupElementGenericTable, pa4, "ZooLookupElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 2, ZooLookupElementGenericTable, pa5, "ZooLookupElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 2, ZooDeleteElementGenericTable, pa6, "ZooDeleteElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 2, ZooDeleteElementGenericTable, pa7, "ZooDeleteElementGenericTable")
UT_FRAME_MAPPING_MEMBER(STATUS_SUCCESS, 2, ZooDeleteElementGenericTable, pa8, "ZooDeleteElementGenericTable")
UT_FRAME_MAPPING_END
