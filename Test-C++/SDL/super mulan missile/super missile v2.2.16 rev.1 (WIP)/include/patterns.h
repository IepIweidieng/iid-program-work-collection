#ifndef PATTERNS_H
#define PATTERNS_H

#include "debug.h"
struct pos
{
    double x,y;

    pos get_pos(){return (*this);}
    void change_pos_by_V(double dx,double dy);
};
struct vec
{
    double x,y;
    double length();

    vec operator+(vec val);
    void operator+=(const vec val);
};
pos to_pos(double _x, double _y);
vec to_vec(double _x, double _y);
static const double G=0.000007;
pos G_v_change_amount(pos big,pos lit,double V);
pos G_force(const pos obj_1,const int m1,const pos obj_2,const int m2);
double dot(vec a,vec b);
double cos(vec a,vec b);
void change_pos_by_vec(pos &tar,vec vec);
double radianToDegree(double v);
vec rotation(vec a,vec b);
#endif // PATTERNS_H
