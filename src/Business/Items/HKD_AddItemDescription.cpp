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

int32_t HookPatch::HKD_AddItemDescription(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, DWORD* line1Color, DWORD* line2Color, DWORD* line3Color, DWORD* line4Color, DWORD* line5Color, DWORD* line6Color, DWORD* line7Color, DWORD* line8Color, DWORD* line9Color, DWORD* line10Color)
{
	if (!item || !line1 || !line2 || !line3 || !line4 || !line5 ||
		!line6 || !line7 || !line8 || !line9 || !line10 ||
		!line1Color || !line2Color || !line3Color || !line4Color || !line5Color ||
		!line6Color || !line7Color || !line8Color || !line9Color || !line10Color)
		return 0;

	char* lines[] = { line1, line2, line3, line4, line5, line6, line7, line8, line9, line10 };
	DWORD* colors[] = { line1Color, line2Color, line3Color, line4Color, line5Color, line6Color, line7Color, line8Color, line9Color, line10Color };
	BusinessRules::ItemDescription::Builder description(lines, colors);
	description.Clear();

	auto addLine = [&description](DWORD color, const char* format, ...) -> bool
		{
			if (!format)
				return false;

			char text[BusinessRules::ItemDescription::LineBufferSize] = { 0 };
			va_list args;
			va_start(args, format);
			const auto written = vsprintf_s(text, sizeof text, format, args);
			va_end(args);

			if (written <= 0)
				return false;

			return description.Add(color, text);
		};

	if (item->sIndex <= 0 || item->sIndex >= 6500)
		return 0;

	auto* itemlist = ClientFunctions::getItemList(item->sIndex);
	if (!itemlist)
		return 0;

	auto mob = UserFunctions::getPlayerMob();
	if (!mob)
		return 0;

	if (item->sIndex == 412)
		addLine(White, "Item ID: %d", item->sIndex);

	return description.Count();
}
