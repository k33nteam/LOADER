IFDEF RAX
ELSE
.model flat
ENDIF

.data

extrn _ExZwQuerySystemInformation:near
extrn _ExDbgPrint:near
extrn _ExRtlInitUnicodeString:near
extrn _ExIoQueueWorkItem:near
extrn _ExIoGetDeviceObjectPointer:near
extrn _ExIoFreeWorkItem:near
extrn _ExIoDetachDevice:near
extrn _ExIoAllocateWorkItem:near
extrn _ExObfReferenceObject:near
extrn _ExObfDereferenceObject:near
extrn _ExIofCallDriver:near
extrn _ExExFreePoolWithTag:near
extrn _ExExAllocatePoolWithTag:near
extrn _Ex_stricmp:near

.code

_ZwQuerySystemInformation@16 proc
	jmp dword ptr _ExZwQuerySystemInformation
_ZwQuerySystemInformation@16 endp

_DbgPrint proc
	jmp dword ptr _ExDbgPrint
_DbgPrint endp

_RtlInitUnicodeString@8 proc
	jmp dword ptr _ExRtlInitUnicodeString
_RtlInitUnicodeString@8 endp

_IoQueueWorkItem@16 proc
	jmp dword ptr _ExIoQueueWorkItem
_IoQueueWorkItem@16 endp

_IoGetDeviceObjectPointer@16 proc
	jmp dword ptr _ExIoGetDeviceObjectPointer
_IoGetDeviceObjectPointer@16 endp

_IoFreeWorkItem@4 proc
	jmp dword ptr _ExIoFreeWorkItem
_IoFreeWorkItem@4 endp

_IoDetachDevice@4 proc
	jmp dword ptr _ExIoDetachDevice
_IoDetachDevice@4 endp

_IoAllocateWorkItem@4 proc
	jmp dword ptr _ExIoAllocateWorkItem
_IoAllocateWorkItem@4 endp

@ObfReferenceObject@4 proc
	jmp dword ptr _ExObfReferenceObject
@ObfReferenceObject@4 endp

@ObfDereferenceObject@4 proc
	jmp dword ptr _ExObfDereferenceObject
@ObfDereferenceObject@4 endp

@IofCallDriver@8 proc
	jmp dword ptr _ExIofCallDriver
@IofCallDriver@8 endp

_ExFreePoolWithTag@8 proc
	jmp dword ptr _ExExFreePoolWithTag
_ExFreePoolWithTag@8 endp

_ExAllocatePoolWithTag@12 proc
	jmp dword ptr _ExExAllocatePoolWithTag
_ExAllocatePoolWithTag@12 endp

_stricmp proc
	jmp dword ptr _Ex_stricmp
_stricmp endp

end