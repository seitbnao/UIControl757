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
class SListBoxServerItem : public SListBox  // *(DWORD *)v11 = &off_5DDA18;
{
public:
    static SListBoxServerItem* Create(int TextureID, const char* text, int a4,
        float x, float y, float Width, float Height,
        int a9, char a10, char a11,
        int Line) {  // att
        DWORD pAllocWindow = SControl::AllocClass(0xE6Cu);
        return callThiscall(CLIENT_RAW_00407409, SListBoxServerItem*, DWORD, int,
            const char*, int, float, float, float, float, int, char,
            char, int)(pAllocWindow, TextureID, text, a4, x, y,
                Width, Height, a9, a10, a11, Line);
    }

    signed int AddOnList(const char* Text, signed int range_min,
        signed int range_max) {
        TreeNode::MakeFunction<signed int, SListBox*, const char*, signed int,
            signed int>(CLIENT_RAW_004A3EFB, this, Text, range_min,
                range_max);
    }

    SProgressBar* getSProgressBar() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 917));
        return pointer ? reinterpret_cast<SProgressBar*>(pointer) : NULL;
    }

    SPanel* getOlderage() {  // icone +18
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 918));
        return pointer ? reinterpret_cast<SPanel*>(pointer) : NULL;
    }

    SPanel* getCrowTexture() {  // coroa de guerra
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 919));
        return pointer ? reinterpret_cast<SPanel*>(pointer) : NULL;
    }

    void setEnableOldeage(BYTE e) {
        this->setValue<SListBoxServerItem*, BYTE>(this, 3689, e);
    }

    void setEnableCrow(BYTE e) {
        this->setValue<SListBoxServerItem*, BYTE>(this, 3690, e);
    }

    BYTE getEnableOldeage() {
        return this->getValue<BYTE, SListBoxServerItem*>(this, 3689);
    }

    BYTE getEnableCrow() {
        return this->getValue<BYTE, SListBoxServerItem*>(this, 3690);
    }
};