#include "line.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace ilrd;

static void DrawFunction();


int main(int argc, char *argv[])
{
    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    DrawMainLoop();

    return 0;
}

static void DrawFunction()
{
    Line l1(COLOR_BLUE, Point(150, 200), 100);
    l1.Draw();
    l1.SetColor(COLOR_CYAN).Rotate(90).Draw();
    l1.SetColor(COLOR_MAGENTA).Revolve(Point(500, 50), 30).Draw();

    Circle c1(COLOR_RED, Point(400,600), 50);
    c1.Draw();
    c1.SetColor(COLOR_WHITE).Revolve(Point(420, 620), 30).Draw();

    Square s1(COLOR_YELLOW, Point(500,720), 70);
    s1.Draw();
    s1.SetColor(COLOR_GREEN).Rotate(20).Draw();
    s1.SetColor(COLOR_RED).Rotate(40).Draw();
    s1.SetColor(COLOR_BLUE).Revolve(Point(800,600), 0).Draw();
    s1.Revolve(Point(900,700), 20).Draw();
    s1.Revolve(Point(800,800), 40).Draw();

    Rectangle r1(COLOR_MAGENTA, Point(500, 100), Point(620, 250));
    r1.Rotate(20).Draw();
    r1.SetColor(COLOR_WHITE).Rotate(40).Draw();
    r1.SetColor(COLOR_MAGENTA).Rotate(60).Draw();
    r1.SetColor(COLOR_WHITE).Rotate(80).Draw();
}

