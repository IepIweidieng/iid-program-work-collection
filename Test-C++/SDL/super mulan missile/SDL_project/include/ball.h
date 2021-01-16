#ifndef BALL_H
#define BALL_H
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "patterns.h"

class ball
{
    public:
        static int ball_num;
        struct rgba
        {
            char r,g,b,a;
        };

        ball();
        virtual ~ball();

        unsigned int get_rad();
        pos get_pos();

        void draw_ball(SDL_Renderer* pRenderer);
        void reset();
        void super();

        void change_color();
        void change_pos(int p_x,int p_y);
        void change_pos_by_V(double dx,double dy);
        void change_rad(int rad);

        bool enable_super;
    protected:
        bool rad_c_vec;
        unsigned int radius;

        pos ball_pos;
        rgba color;

};
#endif // BALL_H
