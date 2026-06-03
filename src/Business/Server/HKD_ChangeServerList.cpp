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

void CGlobalData::HKD_ChangeServerList() {
    struct STRUCT_SERVERLIST {
        struct {
            struct {
                char Site[BusinessRules::ServerList::AddressSize];
            } ChanellList[BusinessRules::ServerList::ChannelCount];
        } ServerList[BusinessRules::ServerList::ServerCount];
    };

    if (auto temp = reinterpret_cast<STRUCT_SERVERLIST*>(
        (DWORD*)ClientAddresses::Memory::ServerList)) {
        for (int i = 0; i < BusinessRules::ServerList::ServerCount; i++) {
            for (int j = 0; j < BusinessRules::ServerList::ChannelCount; j++) {
                if (j == 0)
                    strcpy(temp->ServerList[i].ChanellList[j].Site,
                        BusinessRules::ServerList::MasterListUrl);
                else
                    strcpy(temp->ServerList[i].ChanellList[j].Site,
                        BusinessRules::ServerList::DefaultChannelAddress);
            }
        }
    }
}
