#ifndef WINDOW_H
#define WINDOW_H
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

class window {
    public:
        void setCurrentWindow();
        void setNormalWindow();
        virtual void update() = 0;
        virtual int run() = 0;
        window(int x, int y, int width, int height);
        ~window();

    protected:
        WINDOW* _window;
        WINDOW* box_window;
        int colorPair = 2;
        int x;
        int y;
        int width;
        int height;
};
#endif
