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

void TMScene::HKD_Inventory(UINT32 Open) 
{


}

__declspec(naked) void HookPatch::NKD_Inventory() {
    static int status = 0;

    __asm MOV status, ECX

    status = !status;

    _asm {
        PUSH status
        CALL TMScene::HKD_Inventory

        PUSH ECX
        MOV EDX, DWORD PTR SS : [EBP - 0x18]
        MOV EAX, DWORD PTR DS : [EDX]
        MOV ECX, DWORD PTR SS : [EBP - 0x18]
        CALL DWORD PTR DS : [EAX + 0x60]
        PUSH CLIENT_RAW_0044B840
        RETN
    }
}