#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include <ctime>
#include "SDL.h"
#include "coordinate.h"
#include "game_setting.h"

namespace Game_Objects{
    // Global values
    extern int width;
    extern int height;

    extern bool magic_Mode;
    extern bool accelerative_Mode;
    extern bool gravity_Mode;
    extern bool universal_Gravitation_Mode;

    extern double reg_g;
    extern double acceleration_g;
    extern double max_vel;
    extern double max_acc;

    extern double const G;
    extern double const PI;

    extern int const TICKS_PER_SECOND;
    extern int const TICKS_TIME;
    extern int const MAX_FRAMESKIP;

    // [down, up]
    double rand_Close (double down, double up);
    // [down, up)
    double rand_R_Open(double down, double up);
    extern double (&rand_L_Close)(double down, double up);
    // (down, up]
    double rand_L_Open(double down, double up);
    extern double (&rand_R_Close)(double down, double up);
    // (down, up)
    double rand_Open  (double down, double up);


    class Game{
      private:
        class FPS_Counter{
            clock_t head_clock;
            int update;
            int display;

            friend class Game;
        };
        static Game *m_instance;

        SDL_Window *m_pWindow;
        SDL_Renderer *m_pRenderer;
        SDL_Event m_event;
        bool m_bGameIsRunning;
        Uint8 const *m_keystate;
        double interpolation;
        FPS_Counter loops;

        Game();
        Game(Game const&):
          m_pWindow (), m_pRenderer (), m_event (), m_bGameIsRunning (), m_keystate (),
          interpolation (), loops (){}
        ~Game();

        void init();
        bool initSDL();
        void initialize_game();
        void handle_game();
        void update_game();
        void display_game();
        void display_fps();
        void quit(){m_bGameIsRunning = false;}
        bool isRunning(){return m_bGameIsRunning;}
        void clearSDL();

        Game const &operator=(Game const&){return *this;}

      public:
        static void get_instance();
    };
}

#endif // GAME_H_INCLUDED
