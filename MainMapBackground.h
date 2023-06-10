#ifndef MAINMAPBACKGROUND_H
#define MAINMAPBACKGROUND_H

#include "include/MapBackground.h"
#include "include/Mixer.h"

class MainMapBackground : public MapBackground{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "MainMapBackground";
        }
        /*
            构造函数 参数为 WindowSurface
        */
        MainMapBackground(SDL_Surface * WindowSurface){
            this->Image_1 = Decrypt::DecryptImage("./Resource/Background_1.png.JieEngine");
            this->Image_2 = Decrypt::DecryptImage("./Resource/Background_2.png.JieEngine");
            this->Background_Sound = new Mixer("./Resource/Background.mp3.JieEngine",1);
            SetRectInfo(&Image_2_Pos,0,0,WINDOW_W,WINDOW_H);
            SetRectInfo(&Image_2_Pos_Temp,WINDOW_W,0,WINDOW_W,WINDOW_H);
            this->WindowSurface = WindowSurface;
            this->Background_Sound->Play(10000);
        }
        /*
            每帧更新函数
        */
        void Update(){
            SDL_BlitSurface(Image_1,NULL,WindowSurface,NULL);
            SDL_BlitSurface(Image_2,&Image_2_Pos,WindowSurface,NULL);
            if(Image_2_Pos.x >= Image_2->w - WINDOW_W){
                SDL_BlitSurface(Image_2,NULL,WindowSurface,&Image_2_Pos_Temp);
                Image_2_Pos_Temp.x --;
            }
            Image_2_Pos.x ++;
            if(Image_2_Pos.x == Image_2->w){
                Image_2_Pos.x = 0;
                Image_2_Pos_Temp.x = WINDOW_W;
            }
        }
        /*
            接收事件 除了退出事件 其它事件都接收的到
        */
        void WindowEvent(SDL_Event Event){
            
        }
        /*
            释放资源函数
        */
        void Free(){
            SDL_FreeSurface(this->Image_1);
            SDL_FreeSurface(this->Image_2);
            Background_Sound->Free();
        }
    private:
        SDL_Surface * Image_1;
        SDL_Surface * Image_2;
        Mixer * Background_Sound;
        SDL_Rect Image_2_Pos;
        SDL_Rect Image_2_Pos_Temp;
};

#endif