#ifndef MAINMAPSTRUCT_H
#define MAINMAPSTRUCT_H

#include "include/MapStruct.h"
#include "include/Mixer.h"
#include "Player.h"
#include "Barrier.h"
#include <time.h>

class MainMapStruct : public MapStruct{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "MainMapStruct";
        }
        /*
            构造函数 参数为 WindowSurface
        */
        MainMapStruct(SDL_Surface * WindowSurface){
            srand((unsigned)time(NULL));
            this->WindowSurface = WindowSurface;
            this->ObjectPlayer = new Player("./Resource/Player.png.JieEngine",4,6,{50,50},WindowSurface);
            this->Move = new Mixer("./Resource/Move.wav.JieEngine",2);
            this->Die = new Mixer("./Resource/Die.mp3.JieEngine",3);
            this->MapBarrierArray = new Barrier[BarrierCount];
            for(short i = 0; i < BarrierCount; i++){
                MapBarrierArray[i].SetData("./Resource/Barrier.png.JieEngine",{WINDOW_W + i * 160,(rand() % (WINDOW_H - 260)) + 60},WindowSurface);
            }
        }
        /*
            每帧更新函数
        */
        void Update(){
            for(short i = 0; i < BarrierCount; i++){
                MapBarrierArray[i].Update();
                ObjectPlayer->IsCollideDetect(&MapBarrierArray[i]);
                ObjectPlayer->IsCollideDetect(MapBarrierArray[i].GoLd);
            }
            ObjectPlayer->Update();
            if(ObjectPlayer->Position.x <= 1 || ObjectPlayer->Position.y + ObjectPlayer->Size.y >= WINDOW_H - 1){
                this->Die->Play();
                SDL_Delay(2000);
                this->Free();
                exit(0);
            }
        }
        /*
            接收事件 除了退出事件 其它事件都接收的到
        */
        void WindowEvent(SDL_Event Event){
            switch(Event.key.keysym.sym){
                case SDLK_w:{
                    ObjectPlayer->Jump();
                    this->Move->Play();
                    break;
                }
                case SDLK_a:{
                    ObjectPlayer->MoveLeft();
                    this->Move->Play();
                    break;
                }
                case SDLK_d:{
                    ObjectPlayer->MoveRight();
                    this->Move->Play();
                    break;
                }
                case SDLK_s:{
                    ObjectPlayer->MoveDown();
                    this->Move->Play();
                    break;
                }
            }
        }
        /*
            释放资源函数
        */
        void Free(){
            ObjectPlayer->Free();
            Move->Free();
            Die->Free();
            for(short i = 0; i < BarrierCount; i++){
                MapBarrierArray[i].Free();
            }
        }
    private:
        Player * ObjectPlayer;
        Barrier * MapBarrierArray;
        Mixer * Move;
        Mixer * Die;
        short BarrierCount = 4;
};

#endif