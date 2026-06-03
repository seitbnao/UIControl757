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

class SText : public SControl  // 0x0878BCC - 4884
{
public:
    float ViewLeft;
    float ViewTop;
    float ViewWidth;
    float ViewHeight;
    UINT32 pad_0078[8];
    UINT32 Opacity;
    UINT32 pad_0098[2];
    UINT32 SpriteIndex;
    UINT32 MouseStats;
    UINT32 pad_00a4[73];
    UINT32 PosX;
    UINT32 PosY;
    UINT32 Unk;
    UINT32 ScreenMove;
    UINT32 Unks[796];

public:
    // Cria Um Label
    static SText* Create(int SpriteIndex, const char* Text, DWORD Color, float x,
        float y, float width, float height, int HasBackColor,
        DWORD BackColor, int Shadow, int Align) {  // att

        DWORD pAllocWindow = TreeNode::AllocClass(eAllocType::eLabel);
        return callThiscall(CLIENT_RAW_00401CD9, SText*, DWORD, int, const char*, DWORD,
            float, float, float, float, int, DWORD, int,
            int)(pAllocWindow, SpriteIndex, Text, Color, x, y,
                width, height, HasBackColor, BackColor, Shadow,
                Align);
    }
    static SText* Create(int Handle, int SpriteIndex, const char* Text,
        DWORD Color, float x, float y, float width, float height,
        int HasBackColor, DWORD BackColor, int Shadow,
        int Align) {  // att

        DWORD pAllocWindow = TreeNode::AllocClass(eAllocType::eLabel);
        auto stext =
            callThiscall(CLIENT_RAW_00401CD9, SText*, DWORD, int, const char*, DWORD, float,
                float, float, float, int, DWORD, int,
                int)(pAllocWindow, SpriteIndex, Text, Color, x, y, width,
                    height, HasBackColor, BackColor, Shadow, Align);
        if (stext)
            stext->Handle = Handle;
        else
            return 0;

        return stext;
    }
    void setColor(DWORD newColor) {
        TreeNode::MakeFunction<void, SText*, DWORD>(this, 132, newColor);
    };
    //----- (0040232B) --------------------------------------------------------
    void setString(const char* a2, DWORD Color) {  // att
        this->setString(a2);
        this->setColor(Color);
    }

    signed int UpdateText(const char* Text, DWORD Color, int Flush = FALSE) {
        return callThiscall(CLIENT_RAW_00421D1F, signed int, SText*, const char*, DWORD,
            int)(this, Text, Color, Flush);
    }

    //----- (0040232B) --------------------------------------------------------
    SText* setConstString(const char* a2, ...) {  // att
        char buffer[256] = {
            0,
        };
        memset(buffer, 0, sizeof buffer);
        va_list va;
        va_start(va, a2);
        vsprintf_s(buffer, a2, va);
        va_end(va);
          callThiscall(CLIENT_RAW_0040232B, void, SText*, const char*,
            int)(this, buffer, FALSE);
          return this;
    }
    //----- (0040232B) --------------------------------------------------------
    void setString(const char* a2, ...) {  // att
        static char buffer[0x100] = {
            0,
        };
        memset(buffer, 0, sizeof buffer);
        va_list va;
        va_start(va, a2);
        vsprintf_s(buffer, a2, va);
        va_end(va);
        return callThiscall(CLIENT_RAW_0040232B, void, SText*, const char*,
            int)(this, buffer, FALSE);
    }

    SText* setText(const char* str) {
          callThiscall(CLIENT_RAW_0040232B, void, SText*, const char*, int)(this, str,
            FALSE);
          return this;
    }
    bool isNullOrEmpty() {
        if (this->getText() == NULL) return true;

        return !strcmp(this->getText(), "");
    }

    int Size() { return strlen(this->getText()); }
    //----- (004029B8) --------------------------------------------------------
    const char* getText() {  // att
        return callThiscall(CLIENT_RAW_0040297A, const char*, SControl*)(this);
    }
    int getHandle(void) { return SControl::getHandle(); }
    static SText* _CreateLabel(const char* Text, int v288, float x, float y,
        float width, float height, int v292, int v284,
        int v310, int v311) {  // att
        DWORD pAllocWindow = (DWORD) operator new(eAllocType::eLabel);
        return callThiscall(CLIENT_RAW_00401CD9, SText*, DWORD, const char*, int, float,
            float, float, float, int, int, int,
            int)(pAllocWindow, Text, v288, x, y, width, height,
                v292, v284, v310, v311);
    }
    bool Hiden(int ShowHide) {  // att
        return callThiscall(CLIENT_RAW_0040159D, bool, SControl*, int)(this, ShowHide);
    }
    // Usado pra criar espaçamentos entre labels
    int CreateSpace(int dword_60F280, int nusa_1, int nusa_2, float Left,
        int n_usa3) {  // att
        return callThiscall(CLIENT_RAW_00401188, int, SText*, int, int, int, float,
            int)(this, dword_60F280, nusa_1, nusa_2, Left, n_usa3);
    }

    int UpdateItemAmount(char* str, DWORD Color) {  // att
        return callThiscall(CLIENT_RAW_00421D1F, int, SText*, char*, DWORD, DWORD)(this, str,
            Color, 0);
    }

    int getAlign() { return this->getValue<int, SText*>(this, 3284); }

    void setAlign(int value = 0) {
        this->setValue<SText*, int>(this, 3284, value);
    }

    int getShadown() { return this->getValue<int, SText*>(this, 3288); }

    void setShadown(int value = 0) {
        this->setValue<SText*, int>(this, 3288, value);
    }
};
