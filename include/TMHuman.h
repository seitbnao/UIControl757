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

struct ST_UpdateEquip {
    unsigned short Equip[16];
};

class TMHuman : public TMObject {
public:
    struct ST_EQUIP {
        short Equip;
    };
    static TMHuman* Create(UINPCControl* Tmob) {
        DWORD pAllocWindow = SControl::AllocClass(0xB50u);
        return callThiscall(CLIENT_RAW_004D90FC, TMHuman*, DWORD, UINPCControl*)(pAllocWindow,
            Tmob);
    }
    static int GetMobAddr() {
        static int MainMobAddr = 0;
        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_RAW_01F69F2C]
            MOV MainMobAddr, EAX
        }
        return MainMobAddr == 0 ? NULL : MainMobAddr;
    };

    DWORD STRUCT_MOBADDR() {
        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_RAW_01F69F2C]
            ADD EAX, 0x750
        }
    }

     

    uint32_t getTMScene() {
        static uint32_t rtnValue = 0;
        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_RAW_006D03B8]
            MOV rtnValue, EAX
        }
        return rtnValue == 0 ? NULL : rtnValue;
    }

    void setPkColor(int val, DWORD Color, int val2) {
        return SControl::MakeFunction<void, TMHuman*, int, DWORD, int>(
            this, 64, val, Color, val2);
    }
    void	setIndex(int index) {
        *(WORD*)(this + 2656) = index;
    }
   
    template <class T>
    T* FindControl(signed int handleId) {
        auto scene = TMScene::Instance();
        return scene ? scene->FindControl<T>(handleId) : nullptr;
    }

    static TMHuman* getMobFromIndex(int MobIndex) {
        auto MobAddr = GetMobAddr();
        if (!MobAddr) return 0;
        if (!*(DWORD*)MobAddr) return 0;

        return (*(TMHuman * (__thiscall**)(int, DWORD))(*(DWORD*)MobAddr + 52))(
            MobAddr, MobIndex);
    }

    // Converte a cordenada do mob em cordenada de tela
    BOOL InsideView(float posX, float PosZ, float PosY, int* X, int* Y) {
        return callCdecl(CLIENT_RAW_00437853, BOOL, float, float, float, int*,
            int*)(posX, PosZ, PosY, X, Y);
    }
    // Converte a cordenada do mob em cordenada de tela
    BOOL InsideView(int* X, int* Y) {
        if (!this || !X || !Y)
            return FALSE;

        float PosZ = (float)this->getPosZ() + 1.0;
        return callCdecl(CLIENT_RAW_00437853, BOOL, float, float, float, int*,
            int*)((float)this->getPosX(), PosZ, (float)this->getPosY(),
                X, Y);
    }
    SCoordinate* InsideView() {
        if (!this)
            return NULL;

        int X = 0;
        int Y = 0;
        float PosZ = (float)this->getPosZ() + 1.0;
        if (callCdecl(CLIENT_RAW_00437853, BOOL, float, float, float, int*,
            int*)((float)this->getPosX(), PosZ, (float)this->getPosY(),
                &X, &Y)) {
            return new SCoordinate(X, Y);
        }
        return NULL;
    }
    SText* getLabelTab() { return this->getMobElementByIndex<SText>(1528); }

    SPanel* getGuildmark() { return this->getMobElementByIndex<SPanel>(2712); }

    STRUCT_AFFECT* getAffect(int i) {
        if (!this || i < 0 || i >= 32)
            return nullptr;

        return (STRUCT_AFFECT*)(reinterpret_cast<DWORD>(this) + 2236 + 8 * i);
    }

    int getAffectFromIndex(int Type) {
        for (int i = 0; i < 32; ++i) {
            auto affect = this->getAffect(i);
            if (affect && affect->Type == Type) return i;
        }
        return -1;
    }

    TMHuman* Player() {
        return (TMHuman*)(reinterpret_cast<TMHuman*>(getTMScene()) + 137428);
    }

    SProgressBar* getHPBar() {
        return this->getMobElementByIndex<SProgressBar>(1540);
    }

    SPanel* getMiniMapPointer() {
        return this->getMobElementByIndex<SPanel>(1536);
    }

    bool CheckDword(int dwIndex) {
        auto check = *(DWORD*)(reinterpret_cast<DWORD>(this) + dwIndex);
        return (check);
    }

    int getDword(int dwIndex) {
        return *(DWORD*)(reinterpret_cast<DWORD>(this) + dwIndex);
    }

    template <class T>
    T getDword(int dwIndex) {
        return *(T*)(reinterpret_cast<DWORD>(this) + dwIndex);
    }

    template <class T>
    T* getMobElementByIndex(int dwIndex) {
        return reinterpret_cast<T*>(
            *(DWORD*)(reinterpret_cast<DWORD>(this) + dwIndex));
    }

    template <class T>
    T* getElementFromValue(signed int value, int i) {  // att by seitbnao
        return reinterpret_cast<T*>(
            *(DWORD*)(reinterpret_cast<DWORD>(this) + (value + i * 4)));
    }

    template <class T>
    T* getElementFromValue2(signed int value, int i) {  // att by seitbnao
        return reinterpret_cast<T*>(
            *(DWORD*)(reinterpret_cast<DWORD>(this) + (value + i * 2)));
    }

    short getEquipament(int slot) {
        return (
            short)(*(DWORD*)(reinterpret_cast<DWORD>(this) + (2600 + slot * 2)));
    }

    int getIndex() { return this->getDword(12); }

    char* getMobName() { return this->getDword<char*>(240); }

    int getPosX() {
        return (int)TreeNode::getValue<float, TMHuman*>(this, 40);
    }

    int getPosY() {
        return (int)TreeNode::getValue<float, TMHuman*>(this, 44);
    }

    int getPosZ() {
        return (int)TreeNode::getValue<float, TMHuman*>(this, 48);
    }

    STRUCT_MOB* getMOB() {
        return reinterpret_cast<STRUCT_MOB*>(STRUCT_MOBADDR());
    }

    WORD GetGuildLevel() {
        return *(WORD*)(reinterpret_cast<DWORD>(this) + 2170);
    }

    WORD getMedalGuild() {
        return *(WORD*)(reinterpret_cast<DWORD>(this) + 2868);
    }

    void onUpdate() {
        (*(void(__thiscall**)(TMHuman*))(*(DWORD*)reinterpret_cast<DWORD>(this) +
            56))(this);
    }

    void setColorName(ClientColor Color) {
        (*(void(__thiscall**)(TMHuman*, DWORD, int, DWORD))(
            *(DWORD*)reinterpret_cast<DWORD>(this) + 64))(this, 0, Color, 0);
    }

    signed int getGuilty() {
        return (signed int)*(BYTE*)(reinterpret_cast<DWORD>(this) + 1568) >> 4;
    }

    void setFace(int Face) {
        *(WORD*)(reinterpret_cast<DWORD>(this) + 292) = Face;
    }

    DWORD getFace2() { return *(DWORD*)(reinterpret_cast<DWORD>(this) + 536); }
    
    WORD getFace() { return *(WORD*)(reinterpret_cast<DWORD>(this) + 292); }

    int setGuildMark(TMHuman* a1, SPanel* a2, signed int MedalGuild) {
        return callstdcall(CLIENT_RAW_0047E09C, int, TMHuman*, SPanel*,
            signed int)(a1, a2, MedalGuild);
    }

    BYTE getParty() { return *(BYTE*)(reinterpret_cast<DWORD>(this) + 532); }
    void setParty(int Party) {
        *(BYTE*)(reinterpret_cast<DWORD>(this) + 532) = Party;
    }

    int sendAnimation(TMHuman* CurrentMob, TMHuman* TargetMob, signed int Effect,
        int Value) {
        return callThisfastcall(CLIENT_RAW_00501D66, int, TMHuman*, TMHuman*, signed int,
            int)(CurrentMob, TargetMob, Effect, Value);
    }

    int sendAnimation(TMHuman* TargetMob, signed int Effect, int Value) {
        return callThisfastcall(CLIENT_RAW_00501D66, int, TMHuman*, TMHuman*, signed int,
            int)(this, TargetMob, Effect, Value);
    }

    int sendAnimation(signed int Effect, int Value) {
        return callThisfastcall(CLIENT_RAW_00501D66, int, TMHuman*, TMHuman*, signed int,
            int)(this, this, Effect, Value);
    }

    void setTimeAnimation(int time) {
        *(DWORD*)(*(DWORD*)(*(DWORD*)(reinterpret_cast<DWORD>(this) + 96) + 764) +
            128) = time;
    }
    int MakeMineMapPoint(DWORD Color) {
        return callThiscall(CLIENT_RAW_004DAC12, int, TMHuman*, DWORD)(this, Color);
    }
    int inZone_128(int cord1, int cord2) {
        return callThiscall(CLIENT_RAW_00496ED8, int, TMHuman*, int, int)(this, cord1, cord2);
    }
    int inZone(int cord1, int cord2) {
        return callThiscall(CLIENT_RAW_00496ED8, int, TMHuman*, int, int)(this, cord1 / 128,
            cord2 / 128);
    }
   
    float getViewPosX() { return TreeNode::getValue<float, TMHuman*>(this, 104); }

    float getViewPosY() { return TreeNode::getValue<float, TMHuman*>(this, 108); }

    float getViewWidth() {
        return TreeNode::getValue<float, TMHuman*>(this, 112);
    }
    float getViewHeight() {
        return TreeNode::getValue<float, TMHuman*>(this, 116);
    }
    float setViewPosX(float posX) {
        TreeNode::setValue<TMHuman*>(this, 104, posX);
    }
    float setViewPosY(float posY) {
        TreeNode::setValue<TMHuman*>(this, 108, posY);
    }
    float setViewWidth(float width) {
        TreeNode::setValue<TMHuman*>(this, 112, width);
    }
    float setViewHeight(float height) {
        TreeNode::setValue<TMHuman*>(this, 116, height);
    }

    float getTargetPosX() {
        return TreeNode::getValue<float, TMHuman*>(this, 1648);
    }
    float getTargetPosY() {
        return TreeNode::getValue<float, TMHuman*>(this, 1652);
    }

    short getMount() { return TreeNode::getValue<short, TMHuman*>(this, 252); }

    void setMount(int item) { TreeNode::setValue<TMHuman*>(this, 252, item); }

    void setViewPos(float posX, float posY) {
        this->setViewPosX(posX);
        this->setViewPosY(posY);
    }
    void setStaticFace(WORD value) { SControl::setValue<TMHuman*>(this, 540, value); }
 
    void setBone(int bone) { SControl::setValue<TMHuman*>(this, 92, bone); }

    int getBone() { 
        return SControl::getValue<int, TMHuman*>(this, 92); }

    // Hooks
    static void HKD_TMHumanUpdate(TMHuman* Property);
   
};
