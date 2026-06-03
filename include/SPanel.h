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

class SPanel : public SControl {
public:
    int Unk[15];
    int SpriteIndex;
    int Unk2[106];

public:
    void Routate(double angle) {
        float theta = (angle * 3.14) / 180;
        float cx = rand() % 200, cy = cx;

        this->Position.PosX = ((this->Position.PosX - cx) * cos(theta) -
            (this->Position.PosY - cy) * sin(theta)) +
            cx;
        this->Position.PosY = ((this->Position.PosX - cx) * sin(theta) +
            (this->Position.PosY - cy) * cos(theta)) +
            cy;
    }
    enum VisibleState : int {
        VisibleI = 2,
        VisibleT = 3,
        VisibleS = 4,
    };
    enum OpacityState : int {
        Transparente = 1157627903,
        Opaco = -1,
    };
    // Cria um panel com textura
    static SPanel* Create(int SpriteIndex, float x, float y, float Width,
        float Height, int Opacity, int vState) {  // add
        DWORD pAllocWindow = SControl::AllocClass(0x1E4u);

        return callThiscall(CLIENT_RAW_00401426, SPanel*, DWORD, int, float, float, float,
            float, int, int)(pAllocWindow, SpriteIndex, x, y, Width,
                Height, Opacity, vState);
    }
    // Cria um panel com textura
    static SPanel* Create(int SpriteIndex, SCoordinate Coord, SRectangle rct,
        int Opacity = -1, int vState = 4) {  // add
        DWORD pAllocWindow = SControl::AllocClass(0x1E4u);

        return callThiscall(CLIENT_RAW_00401426, SPanel*, DWORD, int, float, float, float,
            float, int, int)(pAllocWindow, SpriteIndex, Coord.PosX,
                Coord.PosY, rct.Width, rct.Height,
                Opacity, vState);
    }
    //----- (00401584) --------------------------------------------------------
    int DeleteTexture(int a2) {
        return callThiscall(CLIENT_RAW_0040159D, int, SPanel*, int)(this, a2);
    }
    //----- (0040159D) --------------------------------------------------------
    int SetBackgroundColor(int a2) {
        return callThiscall(CLIENT_RAW_00401584, int, SPanel*, int)(this, a2);
    }
    //----- (004015F7) --------------------------------------------------------
    void SetTextureControlScale(int a2, float x, float y, int a5, int a6) {
        return callThiscall(CLIENT_RAW_004015F7, void, SPanel*, int, float, float, int,
            int)(this, a2, x, y, a5, a6);
    }

    // retorna a handled atual
    int getHandle(void) { SControl::getHandle(); }
    // Pega o sprite
    int getSprite() { return this->SpriteIndex; }
    // Set o sprite
    void setSprite(int Spt) { this->SpriteIndex = Spt; }

    void setMove(int Val) { *((DWORD*)this + 119) = Val; }

    void Move(float X, float Y) {
        this->MakeFunction<void, SPanel*, float, float>(this, 112, X, Y);
    }

    void Size(float Width, float Height) {
        this->MakeFunction<void, SPanel*, float, float>(this, 116, Width, Height);
    }

    void IsDraggable(bool isDraggable) {
        this->MakeFunction<void, SPanel*, bool>(this, 476, isDraggable);
    }

    void AnularTextura() { this->SpriteIndex = 578; }
};
