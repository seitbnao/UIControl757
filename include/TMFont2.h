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

class TMFont2 {
public:
    static TMFont2* Create() {
        DWORD pAllocWindow = TreeNode::AllocClass(0x2A0u);
        return callThiscall(CLIENT_RAW_00422AD0, TMFont2*, DWORD)(pAllocWindow);
    }

    int SetString(const char* string, int Color, int unk = 0) {
        return callThiscall(CLIENT_RAW_00421D1F, int, TMFont2*, const char*, int,
            int)(this, string, Color, unk);
    }
    void setUnk(int val) { TreeNode::setValue<TMFont2*, int>(this, 20, val); }
};