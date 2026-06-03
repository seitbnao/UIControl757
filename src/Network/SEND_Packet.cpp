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

void PacketControl::Send(char* pMsg, int size) {
    if (!pMsg || size < sizeof(MSG_STANDARD))
        return;

    auto p = reinterpret_cast<MSG_STANDARD*>(pMsg);


}

__declspec(naked) void PacketControl::NKD_SendPacket() {
    __asm {
        PUSH 0
        LEA ECX, DWORD PTR SS : [EBP + 0x0C]
        PUSH ECX
        PUSH DWORD PTR SS : [EBP + 0x08]

        CALL CPacketControl

        ADD ESP, 0x0C

        MOV DWORD PTR SS : [EBP - 0x0C] , 0x04

        MOV EAX, CLIENT_RAW_004251CE  //| .EB 12          JMP SHORT WYD.004251E2;  primeiro push 758


        JMP EAX
    }
}
