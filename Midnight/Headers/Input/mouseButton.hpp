#ifndef MOUSEBUTTONHPP
#define MOUSEBUTTONHPP


namespace MN{
	using MouseButton = int;
	using PixelType = int;
}

//From glfw mouse button code. Midnight will use the same mouse button code as GLFW

#define MN_MOUSE_BUTTON_1         0
#define MN_MOUSE_BUTTON_2         1
#define MN_MOUSE_BUTTON_3         2
#define MN_MOUSE_BUTTON_4         3
#define MN_MOUSE_BUTTON_5         4
#define MN_MOUSE_BUTTON_6         5
#define MN_MOUSE_BUTTON_7         6
#define MN_MOUSE_BUTTON_8         7
#define MN_MOUSE_BUTTON_LAST      MN_MOUSE_BUTTON_8
#define MN_MOUSE_BUTTON_LEFT      MN_MOUSE_BUTTON_1
#define MN_MOUSE_BUTTON_RIGHT     MN_MOUSE_BUTTON_2
#define MN_MOUSE_BUTTON_MIDDLE    MN_MOUSE_BUTTON_3



#endif