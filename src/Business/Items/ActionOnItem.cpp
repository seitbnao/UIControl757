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
#include <time.h>

/*
    Processa ações sobre o item
*/

int SGridControl::ActionOnItem(SGridControl* ItemGrid, int Action, int Row,int Column, int HaveItem) 
{

    if (!ItemGrid) 
        return TRUE;

    auto ItemClass = ItemGrid->getSGridControlItem(Row, Column);

    if (!ItemClass) 
        return 0;

    auto Item = ItemClass->getItem();

    if (!Item || HaveItem == 0) 
        return 0;

    if (Item->sIndex <= 0 || Item->sIndex >= 6500) 
        return TRUE;
 
    
    return 0;
}