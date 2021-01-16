#ifndef GAME_SETTING_H_INCLUDED
#define GAME_SETTING_H_INCLUDED

namespace Game_Objects{
    double const FPS = 60;
    double const GAME_SPEED_RATE = 1;

    int const TICKS_PER_SECOND = FPS * GAME_SPEED_RATE;
    int const TICKS_TIME = 1000 / TICKS_PER_SECOND;
    int const MAX_FRAMESKIP = 5;
    int const MIN_FPS_DISPLAY_INTERVEL = 1000;
    double const TICKS_INTERVEL = 1 / double(FPS);
}

#endif // GAME_SETTING_H_INCLUDED
