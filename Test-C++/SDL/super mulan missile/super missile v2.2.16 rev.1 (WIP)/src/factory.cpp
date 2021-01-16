#include "factory.h"
#include <iostream>

DEBUG(void factory::check_products(){
    DEBUG_OUTPUT(
      "factory::factory_count: "<< factory::factory_count<< '\n'<<
      "factory::ball_count: "<< factory::ball_count<< '\n'<<
      "factory::player_count: "<< factory::player_count<< '\n'<<
      "factory::mulan_missle_count: "<< factory::mulan_missle_count<< '\n';)
})

int factory::factory_count=0;
int &factory::ball_count = ball::ball_num;
int &factory::player_count = player::player_num;
int &factory::mulan_missle_count = mulan_missle::mis_amount;

factory* factory::pFactory=nullptr;

factory::factory(){++factory_count;}
factory::~factory(){
    --factory_count;
    if(pFactory==this)
        pFactory=nullptr;
}
factory* factory::get_factory()
{
    if(pFactory==nullptr)
        pFactory=new factory();
    return pFactory;
}
ball* factory::get_ball()
{
    ball *b=new ball();
    return b;
}
player* factory::get_player()
{
    ball *player_ball=get_ball();
    player *p=new player(player_ball);
    return p;
}
mulan_missle* factory::get_mulan_missle(double x=0,double y=0)
{
    mulan_missle *m=new mulan_missle(x,y);
    return m;
}

double object::dR=2.0;
double object::radius=10.0;
object::object():
  center (new pos),c_v (new vec),type (),kid (nullptr),kid_num (),_i (factory::get_factory()->get_ball()),routine ()
{}

//for the initial missile
object::object(pos _center,vec _c_v,char *type_str):
  center (new pos),c_v (new vec),type (type_str[0]),kid (nullptr),kid_num (),_i (factory::get_factory()->get_ball()),routine ()
{
    //std::cout<<"object::object(for the initial missile)\n";

    (*center)=_center;
    c_v->x=_c_v.x/_c_v.length();c_v->y=_c_v.y/_c_v.length();

    //std::cout<<"v:"<<c_v->x<<' '<<c_v->y<<'\n';
   // std::cout<<"pos:"<<center->x<<' '<<center->y<<'\n';

//    int w;
//    std::cin>>w;

    int cur_pos=1;
    if(type=='n')
    {
        kid_num=0;
        kid=nullptr;
    }
    else if(type=='m')
    {
        routine=5.5;
        kid_num=2;
        kid=new object[2];

        kid[0].c_v   =kid[1].c_v   =this->c_v;
        kid[0].center=kid[1].center=this->center;

        kid[0].object_initialize(type_str,cur_pos);
        kid[1].object_initialize(type_str,cur_pos);
    }
    else if(type=='s')
    {
        routine=0;
        kid_num=0;
        for(;type_str[cur_pos]>='1'&&type_str[cur_pos]<='9';++cur_pos)
            kid_num=(kid_num*10+type_str[cur_pos]-'0');
        kid=new object[kid_num];

        for(int u=0;u!=kid_num;++u)
        {
            kid[u].center->x=center->x+radius*acos(radianToDegree(360.0/kid_num*u));
            kid[u].center->y=center->y+radius*asin(radianToDegree(360.0/kid_num*u));

            kid[u].c_v->x=acos(radianToDegree(360.0/kid_num*u));
            kid[u].c_v->x=asin(radianToDegree(360.0/kid_num*u));

            kid[u].object_initialize(type_str,cur_pos);
        }
    }
    else
        while(1){std::cout<<"Error!\n";}
}

//For copying.
object::object(const object &val):
  center (new pos),c_v (new vec),type (val.type),kid (nullptr),kid_num (val.kid_num),_i (factory::get_factory()->get_ball()),routine (val.routine)
{
  *center=*val.center;
  *c_v=*val.c_v;

  if (kid_num>0){
      kid = new object[kid_num];
      for (int k=0; k<kid_num; ++k)
      {
          kid[k]=val.kid[k];
      }
  }

  *_i=*val._i;
}

//For assignment.
object &object::operator=(const object &val)
{
  if (this == &val){return *this;}

  if (center==nullptr){
      center=new pos;
  }
  *center=*val.center;

  if (c_v==nullptr){
      c_v=new vec;
  }
  *c_v=*val.c_v;

  type=val.type;

  kid_num=val.kid_num;
  if (kid_num>0){
      kid = new object[kid_num];
      for (int k=0; k<kid_num; ++k)
      {
          kid[k]=val.kid[k];
      }
  }
  else
  {
      kid=nullptr;
  }

  *_i=*val._i;
  routine=val.routine;

  return *this;
}

void object::object_initialize(char *type_str,int &cur_pos)
{
    //std::cout<<"object::object_initialize\n";
    //SDL_Delay(100);
    cur_pos++;
    if(type_str[cur_pos-1]=='n')
    {
        kid_num=0;
        kid=nullptr;
    }
    else if(type_str[cur_pos-1]=='m')
    {
        routine=5.5;
        kid_num=2;
        kid=new object[2];

        kid[0].c_v   =kid[1].c_v   =this->c_v;
        kid[0].center=kid[1].center=this->center;

        kid[0].object_initialize(type_str,cur_pos);
        kid[1].object_initialize(type_str,cur_pos);
    }
    else if(type_str[cur_pos-1]=='s')
    {
        routine=0;
        kid_num=0;
        for(;type_str[cur_pos]>='1'&&type_str[cur_pos]<='9';++cur_pos)
            kid_num=(kid_num*10+type_str[cur_pos]-'0');
        kid=new object[kid_num];

        for(int u=0;u!=kid_num;++u)
        {
            kid[u].center->x=center->x+radius*acos(radianToDegree(360.0/kid_num*u));
            kid[u].center->y=center->y+radius*asin(radianToDegree(360.0/kid_num*u));

            kid[u].c_v->x=acos(radianToDegree(360.0/kid_num*u));
            kid[u].c_v->x=asin(radianToDegree(360.0/kid_num*u));

            kid[u].object_initialize(type_str,cur_pos);
        }
    }
    else
        while(1){std::cout<<"Error!\n";}
}

void object::update(double V)
{
    //std::cout<<"object::update\n";
    //SDL_Delay(100);
    static vec a,b;
    a.x=acos(radianToDegree(dR));a.y=asin(radianToDegree(dR));
    b.x=acos(radianToDegree(-dR));b.y=asin(radianToDegree(-dR));

    center->change_pos_by_V(c_v->x*V,c_v->y*V);

    if(type=='n')
        ;
    else if(type=='m')
    {
        (*kid[0].c_v)=rotation((*c_v),a);
        (*kid[1].c_v)=rotation((*c_v),b);
        kid[0].update(V);
        kid[1].update(V);
    }
    else if(type=='s')
        for(int u=0;u!=kid_num;++u)
        {
            (*(kid[u].c_v))=rotation((*(kid[u].c_v)),a);
            kid[u].center->change_pos_by_V(center->x*V,center->y*V);
            kid[u].update(V);
        }
    else
        while(1){std::cout<<"Error!\n";}
}
void object::draw(SDL_Renderer* pRenderer)
{
    //std::cout<<"object::draw\n";
    //SDL_Delay(100);
    if(type=='n')
    {
        _i->change_pos(center->x,center->y);
        _i->draw_ball(pRenderer);
    }
    else if(type=='m')
    {
        kid[0].draw(pRenderer);
        kid[1].draw(pRenderer);
    }
    else if(type=='s')
    {
        for(int u=0;u!=kid_num;++u)
            kid[u].draw(pRenderer);
        _i->change_pos(center->x,center->y);
        _i->draw_ball(pRenderer);
    }
    else
        while(1){std::cout<<"Error!\n";}
}
bool object::is_out_of_boarder(int _x,int _y)
{
    //std::cout<<"object::is_out_of_boarder\n";
    //SDL_Delay(100);
    return center->x < -20 || center->y < -20 ||
             center->x > _x+20 || center->y > _y+20;
}
object::~object()
{
    //std::cout<<"object::~object\n";
    //SDL_Delay(100);
    if(_i!=nullptr)
        delete _i;
    if(kid!=nullptr)
        delete [] kid;
    if(center!=nullptr)
        delete center;
    if(c_v!=nullptr)
        delete c_v;
}
