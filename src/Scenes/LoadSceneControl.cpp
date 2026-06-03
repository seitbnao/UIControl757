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

void TMScene::LoadSceneControl(int Scene) {
    auto scene = TMScene::Instance();
    if (!scene)
        return;

    switch (Scene) {
    case SceneLogin:
        if (CGlobalData::Instance().ClientInfo.SceneLogin == 0) {
            CGlobalData::Instance().ClientInfo.SceneLogin = 1;
            CGlobalData::Instance().ClientInfo.SceneSelChar = 0;
            CGlobalData::Instance().ClientInfo.SceneWord = 0;
            scene->CTSceneLogin();
        }
        break;

    case SceneSelChar:
        if (CGlobalData::Instance().ClientInfo.SceneSelChar == 0) {
            CGlobalData::Instance().ClientInfo.SceneLogin = 0;
            CGlobalData::Instance().ClientInfo.SceneSelChar = 1;
            CGlobalData::Instance().ClientInfo.SceneWord = 0;
            scene->CTSceneSelChar();
        }
        break;

    case SceneWorld:
        if (CGlobalData::Instance().ClientInfo.SceneWord == 0) {
            CGlobalData::Instance().ClientInfo.SceneLogin = 0;
            CGlobalData::Instance().ClientInfo.SceneSelChar = 0;
            CGlobalData::Instance().ClientInfo.SceneWord = 1;
            scene->CTSceneWorld();
        }
        break;
    }
}
