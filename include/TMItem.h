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


class TMItem : public Singleton<TMItem> 
{
public:
    TMItem* Instance() { return reinterpret_cast<TMItem*>(this->getTMItem()); }

    static uint32_t getTMItem() { 
        static uint32_t rtnValue = 0;

        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_ADDR_SOCKET_INSTANCE]
            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return uint32_t();

        return rtnValue;
    }

    static TMItem* getItemFromIndex(int i) {
        return (*(TMItem * (__thiscall**)(int, DWORD))(
            *(DWORD*)TMItem::getTMItem() + 56))(TMItem::getTMItem(), i);
    };

    int getPosX() {
        return this->toInt(SControl::getValue<float, TMItem*>(this, 616));
    }
    int getPosY() {
        return this->toInt(SControl::getValue<float, TMItem*>(this, 620));
    }
    int toInt(float value) {
        return SControl::CallCdecl<int, float>(CLIENT_RAW_005C5B70, value);
    }
    STRUCT_ITEM* getItem() {
        return SControl::getValue<STRUCT_ITEM*, TMItem*>(this, 232);
    }
};
