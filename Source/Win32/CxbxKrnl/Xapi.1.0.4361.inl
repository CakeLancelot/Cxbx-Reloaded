// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->Xapi.1.0.4361.cpp
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

// ******************************************************************
// * XInitDevices
// ******************************************************************
// * NOTE: We are actually intercepting USBD_Init, because XInitDevices
// *       Simply redirects to that function
// ******************************************************************
SOOVPA<10> XInitDevices_1_0_4361 =
{
    0,  // Large == 0
    10, // Count == 10

    {
        // XInitDevices+0x03 : push 0xB4
        { 0x03, 0x68 }, // (Offset,Value)-Pair #1
        { 0x04, 0xB4 }, // (Offset,Value)-Pair #2

        // XInitDevices+0x10 : jmp +0x13
        { 0x10, 0x74 }, // (Offset,Value)-Pair #3
        { 0x11, 0x13 }, // (Offset,Value)-Pair #4

        // XInitDevices+0x5B : movzx eax, byte ptr [esi+0xA1]
        { 0x5B, 0x0F }, // (Offset,Value)-Pair #5
        { 0x5C, 0xB6 }, // (Offset,Value)-Pair #6
        { 0x5D, 0x86 }, // (Offset,Value)-Pair #7
        { 0x5E, 0xA1 }, // (Offset,Value)-Pair #8

        // XInitDevices+0x8B : retn 8
        { 0x8B, 0xC2 }, // (Offset,Value)-Pair #9
        { 0x8C, 0x08 }, // (Offset,Value)-Pair #10
    }
};

// ******************************************************************
// * XGetDevices
// ******************************************************************
SOOVPA<14> XGetDevices_1_0_4361 =
{
    0,  // Large == 0
    14, // Count == 14

    {
        // XGetDevices+0x07 : mov edx, [esp+arg_0]
        { 0x07, 0x8B }, // (Offset,Value)-Pair #1
        { 0x08, 0x54 }, // (Offset,Value)-Pair #2
        { 0x09, 0x24 }, // (Offset,Value)-Pair #3
        { 0x0A, 0x08 }, // (Offset,Value)-Pair #4

        // XGetDevices+0x0D : and [edx+4], 0
        { 0x0D, 0x83 }, // (Offset,Value)-Pair #5
        { 0x0E, 0x62 }, // (Offset,Value)-Pair #6
        { 0x0F, 0x04 }, // (Offset,Value)-Pair #7
        { 0x10, 0x00 }, // (Offset,Value)-Pair #8

        // XGetDevices+0x11 : mov cl, al
        { 0x11, 0x8A }, // (Offset,Value)-Pair #9
        { 0x12, 0xC8 }, // (Offset,Value)-Pair #10

        // XGetDevices+0x16 : call KfLowerIrql
        { 0x16, 0xFF }, // (Offset,Value)-Pair #11
        { 0x17, 0x15 }, // (Offset,Value)-Pair #12

        // XGetDevices+0x1F : retn 4
        { 0x1F, 0xC2 }, // (Offset,Value)-Pair #13
        { 0x20, 0x04 }, // (Offset,Value)-Pair #14
    }
};

// ******************************************************************
// * XInputOpen
// ******************************************************************
SOOVPA<12> XInputOpen_1_0_4361 =
{
    0,  // Large == 0
    12, // Count == 12

    {
        // XInputOpen+0x14 : push 0x57
        { 0x14, 0x6A }, // (Offset,Value)-Pair #1
        { 0x15, 0x57 }, // (Offset,Value)-Pair #2

        // XInputOpen+0x1D : jmp +0x33
        { 0x1D, 0xEB }, // (Offset,Value)-Pair #3
        { 0x1E, 0x33 }, // (Offset,Value)-Pair #4

        // XInputOpen+0x33 : add edx, 0x10
        { 0x33, 0x83 }, // (Offset,Value)-Pair #5
        { 0x34, 0xC2 }, // (Offset,Value)-Pair #6
        { 0x35, 0x10 }, // (Offset,Value)-Pair #7

        // XInputOpen+0x47 : jmp +0x06
        { 0x47, 0x75 }, // (Offset,Value)-Pair #8
        { 0x48, 0x06 }, // (Offset,Value)-Pair #9

        // XInputOpen+0x52 : leave
        { 0x52, 0xC9 }, // (Offset,Value)-Pair #10

        // XInputOpen+0x53 : retn 0x10
        { 0x53, 0xC2 }, // (Offset,Value)-Pair #11
        { 0x54, 0x10 }, // (Offset,Value)-Pair #12
    }
};

// ******************************************************************
// * CreateThread
// ******************************************************************
SOOVPA<8> CreateThread_1_0_4361 =
{
    0,  // Large == 0
    8,  // Count == 8

    {
        // CreateThread+0x0A : mov eax, ds:10130h
        { 0x0A, 0xA1 }, // (Offset,Value)-Pair #1
        { 0x0B, 0x30 }, // (Offset,Value)-Pair #2
        { 0x0C, 0x01 }, // (Offset,Value)-Pair #3

        // CreateThread+0x1C : and ecx, 0xFFFFFF01
        { 0x1C, 0x81 }, // (Offset,Value)-Pair #4
        { 0x1D, 0xE1 }, // (Offset,Value)-Pair #5
        { 0x1E, 0x01 }, // (Offset,Value)-Pair #6

        // CreateThread+0x6B : retn 4
        { 0x6B, 0xC2 }, // (Offset,Value)-Pair #7
        { 0x6C, 0x18 }  // (Offset,Value)-Pair #8
    }
};

// ******************************************************************
// * CloseHandle
// ******************************************************************
SOOVPA<10> CloseHandle_1_0_4361 =
{
    0,  // Large == 0
    10, // Count == 10

    {
        // CloseHandle+0x00 : push [esp+4]
        { 0x00, 0xFF }, // (Offset,Value)-Pair #1
        { 0x01, 0x74 }, // (Offset,Value)-Pair #2
        { 0x02, 0x24 }, // (Offset,Value)-Pair #3
        { 0x03, 0x04 }, // (Offset,Value)-Pair #4

        // CloseHandle+0x04 : call ds:[addr]
        { 0x04, 0xFF }, // (Offset,Value)-Pair #5
        { 0x05, 0x15 }, // (Offset,Value)-Pair #6

        // CloseHandle+0x11 : jmp +0x08
        { 0x11, 0xEB }, // (Offset,Value)-Pair #7
        { 0x12, 0x08 }, // (Offset,Value)-Pair #8

        // CloseHandle+0x1B : retn 4
        { 0x1B, 0xC2 }, // (Offset,Value)-Pair #9
        { 0x1C, 0x04 }  // (Offset,Value)-Pair #10
    }
};

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
SOOVPA<7> XapiInitProcess_1_0_4361 =
{
    0,  // Large == 0
    7,  // Count == 7

    {
        // XapiInitProcess+0x00 : sub esp, 30h
        { 0x05, 0x30 }, // (Offset,Value)-Pair #1

        // XapiInitProcess+0x0F : push 0x0C
        { 0x0F, 0x6A }, // (Offset,Value)-Pair #2
        { 0x10, 0x0C }, // (Offset,Value)-Pair #3

        // XapiInitProcess+0x17 : repe stosd
        { 0x17, 0xF3 }, // (Offset,Value)-Pair #2
        { 0x18, 0xAB }, // (Offset,Value)-Pair #3

        // XapiInitProcess+0x42 : jnz +0x0B
        { 0x42, 0x75 }, // (Offset,Value)-Pair #2
        { 0x43, 0x0B }, // (Offset,Value)-Pair #3
    }
};

// ******************************************************************
// * XapiBootDash
// ******************************************************************
SOOVPA<9> XapiBootDash_1_0_4361 =
{
    0,  // Large == 0
    9,  // Count == 9

    {
        // XapiBootDash+0x03 : sub esp, 0x0C00
        { 0x03, 0x81 }, // (Offset,Value)-Pair #1
        { 0x04, 0xEC }, // (Offset,Value)-Pair #2
        { 0x06, 0x0C }, // (Offset,Value)-Pair #3

        // XapiBootDash+0x09 : mov eax, ds:0x10118
        { 0x09, 0xA1 }, // (Offset,Value)-Pair #4
        { 0x0A, 0x18 }, // (Offset,Value)-Pair #5
        { 0x0B, 0x01 }, // (Offset,Value)-Pair #6
        { 0x0C, 0x01 }, // (Offset,Value)-Pair #7

        // XapiBootDash+0x25 : repe stosd
        { 0x25, 0xF3 }, // (Offset,Value)-Pair #8
        { 0x26, 0xAB }, // (Offset,Value)-Pair #9
    }
};

// ******************************************************************
// * __rtinit
// ******************************************************************
SOOVPA<8> __rtinit_1_0_4361 =
{
    0,  // Large == 0
    8,  // Count == 8

    {
        // __rtinit+0x02 : mov eax, abs
        { 0x02, 0xB8 }, // (Offset,Value)-Pair #1

        // __rtinit+0x07 : mov edi, abs
        { 0x07, 0xBF }, // (Offset,Value)-Pair #2

        // __rtinit+0x18 : cmp eax, -1
        { 0x18, 0x83 }, // (Offset,Value)-Pair #3
        { 0x19, 0xF8 }, // (Offset,Value)-Pair #4
        { 0x1A, 0xFF }, // (Offset,Value)-Pair #5

        // __rtinit+0x22 : cmp esi, edi
        { 0x22, 0x3B }, // (Offset,Value)-Pair #6
        { 0x23, 0xF7 }, // (Offset,Value)-Pair #7

        // __rtinit+0x28 : retn
        { 0x28, 0xC3 }, // (Offset,Value)-Pair #8
    }
};

// ******************************************************************
// * __cinit
// ******************************************************************
SOOVPA<9> __cinit_1_0_4361 =
{
    0,  // Large == 0
    9,  // Count == 9

    {
        // __cinit+0x09 : call eax
        { 0x09, 0xFF }, // (Offset,Value)-Pair #1
        { 0x0A, 0xD0 }, // (Offset,Value)-Pair #2

        // __cinit+0x1B : jnb +0x14
        { 0x1B, 0x73 }, // (Offset,Value)-Pair #3
        { 0x1C, 0x14 }, // (Offset,Value)-Pair #4

        // __cinit+0x4A : jz +0x02
        { 0x4A, 0x74 }, // (Offset,Value)-Pair #5
        { 0x4B, 0x02 }, // (Offset,Value)-Pair #6

        // __cinit+0x4C : call eax
        { 0x4C, 0xFF }, // (Offset,Value)-Pair #7
        { 0x4D, 0xD0 }, // (Offset,Value)-Pair #8

        // __cinit+0x57 : retn
        { 0x57, 0xC3 }, // (Offset,Value)-Pair #9
    }
};

// ******************************************************************
// * XAPI_1_0_4361
// ******************************************************************
OOVPATable XAPI_1_0_4361[] =
{
    // XInputOpen
    {
        (OOVPA*)&XInputOpen_1_0_4361,

        xboxkrnl::EmuXXInputOpen,

        #ifdef _DEBUG_TRACE
        "EmuXXInputOpen"
        #endif
    },
    // XInitDevices
    {
        (OOVPA*)&XInitDevices_1_0_4361,

        xboxkrnl::EmuXXInitDevices,

        #ifdef _DEBUG_TRACE
        "EmuXXInitDevices"
        #endif
    },
    // XGetDevices
    {
        (OOVPA*)&XGetDevices_1_0_4361,

        xboxkrnl::EmuXXGetDevices,

        #ifdef _DEBUG_TRACE
        "EmuXXGetDevices"
        #endif
    },
    // CreateThread
    {
        (OOVPA*)&CreateThread_1_0_4361,

        xboxkrnl::EmuXCreateThread,

        #ifdef _DEBUG_TRACE
        "EmuXCreateThread" 
        #endif
    },
    // CloseHandle
    {
        (OOVPA*)&CloseHandle_1_0_4361,

        xboxkrnl::EmuXCloseHandle,

        #ifdef _DEBUG_TRACE
        "EmuXCloseHandle" 
        #endif
    },
    // XapiInitProcess
    {
        (OOVPA*)&XapiInitProcess_1_0_4361,

        xboxkrnl::EmuXapiInitProcess,

        #ifdef _DEBUG_TRACE
        "EmuXapiInitProcess" 
        #endif
    },
    // XapiBootToDash
    {
        (OOVPA*)&XapiBootDash_1_0_4361,

        xboxkrnl::EmuXapiBootDash,

        #ifdef _DEBUG_TRACE
        "EmuXapiBootDash"
        #endif
    },
    // __rtinit
    {
        (OOVPA*)&__rtinit_1_0_4361,

        xboxkrnl::EmuX__rtinit,

        #ifdef _DEBUG_TRACE
        "EmuX__rtinit",
        #endif
    },
    // __cinit
    {
        (OOVPA*)&__cinit_1_0_4361,

        xboxkrnl::EmuX__cinit,

        #ifdef _DEBUG_TRACE
        "EmuX__cinit",
        #endif
    },
};

// ******************************************************************
// * XAPI_1_0_4361_SIZE
// ******************************************************************
uint32 XAPI_1_0_4361_SIZE = sizeof(XAPI_1_0_4361);