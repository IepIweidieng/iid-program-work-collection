#ifndef MULAN_MISSLE_H
#define MULAN_MISSLE_H
#include "patterns.h"
#include "debug.h"
class mulan_missle
{
  friend class factory;
    public:
        pos *mass_heart;
        vec *mass_heart_vec;
        pos *twins;//the missiles

        mulan_missle(const mulan_missle &_val);
        virtual ~mulan_missle();
        void missle_initialize(double p_x,double p_y);
        void move(double V);
        bool is_out_of_boarder(int _x, int _y);

        mulan_missle &operator=(const mulan_missle &_val);
    protected:
        mulan_missle(double _x, double _y);

    private:
        unsigned int routine;//the routine of mass heart's change velocity
        static int mis_amount;
        static const double dR;//the amount of velocity change
};

#endif // MULAN_MISSLE_H
