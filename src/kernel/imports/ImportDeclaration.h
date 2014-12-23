
#pragma once

#include "ImportWrapper.hpp"
#include "../../Resolver.h"

static
const
void** const g_pKernelModeImports = reinterpret_cast<const void** const>(&ExZwQuerySystemInformation);

static
const char* const g_pKernelModeModules[] =
{
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
	"ntoskrnl.exe",
};

static
const char* const g_pKernelModeProcedures[] =
{
	"ZwQuerySystemInformation",
	"DbgPrint",
	"RtlInitUnicodeString",
	"IoQueueWorkItem",
	"IoGetDeviceObjectPointer",
	"IoFreeWorkItem",
	"IoDetachDevice",
	"IoAllocateWorkItem",
	"ObfReferenceObject",
	"ObfDereferenceObject",
	"IofCallDriver",
	"ExFreePoolWithTag",
	"ExAllocatePoolWithTag",
	"_stricmp",
};

static
const IMPORT_TABLE const g_KernelModeImportsInfo[14] =
{
	{ &g_pKernelModeModules[0x000], &g_pKernelModeProcedures[0x000], (const void**)(&ExZwQuerySystemInformation) },
	{ &g_pKernelModeModules[0x001], &g_pKernelModeProcedures[0x001], (const void**)(&ExDbgPrint) },
	{ &g_pKernelModeModules[0x002], &g_pKernelModeProcedures[0x002], (const void**)(&ExRtlInitUnicodeString) },
	{ &g_pKernelModeModules[0x003], &g_pKernelModeProcedures[0x003], (const void**)(&ExIoQueueWorkItem) },
	{ &g_pKernelModeModules[0x004], &g_pKernelModeProcedures[0x004], (const void**)(&ExIoGetDeviceObjectPointer) },
	{ &g_pKernelModeModules[0x005], &g_pKernelModeProcedures[0x005], (const void**)(&ExIoFreeWorkItem) },
	{ &g_pKernelModeModules[0x006], &g_pKernelModeProcedures[0x006], (const void**)(&ExIoDetachDevice) },
	{ &g_pKernelModeModules[0x007], &g_pKernelModeProcedures[0x007], (const void**)(&ExIoAllocateWorkItem) },
	{ &g_pKernelModeModules[0x008], &g_pKernelModeProcedures[0x008], (const void**)(&ExObfReferenceObject) },
	{ &g_pKernelModeModules[0x009], &g_pKernelModeProcedures[0x009], (const void**)(&ExObfDereferenceObject) },
	{ &g_pKernelModeModules[0x00a], &g_pKernelModeProcedures[0x00a], (const void**)(&ExIofCallDriver) },
	{ &g_pKernelModeModules[0x00b], &g_pKernelModeProcedures[0x00b], (const void**)(&ExExFreePoolWithTag) },
	{ &g_pKernelModeModules[0x00c], &g_pKernelModeProcedures[0x00c], (const void**)(&ExExAllocatePoolWithTag) },
	{ &g_pKernelModeModules[0x00d], &g_pKernelModeProcedures[0x00d], (const void**)(&Ex_stricmp) },
};

