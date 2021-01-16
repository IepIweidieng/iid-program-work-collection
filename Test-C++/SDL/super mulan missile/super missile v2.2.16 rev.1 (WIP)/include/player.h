#ifndef PLAYER_H
#define PLAYER_H
#include "ball.h"
class player
{
  friend class factory;
    public:
        static player* get_player();

        bool enable_super;

        void update_status(double V,bool dir[4]);
        void draw(SDL_Renderer* pRenderer);

        void pos_reset(int red_x,int red_y);
        void reset();

        pos get_pos();

        virtual ~player();

    protected:
        explicit player(ball *p);
    private:
        player(const player&);
        player &operator=(const player&);

        static player *cur_hold;

        ball *player1;
        vec move_rate;

        void move_update(double V,bool dir[4]);
        void status_update();

        static int player_num;
};

#endif // PLAYER_H
