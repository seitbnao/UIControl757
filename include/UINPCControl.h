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
class UINPCControl  //: public SControl
{
public:
    DWORD unk_1[8];
    uint32_t npcIndex;
    DWORD unk_2[126];
    short mobFace;
    short Unk;
    DWORD Unk_t1;
    DWORD Unk_t3;
    DWORD Unk_t4;
    DWORD Unk_t5;
    DWORD Unk_t6;
    DWORD Unk_t7;
    DWORD Unk_t8;
    DWORD Unk_t9;
    DWORD Unk_t10;
    DWORD Unk_t11;
    DWORD Unk_t12;
    uint16_t Unk_t35;
    DWORD unk_s2[52];
    BYTE hh[768];
    uint8_t merchantId;
    BYTE h2[59];
    int p1;
    int posX;  // [1632]
    int posY;
    int nextX;
    int nextY;
    int extra[50];

public:
    static int ProcessNPCClick(UINPCControl* mob);
};
