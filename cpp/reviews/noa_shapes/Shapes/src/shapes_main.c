#include <iostream>

#include "shapes.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "rectangle.hpp"

using namespace ilrd;

// int main()
// {
//     Line l;
//     Circle c;
//     Square s;
//     Rectangle r;

//     l.Draw();
//     c.Draw();
//     s.Draw();
//     r.Draw();
// }

// #include <stdio.h>
// #include <mcheck.h>

#include "glut_utils.h"

Circle center(COLOR_RED, Point(300, 800), 50);
Line l(COLOR_RED, Point(300, 450), 100.0);
Circle c(COLOR_GREEN, Point(300, 450), 10);
Square s(COLOR_YELLOW, Point(300, 450), 80.0);
Rectangle r(COLOR_CYAN, Point(325, 450), Point(375, 350));
int drawCircle = 1;
int xCircle = 250;
int yCircle = 100;
double rCircle = 100;

static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();


int main(int argc, char** argv)
{
    /*--------------------------- mtrace(); */

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop();

    // printf("exit\n");
    std::cout << "exit" << std::endl;

    return 0;
}


static void DrawFunction()
{
    /* printf("Drawing\n"); */


    center.SetPosition(center.GetPosition() + Point(1, 1)).Draw();
    l.SetPosition(l.GetPosition() + Point(1, 1)).Revolve(center.GetPosition(), 0.0174533).Draw();
    c.SetPosition(c.GetPosition() + Point(1, 1)).Revolve(center.GetPosition(), 0.0174533).Draw();
    s.SetPosition(s.GetPosition() + Point(1, 1)).Revolve(center.GetPosition(), 0.0174533).Draw();
    r.SetPosition(r.GetPosition() + Point(1, 1)).Revolve(center.GetPosition(), 0.0174533).Draw();
    
    // l.SetPosition(l.GetPosition() + Point(1, 1));
    // l.Revolve(Point(300, 500), 0.0174533);
    // l.Draw();
    
    // c.Revolve(Point(300, 500), 0.0174533);
    // c.Rotate(0.0174533);
    // c.Draw();
    // // s.Rotate(.1);
    // // s.Revolve(Point(300, 500), 0.0174533);
    // s.Rotate(0.0174533);
    // s.Draw();
    // // r.SetPosition(r.GetPosition() + Point(1, 1));
    // r.Revolve(Point(300, 500), 0.0174533);
    // r.Draw();
    
    // s.Revolve(Point(200, 300), 360);

    /* draw rectangle */
    DrawPolygon(COLOR_MAGENTA, 4, (int)150, (int)400, (int)150, (int)650, (int)300, (int)650, (int)300, (int)400);

    if (drawCircle)
    {
        DrawCircle(COLOR_GREEN, xCircle, yCircle, rCircle);
    }
}


static int KeyboardFunction(unsigned char key, int x, int y)
{
    // printf("Keyboard: %02x,%d,%d\n", key, x, y);
    std::cout << "Keyboard: " << key << x << y << std::endl;

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}


static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


static int MotionFunction(int x, int y)
{
    // printf("Mouse: %d,%d\n", x, y);
    std::cout << "Mouse: " << x << y << std::endl;

    return 0;
}


static int TimerFunction()
{
    xCircle += 1;
    yCircle += 1;

    return 1;  /* draw */
}

