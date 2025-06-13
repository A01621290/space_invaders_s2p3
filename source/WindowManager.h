#ifndef WIN_H
#define WIN_H
#include <X11/Xlib.h>
#include <iostream>
#include <vector>

#define color(display, colormap, name, var_name)\
    XParseColor(display, colormap, name, &(var_name));\
    XAllocColor(display, colormap, &(var_name));
#define TOTAL_COLORS 7

enum X11_Col{
    dark_purple = 0,
    purple = 1,
    yellow = 2,
    blue = 3,
    light_blue = 4,
    red = 5,
    gray = 6
};

class X11{
    private:
        float Width, Height;
        int XPos, YPos;
        Display *Disp;
        int Scr;
        Window Win;
        std::string Name;
        XWindowAttributes Att;
        XEvent Event;
        Pixmap Pix;
        GC gc;
        Colormap Cmap;
        std::vector<XColor> Color;
    public:
        X11(float Width, float Height, int XPos, int YPos, std::string Name);
        ~X11(void);
        void Open(void);
        void Draw(void);
        void Update(void);
};
#endif
