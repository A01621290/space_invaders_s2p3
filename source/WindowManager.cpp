/*
 * This file is the implementation
 * file of the WindowManager.h header.
 */
#include "WindowManager.h"

XColor RGB(unsigned short Red, unsigned short Green, unsigned short Blue){
    return (XColor) {
        .red = static_cast<unsigned short>(Red * 257),
        .green = static_cast<unsigned short>(Green * 257),
        .blue = static_cast<unsigned short>(Blue * 257),
        .flags = DoRed | DoGreen | DoBlue,
    };
}

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
    color(18, 0, 20, Color[static_cast<int>(X11_Col::dark_blue)]);
    color(163, 9, 235, Color[static_cast<int>(X11_Col::purple)]);
    color(240, 198, 29, Color[static_cast<int>(X11_Col::yellow)]);
    color(0, 0, 255, Color[static_cast<int>(X11_Col::blue)]);
    color(0, 200, 255, Color[static_cast<int>(X11_Col::light_blue)]);
    color(255, 0, 0, Color[static_cast<int>(X11_Col::red)]);
    color(176, 176, 176, Color[static_cast<int>(X11_Col::gray)]);
    color(0, 0, 0, Color[static_cast<int>(X11_Col::black)]);
    color(255, 255, 255, Color[static_cast<int>(X11_Col::white)]);
    color(255,0,0, Color[static_cast<int>(X11_Col::green)]);
    color(255, 153, 0, Color[static_cast<int>(X11_Col::orange)]);
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

void X11::GetInput(void){
    if(XPending(Disp) > 0){
        XNextEvent(Disp, &Event);
    }
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
