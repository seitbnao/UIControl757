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
class SCheckBox : public SControl {
public:
    int UnkNow[eClassSizes::eCheckBox_size];

public:
    static SCheckBox* Create(int SpriteIndex, float X, float Y, float Largura,
        float Altura, int Checked) {
        DWORD pAllocWindow = SControl::AllocClass(0x1F4u);
        return callThiscall(CLIENT_RAW_00409C53, SCheckBox*, DWORD, int, float, float, float,
            float, int)(pAllocWindow, SpriteIndex, X, Y, Largura,
                Altura, Checked);
    }

    int getCheked() { return this->getValue<int, SCheckBox*>(this, 164); }

    void setCheked(int _Checked = 0) {
        this->setValue<SCheckBox*, int>(this, 164, _Checked);
    }

    void onPress() { this->setCheked(!this->getCheked()); }
};
