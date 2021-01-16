#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED


#include <iostream>
#include "SDL.h"

namespace Game_Objects{
    struct XY{
        double x, y;
    };

    XY to_XY(double _x, double _y);

    double dist_sq(XY val);
    double dist_sq(XY lhs, XY rhs);
    double dist(XY val);
    double dist(XY lhs, XY rhs);
    double cos_of_arg(XY val);
    double sin_of_arg(XY val);
    double inner_product(XY lhs, XY rhs);

    XY rotation(XY val, double cost, double sint);

    XY operator+(XY val);
    XY operator-(XY val);

    XY operator+(XY lhs, XY rhs);
    XY operator-(XY lhs, XY rhs);
    XY operator*(XY lhs, double rhs);
    XY operator*(double lhs, XY rhs);
    XY operator/(XY lhs, double rhs);

    XY &operator+=(XY &lhs, XY rhs);
    XY &operator-=(XY &lhs, XY rhs);
    XY &operator*=(XY &lhs, double rhs);
    XY &operator/=(XY &lhs, double rhs);

    bool operator==(XY lhs, XY rhs);
    bool operator!=(XY lhs, XY rhs);

    std::ostream &operator<<(std::ostream &lhs, XY const &rhs);

    struct RGBA{
        Uint8 r, g, b, a;
    };

    RGBA to_RGBA(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a);

    RGBA operator+(RGBA lhs, RGBA rhs);
    RGBA operator-(RGBA lhs, RGBA rhs);
    RGBA operator*(RGBA lhs, Uint8 rhs);
    RGBA operator*(Uint8 lhs, RGBA rhs);
    RGBA operator/(RGBA lhs, Uint8 rhs);

    RGBA &operator+=(RGBA &lhs, RGBA rhs);
    RGBA &operator-=(RGBA &lhs, RGBA rhs);
    RGBA &operator*=(RGBA &lhs, Uint8 rhs);
    RGBA &operator/=(RGBA &lhs, Uint8 rhs);

    std::ostream &operator<<(std::ostream &lhs, RGBA const &rhs);
}

#endif // COORDINATES_H_INCLUDED
