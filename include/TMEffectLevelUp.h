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

class TMEffectLevelUp : public TMEffect {
public:
    static TMEffectLevelUp* Create(float posx, float posy, float poxz, int a5) {
        DWORD pAllocWindow = TreeNode::AllocClass(0x90u);
        return callThiscall(CLIENT_RAW_00559C20, TMEffectLevelUp*, DWORD, float, float,
            float, int)(pAllocWindow, posx, posy, poxz, a5);
    }

    static void SendEffectLevelUp(_In_ TMHuman* tmob, int animation = 0) {
        if (tmob) {
            auto effect = TMEffectLevelUp::Create(tmob->getPosX(), tmob->getPosY(),
                tmob->getPosY(), 0);
            if (!effect) return;

            if (animation) tmob->sendAnimation(14, 0);

            auto scene = TMScene::Instance();
            if (!scene || !scene->TMEffect) return;
            scene->TMEffect->AttachClass(effect);
        }
    }
};
