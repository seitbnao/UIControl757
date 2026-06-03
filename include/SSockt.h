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

class CPacket {
public:
    static CPacket* Instance() {
        // Instance
        PDWORD g_pGameClass = (PDWORD)ClientAddresses::Memory::PacketInstance;

        // Return Instance
        return *g_pGameClass ? (CPacket*)(*g_pGameClass) : nullptr;
    }

    int SendPacket(char* p, int size) {
        if (!this || !p || size <= 0)
            return 0;

        return callThiscall(ClientAddresses::Function::PacketSend, int, CPacket*,
            char*, int)(this, p, size);
    }
};

class CLSock {
public:
    static CLSock* Instance() {
        // Instance
        PDWORD g_pGameClass = (PDWORD)ClientAddresses::Memory::SocketInstance;

        // Return Instance
        return *g_pGameClass ? (CLSock*)(*g_pGameClass) : nullptr;
    }

    BYTE SelectedCharID() {
        return this ? CLSock::getValue<BYTE, CLSock*>(this, 3908) : 0;
    }

    uint32_t getMainSockt() {  // atualizado
        static uint32_t rtnValue = 0;

        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_ADDR_SOCKET_INSTANCE]
            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return uint32_t();

        return rtnValue;
    }
    int getClientID() {  // atualizado
        if (!this)
            return 0;

        return *(WORD*)(reinterpret_cast<DWORD>(this) + 0x0DFC);
    }

    template <typename T>
    void SendPacket(T* Packet) {  // att
        if (!Packet)
            return;

        return callCdecl(ClientAddresses::Function::SendSocketPacket, void, T*, int)(
            (char*)&Packet, sizeof Packet);
    }

    template <typename T, typename TClass>
    static T getValue(TClass dwClass, int dwIndex) {
        if (!dwClass)
            return T();

        return (*(T*)(reinterpret_cast<DWORD>(dwClass) + dwIndex));
    }
    template <typename TClass, typename T>
    static void setValue(TClass dwClass, int dwIndex, T dwValue) {
        *(DWORD*)(reinterpret_cast<DWORD>(dwClass) + dwIndex) = dwValue;
    }
};
static CLSock* g_Sockt;
