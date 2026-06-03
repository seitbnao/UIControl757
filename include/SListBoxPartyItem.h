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
// type 7
class SListBoxPartyItem : SListBox  // *(DWORD *)v11 = &off_5DDA18;
{  // 0xE70u
public:
    static SListBoxPartyItem* Create(LPCSTR lpszStart, int a3, float a4, float a5,
        float a6, float a7, int a8, int a9, int a10,
        int a11, int a12) {  // att
        DWORD pAllocWindow = SControl::AllocClass(0xE70u);
        return callThiscall(CLIENT_RAW_00407877, SListBoxPartyItem*, DWORD, LPCSTR, int, float,
            float, float, float, int, int, int, int,
            int)(pAllocWindow, lpszStart, a3, a4, a5, a6, a7, a8,
                a9, a10, a11, a12);
    }

    SText* getStext() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 921));
        return pointer ? reinterpret_cast<SText*>(pointer) : NULL;
    }

    SPanel* getSPanel() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 922));
        return pointer ? reinterpret_cast<SPanel*>(pointer) : NULL;
    }

    SProgressBar* getSProgress() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 923));
        return pointer ? reinterpret_cast<SProgressBar*>(pointer) : NULL;
    }
};