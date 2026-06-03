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

class SButton : public SControl  // Base &off_5F46D4 sie 520
{
public:
    float ViewLeft;
    float ViewTop;
    float ViewWidth;
    float ViewHeight;
    UINT32 pad_0078;
    UINT32 pad_007C;
    int Texture;
    UINT32 pad_0084;
    UINT32 pad_0088;
    UINT32 pad_008C;
    UINT32 pad_0090;
    UINT32 pad_0094;
    UINT32 pad_0098;
    UINT32 pad_009C;
    UINT32 SpriteIndex;
    UINT32 MouseOver2;
    UINT32 pad_00A8[82];
    UINT32 pad_00FA;
    UINT32 MouseStatus;
    UINT32 Unk[5];

public:
    static SButton* Create(int SpriteIndex, float x, float y, float Width,
        float Height, int color, int focus, const char* Text) {
        DWORD pAllocWindow = TreeNode::AllocClass(0x208u);
        return callThiscall(CLIENT_RAW_0040332F, SButton*, DWORD, int, float, float, float,
            float, int, int, const char*)(pAllocWindow, SpriteIndex,
                x, y, Width, Height,
                color, focus, Text);
    }

    SText* getLabel() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 496));
        return pointer ? reinterpret_cast<SText*>(pointer) : NULL;
    }

    void setStringAddr(const char* String) {
        TreeNode::MakeFunction<void, SButton*, const char*>(CLIENT_RAW_004036FB, this,
            String);
    }

    char* getString() { return (char*)(reinterpret_cast<DWORD>(this) + 172); }

    void setString(char* String) {
        sprintf((char*)(reinterpret_cast<DWORD>(this) + 172), "%s", String);
    }

    void setColor(DWORD Color) {
        TreeNode::MakeFunction<void, DWORD*, const char*, DWORD, int>(
            CLIENT_RAW_00421D1F, *((DWORD**)this + 108), this->getString(), Color, 0);
    }

    void setString(const char* String, DWORD Color) {
        sprintf((char*)(reinterpret_cast<DWORD>(this) + 172), "%s", String);
        this->setColor(Color);
    }

    int getHandle(void) { return SControl::getHandle(); }

    int getSprite() { return this->SpriteIndex; }

    SText* getSText() {
        DWORD Stext = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 124));
        return Stext ? reinterpret_cast<SText*>(Stext) : NULL;
    }

    SFont* getSFont() {
        DWORD cTMFont2 = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 432));
        return cTMFont2 ? reinterpret_cast<SFont*>(cTMFont2) : NULL;
    }

    void setSprite(int sprite) {
        return TreeNode::MakeFunction<void, SButton*, int>(this, 128, sprite);
    }

    void enableClick() {
        return TreeNode::MakeFunction<void, SButton*, int>(this, 80, TRUE);
    }

    void disableClick() {
        return TreeNode::MakeFunction<void, SButton*, int>(this, 80, FALSE);
    }

    void unkfunction_140(int a2) {
        this->MakeFunction<void, SButton*, int>(this, 140, a2);
    }
    void unkfunction_84() {
        this->MakeFunction<void, SButton*>(this, 84);
    }
};
