#include "game.h"
#include <iostream>
using namespace std;
typedef mulan_missle mlm;
typename game::fp game::G_cy[GCNUM]={&game::eve,&game::drawR};
game::game(): width            (800), height           (600),
              pWindow         (NULL), pRenderer       (NULL),
              bGameIsRunning     (1),
              FPS              (100), FramePerSec (1000/FPS),
              debug              (0), V          (750.0/FPS),
              /*mlm_eve             (),*/
              StartingTime        (), EndingTime          (),
              ElapsedMicroseconds (), Frequency           (),
              FACTORY (FACTORY->initial_factory())
{
    players=FACTORY->get_player();
    if(!initSDL())
        cout << "Init SDL failed.\n"<<SDL_GetError()<<'\n';
}
game::~game()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void game::game_event()
{
    QueryPerformanceFrequency(&Frequency);

    for(int current=0;
		bGameIsRunning;
		current++,
		current%=GCNUM,
		GetTicks())
        QueryPerformanceCounter(&StartingTime),(this->*(game::G_cy[current]))();
}
bool game::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        pWindow = SDL_CreateWindow("Your \"Ball\"",                      // 視窗標題
                                 SDL_WINDOWPOS_UNDEFINED,    // X 座標
                                 SDL_WINDOWPOS_UNDEFINED,    // Y 座標
                                 width, height,                                         // 寬、高
                                 SDL_WINDOW_SHOWN|SDL_RENDERER_PRESENTVSYNC);               // 其他設定旗標
        if(pWindow != NULL)
        {
            pRenderer = SDL_CreateRenderer(pWindow,
                                     -1,                                                           // 使用第一個支援的driver
                                     SDL_RENDERER_ACCELERATED); // 使用硬體加速
            if(pRenderer != NULL)
            {
                return true;
            }
        }
    }
    return false;
}
inline void game::GetTicks()
{
    do{
            QueryPerformanceCounter(&EndingTime);
            ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
            ElapsedMicroseconds.QuadPart *= 1000000;
            ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    }while(ElapsedMicroseconds.QuadPart <= (FramePerSec*1000));  // ms
}
void game::eve()
{
    uncon_key_eve();
    con_key_eve();
    mouse_eve();
}
void game::drawR()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 127, 0);  // R, G, B, A
    SDL_RenderClear(pRenderer);
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 127, 0);// R, G, B, A
    for(int k=mlm_eve.size(),t=0;t!=k;t++)
    {
        mlm_eve[t].draw(pRenderer);
        mlm_eve[t].update(V);
        if(mlm_eve[t].is_out_of_boarder(width,height))
                mlm_eve.erase(mlm_eve.begin()+t);
    }
    players->draw(pRenderer);
    // 將背景中的圖片，顯示到前景
    SDL_RenderPresent(pRenderer);
}
inline void game::uncon_key_eve()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            bGameIsRunning = false;
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    bGameIsRunning = false;
                    break;
                case SDLK_r:
                    players->pos_reset(width,height);
                    break;
                case SDLK_u:
                    debug=!debug;
                    break;
                default:
                    break;
            }
        }
    }
}
inline void game::con_key_eve()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_F])
    {
        V+=2;
        SDL_Delay(100);
        cout<<"fast!!!\n";
    }
    if(state[SDL_SCANCODE_G])
    {
        V-=4;
        SDL_Delay(100);
        cout<<((V<=1)? "I can't Baby...\n":"slow...\n");
        if(V<=1) V=0;
    }
    /*
        0->right
        1->left
        2->down
        3->up
    */
    bool dir[4]={(bool)state[SDL_SCANCODE_D],(bool)state[SDL_SCANCODE_A],(bool)state[SDL_SCANCODE_S],(bool)state[SDL_SCANCODE_W]};
    players->update_status(V,dir);
    if(debug)
    {
        int pre=0;
        for(int u=0;u!=9;u++)
            if(state[SDL_SCANCODE_A+u])
                pre++;
        cout<<pre<<'\n';
    }
}

inline void game::mouse_eve()
{
    int m_x,m_y;
    SDL_GetMouseState(&m_x,&m_y);

    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        pos p = players->get_pos();
        vec m;
        m.x=m_x-p.x;   m.y=m_y-p.y;
        char str[]="n";
        object o(p,m,str);
        mlm_eve.push_back(o);
//        SDL_Delay(100);
    }
        //new_ms.super_missile_enable();
       // mlm_eve.push_back(new_ms);
//        SDL_Delay(100);
}
