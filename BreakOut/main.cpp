#include "main.h"

int main(){
    GameManager* gm = gm->getInstance();
    gm->LoadFont();
    while (!gm->gameOver){
        gm->Update();
    }
    //delete gm;
    //gm->~GameManager();
    return 0;
}

