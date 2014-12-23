#! /usr/bin/env python

from ctypes import *
import _ctypes
import string

decl = '''
#pragma once

#include "ImportWrapper.hpp"
#include "../../Resolver.h"

static
const
void** const g_pUserModeImports = reinterpret_cast<const void** const>(&FIRSTIMPORT);

static
const char* const g_pUserModeModules[] =
{
};

static
const char* const g_pUserModeProcedures[] =
{
};

static
const IMPORT_TABLE const g_UserModeImportsInfo[] =
{
};
'''

wrap = '''
#pragma once

#include <windows.h>
#include <Common/user/Externs.h>

#pragma pack(push, 1)
extern "C"
{
}
#pragma pack(pop)
'''

mnames = (
    "ntdll.dll",
    "kernel32.dll",
    "user32.dll",
    "gdi32.dll",
    "advapi32.dll",
    "kernelbase.dll",
    "msvcrt.dll",
    "ws2_32.dll",
    )

modules = (
    windll.ntdll,
    windll.kernel32,
    windll.user32,
    windll.gdi32,
    windll.advapi32,
    windll.kernelbase,
    windll.msvcrt,
    windll.ws2_32,
    )

specialTODO = {}

def CheckDirectProcAddr(proc):
    addr = 0
    i = 0
    for mod in modules:
        addr = windll.kernel32.GetProcAddress(mod._handle, proc) 
        #print hex(addr), mnames[i], mod._handle
        if (0 != addr):
            return mnames[i]

        i += 1
    return None

def SkipAt(imp):
    ret = imp
    if ("@" in imp):
        ret = imp[1:string.find(imp, "@")]
    return ret

def ParseImports():
    imps = []
    mods = []
    f = open("imports.ii", "r")
    for iline in f.readlines():
        try:
            imp = iline.split(" ")[5].split("\t")[0]
    
            if ("__imp_" in imp):
                imp = imp[len("__imp_"):]

            proc = SkipAt(imp)

            if ("vsnprintf" in proc):
                mname = "msvcrt.dll"
            else:
                mname = CheckDirectProcAddr(proc) 

            if (None == mname):
                proc = proc[1:]
                imp = imp[1:]
                mname = CheckDirectProcAddr(proc)
                if (mname and imp not in imps):
                    specialTODO[imp] = "_"+imp


            if (imp in imps):
                continue

            print (mname)
            if (None != mname):
                print(mname," -> %s\n"%imp) 

                imps.append(imp)
                mods.append(mname)
            else:
                raise NameError("import not resolved %s !!"%proc)
                return None
        except:
            break
    f.close()

    return [imps, mods]


def CreateImportDeclaration(lines, imps, mods):
    header = open("ImportDeclaration.h", "w")

    i = 0
    while (i < len(lines)):
        if ("g_pUserModeModules[]" in lines[i]):
            header.write(lines[i]+"\n")

            i += 1
            header.write( lines[i] + "\n" )
            for mod in mods:
                header.write( '\t"%s",\n'%(mod) )
    
        elif ("g_pUserModeProcedures[]" in lines[i]):
            header.write(lines[i]+"\n")

            i += 1
            header.write( lines[i] + "\n" )
            for imp in imps:
                header.write( '\t"%s",\n'%(SkipAt(imp)) )

        elif ("g_UserModeImportsInfo[]" in lines[i]):
            header.write(lines[i].replace("[]", "[%i]"%len(imps))+"\n")

            i += 1
            header.write(lines[i]+"\n")
            
            #drop @X PROTO!
            for j in range(0, len(imps)):
                proc = imps[j]
                if ("@" in imps[j]):
                    proc = imps[j][:string.find(imps[j], "@")]
                header.write('\t{ &g_pUserModeModules[0x%.3x], &g_pUserModeProcedures[0x%.3x], reinterpret_cast<const void**>(&Ex%s) },\n'%(j, j, proc) )
    
        else:
            header.write(lines[i]+"\n")

        i += 1

    header.close()

def CreateImportWrapper(imps):
    wrapper = open("ImportWrapper.hpp", "w")

    extern_c = ""
    for imp in imps:
        proc = imp
        iproc = imp
        if ("@" in imp):
            proc = imp[:string.find(imp, "@")]
            iproc = proc[1:]

        extern_c += "\tdecltype(&%s) Ex%s;\n"%(iproc, proc)

    for line in wrap.split("\n")[1:]:
        wrapper.write(line+"\n")
        if ("{" in line):
            wrapper.write(extern_c)
    wrapper.close()

def CreateUsrImportsAsm(imps):    
    x86 = False
    for imp in imps:
        if ("@" in imp):
            x86 = True

    extrn = ""
    methods = ""
    for imp in imps:
        proc = imp
        if ("@" in imp):
            proc = imp[:string.find(imp, "@")]

        if (proc in specialTODO):
            imp = specialTODO[imp]

        if (x86):
            extrn += "extrn _Ex%s:near\n"%proc
            methods += "%s proc\n\tjmp dword ptr _Ex%s\n%s endp\n\n"%(imp, proc, imp)
        else:
            extrn += "extrn Ex%s:near\n"%proc
            methods += "%s proc\n\tjmp qword ptr Ex%s\n%s endp\n\n"%(imp, imp, imp)

    impasm = open("usr_imports.asm", "w")
    impasm.write("IFDEF RAX\nELSE\n.model flat\nENDIF\n\n.data\n\n%s\n.code\n\n%send"%(extrn, methods))
    impasm.close()

def AppendExportsToImportsDef(imps):
    importsexports = ""
    for imp in imps:
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


[imps, mods] = ParseImports()
if (0 != len(imps)):
    if ('@' in imps[0]):
        head = imps[0][:imps[0].find('@')]
    else:
        head = imps[0]
    decl = decl.replace("FIRSTIMPORT", "Ex%s"%head)
    lines = decl.split("\n")
    CreateImportDeclaration(lines, imps, mods)
    CreateImportWrapper(imps)
    CreateUsrImportsAsm(imps)
    AppendExportsToImportsDef(imps)

