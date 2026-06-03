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
#include "HookPatch.h"

HookPatch* g_Hook = nullptr;
HookMgr* DLL = &HookMgr::instance();


bool HookPatch::InitHooks() {
	try {
		// Remove o cheksum SkillData
		*(BYTE*)ClientAddresses::Hook::SkillDataChecksumPatch = 0xEB;
		// Remove o cheksum ItemList
		*(BYTE*)ClientAddresses::Hook::ItemListChecksumPatchA = 0xEB;
		*(BYTE*)ClientAddresses::Hook::ItemListChecksumPatchB = 0xEB;
		// Remove o cheksum Object
		*(BYTE*)ClientAddresses::Hook::ObjectChecksumPatch = 0xEB;
		// find window
		*(BYTE*)ClientAddresses::Hook::FindWindowPatch = 0xEB;
		// Remove checksum dos mapas


		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::MapChecksumBypassA, ClientAddresses::Hook::MapChecksumBypassADest);
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::MapChecksumBypassB, ClientAddresses::Hook::MapChecksumBypassBDest);

		// Controle de Clicks em botões listas e etc (World)
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::HandleWorldScene, _GET(NKD_HandleWorldScene), 2);

		// Controle de Clicks em botões listas e etc (SelServer)
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::HandleServerScene, _GET(NKD_HandleServerScene), 2);

		// Controle de Clicks em botões listas e etc (SelChar)
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::HandleSelCharScene, _GET(NKD_HandleSelCharScene), 2);

		// Fixa os editbox e controla qualquer tecla usada
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::TextInputKeyControl, _GET(NKD_TControleDeteclas), 1);

		// Controle de Confirmação de MessageBox
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::MessageBoxControl, _GET(NKD_ControlMessageBox), 1);

		// Corrige o Macro mágico
		DLL->setHook(eHookType::JE, ClientAddresses::Hook::FixMageMacroA, _GET(NKD_FixMageMacro));
		DLL->setHook(eHookType::JE, ClientAddresses::Hook::FixMageMacroB, _GET(NKD_FixMageMacro));

		// Controla as descrições dos itens
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ShowItemDescription, _GET(NKD_ShowItemDesc), 2);

		// Controla o click em npcs
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ProcessNpcClick, _GET(NKD_ProcessNpcClick), 2);

		// Controla o botões do teclado
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ControlKeyPress, _GET(NKD_ControlKeyPress), 4);

		// Controla a movimentação de itens
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::CantMoveItem, _GET(NKD_CantMoveItem), 2);

		// Controla a movimentação de itens e suas ações
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ActionOnItem, _GET(NKD_ActionOnItem), 2);

		// Controla o uso dos itens
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ProcessUseItem, _GET(NKD_ProcessUseItem), 1);

		// Aceita novos slots de equipamntos
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::AcceptNewEquipment, _GET(AcceptNewEquipment));

		// Hook no loop de renderização dos componentes
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::MainLoop, _GET(NKD_MainLoop));

		// Hook no final da sendscore do client pode ser usado para atualizar status da UI do mob
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::EndSendScore, _GET(NKD_EndSendScore), 5);
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::LoadWorldScene, _GET(NKD_LoadWordScene), 1);

		// Altera a distancia da camera do jogador
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::CameraDistance, _GET(NKD_Cam), 1);

		// Hook na abertura do inv
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::InventoryOpen, _GET(NKD_Inventory), 1);

		// Controle de Pacotes enviados
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::SendPacket,
			_GET(PacketControl::NKD_SendPacket));

		// Controle de pacotes recebidos
		DLL->setHook(eHookType::JGE, ClientAddresses::Hook::RecvPacket,
			_GET(PacketControl::NKD_RecvPacket));

		// controla eventos do mouse em um textbox
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::TextBoxMouseControl, _GET(NKD_STextBoxMouseController),
			3);

		// Controla o chatbox
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::CommandControl, _GET(NKD_CommandControl));
		
		// Buffs externos
		DLL->setValue(ClientAddresses::Hook::ExternalBuffA + 6, 0);
		DLL->setValue(ClientAddresses::Hook::ExternalBuffB + 6, 0);


		// Hook na chamada da tecla ESC
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::EscapeKeyControl, _GET(NKD_KeyScapeControl), 2);
		DLL->setValue(ClientAddresses::Hook::SelCharLimitPatch + 3, 15145);

		// Altera a serverLIST
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::ChangeServerList, _GET(NKD_ChangeServerList), 1);
		
		
		// Pega as resoluções atuais do jogo
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::CurrentResolution, _GET(NKD_GetCurrentResolution), 5);
		
		// Permite personalizar o Amount
		DLL->setValue(ClientAddresses::Hook::ItemAmountMinPatch + 1, 0);
		DLL->setValue(ClientAddresses::Hook::ItemAmountMaxPatch + 1, 6500);
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::AddAmountItem, _GET(NKD_AddAmountItem),4);


		//Descrição de itens
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::FixItemDescription, _GET(NKD_FixItemDescription), 4);


		//Controles de Mouse Hover
        DLL->setHook(eHookType::JMP, ClientAddresses::Hook::TextMouseControl, _GET(NKD_STextMouseController), 1);
		DLL->setHook(eHookType::JMP, ClientAddresses::Hook::SControlMouseControl, _GET(NKD_SControlMouseController), 1);

		return true;
	}

	 

	catch (...) {
		return false;
	}
}


_declspec(naked) void HookPatch::NKD_SControlMouseController() {
	__asm {
		MOV DWORD PTR DS : [ECX + 0x34] , EAX


		PUSH DWORD PTR SS : [EBP + 0x8]//mouse event
		PUSH DWORD PTR SS : [EBP + 0x14]  // posY
		PUSH DWORD PTR SS : [EBP + 0x10]  // posX
		PUSH DWORD PTR SS : [EBP - 0xC]  // mouseStatus
		PUSH DWORD PTR SS : [EBP - 0x8]  // scontrol
		CALL TMScene::SControlMouseController

		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		PUSH CLIENT_RAW_00401780
		RETN



	}
}

_declspec(naked) void HookPatch::NKD_STextMouseController() {
	__asm {

		MOV DWORD PTR DS : [ECX + 0x34] , EAX
		PUSH DWORD PTR SS : [EBP + 0x14]
		PUSH DWORD PTR SS : [EBP + 0x10]
		PUSH DWORD PTR SS : [EBP + 0x8]
		PUSH DWORD PTR SS : [EBP + 0x4]
		PUSH DWORD PTR SS : [EBP - 0x4]
		CALL TMScene::STextMouseController
		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		PUSH CLIENT_RAW_00402207
		RETN

	}
}


_declspec(naked) void HookPatch::NKD_FixItemDescription()
{
	static COLORREF line1Color = 0, line2Color = 0, line3Color = 0, line4Color = 0,
		line5Color = 0, line6Color = 0, line7Color = 0, line8Color = 0, line9Color = 0, line10Color = 0;
	static int32_t lineCounter = 0, index = 0;
	static char line2[128] = { 0 }, line3[128] = { 0 }, line4[128]{ 0, },
		line5[128] = { 0 }, line6[128] = { 0 }, line7[128]{ 0, },
		line8[128] = { 0 }, line9[128] = { 0 }, line10[128]{ 0, };
	__asm
	{



		LEA EAX, line10Color
		PUSH EAX
		LEA EAX, line9Color
		PUSH EAX
		LEA EAX, line8Color
		PUSH EAX
		LEA EAX, line7Color
		PUSH EAX
		LEA EAX, line6Color
		PUSH EAX
		LEA EAX, line5Color
		PUSH EAX
		LEA EAX, line4Color
		PUSH EAX
		LEA EAX, line3Color
		PUSH EAX
		LEA EAX, line2Color
		PUSH EAX
		LEA EAX, line1Color
		PUSH EAX
		LEA ECX, line10
		PUSH ECX
		LEA ECX, line9
		PUSH ECX
		LEA ECX, line8
		PUSH ECX
		LEA ECX, line7
		PUSH ECX
		LEA ECX, line6
		PUSH ECX
		LEA ECX, line5
		PUSH ECX
		LEA ECX, line4
		PUSH ECX
		LEA ECX, line3
		PUSH ECX
		LEA ECX, line2
		PUSH ECX
		LEA EDX, DWORD PTR SS : [EBP - 0xAC]
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		PUSH EDX
		CALL HookPatch::HKD_AddItemDescription
		TEST EAX, EAX
		JE lblContinueExec

		MOV lineCounter, EAX // 2
		MOV index, 0
		JMP LoopStart

		LoopEnd :
		MOV EAX, index
			ADD EAX, 1
			MOV index, EAX
			LoopStart :
		MOV EAX, index
			CMP EAX, lineCounter
			JGE lblContinueExec


			PUSH 0
			CMP index, 0
			JG lblLine2
			LEA ECX, DWORD PTR SS : [EBP - 0xAC]
			PUSH ECX
			JMP lblContinuePush
			lblLine2 :
		CMP index, 1
			JG  lblLine3
			LEA ECX, line2
			PUSH ECX
			JMP lblContinuePush
			lblLine3 :
		CMP index, 2
			JG  lblLine4
			LEA ECX, line3
			PUSH ECX
			JMP lblContinuePush
			lblLine4 :
		CMP index, 3
			JG  lblLine5
			LEA ECX, line4
			PUSH ECX
			JMP lblContinuePush
			lblLine5 :
		CMP index, 4
			JG  lblLine6
			LEA ECX, line5
			PUSH ECX
			JMP lblContinuePush
			lblLine6 :
		CMP index, 5
			JG  lblLine7
			LEA ECX, line6
			PUSH ECX
			JMP lblContinuePush
			lblLine7 :
		CMP index, 6
			JG  lblLine8
			LEA ECX, line7
			PUSH ECX
			JMP lblContinuePush
			lblLine8 :
		CMP index, 7
			JG  lblLine9
			LEA ECX, line8
			PUSH ECX
			JMP lblContinuePush
			lblLine9 :
		CMP index, 8
			JG  lblLine10
			LEA ECX, line9
			PUSH ECX
			JMP lblContinuePush
			lblLine10 :
		CMP index, 9
			JG  lblEmptyLine
			LEA ECX, line10
			PUSH ECX
			JMP lblContinuePush
			lblEmptyLine :
		PUSH 0
			JMP lblContinuePush
			lblContinuePush :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27944] // 0x278C0
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27944] // 0x278C0
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x80]




			CMP index, 0
			JG lblColorLine2
			PUSH line1Color
			JMP lblContinueFuncCall

			lblColorLine2 :
		CMP index, 1
			JG lblColorLine3
			PUSH line2Color
			JMP lblContinueFuncCall

			lblColorLine3 :
		CMP index, 2
			JG lblColorLine4
			PUSH line3Color
			JMP lblContinueFuncCall

			lblColorLine4 :
		CMP index, 3
			JG lblColorLine5
			PUSH line4Color
			JMP lblContinueFuncCall

			lblColorLine5 :
		CMP index, 4
			JG lblColorLine6
			PUSH line5Color
			JMP lblContinueFuncCall

			lblColorLine6 :
		CMP index, 5
			JG lblColorLine7
			PUSH line6Color
			JMP lblContinueFuncCall

			lblColorLine7 :
		CMP index, 6
			JG lblColorLine8
			PUSH line7Color
			JMP lblContinueFuncCall

			lblColorLine8 :
		CMP index, 7
			JG lblColorLine9
			PUSH line8Color
			JMP lblContinueFuncCall

			lblColorLine9 :
		CMP index, 8
			JG lblColorLine10
			PUSH line9Color
			JMP lblContinueFuncCall

			lblColorLine10 :
		CMP index, 9
			JG lblNoColor
			PUSH line10Color
			JMP lblContinueFuncCall

			lblNoColor :
		PUSH 0
			JMP lblContinueFuncCall

			lblContinueFuncCall :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27944]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27944]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x84]

			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			ADD ECX, 0x1
			MOV DWORD PTR SS : [EBP - 0x28] , ECX

			JMP LoopEnd

			lblContinueExec :
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
			MOV EAX, DWORD PTR DS : [EDX + 0x670]


			PUSH CLIENT_RAW_0041C018 


			RETN
	}
}

_declspec(naked) void HookPatch::NKD_AddAmountItem() {
	__asm {
		MOV EAX, DWORD PTR SS : [EBP - 0x60]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		MOVSX EDX, WORD PTR DS : [ECX]
		CMP EDX, 1964
		JL lblNext
		CMP EDX, 0
		JG lblNext
		JMP lblContinueExec

		lblNext :
		PUSH ECX
			CALL CGlobalData::SepararItens
			TEST AL, AL
			JE lblContinueExec
			MOV BYTE PTR SS : [EBP - 0x5C] , 1
			JMP lblContinueExec

			lblContinueExec :

		PUSH CLIENT_RAW_0042005E


			RETN
	}
}


_declspec(naked) void HookPatch::NKD_GetCurrentResolution() {
	_asm {
		MOV EAX, DWORD PTR SS : [EBP - 0x2D4]
		PUSH DWORD PTR DS : [EAX + 0x10]

		MOV EAX, DWORD PTR SS : [EBP - 0x2D4]
		PUSH DWORD PTR DS : [EAX + 0x14]

		MOV EAX, DWORD PTR SS : [EBP - 0x2D4]
		PUSH DWORD PTR DS : [EAX + 0x18]

		CALL CGlobalData::HKD_GetResolution

		MOV ECX, DWORD PTR SS : [EBP - 0x2D4]
		CMP DWORD PTR DS : [ECX + 0x4] , 0
		PUSH CLIENT_RAW_00549F8E
		RETN
	}
}


_declspec(naked) void HookPatch::NKD_ChangeServerList() {
	_asm
	{
		CALL CGlobalData::HKD_ChangeServerList
		MOV EAX, 1
		PUSH CLIENT_RAW_0054219F
		RETN
	}
}

_declspec(naked) void HookPatch::NKD_KeyScapeControl() {
	__asm {
		CALL TMScene::HKD_KeyScapeControl
		CMP DWORD PTR DS : [CLIENT_RAW_01F6A0B0] , 1
		PUSH CLIENT_RAW_0044F46A
		RETN
	}
}


_declspec(naked) void HookPatch::NKD_MainLoop() {
	_asm {
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		PUSH EAX
		CALL SControl::MainLoop
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		CMP DWORD PTR DS : [EAX + 0x28] , TRUE
		JNZ jnzSECTION
		PUSH CLIENT_RAW_0040CEB9
		RETN
		jnzSECTION :
		PUSH CLIENT_RAW_0040CF0E
			RETN
	}
}

_declspec(naked) void HookPatch::NKD_LoadWordScene() {
	__asm {
		MOV DWORD PTR DS : [CLIENT_RAW_00981F60] , ECX
		PUSH CLIENT_RAW_004D920F
		MOV EAX, CLIENT_RAW_006D03B8
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, EDX
		MOV EAX, CLIENT_RAW_00499EC2
		CALL EAX
		PUSH EAX
		CALL TMScene::LoadSceneControl
		ADD ESP, 0x4
		RETN
	}
}



_declspec(naked) void HookPatch::NKD_STextBoxMouseController() {
	static unsigned int call_func = CLIENT_RAW_004021CB;
	__asm {
		MOV ECX, DWORD PTR SS : [EBP - 0xC]
		CALL call_func



		PUSH DWORD PTR SS : [EBP + 0x14]  // posy
		PUSH DWORD PTR SS : [EBP + 0x10]  // posx
		PUSH DWORD PTR SS : [EBP + 0x8]  // MouseMode
		PUSH DWORD PTR SS : [EBP - 0xC]  // element
		CALL TMScene::SEditableTextMouseControl
		ADD ESP, 0x10
		PUSH 00406374h
		RETN

	}
}

_declspec(naked) void HookPatch::NKD_ActionOnItem() {  
	__asm {
		push dword ptr ss : [ebp - 0x10]
		push dword ptr ss : [ebp - 0x18]
		push dword ptr ss : [ebp - 0x14]
		push dword ptr ss : [ebp + 0x8]
		push dword ptr ss : [ebp - 0x19C]

		call SGridControl::ActionOnItem
		add esp, 0x14
		cmp eax, 1
		jne continueExec

		push CLIENT_RAW_00420C25
		retn

		continueExec :
		cmp dword ptr ss : [ebp + 0x8] , 0x201
			push CLIENT_RAW_0041F88C
			retn
	}
}

_declspec(naked) void HookPatch::NKD_Cam() {
	__asm {
		MOV EAX, DWORD PTR SS : [EBP - 0xC]
		MOV ECX, DWORD PTR SS : [EBP - 0xC]
		MOV DWORD PTR DS : [ECX + 0xC0] , 0x41A00000
		FLD DWORD PTR DS : [EAX + 0x34]
		FCOMP DWORD PTR DS : [ECX + 0xC0]
		FSTSW AX
		TEST AH, 0x41
		JNZ label_saida

		PUSH CLIENT_RAW_004B47CE






		RETN

		label_saida :
		PUSH CLIENT_RAW_004B47E9




			RETN
	}
}

_declspec(naked) void HookPatch::NKD_CommandControl() {  
	__asm {
		MOV EAX, DWORD PTR SS : [EBP - 0x98]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x98]
		CALL DWORD PTR DS : [EDX + 0x88]

		PUSH EAX
		CALL UserFunctions::CommandControl
		ADD ESP, 0x08

		TEST EAX, EAX
		JNZ chk_other_cmd

		MOV EAX, 0x01
		MOV ECX, CLIENT_RAW_00472C29


		JMP ECX

		chk_other_cmd :

		MOV ECX, CLIENT_RAW_00466CE9


			JMP ECX
	}
}

_declspec(naked) void HookPatch::NKD_ShowItemDesc() {
	
	__asm {
		push dword ptr ss : [ebp - 0x18]
		push dword ptr ss : [ebp - 0x14]
		push dword ptr ss : [ebp - 0x19C]

		call SGridControl::ItemTooltipe
		add esp, 0xC

		mov dword ptr ss : [ebp - 0x54] , eax
		cmp dword ptr ss : [ebp - 0x54] , 2
		push CLIENT_RAW_0041FEBF
		retn
	}
}

_declspec(naked) void HookPatch::NKD_CantMoveItem() {
	
	__asm {
		push dword ptr ss : [ebp + 0xC]
		push dword ptr ss : [ebp + 0x8]
		push dword ptr ss : [ebp - 0x20C]

		call SGridControl::CantMoveItemGrid
		add esp, 0xC
		cmp eax, 1
		jne continueExec

		push CLIENT_RAW_00412808
		retn

		continueExec :
		mov ecx, dword ptr ss : [ebp - 0x1D0]
			push ecx
			push CLIENT_RAW_004127E8
			retn
	}
}

_declspec(naked) void HookPatch::NKD_HandleSelCharScene() {
	
	__asm {
		push dword ptr ss : [ebp + 0x8]
		call ClientFunctions::HKD_ControlEventClick
		test eax, eax
		jnz continueExec

		push 004AA13Bh

		retn

		continueExec :
		cmp dword ptr ss : [ebp + 0x8] , 0x1629
			push CLIENT_RAW_004A8AE5
			retn
	}
}

_declspec(naked) void HookPatch::NKD_HandleServerScene() {
	
	__asm {
		push dword ptr ss : [ebp + 0x8]
		call ClientFunctions::HKD_ControlEventClick
		test eax, eax
		jnz continueExec

		push CLIENT_RAW_004B30E0  
						 retn

						 continueExec :      
		cmp dword ptr ss : [ebp + 0x8] , 0x10006
			push CLIENT_RAW_004B1665
			retn
	}
}

_declspec(naked) void HookPatch::NKD_HandleWorldScene() {
	
	__asm {
		push dword ptr ss : [ebp + 0x8]
		call ClientFunctions::HKD_ControlEventClick
		test eax, eax
		jnz continueExec

		push CLIENT_RAW_00472C27  
		retn

		continueExec :  
		cmp dword ptr ss : [ebp + 0x8] , 0x10161
			push CLIENT_RAW_0046AA04
			retn
	}
}

_declspec(naked) void HookPatch::NKD_ControlMessageBox() {
	
	__asm {


		mov dword ptr ss : [ebp - 0x454] , ecx

		push dword ptr ss : [ebp + 0x10]
		push dword ptr ss : [ebp - 0x454]

		call TMScene::ControlMessageBox
		add esp, 0x8

		cmp eax, 1

		jne continueExec

		push CLIENT_RAW_00463D2E
		retn

		continueExec :  // by seitbnao
		push CLIENT_RAW_0046373E
			retn
	}
}

_declspec(naked) void HookPatch::NKD_FixMageMacro() {
	__asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x148]
		CMP DWORD PTR DS : [ECX + 0x83254] , 0x0
		JNZ lbl_JMP
		PUSH CLIENT_RAW_004968C0
		RETN

		lbl_JMP :
		PUSH CLIENT_RAW_00496AAC
			RETN
	}
}

_declspec(naked) void HookPatch::NKD_ProcessUseItem() {

	__asm {
		mov eax, dword ptr ds : [edx + 0x4C]
		mov dword ptr ss : [ebp - 0x10] , eax

		push dword ptr ss : [ebp + 0x10]
		push dword ptr ss : [ebp + 0xC]
		push dword ptr ss : [ebp + 0x8]
		push dword ptr ss : [ebp - 0x3B8]

		call SGridControl::ProcessUseItemA
		add esp, 0x10
		cmp eax, 1
		jne continueExec

		push CLIENT_RAW_0041F73D
		retn

		continueExec :
		push CLIENT_RAW_0041D91B
			retn
	}
}

_declspec(naked) void HookPatch::NKD_ProcessNpcClick() {
	
	__asm {
		mov eax, dword ptr ss : [ebp - 0x3C]
		mov ecx, dword ptr ds : [eax + 0xBC]
		push ecx
		call UINPCControl::ProcessNPCClick

		cmp eax, 1
		jne continueExec

		push CLIENT_RAW_00460257
		retn

		continueExec :
		mov ecx, dword ptr ss : [ebp - 0x4]
			cmp dword ptr ds : [ecx + 0x20] , 0
			push CLIENT_RAW_0045FB73
			retn
	}
}

_declspec(naked) void HookPatch::NKD_ControlKeyPress() {
	
	__asm {
		mov dl, byte ptr ss : [ebp + 0x8]
		push edx
		push dword ptr ss : [ebp - 0x8]

		call TMScene::ControleDeTeclas
		add esp, 0x8

		cmp eax, 1

		jne continueExec

		push CLIENT_RAW_00453FDD  //.B8 01000000    MOV EAX, 1


		retn

		continueExec :
		mov eax, dword ptr ss : [ebp - 0x8]
			mov ecx, dword ptr ds : [eax + 0xCC]
			push CLIENT_RAW_00453B93  //.E8 9886FBFF    CALL WYD.0040C230


			retn
	}
}

_declspec(naked) void HookPatch::NKD_EndSendScore() {
	__asm {//by seitbnao
		MOV ECX, DWORD PTR SS : [EBP - 0xC]
		MOV DWORD PTR FS : [0] , ECX
		CALL HookPatch::HKD_EndSendScore
		push CLIENT_RAW_0044B136
		retn
	}
}

_declspec(naked) void HookPatch::NKD_TControleDeteclas() {  // by seitbnao

	__asm
	{//nop 1


		MOV DL, BYTE PTR SS : [EBP + 0x8]//key
		PUSH EDX
		PUSH DWORD PTR SS : [EBP - 0x8C]//component

		CALL SEditableText::TControleDeTeclas
		ADD ESP, 0x8
		CMP EAX, TRUE
		JNE continueExec

		PUSH CLIENT_RAW_00406FC3//00406FC3   . B8 01000000    MOV EAX,1
		RETN

		continueExec :
		MOV ECX, DWORD PTR SS : [EBP - 0x8C]
			PUSH CLIENT_RAW_00406499
			RETN

	}
}

_declspec(naked) void HookPatch::NKD_TMHumanUpdate() {
	// by   SeiTbNao
	static int continue_cmp = CLIENT_RAW_004E3762;
	__asm {
		PUSH DWORD PTR SS : [EBP - 0x14]
		CALL TMHuman::HKD_TMHumanUpdate
		ADD ESP, 0x4
		MOV DWORD PTR SS : [EBP - 0x70] , ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x70]
		JMP continue_cmp
		RETN
	}
}















