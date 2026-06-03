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

class SCursor : SControl {
public:
    enum MouseState : INT {
        MouseMove = 512,
        LBDown = 513,
        LBUp = 514,
        LBClick = 515,
        RBDown = 516,
        RBUp = 517,
        RBClick = 518
    };
 
    float getPosX() { return this->getValue<float, SControl*>(this, 168); }
    float getPosY() { return this->getValue<float, SControl*>(this, 172); }

    static int getCursorPointer() {
        static int MainCursorAddr = 0;
        MainCursorAddr = *(DWORD*)CLIENT_RAW_00606D80;
        return (MainCursorAddr) ? MainCursorAddr : NULL;
    }

    static int getCursorPointer2() {
        static int MainCursorAddr = 0;
        MainCursorAddr = *(DWORD*)CLIENT_RAW_00616740;
        return (MainCursorAddr) ? MainCursorAddr : NULL;
    }

    static SCursor* GetInstance() {
        return reinterpret_cast<SCursor*>(SCursor::getCursorPointer());
    }

    // Create
    static SCursor* Create(int UITextureID, float PosX, float PosY, float Width,
        float Height) {
        return SControl::MakeFunction<SCursor*, DWORD, int, float, float, float,
            float>(CLIENT_RAW_00409E59, SControl::AllocClass(0x358u),
                UITextureID, PosX, PosY, Width,
                Height);
    };

    static SCursor* Create() {
        auto v2 = (double)*(DWORD*)(SCursor::getCursorPointer2() + 172) / 2.0;
        auto v3 = (double)*(DWORD*)(SCursor::getCursorPointer2() + 168) / 2.0;
        return SCursor::Create(NULL, v3, v2, 32.0, 32.0);
    }

    void Move(float X, float Y) {
        this->MakeFunction<void, SCursor*, float, float>(CLIENT_RAW_0040979C, this, X, Y);
    }
};