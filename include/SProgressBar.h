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
class SProgressBar : public SControl {
public:
    // STexture TextureBase;
    int Orientation;  // 484
    int Min;  // 488
    int Max;  // 492
    int PosY;  // 496
    float Heith;  // 500
    int BackColor;

    enum eOrientation : int {
        Vertical = 0,
        Horizontal = 1,
    };

public:  // Exclusivas deste control
 //(header->SpriteIndex, header->Actual, header->Max, header->X, header->Y,
 //header->Largura, header->Altura, header->Color, header->BackColor,
 //header->Orientation);
    static SProgressBar* Create(int SpriteIndex, int Actual, int Max, float X,
        float Y, float Largura, float Altura, int Color,
        int BackColor, int Orientation) {
        DWORD pAllocWindow = SControl::AllocClass(0x374u);
        return callThiscall(CLIENT_RAW_00404CB5, SProgressBar*, DWORD, int, int, int, float,
            float, float, float, int, int,
            int)(pAllocWindow, SpriteIndex, Actual, Max, X, Y,
                Largura, Altura, Color, BackColor, Orientation);
    }

    void Hiden() { SControl::Visibility = 0; }
    void Show() { SControl::Visibility = 1; }

    void Reset() {
        this->setCurrentProgress(NULL);
        this->setCurrentProgress(NULL);
        this->onUpdate();
    }

    void addProgress(int max, int current = 0, BYTE LabelType = 0,
        bool showLabel = false) {
        if (current < 0) current = 0;

        if (current >= max) current = max;

        this->setCurrentProgress(current);
        this->setMaxProgress(max);

        if (showLabel) {
            if (auto label = this->FindControl<SText>(this->Handle + 50)) {
                if (LabelType == 0)
                    label->setConstString("%.1f%% / %.1f%%",
                        (float)this->getCurrentProgress(),
                        (float)this->getMaxprogress());
                else
                    label->setConstString("%.1f%%", (float)this->getCurrentProgress());
            }
        }

        this->onUpdate();
    }
    void addProgressValue(int max, int current = 0, BYTE LabelType = 0,
        bool showLabel = false) {
        if (current < 0) current = 0;

        if (current >= max) current = max;

        this->setCurrentProgress(current);
        this->setMaxProgress(max);

        if (showLabel) {
            if (auto label = this->FindControl<SText>(this->Handle + 50)) {
                if (LabelType == 0)
                    label->setConstString("%.1f%% / %.1f%%",
                        (float)this->getCurrentProgress() / 100.0,
                        (float)this->getMaxprogress() / 100.0);
                else
                    label->setConstString("%.1f%%",
                        (float)this->getCurrentProgress() / 100.0);
            }
        }

        this->onUpdate();
    }
    void addProgressNoPercent(int max, int current = 0, BYTE LabelType = 0,
        bool showLabel = false) {
        if (current < 0) current = 0;

        if (current >= max) current = max;

        this->setCurrentProgress(current);
        this->setMaxProgress(max);

        if (showLabel) {
            if (auto label = this->FindControl<SText>(this->Handle + 84848)) {
                if (LabelType == 0)
                    label->setConstString("%d / %d", (int)this->getCurrentProgress(),
                        (int)this->getMaxprogress());
                else
                    label->setConstString("%d", (int)this->getCurrentProgress());
            }
        }

        this->onUpdate();
    }

    // seta o current progress
    int setCurrentProgress(int a2)  // Update? Current
    {  // att
        return callThiscall(CLIENT_RAW_00404FAA, int, SProgressBar*, int)(this, a2);
    }
    // seta o max progress
    int setMaxProgress(int a2)  // Update? Maxprogress
    {  // att
        return callThiscall(CLIENT_RAW_00404FF1, int, SProgressBar*, int)(this, a2);
    }
    // retorna o current progres
    int getCurrentProgress()  // getCureProgress?
    {  // att
        return callThiscall(CLIENT_RAW_00405025, int, SProgressBar*)(this);
    }
    // retorna o max progress
    int getMaxprogress()  // getMaxProgress?
    {  // att
        return callThiscall(CLIENT_RAW_00405039, int, SProgressBar*)(this);
    }
    // atualiza a barra
    int onUpdate()  // UpdateProgress
    {  // att
        return callThiscall(CLIENT_RAW_0040504D, int, SProgressBar*)(this);
    }
    // retorna o handled atual
    int getHandle(void) { return SControl::getHandle(); }

    void setOrientation(int Orientation) {
        this->setValue<SProgressBar*, int>(this, 484, Orientation);
    }

    int getOrientation() { return this->getValue<int, SProgressBar*>(this, 484); }

    void setColorRaw(ClientColor Color) {
        this->setValue<SProgressBar*, int>(this, 552, Color);
    }

    void setBackColorRaw(ClientColor Color) {
        this->setValue<SProgressBar*, int>(this, 148, Color);
    }

    void AddLabel() {  //%.1f%%
        auto label = SText::Create(-1, "0", White, (this->Dimension.Width / 2) - 40,
            -1, this->Dimension.Width,
            this->Dimension.Height, 0, 0, 1, 0);
        if (!label) return;
        label->Visibility = this->Visibility;
        label->setHandle(this->Handle + 50);
        this->AttachClass(label);
    }
    void AddLabel2() {  //%.1f%%
        auto label = SText::Create(-1, "0", White, (this->Dimension.Width / 2) - 40,
            -1, this->Dimension.Width,
            this->Dimension.Height, 0, 0, 1, 0);
        if (!label) return;
        label->Visibility = this->Visibility;
        label->setHandle(this->Handle + 84848);
        this->AttachClass(label);
    }
};
