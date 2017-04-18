// Author: Zoo
#pragma once
#include "stdafx.h"

//	WRK 中的一个 avl 树
struct _ZOO_GENERIC_TABLE;
typedef struct _ZOO_GENERIC_TABLE ZOO_GENERIC_TABLE, *PZOO_GENERIC_TABLE;

//	节点调整函数，做节点比较
typedef RTL_GENERIC_COMPARE_RESULTS (NTAPI *PZOO_AVL_COMPARE_ROUTINE) (struct _ZOO_GENERIC_TABLE *Table, PVOID FirstStruct, PVOID SecondStruct);

//	内存申请函数，给节点申请内存
typedef PVOID (NTAPI *PZOO_AVL_ALLOCATE_ROUTINE) (struct _ZOO_GENERIC_TABLE *Table, CLONG ByteSize);

//	内存释放函数，给节点释放内存
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


//	初始化AVL树
VOID ZooInitializeGenericTable(IN PZOO_GENERIC_TABLE Table, IN PZOO_AVL_COMPARE_ROUTINE CompareRoutine, IN PZOO_AVL_ALLOCATE_ROUTINE AllocateRoutine, IN PZOO_AVL_FREE_ROUTINE FreeRoutine, IN PVOID TableContext);

//	插入元素
PVOID ZooInsertElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer, IN CLONG BufferSize, OUT PBOOLEAN NewElement OPTIONAL);

//	删除元素
BOOLEAN ZooDeleteElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer);

//	查找元素
PVOID ZooLookupElementGenericTable(IN PZOO_GENERIC_TABLE Table, IN PVOID Buffer);

//	枚举元素
PVOID ZooEnumerateGenericTable(IN PZOO_GENERIC_TABLE Table, IN BOOLEAN Restart);

//	判断表是否为空
BOOLEAN ZooIsGenericTableEmpty(IN PZOO_GENERIC_TABLE Table);

//	获取内部元素个数
ULONG ZooNumberGenericTableElements(IN PZOO_GENERIC_TABLE Table);



