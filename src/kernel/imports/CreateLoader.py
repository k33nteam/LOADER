#! /usr/bin/env python

from ctypes import *
import _ctypes
import string

X86 = True

header = '''
#pragma once

#include "ImportWrapper.hpp"
#include "../../Resolver.h"

static
const
void** const g_pKernelModeImports = reinterpret_cast<const void** const>(&FIRSTIMPORT);

static
const char* const g_pKernelModeModules[] =
{
};

static
const char* const g_pKernelModeProcedures[] =
{
};

static
const IMPORT_TABLE const g_KernelModeImportsInfo[] =
{
};
'''

mnames = (
    "ntoskrnl.exe",
#    "HAL",
    )

modules = (
    windll.kernel32.LoadLibraryA(mnames[0]),
 #   windll.hal._handle
    )

err = False
print("ntoskrnl.exe -> ", "c:/windows/syswow64/%s"%mnames[0], windll.kernel32.LoadLibraryA("c:/windows/syswow64/%s"%mnames[0]), modules[0])
#print(hex(windll.kernel32.LoadLibraryA("ntoskrnl.exe")), hex(modules[1]))

def CheckDirectProcAddr(proc):
    if modules[0] == 0:
        return mnames[0]
    addr = 0
    i = 0
    for mod in modules:
        addr = windll.kernel32.GetProcAddress(mod, proc)
        if (0 != addr):
            return mnames[i]
        i += 1
    return None

imps = []
imps_raw = []
frw = []
fmods = []
mods = []
f = open("imports.ii", "r")
for iline in f.readlines():
    try:
        imp = iline.split(" ")[5].split("\t")[0]

        if ("__imp_" in imp):
            imp = imp[len("__imp_"):]
        
        proc = imp
        if ("_DbgPrint" in imp):
            proc = "DbgPrint"

        if ("@" in imp):
            proc = imp[1:imp[1:].find("@") + 1]
        iraw = imp
        imp = proc

        mname = CheckDirectProcAddr(proc)
        if (None != mname):
            if imp in imps:
                print imp
                continue
            print(mname," -> %s\n"%imp, proc) 

            imps_raw.append(iraw)
            imps.append(imp)
            mods.append(mname)
        else:
            err = True
            print ("not resolved import => %s"%imp)
            break
    except:
        break
f.close()

if (True == err):
    raise NameError('import not resolved!!')

if (0 != len(imps)):
    proc1 = imps[0]
    header = header.replace("FIRSTIMPORT", "Ex%s"%proc1)

lines = header.split("\n")
i = 0

header = open("ImportDeclaration.h", "w")
while (i < len(lines)):
    if ("g_pKernelModeModules[]" in lines[i]):
        header.write(lines[i]+"\n")

        i += 1
        header.write( lines[i] + "\n" )
        for mod in mods:
            header.write( '\t"%s",\n'%(mod) )
    
    elif ("g_pKernelModeProcedures[]" in lines[i]):
        header.write(lines[i]+"\n")

        i += 1
        header.write( lines[i] + "\n" )
        for imp in imps:
            proc = imp
            header.write( '\t"%s",\n'%(proc) )

    elif ("g_KernelModeImportsInfo[]" in lines[i]):
        header.write(lines[i].replace("[]", "[%i]"%len(imps))+"\n")

        i += 1
        header.write(lines[i]+"\n")
        for j in range(0, len(imps)):
            proc = imps[j]
            header.write('\t{ &g_pKernelModeModules[0x%.3x], &g_pKernelModeProcedures[0x%.3x], (const void**)(&Ex%s) },\n'%(j, j, proc) )
    else:
        header.write(lines[i]+"\n")

    i += 1
header.close()

wrap = '''
#pragma once

#include <ntifs.h>
#include <Common/kernel/Externs.h>

#pragma pack(push, 1)
extern "C"
{
}
#pragma pack(pop)
'''
wrapper = open("ImportWrapper.hpp", "w")

extern_c = ""
for imp in imps:
    proc = imp
    iproc = imp

    extern_c += "\tdecltype(&%s) Ex%s;\n"%(iproc, proc)

for line in wrap.split("\n")[1:]:
    wrapper.write(line+"\n")
    if ("{" in line):
        wrapper.write(extern_c)
wrapper.close()

extrn = ""
methods = ""
for i in range(0, len(imps_raw)):
    imp = imps_raw[i]
    proc = imps[i]

    if (X86):
        extrn += "extrn _Ex%s:near\n"%proc
        methods += "%s proc\n\tjmp dword ptr _Ex%s\n%s endp\n\n"%(imp, proc, imp)
    else:
        extrn += "extrn Ex%s:near\n"%proc
        methods += "%s proc\n\tjmp qword ptr Ex%s\n%s endp\n\n"%(imp, imp, imp)

impasm = open("krn_imports.asm", "w")
impasm.write("IFDEF RAX\nELSE\n.model flat\nENDIF\n\n.data\n\n%s\n.code\n\n%send"%(extrn, methods))
impasm.close()

importsexports = ""
for imp in imps_raw:
    if ("DbgPrint" in imp):
        imp = "_DbgPrint"
    importsexports += "%s\n"%imp
imports = open("../../../../imports.def", "r")
buff = imports.read()
imports.close()

imports = open("../../../../imports.def", "w")
if (len(buff) > 0):
    imports.write("%s"%buff)
else:
    imports.write("EXPORTS")
imports.write("\n%s"%importsexports)
imports.close()

