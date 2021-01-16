#ifndef KEYMAP_H_INCLUDED
#define KEYMAP_H_INCLUDED

#include <list>
#include <vector>
#include "SDL.h"

namespace Game_Objects{
    enum Direction{
        UPPER_LEFT, UP,     UPPER_RIGHT,
        LEFT,       MIDDLE, RIGHT,
        LOWER_LEFT, DOWN,   LOWER_RIGHT
    };

    template<class Type> struct EQU_rhs{
        Type rhs;
        EQU_rhs(Type _rhs): rhs (_rhs){}

        bool operator()(Type lhs){return lhs==rhs;}
    };

    extern Uint8 Key_Mask[];

    struct Key_Arrow{
        SDL_Keycode key_index;
        Uint8 key_value;

        Key_Arrow(SDL_Keycode _index = SDLK_UNKNOWN, Uint8 _value = 0): key_index (_index), key_value (_value){}

        operator SDL_Keycode(){return key_index;}
    };

    struct Key{
        enum Key_Array_Index{
            ARROW_D, ARROW_L, ARROW_R, ARROW_U,
            ARROW_1, ARROW_2, ARROW_3,
            ARROW_4,          ARROW_6,
            ARROW_7, ARROW_8, ARROW_9,
            ARROW_COUNT
        };

        std::list <Key_Arrow> arrow_list;
        Uint8 output;

        Key_Arrow arrow_key[ARROW_COUNT];

        Key():
          arrow_list (), output (), arrow_key (){}

        Key(SDL_Keycode _D, SDL_Keycode _L, SDL_Keycode _R, SDL_Keycode _U,
            SDL_Keycode _1, SDL_Keycode _2, SDL_Keycode _3,
            SDL_Keycode _4,                 SDL_Keycode _6,
            SDL_Keycode _7, SDL_Keycode _8, SDL_Keycode _9):
          arrow_list (), output (), arrow_key (){
            arrow_key[ARROW_D] = Key_Arrow(_D, 1), arrow_key[ARROW_L] = Key_Arrow(_L, 3),
            arrow_key[ARROW_R] = Key_Arrow(_R, 4), arrow_key[ARROW_U] = Key_Arrow(_U, 6),
            arrow_key[ARROW_1] = Key_Arrow(_1, 0), arrow_key[ARROW_2] = Key_Arrow(_2, 1), arrow_key[ARROW_3] = Key_Arrow(_3, 2),
            arrow_key[ARROW_4] = Key_Arrow(_4, 3),                                        arrow_key[ARROW_6] = Key_Arrow(_6, 4),
            arrow_key[ARROW_7] = Key_Arrow(_7, 5), arrow_key[ARROW_8] = Key_Arrow(_8, 6), arrow_key[ARROW_9] = Key_Arrow(_9, 7);
        }

        ~Key(){arrow_list.clear();}

        void input_Key_Down(SDL_Event &event);
        void input_Key_Up(SDL_Event &event, Uint8 const *keystate);
        void update();
        Direction get_Direction();
    };

    extern std::vector<Key> players;
}

#endif // KEYMAP_H_INCLUDED
