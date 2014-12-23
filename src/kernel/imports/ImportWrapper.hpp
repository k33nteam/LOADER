#pragma once

#include <ntifs.h>
#include <Common/kernel/Externs.h>

#pragma pack(push, 1)
extern "C"
{
	decltype(&ZwQuerySystemInformation) ExZwQuerySystemInformation;
	decltype(&DbgPrint) ExDbgPrint;
	decltype(&RtlInitUnicodeString) ExRtlInitUnicodeString;
	decltype(&IoQueueWorkItem) ExIoQueueWorkItem;
	decltype(&IoGetDeviceObjectPointer) ExIoGetDeviceObjectPointer;
	decltype(&IoFreeWorkItem) ExIoFreeWorkItem;
	decltype(&IoDetachDevice) ExIoDetachDevice;
	decltype(&IoAllocateWorkItem) ExIoAllocateWorkItem;
	decltype(&ObfReferenceObject) ExObfReferenceObject;
	decltype(&ObfDereferenceObject) ExObfDereferenceObject;
	decltype(&IofCallDriver) ExIofCallDriver;
	decltype(&ExFreePoolWithTag) ExExFreePoolWithTag;
	decltype(&ExAllocatePoolWithTag) ExExAllocatePoolWithTag;
	decltype(&_stricmp) Ex_stricmp;
}
#pragma pack(pop)

