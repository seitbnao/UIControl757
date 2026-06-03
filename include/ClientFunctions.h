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
#include <string>

class ClientFunctions {
private:
    ClientFunctions() = delete;
    ClientFunctions(const ClientFunctions&) = delete;
    ClientFunctions& operator=(const ClientFunctions&) = delete;

public:
    static bool HKD_ControlEventClick(int Handle);

    static bool ControleDeEventos(int Handle, int Scene);

    static void SendExpMenssage(DWORD Color, const char* Message, ...);

    static STRUCT_SPELL* getSkillData(int SkillID);

    static STRUCT_ITEMLIST* getItemList(int itemId);

    static void ShowEffect();

    static const char* strFormat(const char* Message, ...);

    static void EnableConsole(const char* Titulo);

    static const vector<string> explode(const string& s, const char& c);

    static char* ReadBinaryFile(const char* filename, int* read);

    static void setLog(const char* Str, ...);

    static void FlushLog();
};

extern ClientFunctions* g_Func;
#define _STR ClientFunctions::strFormat
