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

class SGridControl : public SControl {  // 1444 4540
public:
    int Unks[100];
    unsigned int Pointer;
    int InitCount;
    int MaxItemList;
    unsigned int PointerItem[40];

public: 
    //----- (0040DE4C) --------------------------------------------------------
    static SGridControl* Create(int sprit, int Coluna, int Linha, float x, float y,
        float Width, float Height, int EquipPosition) {  // att
        DWORD pAllocWindow = SControl::AllocClass(0x5A4u);
        return callThiscall(CLIENT_RAW_0040DE4C, SGridControl*, DWORD, int, int, int, float,
            float, float, float,
            int)(pAllocWindow, sprit, Coluna, Linha, x, y, Width, Height, EquipPosition);
    }

    int getHandle(void) {  // retorna o id do grid
        return SControl::getHandle();
    }
    SGridControlItem* getItemClass_OL3(int Linha = 0, int Coluna = 0) {
        // att
        return callThiscall(CLIENT_RAW_0040F66A, SGridControlItem*, SGridControl*, int,
            int)(this, Linha, Coluna);
    }
    SGridControlItem* getItemClass_OL2(int Linha = 0, int Coluna = 0) {
        // att
        return callThiscall(CLIENT_RAW_0040F819, SGridControlItem*, SGridControl*, int,
            int)(this, Linha, Coluna);
    }
    SGridControlItem* getSGridControlItem(int Linha = 0, int Coluna = 0) {
        // att
        return callThiscall(CLIENT_RAW_0040F9B2, SGridControlItem*, SGridControl*, int,
            int)(this, Linha, Coluna);
    }
    int DeleteItemOnGrid(int coluna = 0, int linha = 0) {  // apaga o item da grid
      // att
        return callThiscall(CLIENT_RAW_0040F43A, int, SGridControl*, int, int)(this, coluna,
            linha);
    }
    int ClearAllGrid() {  // apaga todos os itens da grid
      // att
        return callThiscall(CLIENT_RAW_0040E35A, int, SGridControl*)(this);
    }
    signed int CreateItemonGrid_3DObject(SGridControlItem* EmptyItem, int a3,
        int a4) {
        // cria um item comum
        // att
        return callThiscall(CLIENT_RAW_0040E516, int, SGridControl*, SGridControlItem*, int,
            int)(this, EmptyItem, a3, a4);
    }
    signed int CreateItemonGrid_24x24(SGridControlItem* EmptyItem, int a3,
        int a4) {
        // cria um item comum com icone 24x24
        // att
        return callThiscall(CLIENT_RAW_0040E673, int, SGridControl*, SGridControlItem*, int,
            int)(this, EmptyItem, a3, a4);
    }
    signed int CreateItemonGrid_35x35(SGridControlItem* EmptyItem, int a3,
        int a4) {
        // cria um item comum com icone 35x35
        // att
        return callThiscall(CLIENT_RAW_0040E7F4, int, SGridControl*, SGridControlItem*, int,
            int)(this, EmptyItem, a3, a4);
    }
    void SendUseItem(int j, int i, int mousehover = 1) {
        return callThiscall(CLIENT_RAW_0041D8D1, void, SGridControl*, int, int,
            int)(this, j, i, mousehover);
    }
    void setNoitem() {
        this->ClearGrid();
        auto item = reinterpret_cast<STRUCT_ITEM*>(
            SControl::AllocClass(sizeof STRUCT_ITEM));
        item->sIndex = 0;
        this->PutItemOnGrid(item);
    }
    int ClearGrid(int col = 0,
        int row = 0) {  // apaga um item de forma correta sem ter crashs
        auto EmptyItem = this->getSGridControlItem(col, row);
        if (EmptyItem) {
            auto cItem = EmptyItem->getItem();
            if (cItem) {
                this->DeleteItemOnGrid(col, row);
                return 1;
            }
            else
                return 0;
        }
        return 0;
    }
    signed int PutItemOnGridWithDelete(STRUCT_ITEM* Item, int coluna = 0,
        int linha = 0) {  // Coloca um item no grid
        auto EmptyItem = this->getSGridControlItem(coluna, linha);
        if (EmptyItem) {
            auto cItem = EmptyItem->getItem();
            if (cItem) return 0;
        }
        else {
            auto Empty = SGridControlItem::Create(0, Item, 0.0, 0.0);
            if (Empty) {
                if (Empty->getItem()->sIndex <= 0 ||
                    Empty->getItem()->sIndex >= 6500) {
                    this->ClearGrid(coluna, linha);
                    return 0;
                }
                return this->CreateItemonGrid_35x35(Empty, coluna, linha);
            }
        }
        return 0;
    }


    SGridControlItem* PutSkill(STRUCT_ITEM* Item, int coluna = 0, int linha = 0)
    {
        auto Empty = SGridControlItem::Create(NULL, Item);
        if (Empty) {
              this->MakeFunction<void, SGridControl*, SGridControlItem*, int, int  >(this, 148, Empty, coluna, linha);
              return Empty;
        }
        return Empty;
    }

    SGridControlItem* PutItemOnGrid(STRUCT_ITEM* Item, int coluna = 0,
        int linha = 0) {  // Coloca um item no grid
        auto EmptyItem = this->getSGridControlItem(coluna, linha);
        if (EmptyItem) {
            auto cItem = EmptyItem->getItem();
            if (cItem) return 0;
        }
        else {
            auto Empty = SGridControlItem::Create(NULL, Item);
            if (Empty) {
                CreateItemonGrid_35x35(Empty, coluna, linha);
                return Empty;
            }
        }
        return 0;
    }
    signed int PutSkillOnGrid(
        STRUCT_ITEM* Item, int coluna = 0,
        int linha = 0) {  // coloca um item com icone 24x24 no grid
        auto EmptyItem = this->getSGridControlItem(coluna, linha);
        if (EmptyItem) {
            auto cItem = EmptyItem->getItem();
            if (cItem) return 0;
        }
        else {
            auto Empty = SGridControlItem::Create(0, Item, 0.0, 0.0);
            if (Empty) return CreateItemonGrid_24x24(Empty, coluna, linha);
        }
        return 0;
    }

    void UpdateGridItem(SGridControlItem* itemCLass, int i = 0, int j = 0) {
        return this->MakeFunction<void, SGridControl*, SGridControlItem*, int, int>(
            this, 140, itemCLass, i, j);
    }
    signed int SendUpdateGrid(STRUCT_ITEM* Item, int coluna = 0,
        int linha = 0) {  // Coloca um item no grid
        auto EmptyItem = this->getSGridControlItem(coluna, linha);
        if (EmptyItem) {
            auto cItem = EmptyItem->getItem();
            if (cItem) return 0;
        }
        else {
            auto Empty = SGridControlItem::Create(NULL, Item);
            if (Empty) {
                this->UpdateGridItem(Empty, coluna, linha);
                return 1;
            }
        }
        return 0;
    }
    BOOL HaveItemOnGrid(int row = 0, int Column = 0) {
        return this->MakeFunction<BOOL, SGridControl*, int, int>(this, 184, row,
            Column);
    }

    SGridControlItem* ItemOnGrid(int row = 0, int Column = 0) {
        return this->MakeFunction<SGridControlItem*, SGridControl*, int, int>(this, 168, row,
            Column);
    }

    void setUnk(int unk = -65536) { *(DWORD*)(*(DWORD*)this + 148) = unk; }

    void setCurrentStore(int NpcID) {
        *(DWORD*)(*(DWORD*)(reinterpret_cast<uint32_t>(this) + 1028)) = NpcID;
    }

    int getColum() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 468);
    }
    int getRow() { return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 464); }
    int getMaxRow() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 472);
    }
    int getMaxColunm() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 476);
    }
    int getInvSlot() {
        int v38 = 5 * this->getColum() + this->getRow();
        return v38 % 9 + 27 * (v38 / 9);
    }

    int getCarryID() {
        int carryID = 0;
        if (this->Handle >= 67072 && this->Handle <= 67075) {
            carryID = 15 * (this->Handle - 67072);
            if (carryID < 0 || carryID > 45) carryID = 0;
        }
        return carryID;
    }

    int getCarrySlot(int l = 0, int j = 0) {
        if (auto itemclass = this->getSGridControlItem(l, j)) {
            return itemclass->getInvSlot() + this->getCarryID();
        }
        return -1;
    }
    // HOOKS
    static int CantMoveItemGrid(SGridControl* ItemGrid, int Column, int Row);
    static int ActionOnItem(SGridControl* ItemGrid, int Action, int Row,int Column, int HaveItem);
    static void ItemTooltipe(SGridControl* ItemGrid, int Row, int Column);
    static int ProcessUseItemA(SGridControl* ItemGrid, int Row, int Column, int Unk);
};
