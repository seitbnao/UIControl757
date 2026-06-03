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
#include "BaseHeader.h"

int SEditableText::TControleDeTeclas(SEditableText* Control, char KeyIndex) {
    if (!Control) return FALSE;

    // remove o bug da fechar o client caso a string esteja vazia
    if (KeyIndex == 8 && Control->getLenth() <= 0) {
        return TRUE;
    }

    return FALSE;
}

int TMScene::ControleDeTeclas(TMScene* main, char Key) {
    if (!main) return 0;

    return 0;
}