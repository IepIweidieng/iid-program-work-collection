#include <cmath>
#include "coordinate.h"

namespace Game_Objects{
    XY to_XY(double _x, double _y){
        XY res = {_x, _y};
        return res;
    }

    double dist_sq(XY val){
        return val.x * val.x + val.y * val.y;
    }

    double dist_sq(XY lhs, XY rhs){
        double dist_x, dist_y;
        dist_x = (rhs.x-lhs.x), dist_y = (rhs.y-lhs.y);
        return dist_x * dist_x + dist_y * dist_y;
    }

    double dist(XY val){
        return sqrt(val.x * val.x + val.y * val.y);
    }

    double dist(XY lhs, XY rhs){
        double dist_x, dist_y;
        dist_x = (rhs.x-lhs.x), dist_y = (rhs.y-lhs.y);
        return sqrt(dist_x * dist_x + dist_y * dist_y);
    }

    double cos_of_arg(XY val){
        return val.x / dist(val);
    }

    double sin_of_arg(XY val){
        return val.y / dist(val);
    }

    double inner_product(XY lhs, XY rhs){
        return lhs.x*rhs.x + lhs.y*rhs.y;
    }

    XY rotation(XY val, double cost, double sint){
        return to_XY( val.x * cost + val.y * sint,
                     -val.x * sint + val.y * cost);
    }

    XY operator+(XY val){
        return to_XY(val.x, val.y);
    }

    XY operator-(XY val){
        return to_XY(-val.x, -val.y);
    }

    XY operator+(XY lhs, XY rhs){
        return to_XY(lhs.x+rhs.x, lhs.y+rhs.y);
    }

    XY operator-(XY lhs, XY rhs){
        return to_XY(lhs.x-rhs.x, lhs.y-rhs.y);
    }

    XY operator*(XY lhs, double rhs){
        return to_XY(lhs.x*rhs, lhs.y*rhs);
    }

    XY operator*(double lhs, XY rhs){
        return to_XY(lhs*rhs.x, lhs*rhs.y);
    }

    XY operator/(XY lhs, double rhs){
        return to_XY(lhs.x/rhs, lhs.y/rhs);
    }

    XY &operator+=(XY &lhs, XY rhs){
        lhs.x+=rhs.x, lhs.y+=rhs.y;
        return lhs;
    }

    XY &operator-=(XY &lhs, XY rhs){
        lhs.x-=rhs.x, lhs.y-=rhs.y;
        return lhs;
    }

    XY &operator*=(XY &lhs, double rhs){
        lhs.x*=rhs, lhs.y*=rhs;
        return lhs;
    }

    XY &operator/=(XY &lhs, double rhs){
        lhs.x/=rhs, lhs.y/=rhs;
        return lhs;
    }

    bool operator==(XY lhs, XY rhs){
        return lhs.x==rhs.x && lhs.y==rhs.y;
    }
    bool operator!=(XY lhs, XY rhs){
        return lhs.x!=rhs.x || lhs.y!=rhs.y;
    }

    std::ostream &operator<<(std::ostream &lhs, XY const &rhs){
        std::cout<< '('<< rhs.x<< ", "<< rhs.y<< ')';
        return lhs;
    }


    RGBA to_RGBA(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a){
        RGBA res = {_r, _g, _b, _a};
        return res;
    }

    RGBA operator+(RGBA lhs, RGBA rhs){
        return to_RGBA(lhs.r+rhs.r, lhs.g+rhs.g, lhs.b+rhs.b, lhs.a+rhs.a);
    }

    RGBA operator-(RGBA lhs, RGBA rhs){
        return to_RGBA(lhs.r-rhs.r, lhs.g-rhs.g, lhs.b-rhs.b, lhs.a-rhs.a);
    }

    RGBA operator*(RGBA lhs, Uint8 rhs){
        return to_RGBA(lhs.r*rhs, lhs.g*rhs, lhs.b*rhs, lhs.a*rhs);
    }

    RGBA operator*(Uint8 lhs, RGBA rhs){
        return to_RGBA(lhs*rhs.r, lhs*rhs.g, lhs*rhs.b, lhs*rhs.a);
    }

    RGBA operator/(RGBA lhs, Uint8 rhs){
        return to_RGBA(lhs.r/rhs, lhs.g/rhs, lhs.b/rhs, lhs.a/rhs);
    }

    RGBA &operator+=(RGBA &lhs, RGBA rhs){
        lhs.r+=rhs.r, lhs.g+=rhs.g, lhs.b+=rhs.b, lhs.a+=rhs.a;
        return lhs;
    }

    RGBA &operator-=(RGBA &lhs, RGBA rhs){
        lhs.r-=rhs.r, lhs.g-=rhs.g, lhs.b-=rhs.b, lhs.a-=rhs.a;
        return lhs;
    }

    RGBA &operator*=(RGBA &lhs, Uint8 rhs){
        lhs.r*=rhs, lhs.g*=rhs, lhs.b*=rhs, lhs.a*=rhs;
        return lhs;
    }

    RGBA &operator/=(RGBA &lhs, Uint8 rhs){
        lhs.r/=rhs, lhs.g/=rhs, lhs.b/=rhs, lhs.a/=rhs;
        return lhs;
    }

    std::ostream &operator<<(std::ostream &lhs, RGBA const &rhs){
        std::cout<< '('<< rhs.r<< ", "<< rhs.g<< ", "<< rhs.b<< ", "<< rhs.a<< ')';
        return lhs;
    }
}