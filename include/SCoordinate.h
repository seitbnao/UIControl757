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

#include <cmath>

class SCoordinate {
public:
#define M_PI 3.14159265358979323846264338327950288
    float PosX;  //+76
    float PosY;  //+80

    SCoordinate() : PosX(0), PosY(0) {}
    SCoordinate(float x, float y) : PosX(x), PosY(y) {}
    SCoordinate(const SCoordinate& v) : PosX(v.PosX), PosY(v.PosY) {}

    SCoordinate& operator=(const SCoordinate& v) {
        PosX = v.PosX;
        PosY = v.PosY;
        return *this;
    }

    SCoordinate operator+(SCoordinate& v) {
        return SCoordinate(PosX + v.PosX, PosY + v.PosY);
    }

    SCoordinate operator-(SCoordinate& v) {
        return SCoordinate(PosX - v.PosX, PosY - v.PosY);
    }

    SCoordinate& operator+=(SCoordinate& v) {
        PosX += v.PosX;
        PosY += v.PosY;
        return *this;
    }

    SCoordinate& operator-=(SCoordinate& v) {
        PosX -= v.PosX;
        PosY -= v.PosY;
        return *this;
    }

    SCoordinate operator+(double s) { return SCoordinate(PosX + s, PosY + s); }

    SCoordinate operator-(double s) { return SCoordinate(PosX - s, PosY - s); }

    SCoordinate operator*(double s) { return SCoordinate(PosX * s, PosY * s); }

    SCoordinate operator/(double s) { return SCoordinate(PosX / s, PosY / s); }

    SCoordinate& operator+=(double s) {
        PosX += s;
        PosY += s;
        return *this;
    }

    SCoordinate& operator-=(double s) {
        PosX -= s;
        PosY -= s;
        return *this;
    }

    SCoordinate& operator*=(double s) {
        PosX *= s;
        PosY *= s;
        return *this;
    }

    SCoordinate& operator/=(double s) {
        PosX /= s;
        PosY /= s;
        return *this;
    }

    void set(float PosX, float PosY) {
        this->PosX = PosX;
        this->PosY = PosY;
    }
    SCoordinate rotate_point(double cx, double cy, double angle, SCoordinate p) {
        double theta = angle / 180.0 * M_PI;
        double s = sin(theta);
        double c = cos(theta);
        p.PosX -= cx;
        p.PosY -= cy;
        double Xnew = p.PosX * c - p.PosY * s;
        double Ynew = p.PosX * s + p.PosY * c;
        p.PosX = Xnew + cx;
        p.PosY = Ynew + cy;
        return p;
    }

    void rotacionar(double graus) {
        double theta = graus / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tPosX = PosX * c - PosY * s;
        double tPosY = PosX * s + PosY * c;
        PosX = tPosX;
        PosY = tPosY;
    }
    void rotacionarEixo(double graus) {
        double theta = graus / 180.0 * M_PI;
        double centroX = 128, centroY = 129;

        double tPosX = centroX + (this->PosX - centroX) * cos(theta) -
            (this->PosY - centroY) * sin(theta);
        double tPosY = centroY + (this->PosX - centroX) * sin(theta) +
            (this->PosY - centroY) * cos(theta);

        PosX = tPosX;
        PosY = tPosY;
    }
    SCoordinate& normalizar() {
        if (this->tamanho() == 0) return *this;

        *this *= (1.0 / this->tamanho());
        return *this;
    }

    float distancia(SCoordinate v) const {
        SCoordinate dist(v.PosX - PosX, v.PosY - PosY);
        return dist.tamanho();
    }

    float tamanho() const { return std::sqrt(PosX * PosX + PosY * PosY); }

    void truncar(double length) {
        double angle = atan2f(PosY, PosX);
        PosX = length * cos(angle);
        PosY = length * sin(angle);
    }

    SCoordinate ortho() const { return SCoordinate(PosY, -PosX); }

    static float ponto(SCoordinate v1, SCoordinate v2) {
        return v1.PosX * v2.PosX + v1.PosY * v2.PosY;
    }

    static float unir(SCoordinate v1, SCoordinate v2) {
        return (v1.PosX * v2.PosY) - (v1.PosY * v2.PosX);
    }

    void rotate_z(double a) {
        double tempx;
        double tempy;

        tempx = PosX;
        tempy = PosY;

        double pitwo;

        pitwo = atan(1.0) * 4.0;

        a = a * (pitwo / 180);

        PosX = (tempx * cos(a)) - (PosY * sin(a));
        PosY = (tempx * sin(a)) + (tempy * cos(a));
    }
};
