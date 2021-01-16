#include <ctime>
#include "SDL2_gfxPrimitives.h"
#include "game.h"
#include "physical_object.h"

namespace Game_Objects{
    extern std::vector<Key> players;

    void Game::initialize_game(){
        srand(time(nullptr)^SDL_GetTicks());
        players.assign(1, Key()); // Player NULL
        balls.list_balls.clear();


        // Player 1
        players.push_back(Key(SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_UP,
                              SDLK_KP_1, SDLK_KP_2, SDLK_KP_3,
                              SDLK_KP_4,            SDLK_KP_6,
                              SDLK_KP_7, SDLK_KP_8, SDLK_KP_9));

        balls.list_balls.push_back(Ball(to_XY(400, 300),
                                        to_XY(0, 0),
                                        1e7, 500, 50, 350,
                                        to_RGBA(255, 255, 0, 255),
                                        0.8, 25));

        balls.list_balls.back().bind_to_key(players.size()-1);


        // Player 2
        players.push_back(Key(SDLK_s, SDLK_a, SDLK_d, SDLK_w,
                              SDLK_j, SDLK_k, SDLK_l,
                              SDLK_u,         SDLK_o,
                              SDLK_7, SDLK_8, SDLK_9));

        balls.list_balls.push_back(Ball(to_XY(400, 300),
                                        to_XY(0, 0),
                                        1e7, 500, 50, 350,
                                        to_RGBA(255, 0, 0, 255),
                                        0.8, 25));

        balls.list_balls.back().bind_to_key(players.size()-1);

        for (Uint32 k = rand_Close(0, 80); k; --k){
            double _move_v = rand_L_Open(0, 5e3),
                   _dec_v = rand_L_Open(0, _move_v),
                   _acc_v = rand_L_Open(0, _acc_v);
            balls.list_balls.push_back(Ball(to_XY(rand_Open(0, width), rand_Open(0, height)),
                                            to_XY(rand_Open(-width / 100, width / 100),
                                                  rand_Open(-height / 100, height / 100)),
                                            rand_L_Open(0, 5e7), _move_v, _dec_v, _acc_v,
                                            to_RGBA(rand_Close(10, 255),
                                                    rand_Close(10, 255),
                                                    rand_Close(10, 255),
                                                    255),
                                            rand_R_Open(0, 1), rand_Close(5, 90))
                                      );
        }

        int max_player_index = players.size();
        for (std::vector<Ball>::iterator k = balls.list_balls.begin(), n = balls.list_balls.end(); k != n; ++k){
            if (!k->key){
                int rnd_player_index = floor(rand_R_Open(0, max_player_index));
                if (rnd_player_index){
                    k->bind_to_key(rnd_player_index);
                }
            }
        }

        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);  // R, G, B, A
        SDL_RenderClear(m_pRenderer);
        m_bGameIsRunning = true;
    }
}
