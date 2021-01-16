#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

// 全域變數
int width = 800;
int height = 600;
SDL_Window* pWindow;
SDL_Renderer* pRenderer;

// 初始化 SDL
bool initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        pWindow = SDL_CreateWindow("SDL2",               // 視窗標題
                                 SDL_WINDOWPOS_UNDEFINED,    // X 座標
                                 SDL_WINDOWPOS_UNDEFINED,    // Y 座標
                                 width, height,                                        // 寬、高
                                 SDL_WINDOW_SHOWN);              // 寬、高、其他設定旗標
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
    cout << "SDL init failed." << endl;
    return false;
}

// 初始化 SDL_Image
bool initSDL_Image()
{
    int flags = IMG_INIT_PNG;  // 我們要使用 png 圖檔
    int initted = IMG_Init(flags);
    if( (initted&flags) != flags) {
        cout << "SDL_image init failed." << endl;
        return false;
    }
    return true;
}

void render_file(string filename)
{
    // 繪製圖片
    SDL_Surface* pTempSurface = IMG_Load(filename.c_str());   // 將影像檔讀入 surface
    // 將 sruface 的資料轉成更有效率的 texture
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);  // 轉成 texture 後，就不需要 surface

    SDL_Rect srcRect;    // 來源矩形區塊(left, top, width, height)
    SDL_Rect destRect;  // 目的矩形區塊(left, top, width, height)

    // 使用 SDL_QueryTexture 取得圖片的寬、高，並分別填入 destRect.w 和 destRect.h
    SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

    srcRect.x =  srcRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    destRect.x =  destRect.y = 0;

    // 從來源複製指定的一個矩形區塊，到目的地指定的一個矩形區塊(含縮放)
    SDL_RenderCopyEx(pRenderer, pTexture,       // 來源為 pTexture, 目的為 pRenderer
                                       &srcRect, &destRect,       // 來源矩形, 目的矩形
                                        0, 0,                                   // 旋轉角度, 旋轉中心點
                                        SDL_FLIP_NONE);          // 翻轉(flip)方式
    SDL_DestroyTexture(pTexture);

}

// 更新遊戲畫面
void render()
{
    // 在背景進行繪製
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);  // R, G, B, A
    SDL_RenderClear(pRenderer);

    render_file("background.png");

    SDL_RenderPresent(pRenderer);
}

int main(int argc, char *argv[])
{
    if(initSDL()==false || initSDL_Image()==false)
        return -1;

    //主迴圈

    SDL_Event e;
    bool quit = false;

    while(!quit) {
        // 事件處理迴圈
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT)    // 按下 [X] 關閉視窗
                quit = true;
            if (e.type == SDL_KEYDOWN){     // 鍵盤按鍵被按下
                switch (e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }

        render();    // 更新遊戲畫面
    }

    // 結束
    IMG_Quit();    // 清除 SDL_image 相關資源
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return 0;
}