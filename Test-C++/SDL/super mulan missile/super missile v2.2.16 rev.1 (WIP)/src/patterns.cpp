#include <math.h>
#include <iostream>
#include "patterns.h"
using namespace std;
const double pi=acos(-1.0);
pos to_pos(double _x = 0, double _y = 0){
  pos res = {_x, _y};
  return res;
}
vec to_vec(double _x = 0, double _y = 0){
  vec res = {_x, _y};
  return res;
}
double radianToDegree(double v)
{
    while(v>360)
        v-=360;
    while(v<0)
        v+=360;
    return v*pi/180;
}
inline int abs(int num)
{
    if(num<0)
        return -num;
    return num;
}
inline double abs(double num)
{
    if(num<0)
        return -num;
    return num;
}
pos G_v_change_amount(pos big,pos lit,double V)
{
    double range=sqrt(pow(big.x-lit.x,2)+pow(big.y-lit.y,2));
    double strength=G*(range*range)*V;
    double costh=(big.x-lit.x)/range;
    double sinth=(big.y-lit.y)/range;
    pos v_change;
    v_change.x=strength*costh;
    v_change.y=strength*sinth;
    return v_change;
}
pos G_force(const pos obj_1,const int m1,const pos obj_2,const int m2)
{
    int x=abs(obj_1.x-obj_2.x),y=abs(obj_1.y-obj_2.y);
    double dis=sqrt(pow(x,2)+pow(y,2));
    double F=G*m1*m2/(dis*dis);
    pos ret;
    ret.x=F*x/dis;
    ret.y=F*y/dis;
    return ret;
}
//vec class fuctions
double vec::length()
{
    return sqrt(x*x+y*y);
}
double dot(vec a,vec b)
{
    return a.x*b.x+a.y*b.y;
}
double cos(vec a,vec b)
{
    return dot(a,b)/(a.length()*b.length());
}
vec vec::operator+(vec val)
{
    val.x+=x;
    val.y+=y;
    return val;
}
void vec::operator+=(const vec val)
{
    x+=(val.x);
    y+=(val.y);
}
//pos fuctions
void pos::change_pos_by_V(double dx,double dy)
{
    x+=dx;
    y+=dy;
}
vec rotation(vec a,vec b)
{
    double l1=a.length(),l2=b.length();
    a.x/=l1;a.y/=l1;
    b.x/=l2;b.y/=l2;
    vec ret;
    ret.x=a.x*b.x-a.y*b.y;
    ret.y=a.y*b.x+b.y+a.x;
    return ret;
}
