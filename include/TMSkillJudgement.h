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

class TMSkillJudgement : public TMEffect {
public:

    static TMSkillJudgement* Create(char a2, int a3, int a4, int a5, int a6, int a7, int a8) {
        DWORD pAllocWindow = TreeNode::AllocClass(0xA0u);
        return callThiscall(CLIENT_RAW_0056AED0, TMSkillJudgement*, DWORD, char, int, int, int, int, int, int)(pAllocWindow, a2, a3, a4, a5, a6, a7, a8);
    }

    static void SendSkillJudgement(_In_ TMHuman* tmob)
    {
        if (!tmob)
            return;

        if (auto intf = TMScene::Instance())
        {
            float YSccale = (double)(intf->sub_4A207A(tmob->getPosX(), tmob->getPosY()) * 0.1 + 0.5);

            auto effect = TMSkillJudgement::Create(0, YSccale, 0, 6, 0, 17544, 17544);
            if (!effect) return;

            if (!intf->TMEffect) return;
            intf->TMEffect->AttachClass(effect);
        }
    }
};
 
