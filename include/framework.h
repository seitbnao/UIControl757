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

#define WIN32_LEAN_AND_MEAN  // Excluir itens raramente utilizados dos
// cabeçalhos do Windows
#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#pragma warning(disable : 4309)
#pragma warning(disable : 26495)

// Arquivos de Cabeçalho do Windows
#include <windows.h>
#include <stdint.h>
using namespace std;

#include <sstream>
#include <locale>
#include <mmsystem.h>
#include <fstream>

#include <thread>
#include <mutex>
#include <iostream>

#include <string>
#include <algorithm>

#include "Singleton.h"
#include "Hook.h"
#include "ClientAddresses.h"
#include "CDefinitions.h"
#include "BusinessRules.h"
#include "LogManager.h"
#include "HookPatch.h"

#include "Console.h"
#include "SCoordinate.h"
#include "SRectangle.h"
// Interface
#include "TreeNode.h"
#include "SControl.h"
#include "SFont.h"
#include "SScrollBar.h"
#include "SText.h"
#include "SButton.h"
#include "SPagingBox.h"
#include "S3DObj.h"
#include "SCheckBox.h"
#include "SPanel.h"
#include "SPanelBox.h"
#include "SProgressBar.h"
#include "TMFont2.h"
#include "SGridControlItem.h"
#include "SGridControl.h"
#include "SEditableText.h"
#include "SListBox.h"
#include "SListBoxServerItem.h"
#include "SListBoxPartyItem.h"
#include "UINPCControl.h"

#include "SSockt.h"
#include "TMItem.h"
#include "SCursor.h"

// Others

#include "ItemEffect.h"
#include "ClientFunctions.h"
#include "UserFunctions.h"

#include "TMObject.h"
#include "TMScene.h"
#include "TMHuman.h"
#include "CGlobalData.h"

#include "TMFont3.h"
#include "TMEffect.h"
#include "TMSkillFire.h"
#include "TMEffectLevelUp.h"
#include "TMEffectParticle.h"
#include "TMSkillJudgement.h"
#include "PacketControl.h"
