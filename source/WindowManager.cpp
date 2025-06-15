/*
 * This file is the implementation
 * file of the WindowManager.h header.
 */

#include "WindowManager.h"
X11::X11(float Width, float Height, int XPos, int YPos, std::string Name)
    :Width(Width), Height(Height), XPos(XPos), YPos(YPos), Name(Name)
{
    //Display and Screen
    Disp = XOpenDisplay(NULL);
    Scr = DefaultScreen(Disp);

    //Window and window name
    Win = XCreateSimpleWindow(
            Disp, DefaultRootWindow(Disp),
            XPos,YPos,
            DisplayWidth(Disp, Scr) * Width,
            DisplayHeight(Disp,Scr) * Height,
            1,
            BlackPixel(Disp, Scr),
            WhitePixel(Disp, Scr)
            );
    XStoreName(Disp, Win, Name.c_str());
    XGetWindowAttributes(Disp, Win, &Att);

    //Window Input
    XSelectInput(Disp, Win,  ExposureMask | ButtonPress | KeyPressMask);

    //GC and Pixmap
    Pix = XCreatePixmap(Disp, Win, Att.width, Att.height, DefaultDepth(Disp, Scr));
	XGCValues _val =  {.cap_style = CapButt, .join_style = JoinBevel};
    gc = XCreateGC(Disp, Pix, GCCapStyle | GCJoinStyle, &_val);

    //Color allocating and parsing
    Cmap = XCreateColormap(Disp, Win, DefaultVisual(Disp, Scr), 0);
    Color.resize(TOTAL_COLORS);
    color(Disp, Cmap, "midnightBlue", Color[static_cast<int>(X11_Col::dark_blue)]);
    color(Disp, Cmap, "purple", Color[static_cast<int>(X11_Col::purple)]);
    color(Disp, Cmap, "yellow", Color[static_cast<int>(X11_Col::yellow)]);
    color(Disp, Cmap, "SlateBlue", Color[static_cast<int>(X11_Col::blue)]);
    color(Disp, Cmap, "PaleTurquoise", Color[static_cast<int>(X11_Col::light_blue)]);
    color(Disp, Cmap, "red", Color[static_cast<int>(X11_Col::red)]);
    color(Disp, Cmap, "LightSlateGray", Color[static_cast<int>(X11_Col::gray)]);
}


void X11::Update(void)
{
    //Get Window Attributes
    XGetWindowAttributes(Disp, Win, &Att);

    //Draw pixmap into window
    XCopyArea(Disp, Pix, Win, gc, 0, 0, Att.width, Att.height, 0, 0);

    //Clear Pixmap
    XSetForeground(Disp, gc, Color[static_cast<int>(X11_Col::dark_blue)].pixel);
    XFillRectangle(Disp, Pix, gc, 0, 0, Att.width, Att.height);
    XFlush(Disp);
}


void X11::Open(void)
{
    XSetWindowBackground(Disp, Win, Color[static_cast<int>(X11_Col::dark_blue)].pixel);
    XMapWindow(Disp, Win);
}

X11::~X11(void)
{
    XDestroyWindow(Disp, Win);
    XCloseDisplay(Disp);
}
