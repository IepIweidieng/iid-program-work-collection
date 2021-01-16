#ifndef PLAYER_H
#define PLAYER_H
#include "ball.h"

class player
{
    public:
        bool enable_super;
        player* init_player(ball *p);

        void update_status(double V,bool dir[4]);
        void draw(SDL_Renderer* pRenderer);

        void pos_reset(int red_x,int red_y);
        void reset();

        pos get_pos();

        virtual ~player();

    protected:
        player(ball *p);
    private:
        static player *cur_hold;

        ball *player1;
        vec move_rate;

        void move_update(double V,bool dir[4]);
        void status_update();
};

#endif // PLAYER_H
