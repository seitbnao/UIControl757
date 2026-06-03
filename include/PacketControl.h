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
#pragma once

class PacketControl : public Singleton<PacketControl> {
private:
    PacketControl() = delete;
    PacketControl(const PacketControl&) = delete;
    PacketControl& operator=(const PacketControl&) = delete;

public:
    static void NKD_SendPacket();

    static void NKD_RecvPacket();

    static void Send(char* pMsg, int size);

    static void Recv(char* pMsg, int size);

};

static void CPacketControl(char* pBuffer, int a_iSize, int a_iType) {
    if (a_iType == 0)
        PacketControl::Send(pBuffer, a_iSize);
    else if (a_iType == 1)
        PacketControl::Recv(pBuffer, a_iSize);

    return;
}
