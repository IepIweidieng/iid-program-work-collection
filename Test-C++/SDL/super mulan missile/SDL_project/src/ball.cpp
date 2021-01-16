#include "ball.h"
#include <algorithm>
#include <time.h>
using namespace std;
int ball::ball_num=0;
ball::ball(): color (), enable_super (0),radius (20),rad_c_vec (1)
{
    ball_pos.x=400;
    ball_pos.y=300;
    color.a=color.g=color.r=255;
    color.b=0;
    ball::ball_num++;
}
ball::~ball(){ball::ball_num--;}
void ball::reset()
{
    color.a=color.g=color.r=255;
    color.b=0;
    radius=20;
}
void ball::draw_ball(SDL_Renderer* pRenderer)
{
    if(enable_super)
        super();
    filledEllipseRGBA(pRenderer, ball_pos.x, ball_pos.y, radius, radius, color.r, color.g, color.b, color.a);
}
void ball::change_color()
{
    color.g=rand()%256;
    color.r=rand()%256;
    color.b=rand()%256;
}
void ball::super()
{
    if(radius<=5||radius>=50)
        rad_c_vec=!rad_c_vec;
    if(rad_c_vec)
        radius+=4;
    else
        radius-=4;
    change_color();
}
void ball::change_pos(int p_x,int p_y)
{
    ball_pos.x=p_x;
    ball_pos.y=p_y;
}
pos ball::get_pos(){
    return pos(ball_pos.x, ball_pos.y);
}
void ball::change_pos_by_V(double dx,double dy)
{
    ball_pos.change_pos_by_V(dx,dy);
}
unsigned int ball::get_rad()
{
    return radius;
}
void ball::change_rad(int rad)
{
    radius=rad;
}
