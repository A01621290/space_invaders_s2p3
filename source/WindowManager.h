/*
 * This header defines the X11 class and its respective methods,
 * as well as the X11_Col enum to help with color management.
 *
 * The X11 class will help with the program's windowing system's
 * management for things like initializing the display, updating it,
 * and actually showing what is happening in the game.
 *
 * Author: José Rodrigo Cisneros Murillo
 *
 */

#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <string>
#include <iostream>
#include <vector>

//Macro for parsing and allocating XColor colors
#define color(r, g, b, var_name)\
    var_name = RGB(r, g, b);\
    XAllocColor(Disp,Cmap, &(var_name));

//Total number of colors
#define TOTAL_COLORS 11

//Enumeration storing each color's position in the X11::Color vector
enum class X11_Col{
    dark_blue = 0,
    purple = 1,
    yellow = 2,
    blue = 3,
    light_blue = 4,
    red = 5,
    gray = 6,
    black = 7,
    white = 8,
    green = 9,
    orange = 10,
};

//Enumeration for storing each color's letter code in the
//asset files
enum class X11_Col_char{
    dark_blue = 'd',
    purple = 'p',
    yellow = 'y',
    blue = 'b',
    light_blue = 'l',
    red = 'r',
    gray = 'g',
    black = 'n',
    white = 'w',
    green = 'v',
    orange = 'o'
};

enum class X11_Input{
    left,
    right,
    shoot
};

//Function to allocate a valid XColor using RGB
XColor RGB(unsigned short Red, unsigned short Green, unsigned short Blue);

class X11{
    public:
        float Width, Height;        //Relative width and height with respect to the screen
        KeySym Key;
        int XPos, YPos;             //X and Y position of the window in the screen
        Display *Disp;              //Pointer to a display structure used in the X Server windowing system
        int Scr;                    //int representing the screen number
        Window Win;                 //A window structure representing the drawable window part
        std::string Name;           //Name of the window
        XWindowAttributes Att;      //A structure with the window's attributes
        XEvent Event;               //This will store the current events (such as clicking or pressing keys)
        Pixmap Pix;                 //A pixmap to draw stuff into before drawing it into the window
        GC gc;                      //The pixmap's Graphics Context structure
        Colormap Cmap;              //Colormap to store the current window's available colors
        std::vector<XColor> Color;  //A vector with XColor variables for the current colormap
        X11(float Width, float Height, int XPos, int YPos, std::string Name); //Create an X11 window
        ~X11(void); //Free resources used by the window and terminate the object
        void Open(void);    //Open the X11 Window
        void GetInput(void);
        void Update(void);    //Updates and draws the X11 Display
};
