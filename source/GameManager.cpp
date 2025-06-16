#include "GameManager.h"
#include "Entity.h"

void Game::SetInitialValues(void)
{
    X = new X11(X11_WIDTH, X11_HEIGHT, 0, 0, X11_NAME);
    Plyr = new Player(
            X->Att.width/2-BASE_WIDTH/2, X->Att.height - 1.5*BASE_HEIGHT,
            BASE_WIDTH, BASE_HEIGHT);
    Aliens.resize(BASE_ALIEN_NUM);

    for(int i = 0; i < 2; i++){
        for(int j = 0; j<BASE_ALIEN_NUM/2; j++){
            Aliens[i*8 + j] = new Alien(
                2*BASE_WIDTH*j+2*BASE_WIDTH, 2*BASE_HEIGHT*i+BASE_HEIGHT,
                BASE_WIDTH, BASE_HEIGHT);
        }
    }

    Blocks.resize(BASE_BLOCK_BUNCHES*4);
    for(int i = 0; i < BASE_BLOCK_BUNCHES; i++){
        //Top left block in bunch
        Blocks[i*4] = new Block(
                i*4*BASE_WIDTH, X->Att.height-5*BASE_HEIGHT,
                BASE_WIDTH, BASE_HEIGHT
                );
        //Bottom left block in bunch
        Blocks[(i*4)+1] = new Block(
                i*4*BASE_WIDTH, X->Att.height-4*BASE_HEIGHT,
                BASE_WIDTH, BASE_HEIGHT
                );
        //Top right in bunch
        Blocks[(i*4)+2] = new Block(
                i*4*BASE_WIDTH + BASE_WIDTH, X->Att.height-5*BASE_HEIGHT,
                BASE_WIDTH, BASE_HEIGHT
                );
        //Bottom right in bunch
        Blocks[(i*4)+3] = new Block(
                i*4*BASE_WIDTH + BASE_WIDTH, X->Att.height-4*BASE_HEIGHT,
                BASE_WIDTH, BASE_HEIGHT
                );
    }

}

Game::Game(void){
    SetInitialValues();
}

void Game::Reset(void){

    //Deletes all pointers
    delete X;
    delete Plyr;
    for(auto i : Aliens)
        delete i;
    Aliens.clear();
    for(auto i : Blocks)
        delete i;
    Blocks.clear();
    for(auto i : Projectiles)
        delete i;
    Projectiles.clear();

    //Sets initial values again
    SetInitialValues();
}

void Game::Open(void){
    X->Open();
}

void Game::Draw(void){
    for(auto i : Blocks)
        i->Draw(*X);
    for(auto i : Projectiles)
        i->Draw(*X);
    for(auto i : Aliens)
        i->Draw(*X);
    Plyr->Draw(*X);

    X->Update();
}

void Game::Update(void){
    for(auto i : Projectiles){
        i->Update();

        //Check for collision
        i->Collision(*Plyr);
        for(auto j : Blocks)
            i->Collision(*j);
        for(auto j : Aliens)
            i->Collision(*j);
    }
    std::cout<<"Updated projectiles.\n";


    for(auto i: Blocks){
        i->Update();

        //Collision
        for(auto j : Projectiles)
            i->Collision(*j);
    }
    std::cout<<"Updated blocks.\n";


    for(auto i : Aliens){
        i->Update();
        //Check for collision
        for(auto j : Blocks)
            i->Collision(*j);
        for(auto j : Projectiles)
            i->Collision(*j);
    }
    std::cout<<"Updated aliens.\n";

    Plyr->Update();
    std::cout<<"Updated player.\n\n";
}

Game::~Game(void){
    delete X;
    delete Plyr;
    for(auto i : Aliens)
        delete i;
    Aliens.clear();
    for(auto i : Blocks)
        delete i;
    Blocks.clear();
    for(auto i : Projectiles)
        delete i;
}
