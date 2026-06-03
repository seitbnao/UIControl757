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

int16_t HookPatch::AcceptNewEquipment(int nPos)
{
	int16_t SlotPos = -1;
	switch (nPos)
	{
	case 2://Elmo
		SlotPos = 1;
		break;
	case 4:
		SlotPos = 2;
		break;
	case 8:
		SlotPos = 3;
		break;
	case 16:
		SlotPos = 4;
		break;
	case 32:
		SlotPos = 5;
		break;
	case 64:
		SlotPos = 6;
		break;
	case 128:
		SlotPos = 7;
		break;
	case 256:
		SlotPos = 8;
		break;
	case 512:
		SlotPos = 9;
		break;
	case 1024:
		SlotPos = 10;
		break;
	case 2048:
		SlotPos = 11;
		break;
	case 4096:
		SlotPos = 12;
		break;
	case 8192:
		SlotPos = 13;
		break;
	case 16384://Montaria
		SlotPos = 14;
		break;
	case 32768://Capas
		SlotPos = 15;
		break;
	case 65536://Equipamento Novo
		SlotPos = 16;
		break;
	case 131072://Equipamento Novo
		SlotPos = 17;
		break;
	}
	 

	return SlotPos;
}