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
#include <string>
#include <iostream>
#include <vector>

//Macro for parsing and allocating XColor colors
#define color(display, colormap, name, var_name)\
    XParseColor(display, colormap, name, &(var_name));\
    XAllocColor(display, colormap, &(var_name));

//Total number of colors
#define TOTAL_COLORS 7

//Enumeration storing each color's position in the X11::Color vector
enum class X11_Col{
    dark_blue = 0,
    purple = 1,
    yellow = 2,
    blue = 3,
    light_blue = 4,
    red = 5,
    gray = 6
};

enum class X11_Col_char{
    dark_blue = 'd',
    purple = 'p',
    yellow = 'y',
    blue = 'b',
    light_blue = 'l',
    red = 'r',
    gray = 'g'
};

class X11{
    public:
        float Width, Height;        //Relative width and height with respect to the screen
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
        void Update(void);    //Updates and draws the X11 Display
};
