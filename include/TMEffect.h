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

class TMEffect : public TreeNode  // eu usav uso mais n
{
public:
    static TMEffect* Instance() {
        static DWORD rtnValue = 0;
        __asm
        // by seitbnao
        {
            MOV EDX, DWORD PTR SS : [CLIENT_RAW_006D03B8]
            MOV ECX, DWORD PTR DS : [EDX + 0x2C]
            MOV EAX, DWORD PTR DS : [ECX]
            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return NULL;

        return reinterpret_cast<TMEffect*>(rtnValue);
    }

    static TMEffect* CreateMesh(int sprite, DWORD tColor, DWORD tCOlor2,
        int unk) {
        DWORD pAllocWindow = SControl::AllocClass(0xCCu);
        return callThiscall(CLIENT_RAW_0055A4D0, TMEffect*, DWORD, int, DWORD, DWORD,
            int)(pAllocWindow, sprite, tColor, tCOlor2, unk);
    }

    static TMEffect* CreateBillBoard(char a2, int a3, int a4, char a5, int a6,
        int a7, int a8, int a9) {
        DWORD pAllocWindow = SControl::AllocClass(0xACu);
        return callThiscall(CLIENT_RAW_00576000, TMEffect*, DWORD, char, int, int, char, int,
            int, int,
            int)(pAllocWindow, a2, a3, a4, a5, a6, a7, a8, a9);
    }
};