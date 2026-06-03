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
class SPanelBox : SControl {
public:
    static SPanelBox* Create(const char* Title, SCoordinate Coord,
        SRectangle Rect, int del = 2000) {
        DWORD pAllocWindow = SControl::AllocClass(0x1FCu);

        return callThiscall(CLIENT_RAW_00403CF5, SPanelBox*, DWORD, const char*, float, float,
            float, float, int)(pAllocWindow, Title, Coord.PosX,
                Coord.PosY, Rect.Width, Rect.Height,
                del);
    }

    static SPanelBox* Create(const char* Title, const char* Menssage) {
        if (auto panel = Create(Title, SCoordinate(160.0, 80.0),
            SRectangle(480.0, 24.0), 2000)) {
            auto text = panel->getTitle();
            if (text != 0) text->setString(Menssage);
        }
    }

    SText* getTitle() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 484));
        return pointer ? reinterpret_cast<SText*>(pointer) : NULL;
    }

    SText* getMenssage() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 488));
        return pointer ? reinterpret_cast<SText*>(pointer) : NULL;
    }

    SPanel* getBackground() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 492));
        return pointer ? reinterpret_cast<SPanel*>(pointer) : NULL;
    }

    SPanel* getBackground2() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 496));
        return pointer ? reinterpret_cast<SPanel*>(pointer) : NULL;
    }
};
