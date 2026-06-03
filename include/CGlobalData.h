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

//#define MAX_SKILLDATA 248
//#define MAX_ITEMLIST 0x2710
#define MAX_SIZE sizeof(CGlobalData::g_ItemList)
// const short  _MSG_MessageBox = 0x3200;
class CGlobalData {
public:
    static CGlobalData& Instance() {
        static CGlobalData _Instance;

        return _Instance;
    }

private:
    CGlobalData() = default;
    CGlobalData(const CGlobalData&) = delete;
    CGlobalData& operator=(const CGlobalData&) = delete;
public:
    struct ST_CLIENT {
        int SceneLogin;
        int SceneSelChar;
        int SceneWord;
        int Font;
        int Altura;
        int Largura;
    };
public:
    ST_CLIENT ClientInfo;

    static bool __stdcall SepararItens(STRUCT_ITEM* itemID);
    static void HKD_GetResolution(int fontSize, int Altura, int Largura);
    static void HKD_ChangeServerList();
    void Default();
};
