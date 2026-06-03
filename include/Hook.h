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
#include <cstring>

enum class eHookType {
    // Inconditional Jump
    JMP = 1,  // 0xE9

    // Call
    CALL,  // 0xE8

    JE,  // 0xF 0x84
    JZ,
    JNZ,  // 0xF 0x85
    JNE,

    // Signed Jumps
    JL,   // 0xF 0x8C
    JGE,  // 0xF 0x8D
    JLE,  // 0xF 0x8E
    JG,   // 0xF 0x8F

    // Unsigned Jumps
    JB,   // 0xF 0x82
    JNB,  // 0xF 0x83
    JBE,  // 0xF 0x86
    JA    // 0xF 0x87
};

class HookMgr : public Singleton<HookMgr> {
public:
    void FillWithNop(DWORD dwAddress, DWORD dwSize) {
        fillWithNop(dwAddress, dwSize);
    }

    void setHook(const eHookType hType, unsigned int hSourceAddress,
        unsigned int hDestAddress, unsigned int hNopSize = 0) {
        if (!hSourceAddress || !hDestAddress)
            return;

        BYTE instruction[16] = {};
        const auto instructionSize = InstructionSize(hType);
        if (!instructionSize || instructionSize + hNopSize > sizeof instruction)
            return;

        if (!EncodeBranch(hType, hSourceAddress, hDestAddress, instruction))
            return;

        if (hNopSize > 0)
            memset(instruction + instructionSize, 0x90, hNopSize);

        WriteProtected(hSourceAddress, instruction, instructionSize + hNopSize);
    }

    template <typename I>
    void setValue(unsigned int hSourceAddress, I hValue) {
        setValue(hSourceAddress, hValue, sizeof(I));
    }

    template <typename I>
    void setValue(unsigned int hSourceAddress, I hValue, unsigned int hSize) {
        if (!hSourceAddress || !hSize)
            return;

        WriteProtected(hSourceAddress, &hValue, hSize);
    }

    void fillWithNop(unsigned int hAddress, unsigned int hNopCount) {
        if (!hAddress || !hNopCount)
            return;

        BYTE nop[32] = {};
        memset(nop, 0x90, sizeof nop);

        while (hNopCount > 0) {
            const auto chunkSize =
                hNopCount > sizeof nop ? static_cast<unsigned int>(sizeof nop) : hNopCount;
            if (!WriteProtected(hAddress, nop, chunkSize))
                return;

            hAddress += chunkSize;
            hNopCount -= chunkSize;
        }
    }

    unsigned int getAddress(const void* ptr) {
        return reinterpret_cast<unsigned int>(ptr);
    }

protected:
    friend class Singleton<HookMgr>;
    HookMgr() {}
    virtual ~HookMgr() {}
    HookMgr(const HookMgr&) = delete;
    HookMgr& operator=(const HookMgr&) = delete;

private:
    static unsigned int InstructionSize(eHookType type) {
        switch (type) {
        case eHookType::JMP:
        case eHookType::CALL:
            return 5;
        case eHookType::JE:
        case eHookType::JZ:
        case eHookType::JNZ:
        case eHookType::JNE:
        case eHookType::JL:
        case eHookType::JGE:
        case eHookType::JLE:
        case eHookType::JG:
        case eHookType::JB:
        case eHookType::JNB:
        case eHookType::JBE:
        case eHookType::JA:
            return 6;
        default:
            return 0;
        }
    }

    static unsigned int DistanceOffset(eHookType type) {
        return (type == eHookType::JMP || type == eHookType::CALL) ? 1 : 2;
    }

    static bool EncodeBranch(eHookType type, unsigned int source,
        unsigned int destination, BYTE* instruction) {
        if (!instruction)
            return false;

        switch (type) {
        case eHookType::JMP:
            instruction[0] = 0xE9;
            break;
        case eHookType::CALL:
            instruction[0] = 0xE8;
            break;
        case eHookType::JE:
        case eHookType::JZ:
            instruction[0] = 0x0F;
            instruction[1] = 0x84;
            break;
        case eHookType::JNZ:
        case eHookType::JNE:
            instruction[0] = 0x0F;
            instruction[1] = 0x85;
            break;
        case eHookType::JL:
            instruction[0] = 0x0F;
            instruction[1] = 0x8C;
            break;
        case eHookType::JGE:
            instruction[0] = 0x0F;
            instruction[1] = 0x8D;
            break;
        case eHookType::JLE:
            instruction[0] = 0x0F;
            instruction[1] = 0x8E;
            break;
        case eHookType::JG:
            instruction[0] = 0x0F;
            instruction[1] = 0x8F;
            break;
        case eHookType::JB:
            instruction[0] = 0x0F;
            instruction[1] = 0x82;
            break;
        case eHookType::JNB:
            instruction[0] = 0x0F;
            instruction[1] = 0x83;
            break;
        case eHookType::JBE:
            instruction[0] = 0x0F;
            instruction[1] = 0x86;
            break;
        case eHookType::JA:
            instruction[0] = 0x0F;
            instruction[1] = 0x87;
            break;
        default:
            return false;
        }

        const auto instructionSize = InstructionSize(type);
        const auto distance = (destination - source) - instructionSize;
        memcpy(instruction + DistanceOffset(type), &distance, sizeof distance);
        return true;
    }

    static bool WriteProtected(unsigned int address, const void* data, unsigned int size) {
        if (!address || !data || !size)
            return false;

        DWORD oldProtect = 0;
        auto target = reinterpret_cast<LPVOID>(address);
        if (!VirtualProtect(target, size, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        memcpy(target, data, size);

        DWORD unusedProtect = 0;
        const auto restored = VirtualProtect(target, size, oldProtect, &unusedProtect) != 0;
        FlushInstructionCache(GetCurrentProcess(), target, size);
        return restored;
    }
};

extern HookMgr* DLL;

#define _GET(function) DLL->getAddress(&function)
