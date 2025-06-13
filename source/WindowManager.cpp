#include "WindowManager.h"

X11::X11(float Width, float Height, int XPos, int YPos, std::string Name)
    :Width(Width), Height(Height), XPos(XPos), YPos(YPos), Name(Name)
{
    Disp = XOpenDisplay(NULL);
    Scr = DefaultScreen(Disp);

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
    XSelectInput(Disp, Win,  ExposureMask | ButtonPress | KeyPressMask);

    //Pix and GC
    Pix = XCreatePixmap(Disp, Win, Att.width, Att.height, DefaultDepth(Disp, Scr));
	XGCValues _val =  {.cap_style = CapButt, .join_style = JoinBevel};
    gc = XCreateGC(Disp, Pix, GCCapStyle | GCJoinStyle, &_val);

    //Colormap
    Cmap = XCreateColormap(Disp, Win, DefaultVisual(Disp, Scr), 0);
    Color.resize(TOTAL_COLORS);
    color(Disp, Cmap, "rebecca purple", Color[X11_Col::dark_purple]);
    color(Disp, Cmap, "purple", Color[X11_Col::purple]);
    color(Disp, Cmap, "yellow", Color[X11_Col::yellow]);
    color(Disp, Cmap, "slate blue", Color[X11_Col::blue]);
    color(Disp, Cmap, "pale turquoise", Color[X11_Col::light_blue]);
    color(Disp, Cmap, "red", Color[X11_Col::red]);
    color(Disp, Cmap, "light slate gray", Color[X11_Col::gray]);
}

void X11::Open(void)
{
    XMapWindow(Disp, Win);
    XFlush(Disp);
    XGetWindowAttributes(Disp, Win, &Att);
}

X11::~X11(void)
{
    XDestroyWindow(Disp, Win);
    XCloseDisplay(Disp);
}
