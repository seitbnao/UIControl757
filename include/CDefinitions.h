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
#include <Windows.h>
#include <vector>
#include <list>

#pragma warning( push )
#pragma warning( disable : 4005)

typedef struct
{
	int colun;
	int row;
}STRUCT_REQUEST;

#define callCdecl(addr, Retn, ...) (*(Retn (__cdecl*)(__VA_ARGS__)) addr)
#define callfastcall(addr, Retn, ...) (*(Retn (__fastcall*)(__VA_ARGS__)) addr)
#define callThiscall(addr, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) addr)
#define callstdcall(addr, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) addr)
#define callThisfastcall(addr, Retn, ...) (*(Retn (__fastcall*)(__VA_ARGS__)) addr)
#define callThiscallMethod(This, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)This) + (dwIndex * 4))))
#define callThiscallMethod_2(This, dwIndex, Retn, ...) (*(Retn (__thiscall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)This) + (dwIndex * 1))))
#define callstdcallMethod(This, dwIndex, Retn, ...) (*(Retn (__stdcall*)(__VA_ARGS__)) (*(PDWORD)((*(PDWORD)This) + dwIndex)))

//newbie defines kaka
#define and &&
#define or ||
#define xor ^
#define not !
#define se if
#define senao else
#define senaose else if
#define fazer do
#define enquanto while
#define igual ==
#define diferente !=
#define maiorigual >=
#define maior >
#define menorigual <=
#define menor <
#define verdadeiro true
#define falso false
//HOOKS
#define JMP_NEAR(addr,function,nop)(HookMgr::instance().setHook(eHookType::JMP, addr, HookMgr::instance().getAddress(&function),nop));
#define JMP_NEAR(addr,function)(HookMgr::instance().setHook(eHookType::JMP, addr, HookMgr::instance().getAddress(&function)));
#define JE_NEAR(addr,function)(HookMgr::instance().setHook(eHookType::JE, addr, HookMgr::instance().getAddress(&function)));
#define CALL_NEAR(addr,function)(HookMgr::instance().setHook(eHookType::CALL, addr, HookMgr::instance().getAddress(&function)));
#define DEF_STR(str, addr) strcpy((CHAR*)addr, (CONST CHAR*)str)
#pragma warning( pop ) 
struct STRUCT_UISTRING
{
	char String[64];
	const char* get()
	{

		if (String[0] == 0)
			return "";

		for (int i = 0; i < 64; ++i)
		{
			if (String[i] == ' ')
				String[i] = '_';
		}

		return String;
	}
};
//Tipos de controles conhecidos do WYD
enum eControlType
{
	Panel = 1,
	Button = 2,
	CheckBox = 3,
	Unk00 = 4,
	unk2 = 5,
	ListBox = 6,
	ListBoxServerItem = 7,
	TypeSMessageBox = 8,
	TypeSMessagePanel = 9,
	Progress = 10,
	ScrollBar = 11,
	Text = 12,
	TextBox = 13,
	unk7 = 14,
	Obj3d = 15,
	Grid = 16,
	PagingBox = 32,
};

//Tipo de Cenário
enum eSceneType : int
{
	SceneBeforeLogin = 30005,
	SceneLogin = 30004,
	SceneSelChar = 30001,
	SceneWorld = 30000,

};

//Tamanho das Classes de cada controle, é usado tb para indentificar melhor no .c
enum eAllocType : int
{
	ePanel = 0x1E4,
	eButton = 0x208,
	eLabel = 0xE4C,
	eProgressBar = 0x374,

};


//Endereço Base de cada controle
enum eClassType : DWORD
{
	eTextLabel_ = CLIENT_RAW_005F4628,
	eButtonLabel_ = CLIENT_RAW_005F46D4,
	eProgressBar_ = CLIENT_RAW_005F489C,
	eGridItem_ = CLIENT_RAW_005F5090,
	e3DObject = CLIENT_RAW_005F4598,
	ePanel_ = CLIENT_RAW_005F450C,
	eEditBox = CLIENT_RAW_005F49E4,
	eCheckBox = CLIENT_RAW_005F4DE4,
	eListBox = CLIENT_RAW_005F4D58,
	eUnkNowClass_5F5174 = CLIENT_RAW_005F5174,
};

//Size da classe de cada controle
enum eClassSizes : int
{
	eTextLabel_size = 3660,
	eButtonLabel_size = 520,
	eProgressBar_size = 884,
	eGridItem_size = 1444,
	e3DObject_size = 464,
	ePanel_size = 484,
	eEditBox_size = 4196,
	eCheckBox_size = 500,
	eListBox_size = 4540,
	eItemClass = 1656,
	//é usada dentro da SetLabel
	eUnkNowClass_5f5174 = 432,
};


#define COLORBASE	0xFF000000
#define BlueAdd  -4473857
enum ClientColor : DWORD
{
	Black = COLORBASE + 0x000000,
	White = COLORBASE + 0xFFFFFF,
	Red = COLORBASE + 0xFF0000,
	Blue = COLORBASE + 0x0000FF,
	Yellow = COLORBASE + 0xFFFF00,
	LightGreen = COLORBASE + 0x00FF00,
	Orange = COLORBASE + 0xFF9900,
	Blue2 = COLORBASE + 0x3399FF,
	Pink = COLORBASE + 0xFF0066,
	Pink2 = COLORBASE + 0xCC0033,
	DarkGolden1 = COLORBASE + 0xFFB90F,
	DarkGolden3 = COLORBASE + 0xCD950C,
	DarkOrchid1 = COLORBASE + 0xBF3EFF,
	Orchid = COLORBASE + 0xD966FF,
	GreenWeak = COLORBASE + 0xD2F4D2,
	Grey = COLORBASE + 0x808080,
	RoyalBlue = COLORBASE + 0x4682B4,
	
	Salmon = COLORBASE + 0xFA8072,
	DarkSalmon = COLORBASE + 0xE9967A,
	LightSalmon = COLORBASE + 0xFFA07A,
	Coral = COLORBASE + 0xFF7F50,
	Tomato = COLORBASE + 0xFF6347,
};

//Constantes da Tooltipe
static short zHandles[] = { 773 ,774 ,775 ,776 ,777 ,784 ,794 ,795 ,796 ,797 ,798 ,799 ,800 ,801 };
#define MAX_LINE (sizeof(zHandles) / sizeof(short))

enum eMenssageBox : int
{
	GameMasterSuport = 1,
	ItemClick = 10000,
	//... ir adicionando
};


enum eActionType : int
{
	MouseHover = 512,
	LeftClickPressed = 513,
	LeftClickUnPressed = 514,
	RightClickPressed = 516,
	RightClickUnPressed = 517,
};

#include "Structs.h"