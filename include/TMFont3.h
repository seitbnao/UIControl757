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
class TMFont3 : public TreeNode {
public:
    

    static TMFont3* Create(const char* a2, int a3, int a4, int a5, int a6, int a7,
        __int16 a8, int a9, int a10, int a11) {
        DWORD pAllocWindow = TreeNode::AllocClass(0x2A0u);
        return callThiscall(CLIENT_RAW_00422AD0, TMFont3*, DWORD, const char*, int, int, int,
            int, int, __int16, int, int,
            int)(pAllocWindow, a2, a3, a4, a5, a6, a7, a8, a9, a10,
                a11);
    }

    static void Create(TMHuman* tmob, int damage, int type) {
        if (tmob) {
            int PointX = 0, PointY = 0;
            if (int ret = tmob->InsideView(&PointX, &PointY)) {
                char Str[256];
                memset(Str, 0, sizeof Str);
                sprintf(Str, "%d", damage);
                float ScaleY = (*(float*)CLIENT_RAW_005F9F4C * 80.0);
                auto tmfont3 = TMFont3::Create(Str, PointX, ScaleY + PointY, -65536,
                    0x40000000, 500, 1, 1500, 0, type);
                if (!tmfont3) return;

                auto scene = TMScene::Instance();
                if (!scene || !scene->TMFont3) return;
                scene->TMFont3->AttachClass(tmfont3);
            }
        }
    }

    int getTexture() { return this->getValue<int, TMFont3*>(this, 176); }

    void setTexture(int Index) {
        this->setValue<TMFont3*>(this, 176, Index);
    }

    int getTextureShadow() { return this->getValue<int, TMFont3*>(this, 212); }

    void setTextureShadow(int Index) {
        this->setValue<TMFont3*>(this, 212, Index);
    }

    int getPosX() { return this->getValue<int, TMFont3*>(this, 184); }

    void setPosX(int Index) {
        this->setValue<TMFont3*>(this, 184, Index);
    }

    int getPosY() { return this->getValue<int, TMFont3*>(this, 188); }

    void setPosY(int Index) {
        this->setValue<TMFont3*>(this, 188, Index);
    }

    int getType() { return this->getValue<int, TMFont3*>(this, 172); }

    void setType(int Index) { this->setValue<TMFont3*>(this, 172, Index); }

    int getSubMesh(int Index) {
        return this->getValue<int, TMFont3*>(this, 48 + (12 * Index));
    }

    void setSubMesh(int Index, int value) {
        this->setValue<TMFont3*>(this, 48 + (12 * Index), value);
    }
};
