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

void PacketControl::Recv(char* pMsg, int size) {
    if (!pMsg || size < sizeof(MSG_STANDARD))
        return;

    auto p = reinterpret_cast<MSG_STANDARD*>(pMsg);

}

__declspec(naked) void PacketControl::NKD_RecvPacket() {
    __asm {
        MOV EAX, DWORD PTR SS : [EBP - 0x08]
        AND EAX, 0xFFFF
        MOV DWORD PTR SS : [EBP - 0x08] , EAX

        PUSH 1
        LEA ECX, DWORD PTR SS : [EBP - 0x08]

        PUSH ECX
        PUSH DWORD PTR SS : [EBP - 0x18]

        CALL CPacketControl
        ADD ESP, 0x0C

        MOV EAX, CLIENT_RAW_00424D0C


        JMP EAX
    }
}
