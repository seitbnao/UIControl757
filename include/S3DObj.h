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
class S3DObj : public SControl {
private:
    BYTE UnkNow[eClassSizes::e3DObject_size];

public:
    static S3DObj* Create(int SpriteIndex, float x, float y, float Width,
        float Height) {
        DWORD pAllocWindow = SControl::AllocClass(0x1D0u);
        return callThiscall(CLIENT_RAW_00401A96, S3DObj*, DWORD, int, float, float, float,
            float)(pAllocWindow, SpriteIndex, x, y, Width, Height);
    }
};
