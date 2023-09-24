#pragma once

#include "JieEngine/JE.h"

using namespace JieEngine;

class Background : public JEEntity{
public:
    Background(){
        map<string,JEAnimationImage> Image;
        if(JECreateAnimationImage("Background_1",1,Image["Image1"]) == SUCCEED && JECreateAnimationImage("Background_2",1,Image["Image2"]) == SUCCEED){
            this->AddComponent<JEAnimation>({
                Image,"Image1",false
            });
            Image_2_Pos = JERect{
                0,0,600,512
            };
            Image_2_Pos_Temp = JERect{
                600,0,600,512
            };
            Image_2_Show_Pos = Image_2_Pos;
            Temp = Image_2_Show_Pos;
        }
        JECreateAudio("Background",Audio);
        Mix_PlayChannel(Audio.Channel,Audio.Sound,0);
    }
    ~Background(){
        JEDestroyAudio(Audio);
    }
private:
    void Update(){
        auto Image = this->GetComponent<JEAnimation>();
        SDL_Texture * Image_1 = Image.Image["Image1"].Texture;
        SDL_Texture * Image_2 = Image.Image["Image2"].Texture;
        JESize2D Image_2_Size = Image.Image["Image2"].Size;

        SDL_RenderCopy(Resource._Renderer,Image_1,NULL,NULL);
        SDL_RenderCopy(Resource._Renderer,Image_2,&Image_2_Pos,&Image_2_Show_Pos);

        if(Image_2_Pos.x >= Image_2_Size.W - 600){
            SDL_RenderCopy(Resource._Renderer,Image_2,&Temp,&Image_2_Pos_Temp);
            Image_2_Show_Pos.w --;
            Image_2_Pos_Temp.x --;
        }

        Image_2_Pos.x ++;

        if(Image_2_Pos.x == Image_2_Size.W){
            Image_2_Pos.x = 0;
            Image_2_Show_Pos.w = 600;
            Image_2_Pos_Temp.x = 600;
        }

        if(Mix_Playing(Audio.Channel) == 0){
            Mix_PlayChannel(Audio.Channel,Audio.Sound,0);
        }

    }
    void Event(SDL_Event Event){

    }
private:
    JERect Image_2_Pos;
    JERect Image_2_Pos_Temp;
    JERect Image_2_Show_Pos;
    JERect Temp;
    JEAudio Audio;
};