#include "player.h"

player* player::cur_hold=nullptr;

const double move_accelerate=0.05;
const double sqr2=1/sqrt(2.0);
const double move_fricture=0.05;
static vec v_c[4];
inline int abs(int num)
{
    if(num<0)
        return -num;
    return num;
}
player::player(ball *p): enable_super (0),player1 (p)
{
    /*
        0->right
        1->left
        2->down
        3->up
    */
    v_c[0].x=1 ;v_c[0].y=0 ;
    v_c[1].x=-1;v_c[1].y=0 ;
    v_c[2].x=0 ;v_c[2].y=1 ;
    v_c[3].x=0 ;v_c[3].y=-1;
}
player::~player()
{
    delete [] player1;
}
void player::update_status(double V,bool dir[4])
{
    move_update(V,dir);
    status_update();
}
void player::move_update(double V,bool dir[4])
{
    /*
        0->right
        1->left
        2->down
        3->up
    */
    vec cur_v(0,0);
    for(int u=0;u!=4;++u)
        if(dir[u])
            cur_v+=v_c[u];
    if(cur_v.length()==0)
    {
        move_rate.x*=(1.0-move_fricture);
        move_rate.y*=(1.0-move_fricture);
    }
    else
    {
        if(cur_v.length()!=1)
        {
            cur_v.x*=sqr2;
            cur_v.y*=sqr2;
        }
        move_rate.x+=(cur_v.x*move_accelerate);
        move_rate.y+=(cur_v.y*move_accelerate);
    }

    if(move_rate.x>1)
        move_rate.x=1;
    if(move_rate.x<-1)
        move_rate.x=-1;
    if(move_rate.y>1)
        move_rate.y=1;
    if(move_rate.y<-1)
        move_rate.y=-1;

    player1->change_pos_by_V(move_rate.x*V,move_rate.y*V);
}
void player::status_update()
{
    if(enable_super)
        player1->super();
}
player* player::init_player(ball *p)
{
    if(cur_hold==nullptr)
        cur_hold=new player(p);
    return cur_hold;
}
void player::draw(SDL_Renderer* pRenderer)
{
    player1->draw_ball(pRenderer);
}
void player::pos_reset(int red_x,int red_y)
{
    player1->change_pos(red_x/2,red_y/2);
}
void player::reset()
{
    player1->reset();
}
pos player::get_pos()
{
    return player1->get_pos();
}
