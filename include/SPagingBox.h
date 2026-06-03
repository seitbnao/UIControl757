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
class SPagingBox : public SControl {
public:
    // Create
    static SPagingBox* Create(float PosX, float PosY, float Width, float Height,
        int Offset, int MaxIndexes, int SelectedIndex,
        int a9, int a10, int a11, int a12) {
        auto pointer =
            TreeNode::MakeFunction<SPagingBox*, DWORD, float, float, float, float,
            int, int, int, int, int, int, int>(
                CLIENT_RAW_004083B9, TreeNode::AllocClass(0xB8u), PosX, PosY, Width, Height,
                Offset, MaxIndexes, SelectedIndex, a9, a10, a11, a12);
        if (pointer) {
            pointer->EnableClick(TRUE);
            pointer->Type = eControlType::PagingBox;
            return pointer;
        }
        return NULL;
    };

    static SPagingBox* Create(int handle, int EnableClick, float PosX, float PosY,
        float Width, float Height, int Offset,
        int MaxIndexes, int SelectedIndex = 2, int a9 = 1,
        int a10 = 10, int a11 = 1, int a12 = 10) {
        auto pointer =
            TreeNode::MakeFunction<SPagingBox*, DWORD, float, float, float, float,
            int, int, int, int, int, int, int>(
                CLIENT_RAW_004083B9, TreeNode::AllocClass(0xB8u), PosX, PosY, Width, Height,
                Offset, MaxIndexes, SelectedIndex, a9, a10, a11, a12);
        if (pointer) {
            pointer->EnableClick(EnableClick);
            pointer->Visibility = 1;
            pointer->Handle = handle;
            return pointer;
        }

        return NULL;
    };

    void EnableClick(bool Enable = true) {
        TreeNode::MakeFunction<void, SPagingBox*, int>(CLIENT_RAW_00408605, this, Enable);
    };

    void SetTextAddr(const char* String, ClientColor Color, int Parm = 0) {
        ((void(__thiscall*)(SPagingBox*, const char*, ClientColor, int))CLIENT_RAW_00421D1F)(
            this, String, Color, Parm);
    };

    SButton* GetButtonByIndex(int nIndex) {
        return reinterpret_cast<SButton*>(
            *(DWORD*)(reinterpret_cast<DWORD>(this) + 4 * nIndex + 100));
    }

    void RegisterButtonsInScene() {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                button->RegisterScene(button);
            }
        }
    }
    void RegisterButtonHandle(int BaseHandled) {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                button->Handle = this->Handle + BaseHandled + i;
            }
        }
    }
    SButton* getButtonByHandle(int Handle) {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                if (Handle == button->Handle) return button;
            }
        }

        return NULL;
    }

    void setIndex(int a4) {
        *(DWORD*)(reinterpret_cast<unsigned int>(this) + 156) = a4;
    }
    int getIndex() {
        return *(DWORD*)(reinterpret_cast<unsigned int>(this) + 156);
    }

    void setSelected(int Index) {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                button->setColor(ClientColor::White);
                if (i - 1 == Index) {
                    button->setColor(ClientColor::Yellow);
                    this->setIndex(Index);
                }
            }
        }
    }
    void setSelected_OL2(int Index) {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                button->setColor(ClientColor::White);
                if (i == Index) {
                    button->setColor(ClientColor::Yellow);
                    this->setIndex(Index);
                }
            }
        }
    }

    void setSelected_OL3(int Index) {
        if (Index < 2) Index = 2;
        if (Index >= 12) Index = 11;
        for (int i = 2; i < 12; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                button->setColor(ClientColor::White);
                if (i == Index) {
                    button->setColor(ClientColor::Yellow);
                    this->setIndex(Index);
                }
            }
        }
    }

    void first() { this->setSelected_OL2(2); }
    void last() { this->setSelected_OL2(11); }
    void forward(int Index) { this->setSelected_OL3(Index); }
    void back(int Index) { this->setSelected_OL3(Index); }

    void setReference(int Handle) {
        for (int i = 0; i < 14; ++i) {
            if (auto button = this->GetButtonByIndex(i)) {
                // this->Reference = Handle;
                // button->Reference = Handle;
            }
        }
    }
};
