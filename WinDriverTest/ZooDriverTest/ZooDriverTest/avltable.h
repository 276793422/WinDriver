// Author: Zoo
#pragma once
#include "stdafx.h"

//	WRK �е�һ�� avl ��
struct _ZOO_GENERIC_TABLE;
typedef struct _ZOO_GENERIC_TABLE ZOO_GENERIC_TABLE, *PZOO_GENERIC_TABLE;

//	�ڵ�������������ڵ�Ƚ�
typedef RTL_GENERIC_COMPARE_RESULTS (NTAPI *PZOO_AVL_COMPARE_ROUTINE) (struct _ZOO_GENERIC_TABLE *Table, PVOID FirstStruct, PVOID SecondStruct);

//	�ڴ����뺯�������ڵ������ڴ�
typedef PVOID (NTAPI *PZOO_AVL_ALLOCATE_ROUTINE) (struct _ZOO_GENERIC_TABLE *Table, CLONG ByteSize);

//	�ڴ��ͷź��������ڵ��ͷ��ڴ�
typedef VOID (NTAPI *PZOO_AVL_FREE_ROUTINE) (struct _ZOO_GENERIC_TABLE *Table, PVOID Buffer);

typedef struct _ZOO_BALANCED_LINKS {
	struct _RTL_BALANCED_LINKS *Parent;
	struct _RTL_BALANCED_LINKS *LeftChild;
	struct _RTL_BALANCED_LINKS *RightChild;
	CHAR Balance;
	UCHAR Reserved[3];
} ZOO_BALANCED_LINKS;
typedef ZOO_BALANCED_LINKS *PZOO_BALANCED_LINKS;

struct _ZOO_GENERIC_TABLE {
	ZOO_BALANCED_LINKS BalancedRoot;
	PVOID OrderedPointer;
	ULONG WhichOrderedElement;
	ULONG NumberGenericTableElements;
	ULONG DepthOfTree;
	PZOO_BALANCED_LINKS RestartKey;
	ULONG DeleteCount;
	PZOO_AVL_COMPARE_ROUTINE CompareRoutine;
	PZOO_AVL_ALLOCATE_ROUTINE AllocateRoutine;
	PZOO_AVL_FREE_ROUTINE FreeRoutine;
	PVOID TableContext;
};


#define PZOO_GENERIC_COMPARE_ROUTINE	PZOO_AVL_COMPARE_ROUTINE
#define PZOO_GENERIC_ALLOCATE_ROUTINE	PZOO_AVL_ALLOCATE_ROUTINE
#define PZOO_GENERIC_FREE_ROUTINE		PZOO_AVL_FREE_ROUTINE


//	��ʼ��AVL��
VOID ZooInitializeGenericTable(IN PZOO_GENERIC_TABLE Table, IN PZOO_AVL_COMPARE_ROUTINE CompareRoutine, IN PZOO_AVL_ALLOCATE_ROUTINE AllocateRoutine, IN PZOO_AVL_FREE_ROUTINE FreeRoutine, IN PVOID TableContext);

//	����Ԫ��
PVOID ZooInsertElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer, IN CLONG BufferSize, OUT PBOOLEAN NewElement OPTIONAL);

//	ɾ��Ԫ��
BOOLEAN ZooDeleteElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer);

//	����Ԫ��
PVOID ZooLookupElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer);

//	ö��Ԫ��
PVOID ZooEnumerateGenericTable(IN PZOO_GENERIC_TABLE Table, IN BOOLEAN Restart);

//	�жϱ��Ƿ�Ϊ��
BOOLEAN ZooIsGenericTableEmpty(IN PZOO_GENERIC_TABLE Table);

//	��ȡ�ڲ�Ԫ�ظ���
ULONG ZooNumberGenericTableElements(IN PZOO_GENERIC_TABLE Table);



