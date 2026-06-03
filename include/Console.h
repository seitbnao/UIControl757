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
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <locale.h>
#include "ClientFunctions.h"

inline void ClientFunctions::EnableConsole(const char* Titulo) {
    // Fixed bug printf vs 15 - 17
    // By seitbnao
    char Temp[256];
    AllocConsole();
    sprintf(Temp, "%s", Titulo);
#ifdef _DEBUG
    sprintf(Temp, "[DEBUG] - %s", Titulo);
#endif  // _DEBUG

#ifdef _RELEASE
    sprintf(Temp, "[RELEASE] - %s", Titulo);
#endif  // __RELEASE

    SetConsoleTitleA(Temp);

    typedef struct {
        char* _ptr;
        int _cnt;
        char* _base;
        int _flag;
        int _file;
        int _charbuf;
        int _bufsiz;
        char* _tmpfname;
    } FILE_COMPLETE;

    *(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(
        _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(
        _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(
        _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setlocale(LC_ALL, "Portuguese");
}
