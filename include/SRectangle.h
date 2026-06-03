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

class SRectangle {
public:
    float Width;
    float Height;

    SRectangle() : Width(0), Height(0) {}
    SRectangle(float x, float y) : Width(x), Height(y) {}
    SRectangle(const SRectangle& v) : Width(v.Width), Height(v.Height) {}

    SRectangle& operator=(const SRectangle& v) {
        this->Width = v.Width;
        this->Height = v.Height;
        return *this;
    }

    SRectangle operator+(SRectangle& v) {
        return SRectangle(this->Width + v.Width, this->Height + v.Height);
    }

    SRectangle operator-(SRectangle& v) {
        return SRectangle(this->Width - v.Width, this->Height - v.Height);
    }

    SRectangle& operator+=(SRectangle& v) {
        this->Width += v.Width;
        this->Height += v.Height;
        return *this;
    }

    SRectangle& operator-=(SRectangle& v) {
        this->Width -= v.Width;
        this->Height -= v.Height;
        return *this;
    }

    SRectangle operator+(double s) {
        return SRectangle(this->Width + s, this->Height + s);
    }

    SRectangle operator-(double s) {
        return SRectangle(this->Width - s, this->Height - s);
    }

    SRectangle operator*(double s) {
        return SRectangle(this->Width * s, this->Height * s);
    }

    SRectangle operator/(double s) {
        return SRectangle(this->Width / s, this->Height / s);
    }

    SRectangle& operator+=(double s) {
        this->Width += s;
        this->Height += s;
        return *this;
    }

    SRectangle& operator-=(double s) {
        this->Width -= s;
        this->Height -= s;
        return *this;
    }

    SRectangle& operator*=(double s) {
        this->Width *= s;
        this->Height *= s;
        return *this;
    }

    SRectangle& operator/=(double s) {
        if(s == 0)
            s = 1.0;
        this->Width /= s;
        this->Height /= s;
        return *this;
    }

    double getWidth() { return this->Width; }

    void setWidth(float w) { this->Width = w; }

    double getHeight() { return this->Height; }

    void setHeight(float h) { this->Height = h; }

    double getArea() { return this->Width * this->Height; }

    double getPerimeter() { return 2 * (this->Width + this->Height); }

    void rotate(double a) {
        double tempx;
        double tempy;

        tempx = Width;
        tempy = Height;

        double pitwo;

        pitwo = atan(1.0) * 4.0;

        a = a * (pitwo / 180);

        Width = (tempx * cos(a)) - (Width * sin(a));
        Height = (tempx * sin(a)) + (tempy * cos(a));
    }
};
