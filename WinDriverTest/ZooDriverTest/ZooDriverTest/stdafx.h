// Author: Zoo
#pragma once
#include <ntddk.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>

#define ZooLogV(...) {{KdPrint(("[ZooDriver] " __VA_ARGS__));}}
#define ZooLogUT(...) {{KdPrint(("[ZooDriverUT] " __VA_ARGS__));}}
#define ZooLogUTFrame(...) {{KdPrint(("[ZooLogUTFrame] " __VA_ARGS__));}}
#define ZooLogDebug(...) {{KdPrint(("[ZooDriverDebug] " __VA_ARGS__));}}


#define VT_DEVICE_NAME		L"\\Device\\ZooDriver"
#define VT_SYBLINK_NAME		L"\\DosDevices\\ZooDriver"

#include "unit_test.h"
