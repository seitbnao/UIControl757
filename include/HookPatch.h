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

class HookPatch {
private:
	HookPatch() = delete;
	virtual ~HookPatch() = delete;
	HookPatch(const HookPatch&) = delete;
	HookPatch& operator=(const HookPatch&) = delete;

public:
	static bool InitHooks();

	static void NKD_STextMouseController();

	static void NKD_FixItemDescription();

	static void NKD_TControleDeteclas();

	static void NKD_TMHumanUpdate();

	static void NKD_AddAmountItem();

	static void NKD_GetCurrentResolution();

	static void NKD_ChangeServerList();

	static void NKD_KeyScapeControl();

	static void NKD_MainLoop();

	static void NKD_LoadWordScene();

	static void NKD_SControlMouseController();

	static void NKD_STextBoxMouseController();

	static void NKD_ActionOnItem();

	static void NKD_Cam();

	static void NKD_CommandControl();

	static void NKD_ShowItemDesc();

	static void NKD_CantMoveItem();

	static void NKD_HandleSelCharScene();

	static void NKD_HandleServerScene();

	static void NKD_HandleWorldScene();

	static void NKD_ControlMessageBox();

	static void NKD_FixMageMacro();

	static void NKD_ProcessUseItem();

	static void NKD_ProcessNpcClick();

	static void NKD_ControlKeyPress();

	static void HKD_EndSendScore();

	static void NKD_EndSendScore();

	static int16_t AcceptNewEquipment(int nPos);

	static void NKD_Inventory();

	static int32_t HKD_AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, DWORD* line1Color, DWORD* line2Color, DWORD* line3Color, DWORD* line4Color, DWORD* line5Color, DWORD* line6Color, DWORD* line7Color, DWORD* line8Color, DWORD* line9Color, DWORD* line10Color);
};

extern HookPatch* g_Hook;
