#include "mulan_missle.h"
#include <math.h>
#include <iostream>
#include "factory.h"

typedef mulan_missle mlm;
int mlm::mis_amount=0;
const double mlm::dR=10.0;

//mlm fuctions
void mlm_single_twin_update(const pos *mass_heart,vec *mass_heart_vec,pos &twins,const double routine,double V,const int num)
{
    vec dp;
    double cosx=cos(routine)*((num==0)? 1:-1),
           k=sqrt(1.0+(1/(cosx*cosx))),
           cosa=1.0/cosx/k,      sina=1.0/k,
           cost=mass_heart_vec->x,sint=mass_heart_vec->y;
    dp.x=V*k*cosx*(cosa*cost-sina*sint);
    dp.y=V*k*cosx*(sina*cost+sint*cosa);
    twins.change_pos_by_V(dp.x,dp.y);
}
void mlm_move(pos *mass_heart,vec *mass_heart_vec,pos *twins,unsigned int &routine,unsigned int dR,double V)
{
    //mass heart update
    double cur=radianToDegree(routine);
    mass_heart->x+=mass_heart_vec->x*V;
    mass_heart->y+=mass_heart_vec->y*V;
    routine+=(dR);
    routine%=360;
    mlm_single_twin_update(mass_heart,mass_heart_vec,twins[0],cur,V,0);
    mlm_single_twin_update(mass_heart,mass_heart_vec,twins[1],cur,V,1);
}

mulan_missle::mulan_missle(double _x, double _y/*the start point*/):
  mass_heart (),mass_heart_vec (),twins (new pos[2]),routine (5.5)
{
    DEBUG(just_for_debug("mulan_missle::mulan_missle\n");)
    mass_heart->x=_x;
    mass_heart->y=_y;

    twins[0].x=twins[1].x=_x;
    twins[0].y=twins[1].y=_y;

    mis_amount++;
    DEBUG(just_for_debug("exit\n");)
}

mulan_missle::mulan_missle(const mulan_missle &_val):
  mass_heart (_val.mass_heart),mass_heart_vec (_val.mass_heart_vec),
  twins (new pos[2])          ,routine (_val.routine)
{
    DEBUG(just_for_debug("mulan_missle::mulan_missle (copy)\n");)
    routine=_val.routine;
    mass_heart->x = _val.mass_heart->x;
    mass_heart->y = _val.mass_heart->y;
    mass_heart_vec->x =_val.mass_heart_vec->x;
    mass_heart_vec->y =_val.mass_heart_vec->y;
    twins[0] =_val.twins[0];
    twins[1] =_val.twins[1];
    ++mis_amount;
}

mulan_missle &mulan_missle::operator=(const mulan_missle &_val)
{
    DEBUG(just_for_debug("mulan_missle::mulan_missle (assign)\n");)
    routine=_val.routine;
    mass_heart->x = _val.mass_heart->x;
    mass_heart->y = _val.mass_heart->y;
    mass_heart_vec->x =_val.mass_heart_vec->x;
    mass_heart_vec->y =_val.mass_heart_vec->y;
    twins[0] =_val.twins[0];
    twins[1] =_val.twins[1];
    return *this;
}
mulan_missle::~mulan_missle()
{
    DEBUG(just_for_debug("mulan_missle::~mulan_missle\n");)
    delete [] twins;
    mis_amount--;
}
void mulan_missle::missle_initialize(double p_x,
                                     double p_y/*the way where it goes.*/)
{
    DEBUG(just_for_debug("mulan_missle::missle_initialize\n");)
    //initialize all the velocity of missile
    mass_heart_vec->x=p_x-mass_heart->x;
    mass_heart_vec->y=p_y-mass_heart->y;
    double R=mass_heart_vec->length();
    mass_heart_vec->x/=R;
    mass_heart_vec->y/=R;
}
bool mlm::is_out_of_boarder(int _x, int _y)
{
    DEBUG(just_for_debug("mlm::is_out_of_boarder\n");)
    return mass_heart->x < -20 || mass_heart->y < -20 ||
             mass_heart->x > _x+20 || mass_heart->y > _y+20;
}
void mlm::move(double V)
{
    DEBUG(just_for_debug("mlm::move\n");)
    mlm_move(mass_heart,mass_heart_vec,twins,routine,dR,V);
}
