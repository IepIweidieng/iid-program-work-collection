#ifndef FACTORY_H
#define FACTORY_H
#include "ball.h"
#include "player.h"
#include "mulan_missle.h"
#include "debug.h"

class object
{
    public:
        //for the initial missile
        object(pos _center,vec _c_v,char *type_str);
        object();
        object(const object &val);
        object &operator=(const object&);
        ~object();
        void update(double V);
        void draw(SDL_Renderer* pRenderer);
        bool is_out_of_boarder(int width,int height);

    private:
        pos *center;
        vec *c_v;
        char type;
        object *kid;
        int kid_num;
        ball *_i;
        static double dR;
        double routine;
        static double radius;
        void object_initialize(char *type_str,int &cur_pos);
        void star_missle_initial();
};
class factory
{
    public:
        DEBUG(static void check_products();)
        static factory* get_factory();

        ball* get_ball();
        player* get_player();
        mulan_missle* get_mulan_missle(double x,double y);
        virtual ~factory();
    protected:
        factory();
    private:
        static int factory_count;
        static int &ball_count;
        static int &player_count;
        static int &mulan_missle_count;

        static factory* pFactory;
};

#endif // FACTORY_H
