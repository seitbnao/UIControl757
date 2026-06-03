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

class SGridControlItem : public SControl {
public:
    BYTE Unks[0x678u];

public:
    // Cria um slot vago na gridlist
    static SGridControlItem* Create(int Grade, STRUCT_ITEM* a3, float Width = 0.0,
        float Height = 0.0) {
        DWORD pAllocItem = SControl::AllocClass(0x8);

        /*auto item = reinterpret_cast<STRUCT_ITEM*>(pAllocItem);

        memcpy(item, a3, sizeof STRUCT_ITEM);*/

        DWORD pAllocWindow = SControl::AllocClass(0x678u);
        return callThiscall(CLIENT_RAW_0040D36E, SGridControlItem*, DWORD, int, STRUCT_ITEM*,
            float, float)(pAllocWindow, Grade, a3, Width, Height);
    }

    int Clear() { return callThiscall(CLIENT_RAW_0040DB2D, int, SGridControlItem*)(this); }

    STRUCT_ITEM* getItem() {
        return callThiscall(CLIENT_RAW_00421B10, STRUCT_ITEM*, SGridControlItem*)(this);
    }

    int getColunm() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 468);
    }

    // retorna a linha em q o item esta
    int getRow() { return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 464); }

    // retorna o tamanho maximo de itens permitido no grid
    int getMaxRow() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 472);
    }

    // retorna a coluna em q o item esta
    int getMaxColunm() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 476);
    }

    // pega um slot na janela de NPC ou banqueiro
    int getInvSlotNPC() {
        int v38 = 5 * this->getColunm() + this->getRow();
        return v38 % 9 + 27 * (v38 / 9);
    }

    // pega um slot na janela de NPC ou banqueiro
    int getInvSlot() {
        int v38 = 5 * this->getColunm() + this->getRow();
        return ((v38 % 15 + 15 * (v38 / 15)));
    }
    // retorna o handle
    int getHandle() { return SControl::getHandle(); }

    // retorna de o slot é válido para receber um item
    BOOL isValidRowColunm(int row, int col) {
        return callThiscall(CLIENT_RAW_0040DD96, BOOL, SGridControlItem*, int,
            int)(this, row, col);
    }

    // Altera a borda da Refinação
    void setItemBorder(short BorderID) {
        this->setValue<SGridControlItem*, short>(this, 84, BorderID);
    }

    // retorna o ID da borda da refinação
    WORD getItemBorder() {
        return this->getValue<int, SGridControlItem*>(this, 84);
    }

    // seta o Sprite olhar na UitextureList
    void setSpriteID(int SetIndex) {
        this->setValue<SGridControlItem*, int>(this, 40, SetIndex);
    }

    // retorna o SpriteID
    DWORD getSpriteID() {
        return this->getValue<int, SGridControlItem*>(this, 40);
    }

    // Seta o Icone do Item
    void setIconID(int Icon) {
        this->setValue<SGridControlItem*, int>(this, 41, Icon);
    }
    // Seta o Icone do Item
    void set25(int Icon) {
        this->setValue<SGridControlItem*, int>(this, 25, Icon);
    }
    // Retorna o ID doIcone
    DWORD getIconID() { return this->getValue<int, SGridControlItem*>(this, 41); }

    void setSelected(bool val = true) {
        this->setValue<SGridControlItem*, int>(this, 148,
            val == true ? -65536 : -1);
    }

    bool getSelected() {
        return this->getValue<int, SGridControlItem*>(this, 148) == -65536 ? true
            : false;
    }
    // Seta um novo item na struct
    void setItemStruct(STRUCT_ITEM* Item) {
        this->setObject<SGridControlItem*, STRUCT_ITEM*>(this, 412, Item);
    }

    // Seta delay
    void setDelay(float Delay) {
        this->setValueTyped<SGridControlItem*, float>(this, 1652, Delay);
    }

    char* getString() {
        return this->getValue<char*, SGridControlItem*>(this, 172);
    }

    STRUCT_ITEM* getItem2() {
        return this->getValue<STRUCT_ITEM*, SGridControlItem*>(this, 1648);
    }

    void setString(const char* str) {
        strcpy((char*)(reinterpret_cast<unsigned int>(this) + 172), str);
    }

    DWORD getColor() {
        return this->getValue<DWORD, SGridControlItem*>(this, 37);
    }
    SText* getStext() {
        return this->getValue<SText*, SGridControlItem*>(this, 296);
    }

    TMFont2* getTMFont() {
        return this->getValue<TMFont2*, SGridControlItem*>(this, 432);
    }

    void setString(const char* Str, int Color) {
        if (auto font = this->getTMFont()) {
            this->setString(Str);
            font->SetString(Str, Color);
        }
    }

    signed int setStringValue(int value) {
        return callThiscall(CLIENT_RAW_004036FB, signed int, SGridControlItem*, int)(this,
            value);
    }
    void setColor(int color) {
        this->setValue<SGridControlItem*, int>(this, 0x94, color);
    }

    void setIconConfig(int Textura, int IconeID) {
        *((DWORD*)this + 25) = 4;
        *((DWORD*)this + 40) = Textura;
        *((DWORD*)this + 41) = IconeID;
    }

    void setIconConfig(int IconeID) {
        *((DWORD*)this + 25) = 4;
        *((DWORD*)this + 40) = 526;
        *((DWORD*)this + 41) = IconeID;
    }

    void _rem(int value = 1)
    {
        (**(void(__thiscall***)(SGridControlItem*, DWORD))this)(this, value);
    }
};
