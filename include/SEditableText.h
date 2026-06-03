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

class SEditableText : public SControl {
    enum Alignment { Left = 0, Right = 2, Center = 1 };
    enum EShadow {
        NoShadow = 0,
        HasShadow = 1,
        ShadowT = 2,
    };

private:
    int Unks[260];
    BYTE MaxLenth;      //+ 1044
    BYTE unk2;          //+ 1045
    BYTE PassWordType;  //+ 1046
    BYTE unk3;          //+ 1047
    BYTE unk4;          //+ 1048
public:  // Essas funcs são exclusivas deste control
 //	//----- (00406083)
 //--------------------------------------------------------
    static SEditableText* Create(int Texture, const char* lpString, int MaxLength,
        int pass, DWORD Color, float PosX, float PosY,
        float Width, float Height, int backGroundColor,
        DWORD BackColor, int Shadow, int Align) {
        DWORD pAllocWindow = SControl::AllocClass(0x1064u);
        return callThiscall(CLIENT_RAW_00406083, SEditableText*, DWORD, int, const char*,
            int, int, DWORD, float, float, float, float, int, DWORD,
            int, int)(pAllocWindow, Texture, lpString, MaxLength,
                pass, Color, PosX, PosY, Width, Height,
                backGroundColor, BackColor, Shadow, Align);
    }
    // Create
    static SEditableText* Create(int UITextureID, const char* String,
        int MaxLength, bool IsPassword,
        /* ClientColor Color,*/ float PosX, float PosY,
        float Width, float Height, bool HasBackColor,
        ClientColor BackColor, int Shadow, int Align) {
        return SControl::MakeFunction<SEditableText*, DWORD, int, const char*, int,
            bool, /*ClientColor,*/ int, float, float,
            float, float, int, int, int, int>(
                CLIENT_RAW_00406083, SControl::AllocClass(0x1064u), UITextureID, String,
                MaxLength, IsPassword, /*Color*/ -1, PosX, PosY, Width, Height,
                HasBackColor, BackColor, Shadow, Align);
    };
    // Create

    void setMask(bool Mask) {
        *(DWORD*)(reinterpret_cast<DWORD>(this) + 4184) = Mask;
    }
    // seta um texto no input
    int setString(const char* text) {  // att
        return callThiscall(CLIENT_RAW_00406220, int, SEditableText*, const char*)(this,
            text);
    }
    // seta um texto no input
    int Empty() { return this->setString(""); }
    // retorna o texto digitado
    char* getString() {  // att
        return callThiscall(CLIENT_RAW_004062C7, char*, SEditableText*)(this);
    }

    int getLenth() { return strlen(this->getString()); }
    // retorna a mascara
    bool getPassWordType() { return PassWordType == 1; }
    // retorna a quantidade de caracteres
    int getMaxLenth() { return MaxLenth; }
    // seta a quantidade de caracteres do input
    void setMaxLenth(BYTE Lenth = 16) { MaxLenth = Lenth; }
    // Seta o formato da mascara se vi aparecer ***** ou não
    void setPassWordType(BYTE type = 0) { PassWordType = type; }
    // Retorna o handled atual
    int getHandle(void) { SControl::getHandle(); }

    // verifica o focus
    bool onFocus(int a2 = NULL) {  // att

        return callThiscall(CLIENT_RAW_00406452, bool, SEditableText*, int)(this, a2);
    }
    // Seta o focus
    void Focus() {  // att
        static uint32_t rtnValue = 0;
        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_RAW_006D03B8]
            MOV rtnValue, EAX
        }
        return (*(void(__thiscall**)(DWORD, SEditableText*))(
            **(DWORD**)(rtnValue + 40) + 64))(*(DWORD*)(rtnValue + 40), this);
    }

    static int TControleDeTeclas(SEditableText* Control, char KeyIndex);
};
