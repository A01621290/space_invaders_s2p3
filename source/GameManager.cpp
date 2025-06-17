#include "GameManager.h"
#include "Entity.h"

void Game::SetInitialValues(void)
{
    Plyr = new Player(
            X->Att.width/2-BASE_WIDTH/2, X->Att.height - 1.5*BASE_HEIGHT,
            BASE_WIDTH, BASE_HEIGHT);
    Aliens.resize(BASE_ALIEN_NUM);

    for(int i = 0; i < BASE_ALIEN_NUM/8; i++){
        for(int j = 0; j< 8; j++){
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
    X = new X11(X11_WIDTH, X11_HEIGHT, 0, 0, X11_NAME);
    Open();
    SetInitialValues();
}

void Game::Reset(void){

    //Deletes all pointers
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


    for(int i = 0; i < Blocks.size();i++){
        Blocks[i]->Update();

        //Collision
        for(auto j : Projectiles){
            Blocks[i]->Collision(*j);
        }
        if(Blocks[i]->Hp <= 0){
            delete Blocks[i];
            Blocks.erase(Blocks.begin() + i);
            i--;
        }
    }


    for(int i = 0; i < Aliens.size(); i++){
        Aliens[i]->Update();

        //Have a random chance to shoot
        if(std::rand() % (BASE_ALIEN_NUM * ALIEN_WAIT_TIME) == 1 && Aliens[i]->CanShoot){
            Projectiles.push_back(
                    Aliens[i]->Shoot(
                        Plyr->XPos+Plyr->Width/2,
                        Plyr->YPos+Plyr->Height/2)
                    );
        }
        //Check for collision
        for(auto j : Blocks)
            Aliens[i]->Collision(*j);
        for(auto j : Projectiles)
            Aliens[i]->Collision(*j);

        if(Aliens[i]->Hp <= 0){
            delete Aliens[i];
            Aliens.erase(Aliens.begin() + i);
            i--;
        }
    }

    for(auto i : Projectiles)
        Plyr->Collision(*i);
    //Will get input and act accordingly
    X->GetInput();
    switch(X->Key){
        default:
            Plyr->Moving = false;
            Plyr->setXSpeed(0);
            break;
        case (XK_Left):
            {
                Plyr->setXSpeed(-BASE_PLYR_SPEED);
                Plyr->Moving = true;
                break;
            }
        case (XK_Right):
            {
                Plyr->setXSpeed(BASE_PLYR_SPEED);
                Plyr->Moving = true;
                break;
            }
        case (XK_space):
            {
                if(!Plyr->CanShoot){
                    break;
                }
                else{
                    Projectiles.push_back(Plyr->Shoot());
                }
                break;
            }
        case (XK_Escape):
            {
                std::exit(1);
                break;
            }
    }
    Plyr->Update();

    for(int i = 0; i < Projectiles.size();){
        Projectiles[i]->Update();

        //Check for collision
        Projectiles[i]->Collision(*Plyr);
        for(auto j : Blocks)
            Projectiles[i]->Collision(*j);
        for(auto j : Aliens)
            Projectiles[i]->Collision(*j);
        if(Projectiles[i]->Hp < 0){
            delete Projectiles[i];
            Projectiles.erase(Projectiles.begin() + i);
        }
        else{
            i++;
        }
    }
}

void Game::Run(void){
    Open();
    for(;;){
        Update();
        Draw();
        if(Plyr->Hp <= 0){
            Reset();
        }
        if(Aliens.size() == 0){
            std::cout << "You win!\n";
            std::exit(1);
        }
    }
};

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

