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

class UserFunctions : public Singleton<UserFunctions> {
private:
	UserFunctions() = delete;
	UserFunctions(const UserFunctions&) = delete;
	UserFunctions& operator=(const UserFunctions&) = delete;

public:
	static STRUCT_MOB* getPlayerMob();

	static STRUCT_ITEMCARGO* getPlayerCargo();

	static STRUCT_ITEM* getItemPointer(int Slot, int SlotType);

	static bool __stdcall CommandControl(char* String);
};

extern UserFunctions* g_UserFunc;
