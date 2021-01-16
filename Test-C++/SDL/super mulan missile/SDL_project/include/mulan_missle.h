#ifndef MULAN_MISSLE_H
#define MULAN_MISSLE_H
#define MLDEBUG 1
#include "ball.h"
class mulan_missle:protected ball
{
    public:
        pos *mass_heart;
        vec *mass_heart_vec;
        pos *twins;//the missiles

        static unsigned int mis_amount;
        mulan_missle();
        mulan_missle(double _x, double _y);
        mulan_missle(mulan_missle const &_val);
        virtual ~mulan_missle();
        void missle_initialize(double p_x,double p_y);
        void move(double V);
        bool is_out_of_boarder(int _x, int _y);

        mulan_missle &operator=(mulan_missle const &_val);
    protected:

    private:
    unsigned int routine;//the routine of mass heart's change velocity
    static const double dR;//the amount of velocity change
};

#endif // MULAN_MISSLE_H
