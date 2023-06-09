#ifndef MAINBACKGROUND_H
#define MAINBACKGROUND_H

#include "JieEngine/MapBackground.h"
#include "JieEngine/Mixer.h"

class MainBackground : MapBackground{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "MainBackground";
        }
        /*
            构造函数
        */
        MainBackground(SDL_Surface * WindowSurface){
            this->WindowSurface = WindowSurface;
            this->Image_1 = Decrypt::DecryptImage("./Resource/Background_1.png.JieEngine");
            this->Image_2 = Decrypt::DecryptImage("./Resource/Background_2.png.JieEngine");
            this->Background_Sound = new Mixer("./Resource/Background.mp3.JieEngine",1);
            SetRectInfo(&Image_2_Pos,0,0,WINDOW_W,WINDOW_H);
            SetRectInfo(&Image_2_Pos_Temp,WINDOW_W,0,WINDOW_W,WINDOW_H);
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