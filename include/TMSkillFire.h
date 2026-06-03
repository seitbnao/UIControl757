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

class TMSkillFire : public TMEffect {
public:
    //----- (0056AED0) --------------------------------------------------------
    // int __thiscall TMSkillFire::Create(void* this, char a2, int a3, int a4, int
    // a5, int a6, int a7, int a8)

    static TMSkillFire* Create(int a2, int a3, int a4, int a5, int a6, int a7,
        int a8) {
        DWORD pAllocWindow = TreeNode::AllocClass(0xA0u);
        return callThiscall(CLIENT_RAW_0056AED0, TMSkillFire*, DWORD, int, int, int, int,
            int, int,
            int)(pAllocWindow, a2, a3, a4, a5, a6, a7, a8);
    }

    static void SendTMSkillFire(TMHuman* tmob) {
        if (tmob) {
            int PointX = 0, PointY = 0;
            if (int ret = tmob->InsideView(&PointX, &PointY)) {
                float ScaleY = (*(float*)CLIENT_RAW_005F9F4C * 80.0);
                auto effect = TMSkillFire::Create(0, PointX, ScaleY + PointY, 0, 0, -1,
                    573772032);
                if (!effect) return;
                auto scene = TMScene::Instance();
                if (!scene || !scene->TMEffect) return;
                scene->TMEffect->AttachClass(effect);
            }
        }
    }
};
