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
#include <iostream>
#include <fstream>
#include <list>
 

ClientFunctions* g_Func = nullptr;





//Envia uma menssagem na lista de experiencia sem erros de fechar chat
void ClientFunctions::SendExpMenssage(DWORD Color, const char* Message, ...)
{
	if (!Message)
		return;

	auto scene = TMScene::Instance();
	if (!scene || scene->getFieldScene() != SceneWorld)
		return;


	//by seitbnao
	static char buffer[256] = { 0, };
	va_list va;
	va_start(va, Message);
	vsprintf_s(buffer, Message, va);
	va_end(va);
	SListBox* control = scene->FindControl<SListBox>(65944);
	if (!control)
		return;

	auto text = SListBox::CreateSelectionLabel(buffer, Color);
	if (text)
		control->add(text);
}


STRUCT_SPELL* ClientFunctions::getSkillData(int SkillID)
{//att

	static auto* SkillDATA =
		reinterpret_cast<STRUCT_SPELL*>(ClientAddresses::Memory::SkillData);

	if (SkillID < 0 || SkillID >= 248)
		return nullptr;

	return &SkillDATA[SkillID];
}

STRUCT_ITEMLIST* ClientFunctions::getItemList(int itemId)
{//att
	if (itemId == NULL || itemId < 0 || itemId >= 6500)
		return NULL;

	static auto* itemlist =
		reinterpret_cast<STRUCT_ITEMLIST*>(ClientAddresses::Memory::ItemList);

	if (itemId >= 6500)
		return nullptr;

	return &itemlist[itemId];
}

void ClientFunctions::ShowEffect()
{//att

 

	if (*(int*)ClientAddresses::Memory::EffectFlag0)
	{
		__asm
		{
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_0] , 0
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_1] , 0
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_2] , 0
		}
	}
	else
	{
		__asm
		{
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_0] , 1
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_1] , 1
			MOV DWORD PTR DS : [CLIENT_ADDR_EFFECT_FLAG_2] , 1
		}
	}
}


const char* ClientFunctions::strFormat(const char* Message, ...)
{
	 
	static thread_local char buffer[1024] = { 0, };
	memset(buffer, 0, sizeof buffer);
	if (!Message)
		return buffer;
 
	va_list va;
	va_start(va, Message);
	vsprintf_s(buffer, sizeof buffer, Message, va);
	va_end(va);

 

	return  buffer;
}



const vector<string> ClientFunctions::explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}


char* ClientFunctions::ReadBinaryFile(const char* filename, int* read)
{
	try {
		if (!filename || !read)
			return nullptr;

		ifstream ifs(filename, ios::binary | ios::ate);
		if (!ifs)
			return nullptr;

		ifstream::pos_type pos = ifs.tellg();
		int length = pos;
		if (length <= 0)
			return nullptr;

		char* pChars = new char[length];
		ifs.seekg(0, ios::beg);
		ifs.read(pChars, length);
		ifs.close();
		*read = length;
		return pChars;
	}
	catch (...)
	{
		return 0;
	}
}

void ClientFunctions::setLog(const char* Str, ...)
{
	if (!Str)
		return;

	char buffer[0x100] = { 0, };
	memset(buffer, 0, sizeof buffer);
	va_list va;
	va_start(va, Str);
	vsprintf_s(buffer, sizeof buffer, Str, va);
	va_end(va);

	LogManager::Write(buffer);
}

void ClientFunctions::FlushLog()
{
	LogManager::Flush();
}

#define addLog(Str) ClientFunctions::setLog(Str)
