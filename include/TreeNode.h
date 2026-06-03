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

class IEventListener
{
public:
    virtual int OnControlEvent(DWORD idwControlID, DWORD idwEvent) = 0;
};

class TreeNode {
public:
    TreeNode* MainClass;    //+4
    TreeNode* PrevElement;  //+8
    TreeNode* NextElement;  //+12
    TreeNode* BackGround;   //+16
public:
    int isDisposed;  //+20
    int Unks_5;      //+24
    int Unks_6;      //+28
    int Unks_7;      //+32
    virtual void unk_function(void) = 0;

    static DWORD AllocClass(uint32_t Size) {  // att
        return TreeNode::CallCdecl<DWORD, uint32_t>(ClientAddresses::Function::AllocClass, Size);
    }

    TreeNode* getTreeNode() {
        return callThiscall(ClientAddresses::Function::TreeNodeGet, TreeNode*, TreeNode*)(this);
    }

    static TreeNode* Create(int val) {
        DWORD pAllocWindow = TreeNode::AllocClass(0x24u);
        return callThiscall(ClientAddresses::Function::TreeNodeCtor, TreeNode*, DWORD, int)(pAllocWindow, val);
    }

    //----- (00499130) --------------------------------------------------------
    TreeNode* sRemove(BYTE a2) {
        return callThiscall(ClientAddresses::Function::TreeNodeRemove, TreeNode*, TreeNode*, BYTE)(this, a2);
    }

    //----- (00534B69) --------------------------------------------------------
    template <class T>
    int AttachClass(T* Component) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TreeNode*, T*)(this, Component);
    }

    int AttachClass(TreeNode* Component) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::TreeNodeAttach, int, TreeNode*, TreeNode*)(this, Component);
    }
    template <class T>
    int OverClass(T* Component) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::TreeNodeOver, int, TreeNode*, T*)(this, Component);
    }

    template <class T>
    int AboveClass(T* Component) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::TreeNodeAbove, int, TreeNode*, T*)(this, Component);
    }

    template <class T>
    T* getMainClass() {
        return this->MainClass == 0 ? 0 : reinterpret_cast<T*>(this->MainClass);
    }

    template <class T>
    T* getPrevElement() {
        return this->PrevElement == 0 ? 0 : reinterpret_cast<T>(this->PrevElement);
    }

    template <class T>
    T* getNextElement() {
        return this->NextElement == 0 ? 0 : reinterpret_cast<T>(this->NextElement);
    }

    template <class T>
    T* getBackGround() {
        return this->BackGround == 0 ? 0 : reinterpret_cast<T>(this->BackGround);
    }

    uint32_t getTMScene() {  // att
        static uint32_t rtnValue = 0;

        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_ADDR_TM_SCENE]
            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return uint32_t();

        return rtnValue;
    }

    uint32_t getMainAddrs() {  // att
        static uint32_t rtnValue = 0;

        __asm {
            MOV EAX, DWORD PTR DS : [CLIENT_ADDR_TM_SCENE]
            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return uint32_t();

        return rtnValue;
    }
    int getScene() {
        // by SeiTbNao
        //----- (00499EC2) --------------------------------------------------------
        static DWORD rtnValue = 0;
        __asm {
            MOV EAX, CLIENT_ADDR_TM_SCENE
            MOV EDX, DWORD PTR DS : [EAX]
            MOV ECX, EDX
            MOV EAX, CLIENT_RAW_00499EC2
            CALL EAX  // Scene Atual
            MOV rtnValue, EAX
        }
        return rtnValue;
    }
    void AddElementInScene() {
        auto scenepointer = this->getTMScene();
        (*(void(__thiscall**)(DWORD, TreeNode*))(**(DWORD**)(scenepointer + 40) +
            68))(*(DWORD*)(scenepointer + 40),
                this);
    }
    template <class T>
    void RegisterScene(T* Component) {
        if (this->SceneLoaded())
            (*(void(__thiscall**)(T*, int))(*(DWORD*)Component + 80))(
                Component, *(DWORD*)(this->getMainAddrs() + 40) + 36);
        else
            (*(void(__thiscall**)(T*, DWORD))(*(DWORD*)Component + 80))(Component, 0);
    }

    void RegisterScene() {
        if (this->SceneLoaded())
            (*(void(__thiscall**)(TreeNode*, int))(*(DWORD*)this + 80))(
                this, *(DWORD*)(this->getMainAddrs() + 40) + 36);
        else
            (*(void(__thiscall**)(TreeNode*, DWORD))(*(DWORD*)this + 80))(this, 0);
    }

    template <class T>
    void RegisterScene(T* Component, int Scene) {
        if (this->SceneLoaded())
            (*(void(__thiscall**)(T*, int))(*(DWORD*)Component + 80))(Component,
                Scene);
        else
            (*(void(__thiscall**)(T*, DWORD))(*(DWORD*)Component + 80))(Component, 0);
    }

    template <class T>
    void AddElementInScene(T* Val) {
        auto scenepointer = this->getTMScene();
        (*(void(__thiscall**)(DWORD, T*))(**(DWORD**)(scenepointer + 40) + 68))(
            *(DWORD*)(scenepointer + 40), Val);
    }
    int SceneLoaded() {
        // by SeiTbNao
        //----- (00499EC2) --------------------------------------------------------
        static DWORD rtnValue = 0;
        __asm {
            MOV EAX, CLIENT_ADDR_TM_SCENE
            MOV EDX, DWORD PTR DS : [EAX]
            MOV ECX, EDX
            MOV EAX, CLIENT_RAW_00499ED3
            CALL EAX  // Scene Atual
            MOV rtnValue, EAX
        }
        return rtnValue;
    }

    template <class T>
    void setScene(T* Control, int Scene) {
        if (!this->SceneLoaded()) Scene = 0;
        this->MakeFunction<void, T*, int>(Control, 80, Scene);
    }

    void setScene(int Scene) {
        if (!this->SceneLoaded()) Scene = 0;

        this->MakeFunction<void, TreeNode*, int>(this, 80, Scene);
    }

    void setScene() {
        int Scene = 0;
        if (!this->SceneLoaded())
            Scene = 0;
        else
            Scene = *(DWORD*)(this->getMainAddrs() + 40) + 36;

        this->MakeFunction<void, TreeNode*, int>(this, 80, Scene);
    }
    template <class T>
    int setReference(T* Ref) {
        return callThiscall(ClientAddresses::Function::TreeNodeSetReference, int, TreeNode*, T*)(this, Ref);
    }
    int Dispose() { return callThiscall(ClientAddresses::Function::TreeNodeDispose, int, TreeNode*)(this); }
    template <typename T, typename... Args>
    static T MakeFunction(int address, Args... args) {
        return (*(T(__thiscall*)(Args...))address)(args...);
    }

    template <typename T, typename TClass, typename... Args>
    static T MakeFunction(TClass dwClass, int dwIndex, Args... args) {
        return (*(T(__thiscall**)(TClass, Args...))(*(DWORD*)dwClass + dwIndex))(
            dwClass, args...);
    }

    template <typename T, typename... Args>
    T CallStd(int address, Args... args) {
        return (*(T(__stdcall*)(Args...))address)(args...);
    }

    template <typename T, typename... Args>
    T CallThisCall(int address, Args... args) {
        return (*(T(__thiscall*)(Args...))address)(args...);
    }

    template <typename T, typename... Args>
    static T CallCdecl(int address, Args... args) {
        return (*(T(__cdecl*)(Args...))address)(args...);
    }

    template <typename T, typename TClass>
    static T getValue(TClass dwClass, int dwIndex) {
        return (*(T*)(reinterpret_cast<DWORD>(dwClass) + dwIndex));
    }
    template <typename TClass, typename T>
    static void setValue(TClass dwClass, int dwIndex, T dwValue) {
        *(DWORD*)(reinterpret_cast<DWORD>(dwClass) + dwIndex) = dwValue;
    }

    template <typename T, typename TClass>
    T* getObject(TClass dwClass, int dwIndex) {
        return *(T*)(reinterpret_cast<DWORD>(dwClass) + dwIndex);
    }

    template <typename TClass, typename T>
    void setValueTyped(TClass dwClass, int dwIndex, T dwValue) {
        *(T*)(reinterpret_cast<DWORD>(dwClass) + dwIndex) = dwValue;
    }

    template <typename TClass, typename T>
    void setObject(TClass dwClass, int dwIndex, T dwValue) {
        *(T*)(reinterpret_cast<DWORD>(dwClass) + dwIndex) = dwValue;
    }
 
    template <class T>
    T* FindControl(int Handle) {  // att
        static DWORD rtnValue = 0;
        __asm
        // by seitbnao
        {
            PUSH Handle
            MOV EDX, DWORD PTR SS : [CLIENT_ADDR_TM_SCENE]
            MOV ECX, DWORD PTR DS : [EDX + 0x28]
            MOV EAX, DWORD PTR DS : [ECX]
            CALL DWORD PTR DS : [EAX + 0x48]

            MOV rtnValue, EAX
        }

        if (rtnValue == 0) return NULL;

        return reinterpret_cast<T*>(rtnValue);
    }
};
