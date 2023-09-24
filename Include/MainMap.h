#pragma once

#include "JieEngine/JE.h"
#include "Background.h"
#include "Barrier.h"
#include "Player.h"
#include <time.h>

using namespace JieEngine;

class Main : public JEMap{
public:
    Main(){
        Resource.FixedFPS = 240;
    }
    ~Main(){

    }
private:
    void Init(){
        srand((unsigned)time(NULL));
        this->AddEntity<Background>();
        this->AddEntity<Player>();
        shared_ptr<Barrier> BarrierPoint = nullptr;
        for(int i = 0; i < 4;i++){
            JETransform Transform = {(float)600 + i * 160,(float)(rand() % (500 - 210))};
            if(Transform.Position.Y <= 200){
                Transform.Position.Y += 180;
            }
            BarrierPoint = make_shared<Barrier>(Transform);
            this->AddEntity(BarrierPoint);
        }
    }
    void Update(){
        // Resource._Box2DWorld->DebugDraw();
    }
    void Event(SDL_Event Event){

    }
private:

};