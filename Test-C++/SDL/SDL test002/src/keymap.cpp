#include "keymap.h"

namespace Game_Objects{
    std::vector<Key> players;

    Uint8 const KEY_MASK[]={1<<7,                     //0b10000000  Repellent keys of key NO. 1
                            1<<6 | 1<<4 | 1<<3,       //0b01011000  Repellent keys of key NO. 2
                            1<<5,                     //0b00100000  Repellent keys of key NO. 3
                            1<<4 | 1<<6 | 1<<1,       //0b01010010  Repellent keys of key NO. 4
                            1<<3 | 1<<6 | 1<<1,       //0b01001010  Repellent keys of key NO. 6
                            1<<2,                     //0b00000100  Repellent keys of key NO. 7
                            1<<1 | 1<<4 | 1<<3,       //0b00011010  Repellent keys of key NO. 8
                            1<<0              };      //0b00000001  Repellent keys of key NO. 9
                            //  Repellent keys of key NO. 12346789

    void Key::input_Key_Down(SDL_Event &event){
        if (event.type == SDL_KEYDOWN && event.key.repeat == false){
            for (Uint8 k=0; k<ARROW_COUNT; ++k){
                if (arrow_key[k].key_index != SDLK_UNKNOWN){
                    if (event.key.keysym.sym == arrow_key[k].key_index){
                        arrow_list.push_back(arrow_key[k]);;
                        return;
                    }
                }
            }
        }
    }

    void Key::input_Key_Up(SDL_Event &event, Uint8 const *keystate){
        if (event.type == SDL_KEYUP){
            for (Uint8 k=0; k<ARROW_COUNT; ++k){
                if (arrow_key[k].key_index != SDLK_UNKNOWN){
                    if (event.key.keysym.sym == arrow_key[k].key_index){
                        arrow_list.remove_if(EQU_rhs<SDL_Keycode> (arrow_key[k].key_index));
                        break;
                    }
                }
            }
        }
        for (Uint8 k=0; k<ARROW_COUNT; ++k){
            if (arrow_key[k].key_index != SDLK_UNKNOWN){
                if (!keystate[SDL_GetScancodeFromKey(arrow_key[k].key_index)]){
                    arrow_list.remove_if(EQU_rhs<SDL_Keycode> (arrow_key[k].key_index));
                }
            }
        }
    }

    void Key::update(){
        output = 0x00000000;
        for (std::list<Key_Arrow>::iterator k = arrow_list.begin(), n = arrow_list.end(); k != n; ++k){
            output = (output | 1<<(7-(k->key_value))) & KEY_MASK[k->key_value];
        }
    }

    Direction Key::get_Direction(){
        switch(output){
            case 1<<2       :                      //0b00000100
            case 1<<1 | 1<<4: return UPPER_LEFT;   //0b00010010

            case 1<<1       : return UP;           //0b00000010

            case 1<<0       :                      //0b00000001
            case 1<<1 | 1<<3: return UPPER_RIGHT;  //0b00001010

            case 1<<4       : return LEFT;         //0b00010000

            case 0          : return MIDDLE;       //0b00000000

            case 1<<3       : return RIGHT;        //0b00001000

            case 1<<7       :                      //0b10000000
            case 1<<6 | 1<<4: return LOWER_LEFT;   //0b01010000

            case 1<<6       : return DOWN;         //0b01000000

            case 1<<5       :                      //0b00100000
            case 1<<6 | 1<<3: return LOWER_RIGHT;  //0b01001000

            default: return MIDDLE;
        }

        return MIDDLE;
    }
}