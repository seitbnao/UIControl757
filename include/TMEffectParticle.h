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

class CMake {
public:
    DWORD p1;
    DWORD p2;
    DWORD p3;

public:
    static CMake* Create(int a2, int a3, int a4) {
        return callThiscall(CLIENT_RAW_00437B10, CMake*, int, int, int)(a2, a3, a4);
    }
};

class TMEffectParticle : public TMEffect {
public:
    static TMEffectParticle* Create(float a2, float a3, float a4, int a5, int a6,
        float a7, int a8, int a9, int a10, float a11,
        int a12, int a13, int a14, int a15, int a16) {
        DWORD pAllocWindow = TreeNode::AllocClass(0x90u);
        return callThiscall(CLIENT_RAW_0055CF40, TMEffectParticle*, DWORD, float, float,
            float, int, int, float, int, int, int, float, int, int,
            int, int, int)(pAllocWindow, a2, a3, a4, a5, a6, a7, a8,
                a9, a10, a11, a12, a13, a14, a15, a16);
    }

    static void SendParticle(_In_ TMHuman* tmob) {
        if (!tmob)
            return;

        float ScaleY = tmob->getPosZ() + 1.0;
        auto effect = TMEffectParticle::Create((float)tmob->getPosX(), ScaleY,
            (float)tmob->getPosY(), 1, 3, 3.0, 0, 1, 56,
            1.0, 1, 0, 0, 0, 1000);

        if (!effect) return;

        auto scene = TMScene::Instance();
        if (!scene || !scene->TMEffect) return;
        scene->TMEffect->AttachClass(effect);
    }
};
