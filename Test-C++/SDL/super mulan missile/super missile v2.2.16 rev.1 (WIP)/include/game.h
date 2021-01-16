#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <vector>
#include "ball.h"
#include "mulan_missle.h"
#include "factory.h"
#include "debug.h"

const int GCNUM = 2;
class game
{
    public:
        game();
        virtual ~game();
        void game_event();
        typedef void (game::*fp)();
        static fp G_cy[GCNUM];
    private:
        bool initSDL();
        void eve();
        void drawR();
        void GetTicks();
        void uncon_key_eve();
        void con_key_eve();
        void mouse_eve();
        int width;
        int height;
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;

        bool bGameIsRunning;

        uint_fast16_t FPS;
        uint_fast32_t FramePerSec;


        bool debug;
        bool super_mode;
        double V;
        std::vector<object> mlm_eve;
        player *players;
        LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
        LARGE_INTEGER Frequency;
        factory* FACTORY;

        game(game const &);
        game &operator=(const game &);
};
#endif // GAME_H
