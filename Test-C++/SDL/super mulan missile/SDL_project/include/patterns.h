#ifndef PATTERNS_H
#define PATTERNS_H

struct pos
{
    double x,y;
        pos(double _x = 0, double _y = 0): x (_x), y (_y){}
        pos get_pos(){return (*this);}
        void change_pos_by_V(double dx,double dy);
};
class vec
{
    public:
        double x,y;
        vec(double _x = 0, double _y = 0): x (_x), y (_y){}
        double length();
        vec operator+(vec val);
        void operator+=(const vec val);
};
static const double G=0.000007;
pos G_v_change_amount(pos big,pos lit,double V);
pos G_force(const pos obj_1,const int m1,const pos obj_2,const int m2);
double dot(vec a,vec b);
double cos(vec a,vec b);
void change_pos_by_vec(pos &tar,vec vec);
double radianToDegree(double v);
vec rotation(vec a,vec b);
#endif // PATTERNS_H
