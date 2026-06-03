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

// Hierarquia de classes baseada no Tantra Online, arquivos HTInterface.cpp e
// HTInterface.h

#include <functional>


class SControl : public TreeNode {
public:
    int Unks_8;                //+36
    unsigned int Visibility;   //+40
    int Enabled;               //+44
    unsigned int Focus;        //+48
    unsigned int MouseHover;   //+52
    int SpriteIndex;           //+56
    unsigned int IndexInList;  //+60
    unsigned int Type;         //+64
    unsigned int Handle;       //+68
    unsigned int CountIndex;   //+72
    SCoordinate Position;      // 76 - 88
    SRectangle Dimension;

protected:
    SControl* ReferencedClass;  //+92
public:
    unsigned int ScreenMove;  //+96
public:
    bool operator==(const SControl& s) const { return this->Handle == s.Handle; }

    bool operator!=(const SControl& s) const { return this->Handle != s.Handle; }

    static SControl* Create(SCoordinate Point, float Width = 0.0,
        float Height = 0.0) {
        DWORD pAllocWindow = SControl::AllocClass(0x64u);
        return callThiscall(ClientAddresses::Function::SControlCreate, SControl*, DWORD, float, float, float,
            float)(pAllocWindow, Point.PosX, Point.PosY, Width,
                Height);
    }

    void sRemove() {
        if (!this) return;
        (**(void(__thiscall***)(SControl*, DWORD)) this)(this, 1);
    }

    //----- (004011FA) --------------------------------------------------------
    int isMouseHover(int x, int y) {
        return callThiscall(ClientAddresses::Function::SControlCheckRect, int, SControl*, int, int)(this, x, y);
    }
    BOOL isMouseHover(int a1, int a2, int PosX, int PosY, int Width, int Height) {
        return a1 >= PosX && a2 >= PosY && PosX + Width > a1 && PosY + Height > a2;
    }

    void KeyBoad(char Key) {
        if (Key == 97) this->Position.PosX--;
        if (Key == 100) this->Position.PosX++;
        if (Key == 119) this->Position.PosY++;
        if (Key == 115) this->Position.PosY--;
    }

    // Esconde a Janela
    void Hide() { Visibility = 0; };
    // Exibe a janela
    void Show() { Visibility = 1; };
    // Retorna o Handled Atual
    int getHandle() { return this->Handle; }  // att
    // Pega o focus (cursor no input)
    int getFocus() { return this->Focus; }
    // Set o focus (cursor no input)
    void setFocus(int Focus) {
        this->Focus = Focus;
        return this->MakeFunction<void, SControl*, int>(this, 100, 1);
        // return this->MakeFunction<void, SControl*>(this, 80);
    }

    // Seta a posição da janela (X Y)
    int SetLeftTop(float Left, float Top) {  // att
        return callThiscall(ClientAddresses::Function::SControlSetLeftTop, int, SControl*, float, float)(this, Left,
            Top);
    }
    // Seta o tamanho da janela (largura altura)
    int SetWidthHeigth(int Width, int Heigth) {  // att
        return callThiscall(ClientAddresses::Function::SControlSetSize, int, SControl*, int, int)(this, Width,
            Heigth);
    }
    // Seta o tamanho da janela (largura altura)
    int SetWidthHeigth_OL2(int Width, int Heigth) {  // att
        return callThiscall(ClientAddresses::Function::SControlSetSizeAlt, int, SControl*, int, int)(this, Width,
            Heigth);
    }
    // Atualiza as proporções, so pode usar uma vez
    int UpdateProporcions() {  // att
        return callThiscall(ClientAddresses::Function::SControlUpdateProportions, int, SControl*)(this);
    }
    // Limpa a posição X
    int ClearLeft() {  // att
        return callThiscall(ClientAddresses::Function::SControlClearLeft, int, SControl*)(this);
    }
    // Limpa a posição Y
    int ClearTop() {  // att
        return callThiscall(ClientAddresses::Function::SControlClearTop, int, SControl*)(this);
    }
    // Multiplica as posições por *1
    int AssertLeftTop(float Left, float Top) {  // att
        return callThiscall(ClientAddresses::Function::SControlAssertLeftTop, int, SControl*, float, float)(this, Left,
            Top);
    }
    int Descer() {  // att
        return callThiscall(ClientAddresses::Function::SControlDown, int, SControl*)(this);
    }
    // Verifica se x e y emtão dentro do QUADRADO da janela ( cursor )
    int CheckRect(int posX, int posY) {  // att
        return callThiscall(ClientAddresses::Function::SControlCheckRect, int, SControl*, int, int)(this, posX, posY);
    }
    // Seta a visibilidade da janela
    bool SetVisibility(int ShowHide) {  // att
        return callThiscall(ClientAddresses::Function::SControlSetVisibility, bool, SControl*, int)(this, ShowHide);
    }
    // Seta o handled atual, pode dar crash se não souber usar
    int setHandled(int Handled) {
        return callThiscall(ClientAddresses::Function::SControlSetHandle, int, SControl*, int)(this, Handled);
    }
    // Seta o handle do componente (usar apos criações)
    void setHandle(int Handle) { this->Handle = Handle; }

    template <class T>
    int RemoveClass(T* Component) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::SControlRemoveClass, int, SControl*, T*)(this, Component);
    }

    void Delete() {
        return (***(void(__thiscall****)(SControl*, DWORD))(this))(this, 1);
    }
    void Delete(BYTE val) {
        return callThiscall(ClientAddresses::Function::SControlDelete, void, SControl*, BYTE)(this, val);
    }

    template <class T>
    int SetClass(T* Component, int unk5, int unk7) {
        if (!Component) return 0;

        return callThiscall(ClientAddresses::Function::SControlSetClass, int, SControl*, T*, int,
            int)(this, Component, unk5, unk7);
    }

    int RemoveClass() { return callThiscall(ClientAddresses::Function::SControlRemoveAll, int, SControl*)(this); }

    void AssertResolutions(int Handle, int Altura, int Largura, int Y, int X) {
        return (*(void(__thiscall**)(int, int, DWORD, DWORD, DWORD, DWORD))(
            *(DWORD*)this + 124))(*(DWORD*)this, Handle, X, Y, Largura, Altura);
    }
    void AssertResolution() {
        this->AssertResolutions(this->Handle, this->Position.PosX,
            this->Position.PosY, this->Dimension.Width,
            this->Dimension.Height);
    }

    template <class T>
    T* getReferencedClass() {
        return this->ReferencedClass == 0
            ? 0
            : reinterpret_cast<T>(this->ReferencedClass);
    }

    int UpdateHover() { return this->MakeFunction<int, SControl*>(this, 84); }

    void ElementResize(int a2, float a3, float a4, signed int a5, int a6) {
        return callThiscall(ClientAddresses::Function::SControlResize, void, SControl*, int, float, float,
            signed int, int)(this, a2, a3, a4, a5, a6);
    }

    void setVisibility(int Vis = 0) {
        this->MakeFunction<void, SControl*, int>(this, 96, Vis);
    }

    void setIndex80(int Other) {
        this->MakeFunction<void, SControl*, int>(this, 80, Other);
    }

    void Rederize() {
        this->AssertResolution();
        this->RegisterScene();
        this->AddElementInScene();
        this->SetVisibility(TRUE);
    }

    void Rederize(SControl* Control) {
        Control->AssertResolution();
        Control->RegisterScene();
        Control->AddElementInScene();
        Control->SetVisibility(TRUE);
    }

    const char* getControlName() {
        char temp[64];
        switch (this->Type) {
        case eControlType::Panel:
            return "[PANEL]";
            break;

        case eControlType::Button:
            return "[BUTTON]";
            break;

        case eControlType::CheckBox:
            return "[CHECKBOX]";
            break;

        case eControlType::ListBox:
            return "[LISTBOX]";
            break;

        case eControlType::TypeSMessageBox:
            return "[SMESSAGEBOX]";
            break;

        case eControlType::TypeSMessagePanel:
            return "[SMESSAGEPANEL]";
            break;

        case eControlType::Progress:
            return "[PROGRESSBAR]";
            break;

        case eControlType::ScrollBar:
            return "[SCROLLBAR]";
            break;

        case eControlType::Text:
            return "[TEXT]";
            break;

        case eControlType::TextBox:
            return "[TEXTBOX]";
            break;

        case eControlType::Obj3d:
            return "[OBJECT3D]";
            break;

        case eControlType::Grid:
            return "[GRIDITEM]";
            break;

        case eControlType::PagingBox:
            this->Type = eControlType::PagingBox;
            return "[PAGINGBOX]";
            break;

        default:
            memset(temp, 0, sizeof temp);
            sprintf(temp, "[UNKNOW-%d]", this->Type);
            return temp;
            break;
        }
    }

    void setMainVisibility(int e) {
        if (auto main = reinterpret_cast<SControl*>(this->MainClass)) {
            main->Visibility = e;
        }
    }

    template <class T>
    T* AddElement(T* Element) {
        if (!Element) return 0;

        Element->AssertResolution();
        Element->RegisterScene();

        if (this->Handle)
            this->AttachClass(Element);
        else
            Element->AddElementInScene();

        Element->SetVisibility(TRUE);

        return Element;
    }
    float getViewPosX() { return this->getValue<float, SControl*>(this, 104); }
    float getViewPosY() { return this->getValue<float, SControl*>(this, 108); }
    float getViewWidth() { return this->getValue<float, SControl*>(this, 112); }
    float getViewHeight() { return this->getValue<float, SControl*>(this, 116); }
    float setViewPosX(float posX) { this->setValue<SControl*>(this, 104, posX); }
    float setViewPosY(float posY) { this->setValue<SControl*>(this, 108, posY); }
    float setViewWidth(float width) {
        this->setValue<SControl*>(this, 112, width);
    }
    float setViewHeight(float height) {
        this->setValue<SControl*>(this, 116, height);
    }
    void setViewPos(float posX, float posY) {
        this->setViewPosX(posX);
        this->setViewPosY(posY);
    }
    int toInt(float value) {
        return this->CallCdecl<int, float>(ClientAddresses::Function::FloatToInt, value);
    }
 
    static void MainLoop(SControl* p);
};
