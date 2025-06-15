//This is the implementation file of the entity class and the
//getAsset function
#include "Entity.h"

//Read asset file into string
std::string GetAsset(const std::string file_name){
    std::ifstream file(file_name);
    std::string read;
    std::string asset;
    while(std::getline(file, read)){
        asset += read + '\n';
    }
    file.close();

    return asset;
};

//Constructor
Entity::Entity(
                float XPos, float YPos,
                unsigned int Width, unsigned int Height,
                short Hp,
                unsigned int Anim_Frames,
                std::string FirstAssetName,
                Ent_type Type
                )
    :
        XPos(XPos), YPos(YPos),
        Width(Width), Height(Height), 
        Hp(Hp),
        Anim_Frames(Anim_Frames), FirstAssetName(FirstAssetName),
        Type(Type)
{
    Alive = true;//All entities start of alive

    //Read asset_n into the Assets vector
    Assets.resize(Anim_Frames);
    for(int i = 1; i <= Anim_Frames; i++){
        Assets[i] = GetAsset(FirstAssetName + '_' + std::to_string(i));
    }
    std::cout << "New entity with following parameters.\n";
    this->Print();
};


//Give information about entity's position
float Entity::Top(void) const{
    return YPos;
};
float Entity::Bottom(void) const{
    return YPos + Height;
};
float Entity::Left(void) const{
    return XPos;
};
float Entity::Right(void) const{
    return XPos + Width;
};


//Draw each entity
void Entity::Draw(const X11& x11, unsigned int Frame){
    float currentY = YPos;
    float currentX = XPos;
    bool nl = false;

    //For each char in the current frame of assets it will paint
    //a square
    for(char c : Assets[Frame]){
        switch (c) {
            case (static_cast<char>(X11_Col_char::dark_blue)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::dark_blue)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::purple)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::purple)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::yellow)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::yellow)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::blue)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::blue)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::light_blue)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::light_blue)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::red)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::red)].pixel);
                    break;
                }
            case (static_cast<char>(X11_Col_char::gray)):
                {
                    XSetForeground(x11.Disp, x11.gc, x11.Color[static_cast<int>(X11_Col::gray)].pixel);
                    break;
                }
            case '\n':
                {
                    //Will add one to the height (going lowe)
                    currentY += Height/Y_PIXEL_NUMBER;

                    //Will reset the x position to the original one
                    //(goes left)
                    currentX = XPos;

                    //Newline is set to true
                    nl = true;
                    break;
                }
        }

        //If last read character isn't a newline, it will draw 
        //a square. If not it skips to the next character
        if(!nl){
            //Draws a new pixel at the given point
            XFillRectangle(x11.Disp, x11.Pix, x11.gc, currentX, currentY, Width/X_PIXEL_NUMBER, Height/Y_PIXEL_NUMBER);
            currentX += Width/X_PIXEL_NUMBER;
        }
        nl = false;
    }
};


//Operator overloading to compare entities' collision
bool Entity::operator& (const Entity& b){
    /*Left side of A is greater or equal to right side of B
     * OR
     * right side of A is lesser or equal to left side of B*/
    bool XInRange = this->Left() >= b.Right() || this->Right() <= b.Left();

    /*Bottom of object A is greater than top of B
     * OR
     * Top of A is lesser than bottom of B*/
    bool YInRange = this->Bottom() >= b.Top() || this->Top() <= b.Bottom();

    return XInRange && YInRange;
};
