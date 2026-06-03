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

class SScrollBar : public SControl, public IEventListener {
public:
    int GuildPanel;   //+4
    int CurrentLine;  //+8
    int MaxLine;      //+12
    int Unks_4;       //+16
    int ScrollPosition;  // 20
    int cHeight;  // 24
    int cWidth;  // 28
    SControl* Panel_1;  // 32 //sub_401426(v31, -2, 0.0, 0.0, *(float *)(v27 +
                        // 128), *(float *)(v27 + 88), 1145324612, 4);
    SControl* Panel_2;  // 36 //sub_401426(v30, -2, v17, 0.0, *(float *)(v27 +
                        // 128), *(float *)(v27 + 88), 1145324612, 4);
    SControl* Panel_3;  // 40 //sub_401426(v33, 425, v15, 0.0, v11, 17.0, -1, 4);
    SControl* Panel_4;  // 44 //sub_401426(v32, 426, v16, 0.0, 10.0, a7, -1, 4);
    int Unks_12;  // 48
    // Create
    static SScrollBar* Create(int CurrentLine, int MaxLines, float PosX,
        float PosY, float Height, float Width = 12.0f,
        int GuildPanel = 0, int Zero_NotUsed = 0,
        int ColorNotUsed = 0xFFAAAAAA,
        bool OneMoreIndex = false) {
        return TreeNode::MakeFunction<SScrollBar*, DWORD, int, int, float, float,
            float, float, int, int, int, bool>(
                CLIENT_RAW_004053E3, TreeNode::AllocClass(0x94u), CurrentLine * 5, MaxLines * 5,
                PosX, PosY, Width, Height, GuildPanel, Zero_NotUsed, ColorNotUsed,
                OneMoreIndex);
    };

    int GetCurrentLine() {
        return TreeNode::MakeFunction<int, SScrollBar*>(CLIENT_RAW_00405C2C, this);
    }

    void SetCurrentLine(int Line) {
        TreeNode::MakeFunction<void, SScrollBar*, int>(CLIENT_RAW_00405C0B, this, Line * 5);
    }

    int GetMaxLines() {
        TreeNode::MakeFunction<int, SScrollBar*>(CLIENT_RAW_00405C5E, this);
    }

    void SetMaxLines(int Max) {
        TreeNode::MakeFunction<void, SScrollBar*, int>(CLIENT_RAW_00405C3D, this, Max * 5);
    }

    void GoUp() {
        TreeNode::MakeFunction<void, SScrollBar*>(CLIENT_RAW_00405E0D, this);
    }  //-5

    void GoDown() {
        TreeNode::MakeFunction<void, SScrollBar*>(CLIENT_RAW_00405E50, this);
    }  //+5

    void ForceUpdate() {
        TreeNode::MakeFunction<void, SScrollBar*>(CLIENT_RAW_00405C6F, this);
    }

    void ReSize(float Width, float Height) {
        TreeNode::MakeFunction<void, SScrollBar*, float, float>(CLIENT_RAW_00405D6D, this,
            Width, Height);
    }

    SControl* getTopButton() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 132));
        return pointer ? reinterpret_cast<SControl*>(pointer) : NULL;
    }
    SControl* getBottomButton() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 136));
        return pointer ? reinterpret_cast<SControl*>(pointer) : NULL;
    }
    SControl* getScroller() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 140));
        return pointer ? reinterpret_cast<SControl*>(pointer) : NULL;
    }
    SControl* getTextureBar() {
        DWORD pointer = (*(DWORD*)(reinterpret_cast<DWORD>(this) + 144));
        return pointer ? reinterpret_cast<SControl*>(pointer) : NULL;
    }
};
