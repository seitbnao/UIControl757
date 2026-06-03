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
class SListBox : public SControl, public IEventListener
{
public:
    int Unks[100];  // 596
    int MaxList;      //+ 496
    int Unks_0;       //+ 524
    int SelectIndex;  //+ 528

public:
    static SListBox* Create(int sprite, int maxlist, int item_per_page, float x,
        float y, float w, float h, int opacity, int vstate,
        int indexlist, char barrapos, char editable) {  // att
        DWORD pAllocWindow = SControl::AllocClass(0x11BCu);

        return callThiscall(CLIENT_RAW_00408842, SListBox*, DWORD, int, int, int, float,
            float, float, float, int, int, int, char,
            char)(pAllocWindow, sprite, maxlist, item_per_page, x,
                y, w, h, opacity, vstate, indexlist, barrapos,
                editable);
    }
    // Cria um label que pode ser selecionada em listas como chat
    static SText* CreateSelectionLabel(const char* String, int Color = -16733441,
        float x = 0.0, float y = 0.0,
        float Width = 12.0, float Height = 12.0,
        char HasBackColor = 0,
        int BackColor = 2004318071, int Shadow = 1,
        int Align = 0) {  // att
        DWORD pAllocWindow = SControl::AllocClass(0xE54u);

        return callThiscall(CLIENT_RAW_0040730D, SText*, DWORD, const char*, int, float,
            float, float, float, char, int, int,
            int)(pAllocWindow, String, Color, x, y, Width, Height,
                HasBackColor, BackColor, Shadow, Align);
    }

    SScrollBar* getScroolBar() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 524));
        return pointer ? reinterpret_cast<SScrollBar*>(pointer) : NULL;
    }

    void toBack() {
        for (int i = 0; i < this->GetMaxList(); ++i) this->getScroolBar()->GoUp();
    }

    int GetScrollType() { return this->getValue<int, SListBox*>(this, 488); }

    void setScrollType(BYTE Type) {
        *(DWORD*)(reinterpret_cast<DWORD*>(this) + 488) = Type;
    }

    void addScrollPointer(SScrollBar* Scroll) {
        *(SScrollBar*)(reinterpret_cast<DWORD*>(this) + 524) = *Scroll;
    }

    void removeScrollPointer() {
        if (auto scrol = this->getScroolBar()) {
            scrol->Dispose();
            this->setObject<SListBox*, SScrollBar*>(this, 524, 0);
        }
    }

    void CreateSScrollBar(int scrollbarType) {
        if (this->GetScrollType() != 0) return;  // Already Created

        if (auto Scroll = SScrollBar::Create(
            0, 0, scrollbarType == 1 ? (this->Dimension.Width -
                (this->Dimension.Width * 120 / 100))
            : this->Dimension.Width - 12.0f + 2.0f,
            0.0f, 12.0f, this->Dimension.Height - 1.0f, 0, 0, 0xFFAAAAAA,
            scrollbarType == 1 ? 1 : 0)) {
            this->setValue<SListBox*, int>(this, 488, scrollbarType);
            this->setObject<SListBox*, SScrollBar*>(this, 524, Scroll);
            if (auto getScrol = this->getScroolBar()) {
                this->setIndex80(this->getValue<int, SListBox*>(this, 484));
                getScrol->Handle = 1;
                getScrol->Visibility = 1;
                this->AttachClass(getScrol);
                getScrol->ReSize(12.0f, this->Dimension.Height);
                getScrol->ForceUpdate();
            }
        }
    }
    void CreateSScrollBar(int scrollbarType, SScrollBar* Scroll) {
        if (this->GetScrollType() != 0) return;  // Already Created

        if (Scroll) {
            this->setValue<SListBox*, int>(this, 488, scrollbarType);
            this->setObject<SListBox*, SScrollBar*>(this, 524, Scroll);
            if (auto getScrol = this->getScroolBar()) {
                this->setIndex80(this->getValue<int, SListBox*>(this, 484));
                getScrol->Handle = 1;
                getScrol->Visibility = 1;
                this->AttachClass(getScrol);
                getScrol->ReSize(12.0f, this->Dimension.Height);
                getScrol->ForceUpdate();
            }
        }
    }

    void setScrollVisibility(int visibility) {
        if (auto scroll = this->getScroolBar()) {
            scroll->SetVisibility(visibility);
            scroll->ForceUpdate();
        }
    }

    void FixScrollPosition() {
        auto scroll = this->getScroolBar();
        if (scroll) {
            scroll->getBottomButton()->Position.PosY -= 92;
            this->toBack();
        }
    }

    void setMaxList(int Max) { this->MaxList = Max; }
    void setSelected(int Index) {
        if (Index > this->GetMaxList()) {
            Index = this->GetMaxList() - 1;
        }
        if (Index < 0) {
            Index = 0;
        }
        this->setValue<SListBox*, int>(this, 508, Index);
    }
    int getMaxList() { return this->MaxList; }
    int getHandle(void) { return SControl::getHandle(); }
    // adiciona um componente na listBox (Ex: label progress grid)
    template <class T>
    signed int add(T* a2) {  // att
        if (!a2) return 0;

        return callThiscall(CLIENT_RAW_00408DC5, signed int, SListBox*, T*)(this, a2);
    }

    // retorna o componente da listbox pelo selectedID
    template <class T>
    T* get(int Index) {  // att
        return callThiscall(CLIENT_RAW_0040914B, T*, SListBox*, int)(this, Index);
    }

    // remove o componente da listbox pelo selectedID
    signed int remove(int SelectedIndex) {  // att
        return callThiscall(CLIENT_RAW_00409024, signed int, SListBox*, int)(this,
            SelectedIndex);
    }

    void remove() { this->remove(this->SelectIndex); }

    template <class T>
    T* get() {
        return this->get<T*>(this->SelectIndex);
    }
    // seta o selectedID
    signed int setSelected_OL2(int SelectedIndex) {  // att
        return callThiscall(CLIENT_RAW_0040917D, signed int, SListBox*, int)(this,
            SelectedIndex);
    }
    // Limpa a lista
    int clear() {  // att
        return callThiscall(CLIENT_RAW_004092B0, int, SListBox*)(this);
    }
    // Retorna o ID selecionado na lista
    int getSelected() {  // att
        return callThiscall(CLIENT_RAW_004990C0, int, SListBox*)(this);
    }
    // Le um arquivo e coloca o seu conteudo na lista

    signed int fileToListInt(const char* a2, signed int a3, signed int a4) {
        return callstdcall(CLIENT_RAW_004A3EFB, signed int, SListBox*, const char*,
            signed int, signed int)(this, a2, a3, a4);
    }
    signed int fileToList(const char* a2, ...) {  // att
        char buffer[0x100] = {
            0,
        };
        memset(buffer, 0, sizeof buffer);
        va_list va;
        va_start(va, a2);
        vsprintf_s(buffer, a2, va);
        va_end(va);
        this->clear();
        return callstdcall(CLIENT_RAW_004A3CDB, unsigned int, SListBox*,
            const char*)(this, buffer);
    }
    void AddText(const char* Texto, ClientColor Color = White) {
        auto size = (this->Dimension.Width / 2) - 5;

        if (this->Handle == 846484) size = (this->Dimension.Width / 2) + 32;
        auto Label = SListBox::CreateSelectionLabel(Texto, Color, 0, 0, size, 12);
        if (Label) this->add(Label);
    }

    int Count() { return this->getValue<int, SListBox*>(this, 528); }

    bool GetHasChat() { return this->getValue<int, SListBox*>(this, 489); }

    SEditableText* GetSEditableText() {
        DWORD SEdit = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 520));
        return SEdit ? reinterpret_cast<SEditableText*>(SEdit) : NULL;
    }

    void CreateSEditableText() {
        this->MakeFunction<void, SListBox*>(CLIENT_RAW_00408C7F, this);
    }

    template <class T>
    T* GetComponentByIndex(int nIndex) {
        return this->getValue<T*, SListBox*>(this, 4 * nIndex + 532);
    }

    int GetMaxList() { return this->getValue<int, SListBox*>(this, 496); }

    int GetColumnWidth() { return this->getValue<int, SListBox*>(this, 500); }

    void SetMaxList(int Max) { this->setValue<SListBox*, int>(this, 496, Max); }

    void SetColumnWidth(int Column) {
        this->setValue<SListBox*, int>(this, 500, Column);
    }

    SControl* getUnkControl() {
        return this->getValue<SControl*, SListBox*>(this, 524);
    }

    void Update(int val = 0) {
        if (auto control = this->getUnkControl())
            this->MakeFunction<void, SControl*, int>(control, 128, val);
    }
};
