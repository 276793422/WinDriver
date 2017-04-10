#include "stdafx.h"

void ZooDriverUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS ZooDriverDispatchDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);


NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath)
{
	UNICODE_STRING DeviceName;
	UNICODE_STRING SybLinkName;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS status;
	ULONG i;


	ZooLogV("进入 DriverEntry : %wZ \n", RegistryPath);

	RtlInitUnicodeString(&DeviceName, VT_DEVICE_NAME);
	RtlInitUnicodeString(&SybLinkName, VT_SYBLINK_NAME);

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = ZooDriverDispatchDefaultHandler;
	}
	
	DriverObject->DriverUnload = ZooDriverUnload;
	status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &DeviceObject);
	if (!NT_SUCCESS(status))
	{
		return status;
	}
	if (!DeviceObject)
	{
		return STATUS_UNEXPECTED_IO_ERROR;
	}

	DeviceObject->Flags |= DO_BUFFERED_IO;
	DeviceObject->AlignmentRequirement = FILE_WORD_ALIGNMENT;
	status = IoCreateSymbolicLink(&SybLinkName, &DeviceName);

	ZooLogV("驱动加载成功 \n");
	return STATUS_SUCCESS;
}

void ZooDriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING SybLinkName;
	RtlInitUnicodeString(&SybLinkName, VT_SYBLINK_NAME);
	IoDeleteSymbolicLink(&SybLinkName);
	IoDeleteDevice(DriverObject->DeviceObject);
	ZooLogV("驱动卸载成功 \n");
}

NTSTATUS ZooDriverDispatchDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	ZooLogV("Function %s() \n", __FUNCTION__);
	return Irp->IoStatus.Status;
}
