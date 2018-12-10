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
        window(int x, int y, int width, int height);
        ~window();

    protected:
        void draw_border();
        void refresh();
        WINDOW* _window;
        WINDOW* box_window;
        int colorPair = 2;
        int x;
        int y;
        int width;
        int height;
};
#endif
