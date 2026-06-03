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
#include <cstring>

namespace BusinessRules {
namespace ServerList {
constexpr int ServerCount = 10;
constexpr int ChannelCount = 11;
constexpr int AddressSize = 64;

constexpr const char* MasterListUrl =
    "http://www.wyd.com.br/wyd_br/servers/serv012.asp";
constexpr const char* DefaultChannelAddress = "192.168.0.103";
}  // namespace ServerList

namespace ItemDescription {
constexpr int MaxLines = 10;
constexpr size_t LineBufferSize = 128;

class Builder {
public:
    Builder(char* (&lines)[MaxLines], DWORD* (&colors)[MaxLines])
        : lines_(lines), colors_(colors) {}

    void Clear() {
        for (int i = 0; i < MaxLines; ++i)
            memset(lines_[i], 0x0, LineBufferSize);
    }

    bool Add(DWORD color, const char* text) {
        if (count_ >= MaxLines || !text)
            return false;

        strcpy_s(lines_[count_], LineBufferSize, text);
        *colors_[count_] = color;
        ++count_;
        return true;
    }

    int Count() const { return count_; }

private:
    char** lines_;
    DWORD** colors_;
    int count_ = 0;
};
}  // namespace ItemDescription
}  // namespace BusinessRules
