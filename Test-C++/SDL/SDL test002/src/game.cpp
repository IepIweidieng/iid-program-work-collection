#include <sstream>
#include <cstdlib>
#include <cmath>
#include "SDL2_gfxPrimitives.h"
#include "game.h"
#include "physical_object.h"
#include "debug.h"


bool DEBUG_OUT = false;

namespace Game_Objects{
    // Global Values
    int width = 800;
    int height = 600;

    bool magic_Mode = false;
    bool accelerative_Mode = false;
    bool gravity_Mode = false;
    bool universal_Gravitation_Mode = false;

    double reg_g;
    double acceleration_g;
    double max_vel = sqrt((width * width) + (height * height)) * 1e3;
    double max_acc = max_vel;

    double const G = 6.67408e-5;
    double const PI = acos(-1);

    Game *Game::m_instance = nullptr;  // Static data members should be initialized when the program launches.

    // [down, up]
    double rand_Close (double down, double up){return( (up-down) * rand()        / double(RAND_MAX      ) + down);}
    // [down, up)
    double rand_R_Open(double down, double up){return( (up-down) * rand()        / double(RAND_MAX + 1.0) + down);}
    double (&rand_L_Close)(double down, double up) = rand_R_Open;    // (down, up]
    // (down, up]
    double rand_L_Open(double down, double up){return(((up-down) * rand() + 1.0) / double(RAND_MAX + 1.0) + down);}
    double (&rand_R_Close)(double down, double up) = rand_L_Open;
    // (down, up)
    double rand_Open  (double down, double up){return(((up-down) * rand() + 1.0) / double(RAND_MAX + 2.0) + down);}


    void Game::get_instance(){
        if (!m_instance){
            m_instance = new Game;
            delete m_instance;
        }
    }

    Game::Game():
      m_pWindow (), m_pRenderer (), m_event (), m_bGameIsRunning (), m_keystate (),
      interpolation (), loops (){
        init();

        Uint32 next_game_tick = SDL_GetTicks();
        int update_loops = 0;
        loops.update = 0;
        loops.display = 0;
        loops.head_clock = clock();

        display_fps();

        while(isRunning()){
            update_loops = 0;
            while (SDL_GetTicks() > next_game_tick && update_loops < MAX_FRAMESKIP){
                handle_game();         // 2 - Handle events.
                update_game();         // 3 - Update physical state.

                next_game_tick += TICKS_TIME;
                ++update_loops;
            }
            loops.update += update_loops;

            interpolation = double(SDL_GetTicks() + TICKS_TIME - next_game_tick)
                            / double(TICKS_TIME);
            display_game(); // 4 - Draw the stage.
            ++loops.display;

            if (clock() - loops.head_clock >= MIN_FPS_DISPLAY_INTERVEL * CLOCKS_PER_SEC / 1000){
                display_fps();
                loops.update = 0;
                loops.display = 0;
                loops.head_clock = clock();
            }
        }
    }

    Game::~Game(){
        clearSDL();                    // 5 - Quit the game; release used resource.
        if (m_instance == this){
            m_instance = nullptr;
        }
    }

    void Game::init(){
        if(!initSDL()){                   // 1 - Initialize the game.
            std::cout<< "Init failed. "<< SDL_GetError()<< std::endl;
            quit();
            return;
        }
        initialize_game();
    }

    // Initialize SDL
    bool Game::initSDL(){
        if (SDL_Init(SDL_INIT_EVERYTHING) >= 0){
            m_pWindow = SDL_CreateWindow("SDL test002",                   // Window title
                                     SDL_WINDOWPOS_UNDEFINED,    // X coordination of window position
                                     SDL_WINDOWPOS_UNDEFINED,    // Y coordination of window position
                                     width, height,                               // Width and height
                                     SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);  // Other optional flags
            if (m_pWindow){
                m_pRenderer = SDL_CreateRenderer(m_pWindow,
                                         -1,                      // Use the first supported driver.
                                         SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC); // Use hardware acceleration.
                if (m_pRenderer){
                    m_keystate = SDL_GetKeyboardState(nullptr);
                    return true;
                }
            }
        }
        return false;
    }

    void Game::handle_game(){
        while (SDL_PollEvent(&m_event)){
            if (m_event.type == SDL_QUIT){
                quit();
            } else if (m_event.type == SDL_KEYDOWN && m_event.key.repeat == false){
                switch (m_event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quit();
                        std::cout<< "Quited game!"<< std::endl;
                        break;
                    case SDLK_m:
                        magic_Mode ^= 1;
                        std::cout<< "Magic Mode "<< (magic_Mode? "ACTIVATED!": "DEACTIVATED!")<< std::endl;
                        break;
                    case SDLK_c:
                        accelerative_Mode ^= 1;
                        std::cout<< "Accelerative Mode "<<(accelerative_Mode? "ACTIVATED!": "DEACTIVATED!")<< std::endl;
                        break;
                    case SDLK_g:
                        gravity_Mode ^= 1;
                        if (gravity_Mode){
                            reg_g = rand_R_Open(0, 2*PI);
                            acceleration_g = rand_L_Open(0, 1200);
                        }
                        std::cout<< "Gravity Mode "<<(gravity_Mode? "ACTIVATED!": "DEACTIVATED!")<< std::endl;
                        break;
                    case SDLK_v:
                        universal_Gravitation_Mode ^= 1;
                        std::cout<< "Universal Gravitation Mode "<<(universal_Gravitation_Mode? "ACTIVATED!": "DEACTIVATED!")<< std::endl;
                        break;
                    case SDLK_r:
                        initialize_game();
                        std::cout<< "Reset game!"<< std::endl;
                        break;
                    default:
                        break;
                }

                for (std::vector<Key>::iterator k = players.begin(), n = players.end(); k != n; ++k){
                    (k->input_Key_Down)(m_event);
                }
            } else if (m_event.type == SDL_KEYUP && m_event.key.repeat == false){
                switch (m_event.key.keysym.sym){
                    default:
                        break;
                }
                for (std::vector<Key>::iterator k = players.begin(), n = players.end(); k != n; ++k){
                    (k->input_Key_Up)(m_event, m_keystate);
                }
            }
        }
    }

    void Game::update_game(){
        for (std::vector<Key>::iterator k = players.begin(), n = players.end(); k != n; ++k){
            k->update();
        }

        for (std::vector<Ball>::iterator k = balls.list_balls.begin(), n = balls.list_balls.end(); k != n; ++k){
            k->update_position();

            balls.update();
            k->collision_Border();
            for (std::vector<Ball>::iterator m = k+1; m != n; ++m){
                ball_Collision(*k, *m);
            }
            if (magic_Mode){
                for (std::vector<Ball>::iterator m = k+1; m != n; ++m){
                    ball_Magic_Collision(*k, *m);
                }
            }
            k->force_to_velocity();
            k->move();
        }

        for (std::vector<Ball>::iterator k = balls.list_balls.begin(), n = balls.list_balls.end(); k != n; ++k){
            if (gravity_Mode){
                k->fs.push_back(Force_Element(to_XY(acceleration_g*cos(reg_g) * k->mass,
                                                    acceleration_g*sin(reg_g) * k->mass),
                                              1,
                                              "Gravity"));
            }

            if (universal_Gravitation_Mode){
                for (std::vector<Ball>::iterator m = k+1; m != n; ++m){
                    gravitation(*k, *m);
                }
            }
        }

DEBUG_output_if(std::cout<< "\n";)
DEBUG_reset
    }

    void Game::display_game(){
        // Draw background.
        boxRGBA(m_pRenderer, 0, 0, width, height, 0, 0, 0, 191);

        // Draw balls.
        for (std::vector<Ball>::iterator k = balls.list_balls.begin(), n = balls.list_balls.end(); k != n; ++k){
            if (magic_Mode && k+1!=n){
                thickLineRGBA(m_pRenderer,
                              k->pos.x + (k->vel.x * TICKS_INTERVEL * (interpolation)), k->pos.y + (k->vel.y * TICKS_INTERVEL * (interpolation)),
                              (k+1)->pos.x + ((k+1)->vel.x * TICKS_INTERVEL * (interpolation)), (k+1)->pos.y + ((k+1)->vel.y * TICKS_INTERVEL * (interpolation)),
                              15, 200, 255, 200, 127);
            }
            k->display(m_pRenderer, interpolation);
        }
        // Display
        SDL_RenderPresent(m_pRenderer);
    }

    void Game::display_fps(){
        double loop_intervel = (clock() - loops.head_clock) / double(CLOCKS_PER_SEC);

        std::stringstream title_str ("");
        title_str<< "SDL test002 - update: "<< loop_intervel*loops.update<< " FPS / display: "<< loop_intervel*loops.display<< " FPS";

        SDL_SetWindowTitle(m_pWindow,title_str.str().c_str());
    }

    void Game::clearSDL(){
        // Release used SDL resource.
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
    }
}