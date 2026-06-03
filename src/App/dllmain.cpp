/*
*   Copyright (C) {2019.1}  {Djunio - SeiTbNao - Wed}
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see [http://www.gnu.org/licenses/].
*
*/

#include "BaseHeader.h"



__declspec(dllexport) BOOL APIENTRY
DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    DWORD ThreadIDKeyControl = 0;
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        DWORD dwOldProtectFlag_text;
        VirtualProtect((void*)ClientAddresses::Memory::TextSectionBegin,
            ClientAddresses::Memory::TextSectionSize, PAGE_READWRITE,
            &dwOldProtectFlag_text);

        ClientFunctions::EnableConsole("Console");


       
        HookPatch::InitHooks();
        VirtualProtect((void*)ClientAddresses::Memory::TextSectionBegin,
            ClientAddresses::Memory::TextSectionSize, dwOldProtectFlag_text,
            &dwOldProtectFlag_text);
    }
    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        ClientFunctions::FlushLog();
        FreeLibrary(hModule);
        break;
    }

    return TRUE;
}
