// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->EmuX.cpp
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#define _CXBXKRNL_INTERNAL
#define _XBOXKRNL_LOCAL_

#include "Cxbx.h"
#include "EmuX.h"

// ******************************************************************
// * prevent name collisions
// ******************************************************************
namespace xntdll
{
    #include "xntdll.h"
};

using namespace win32;

// ******************************************************************
// * static functions
// ******************************************************************
static void EmuXInstallWrappers(OOVPATable *OovpaTable, uint32 OovpaTableSize, void (*Entry)(), Xbe::Header *XbeHeader);

// ******************************************************************
// * func: EmuXInit
// ******************************************************************
CXBXKRNL_API void NTAPI EmuXInit(Xbe::LibraryVersion *LibraryVersion, DebugMode DebugConsole, char *DebugFilename, Xbe::Header *XbeHeader, uint32 XbeHeaderSize, void (*Entry)())
{
    // ******************************************************************
    // * debug console allocation (if configured)
    // ******************************************************************
    if(DebugConsole == DM_CONSOLE)
    {
        if(AllocConsole())
        {
            freopen("CONOUT$", "wt", stdout);

            SetConsoleTitle("Cxbx : Kernel Debug Console");

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            
            printf("CxbxKrnl (0x%.08X): Debug console allocated.\n", GetCurrentThreadId());
        }
    }
    else if(DebugConsole == DM_FILE)
    {
        FreeConsole();

        freopen(DebugFilename, "wt", stdout);

        printf("EmuX (0x%.08X): Debug console allocated.\n", GetCurrentThreadId());
    }

    // ******************************************************************
    // * debug trace
    // ******************************************************************
    {
        printf("EmuX: EmuXInit\n"
               "(\n"
               "   LibraryVersion      : 0x%.08X\n"
               "   DebugConsole        : 0x%.08X\n"
               "   DebugFilename       : \"%s\"\n"
               "   XBEHeader           : 0x%.08X\n"
               "   XBEHeaderSize       : 0x%.08X\n"
               "   Entry               : 0x%.08X\n"
               ");\n",
               LibraryVersion, DebugConsole, DebugFilename, XbeHeader, XbeHeaderSize, Entry);
    }

    // ******************************************************************
    // * Locate functions and install wrapper vectors
    // ******************************************************************
    {
        uint32 dwLibraryVersions = XbeHeader->dwLibraryVersions;
        uint32 dwHLEEntries      = HLEDataBaseSize/sizeof(HLEData);

        for(uint32 v=0;v<dwLibraryVersions;v++)
        {
            uint16 MajorVersion = LibraryVersion[v].wMajorVersion;
            uint16 MinorVersion = LibraryVersion[v].wMinorVersion;
            uint16 BuildVersion = LibraryVersion[v].wBuildVersion;

            char szLibraryName[9] = {0};

            for(uint32 c=0;c<8;c++)
                szLibraryName[c] = LibraryVersion[v].szName[c];

            printf("EmuX: Locating HLE Information for %s %d.%d.%d...", szLibraryName, MajorVersion, MinorVersion, BuildVersion);

            bool found=false;

            for(uint32 d=0;d<dwHLEEntries;d++)
            {
                if
                (
                    BuildVersion != HLEDataBase[d].BuildVersion ||
                    MinorVersion != HLEDataBase[d].MinorVersion ||
                    MajorVersion != HLEDataBase[d].MajorVersion ||
                    strcmp(szLibraryName, HLEDataBase[d].Library) != 0
                )
                continue;

                found = true;

                printf("Found\n");

                EmuXInstallWrappers(HLEDataBase[d].OovpaTable, HLEDataBase[d].OovpaTableSize, Entry, XbeHeader);
            }

            if(!found)
                printf("Skipped\n");
        }
    }

    // ******************************************************************
    // * Load the necessary pieces of XBEHeader
    // ******************************************************************
    {
        Xbe::Header *MemXbeHeader = (Xbe::Header*)0x00010000;

        uint32 old_protection = 0;

        VirtualProtect(MemXbeHeader, 0x1000, PAGE_READWRITE, &old_protection);

        // we sure hope we aren't corrupting anything necessary for an .exe to survive :]
        MemXbeHeader->dwSizeofHeaders        = XbeHeader->dwSizeofHeaders;
        MemXbeHeader->dwCertificateAddr      = XbeHeader->dwCertificateAddr;
        MemXbeHeader->dwPeHeapReserve        = XbeHeader->dwPeHeapReserve;
        MemXbeHeader->dwPeHeapCommit         = XbeHeader->dwPeHeapCommit;

        memcpy(&MemXbeHeader->dwInitFlags, &XbeHeader->dwInitFlags, sizeof(XbeHeader->dwInitFlags));

        memcpy((void*)XbeHeader->dwCertificateAddr, &((uint08*)XbeHeader)[XbeHeader->dwCertificateAddr - 0x00010000], sizeof(Xbe::Certificate));
    }

    // ******************************************************************
    // * Initialize FS system
    // ******************************************************************
    {
        EmuXInitFS();
    }

    // ******************************************************************
    // * Initialize FS:* structure
    // ******************************************************************
    {
        EmuXGenerateFS();
    }

    // ******************************************************************
    // * Initialize Direct3D8
    // ******************************************************************
    {
        xboxkrnl::EmuXInitD3D(XbeHeader, XbeHeaderSize);
    }

    printf("EmuX (0x%.08X): Initial thread starting.\n", GetCurrentThreadId());

    // This must be enabled or the debugger may crash (sigh)
    // __asm _emit 0xF1

    EmuXSwapFS();   // XBox FS

    Entry();

    EmuXSwapFS();   // Win2k/XP FS

    printf("EmuX (0x%.08X): Initial thread ended.\n", GetCurrentThreadId());

    fflush(stdout);

    while(true)
        Sleep(1000);

    return;
}

// ******************************************************************
// * func: EmuXDummy
// ******************************************************************
CXBXKRNL_API void NTAPI EmuXDummy()
{
    EmuXSwapFS();   // Win2k/XP FS

    printf("EmuX (0x%.08X): EmuXDummy()\n", GetCurrentThreadId());

    EmuXSwapFS();   // XBox FS
}

// ******************************************************************
// * func: EmuXPanic
// ******************************************************************
CXBXKRNL_API void NTAPI EmuXPanic()
{
    EmuXSwapFS();   // Win2k/XP FS

    printf("EmuX (0x%.08X): EmuXPanic()\n", GetCurrentThreadId());

#ifdef _DEBUG_TRACE
    MessageBox(NULL, "Kernel Panic! Process will now terminate.\n\n"
                     "Check debug traces for hints on the cause of this crash.", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);
#else
    MessageBox(NULL, "Kernel Panic! Process will now terminate.", "CxbxKrnl", MB_OK | MB_ICONEXCLAMATION);
#endif
    EmuXSwapFS();   // XBox FS
}

// ******************************************************************
// * func: EmuXInstallWrapper
// ******************************************************************
inline void EmuXInstallWrapper(void *FunctionAddr, void *WrapperAddr)
{
    uint08 *FuncBytes = (uint08*)FunctionAddr;

    *(uint08*)&FuncBytes[0] = 0xE9;
    *(uint32*)&FuncBytes[1] = (uint32)WrapperAddr - (uint32)FunctionAddr - 5;
}

// ******************************************************************
// * func: EmuXInstallWrappers
// ******************************************************************
void EmuXInstallWrappers(OOVPATable *OovpaTable, uint32 OovpaTableSize, void (*Entry)(), Xbe::Header *XbeHeader)
{
    // ******************************************************************
    // * traverse the full OOVPA table
    // ******************************************************************
    for(uint32 a=0;a<OovpaTableSize/sizeof(OOVPATable);a++)
    {
        #ifdef _DEBUG_TRACE
        printf("EmuXInstallWrappers: Searching for %s...", OovpaTable[a].szFuncName);
        #endif

        OOVPA *Oovpa = OovpaTable[a].Oovpa;

        uint32 count = Oovpa->Count;
        uint32 lower = XbeHeader->dwBaseAddr;
        uint32 upper = XbeHeader->dwBaseAddr + XbeHeader->dwSizeofImage;

        // ******************************************************************
        // * Large
        // ******************************************************************
        if(Oovpa->Large == 1)
        {
            LOOVPA<1> *Loovpa = (LOOVPA<1>*)Oovpa;

            upper -= Loovpa->Lovp[count-1].Offset;

            bool found = false;

            // ******************************************************************
            // * Search all of the image memory
            // ******************************************************************
            for(uint32 cur=lower;cur<upper;cur++)
            {
                uint32  v=0;

                // ******************************************************************
                // * check all pairs, moving on if any do not match
                // ******************************************************************
                for(v=0;v<count;v++)
                {
                    uint32 Offset = Loovpa->Lovp[v].Offset;
                    uint32 Value  = Loovpa->Lovp[v].Value;

                    uint08 RealValue = *(uint08*)(cur + Offset);

                    if(RealValue != Value)
                        break;
                }

                // ******************************************************************
                // * success if we found all pairs
                // ******************************************************************
                if(v == count)
                {
                    #ifdef _DEBUG_TRACE
                    printf("Found! (0x%.08X)\n", cur);
                    #endif

                    EmuXInstallWrapper((void*)cur, OovpaTable[a].lpRedirect);

                    found = true;

                    break;
                }
            }

            // ******************************************************************
            // * not found
            // ******************************************************************
            if(!found)
            {
                #ifdef _DEBUG_TRACE
                printf("None (OK)\n");
                #endif
            }
        }
        // ******************************************************************
        // * Small
        // ******************************************************************
        else
        {
            SOOVPA<1> *Soovpa = (SOOVPA<1>*)Oovpa;

            upper -= Soovpa->Sovp[count-1].Offset;

            bool found = false;

            // ******************************************************************
            // * Search all of the image memory
            // ******************************************************************
            for(uint32 cur=lower;cur<upper;cur++)
            {
                uint32  v=0;

                // ******************************************************************
                // * check all pairs, moving on if any do not match
                // ******************************************************************
                for(v=0;v<count;v++)
                {
                    uint32 Offset = Soovpa->Sovp[v].Offset;
                    uint32 Value  = Soovpa->Sovp[v].Value;

                    uint08 RealValue = *(uint08*)(cur + Offset);

                    if(RealValue != Value)
                        break;
                }

                // ******************************************************************
                // * success if we found all pairs
                // ******************************************************************
                if(v == count)
                {
                    #ifdef _DEBUG_TRACE
                    printf("Found! (0x%.08X)\n", cur);
                    #endif

                    EmuXInstallWrapper((void*)cur, OovpaTable[a].lpRedirect);

                    found = true;

                    break;
                }
            }

            // ******************************************************************
            // * not found
            // ******************************************************************
            if(!found)
            {
                #ifdef _DEBUG_TRACE
                printf("None (OK)\n");
                #endif
            }
        }
    }

}