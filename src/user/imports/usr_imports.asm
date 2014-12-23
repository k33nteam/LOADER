IFDEF RAX
ELSE
.model flat
ENDIF

.data

extrn _Ex_vsnprintf:near
extrn _Ex_RtlUnicodeToMultiByteN:near
extrn _Ex_RtlRaiseException:near
extrn _Ex_OutputDebugStringA:near
extrn _Ex_HeapReAlloc:near
extrn _Ex_HeapFree:near
extrn _Ex_HeapAlloc:near
extrn _Ex_GetProcessHeap:near
extrn _Ex_GetModuleHandleW:near
extrn _Ex_GetCommandLineW:near
extrn _Ex_strnicmp:near

.code

_vsnprintf proc
	jmp dword ptr _Ex_vsnprintf
_vsnprintf endp

_RtlUnicodeToMultiByteN@20 proc
	jmp dword ptr _Ex_RtlUnicodeToMultiByteN
_RtlUnicodeToMultiByteN@20 endp

_RtlRaiseException@4 proc
	jmp dword ptr _Ex_RtlRaiseException
_RtlRaiseException@4 endp

_OutputDebugStringA@4 proc
	jmp dword ptr _Ex_OutputDebugStringA
_OutputDebugStringA@4 endp

_HeapReAlloc@16 proc
	jmp dword ptr _Ex_HeapReAlloc
_HeapReAlloc@16 endp

_HeapFree@12 proc
	jmp dword ptr _Ex_HeapFree
_HeapFree@12 endp

_HeapAlloc@12 proc
	jmp dword ptr _Ex_HeapAlloc
_HeapAlloc@12 endp

_GetProcessHeap@0 proc
	jmp dword ptr _Ex_GetProcessHeap
_GetProcessHeap@0 endp

_GetModuleHandleW@4 proc
	jmp dword ptr _Ex_GetModuleHandleW
_GetModuleHandleW@4 endp

_GetCommandLineW@0 proc
	jmp dword ptr _Ex_GetCommandLineW
_GetCommandLineW@0 endp

_strnicmp proc
	jmp dword ptr _Ex_strnicmp
_strnicmp endp

end