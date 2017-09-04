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
        void update();
        int run();
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
        string str;
        vector<string> history;
};
#endif
